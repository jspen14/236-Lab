//
//  Interpreter.cpp
//  LAB3
//
//  Created by Josh Spencer on 3/12/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Interpreter.h"


void Interpreter::interpret(DatalogProgram dp){
    Database database;
    createRelations(dp.getSchemeList(), database);
    populateRelationsFromFacts(dp.getFactList(), database);
    populateRelationsFromRules(dp.getRuleList(), database);
    evaluateQueries(dp.getQueryList(), database);
    cout << "";
}

void Interpreter::createRelations(vector<Predicate> schemes, Database &database){
    for (unsigned int i = 0; i<schemes.size(); i++){
        Relation relation;
        vector<string> parametersInScheme;
        Scheme colHeader;
        
        relation.setName(schemes[i].getName());
        
        parametersInScheme = schemes[i].getParamList();
        for(unsigned int j = 0; j<parametersInScheme.size(); j++){
            colHeader.push_back(parametersInScheme[j]);
        }
        
        relation.addColHeader(colHeader);
        
        database.addRelation(relation.getName(), relation);
    }
}

void Interpreter::populateRelationsFromFacts(vector<Predicate> facts, Database &database){
    //forEach fact in Facts
        //Find the matching relation by matching facts name and relation name from database
        //Once relation found, add a tuple by iterating through each
    // map<string,Relation> relations;
    // relations = database.getRelationsMap();
    
    for (unsigned int i = 0; i<facts.size(); i++){
        Tuple tuple;
        vector<string> parametersInFact;
        
        parametersInFact = facts[i].getParamList();
        
        for(unsigned int j = 0; j<parametersInFact.size(); j++){
            tuple.push_back(parametersInFact[j]);
        }
        
        // duplicate check tuple
       
        database.getRelationsMap()[facts[i].getName()].addTuple(tuple);
    }
}

void Interpreter::populateRelationsFromRules(vector<Rule> rules, Database &database){
    int tupleCountBefore = 0;
    int tupleCountAfter = 0;
    int fixedPointPasses = 0;
    
    cout << "Rule Evaluation" << endl;
    
    do{
        tupleCountBefore = database.getTupleCount();
        
        for(unsigned int i = 0; i < rules.size(); i++){
            evaluateRule(rules[i], database);
        }
        
        tupleCountAfter = database.getTupleCount();
        fixedPointPasses++;
    } while (tupleCountAfter-tupleCountBefore != 0);
    
    cout << endl << "Schemes populated after " << fixedPointPasses << " passes through the Rules." << endl << endl;
}

void Interpreter::evaluateRule(Rule &rule, Database &database){
    vector<Relation> relationVec;
    vector<Predicate> predicateVector = rule.getPredList();
    Relation formedRelation; // this is going to be the relation that everything is added to
    Scheme formedRelationCH;
    vector<string> formedRelationPL = predicateVector[0].getParamList();
    
    //Set up formedRelation
    formedRelation.setName(predicateVector[0].getName());
    
    for (unsigned int j = 0; j < formedRelationPL.size(); j++){
        formedRelationCH.push_back(formedRelationPL[j]);
    }
    
    formedRelation.addColHeader(formedRelationCH);
    
    formedRelation = evaluateSingleQuery(formedRelationPL,database.getRelationsMap()[formedRelation.getName()]);
    
    for (unsigned int j = 1; j < predicateVector.size(); j++){
        Relation tempRelation;
        Scheme tempRelationCH;
        vector<string> tempRelationPL = predicateVector[j].getParamList();
        
        tempRelation.setName(predicateVector[j].getName());
        
        for (unsigned int j = 0; j < formedRelationPL.size(); j++){
            tempRelationCH.push_back(formedRelationPL[j]);
        }
        
        tempRelation.addColHeader(tempRelationCH);
        
        tempRelation = evaluateSingleQuery(tempRelationPL,database.getRelationsMap()[tempRelation.getName()]);
        
        // make as many of these as possible not copy things over
        formedRelation=formedRelation.join(tempRelation);
    }
        formedRelation.setName(rule.getHeadName());
        evaluateRulesProject(rule.getHeadParams(), formedRelation);
        formedRelation=evaluateRulesRename(formedRelation, database);
        evaluateRulesUnion(formedRelation, database, rule);
//        cout << "in predicateVector forLoop" << endl;
    
}



void Interpreter::evaluateRulesProject(vector<string> const &ruleParams, Relation &formedRelation){
    unsigned long colHeaderSize = formedRelation.getColHeader().size();
    vector<int> indicesToProject;
    
    for (unsigned int i = 0; i < ruleParams.size(); i++){
        for (unsigned int j = 0; j < colHeaderSize; j++){
            if (ruleParams[i] == formedRelation.getColHeader()[j]){
                indicesToProject.push_back(j);
            }
        }
    }
    
   formedRelation.project(indicesToProject);
}

Relation Interpreter::evaluateRulesRename(Relation &formedRelation, Database &database){
    // set params to match values in Scheme in Database
    Scheme newColHeader;
    newColHeader = database.getRelationsMap()[formedRelation.getName()].getColHeader();
    
    formedRelation.addColHeader(newColHeader);
  
    return formedRelation; //
}

void Interpreter::evaluateRulesUnion(Relation &formedRelation, Database &database, Rule &rule){
    set<Tuple> rows = formedRelation.getRows();
    
    printRulesHeader(rule);
    
    for (auto row:rows){
        if (!tupleFoundinDB(row, formedRelation, database)){
            database.getRelationsMap()[formedRelation.getName()].addTuple(row);
            printRulesRow(formedRelation, row);
        }
    }
}

void Interpreter::printRulesRow(Relation &formedRelation, Tuple &row){
    cout << "  ";
    for (unsigned int i = 0; i < row.size(); i++){
        cout << formedRelation.getColHeader()[i] << "=" << row[i];
        if (i < row.size()-1){
            cout << ", ";
        }
    }
    cout << endl;
}


bool Interpreter::tupleFoundinDB(Tuple &rowIN, Relation &formedRelation, Database &database){
    cout << "";
    
    for (auto rowDB:database.getRelationsMap()[formedRelation.getName()].getRows()){
        if (rowIN == rowDB) {
            return true;
        }
    }
    
    return false;
}

void Interpreter::printRulesHeader(Rule &rule){
    cout << rule.getHeadName() << "(";
    for (unsigned int i = 0; i < rule.getHeadParams().size(); i++){
        cout << rule.getHeadParams()[i];
        if (i < rule.getHeadParams().size()-1){
            cout << ",";
        }
    }
    cout << ") :- ";
    for (unsigned int i = 0; i < rule.getPredList().size(); i++){
        cout << rule.getPredList()[i].getName()<< "(";
        for (unsigned  int j = 0; j < rule.getPredList()[i].getParamList().size(); j++){
            cout << rule.getPredList()[i].getParamList()[j];
            if (j < rule.getPredList()[i].getParamList().size()-1){
                cout << ",";
            }
        }
        cout << ")";
        if ( i < rule.getPredList().size()-1){
            cout << ",";
        }
    }
    cout << endl;
}

void Interpreter::evaluateQueries(vector<Predicate> queries, Database database){
    cout << "Query Evaluation" << endl;
    for (unsigned int i = 0; i < queries.size(); i++){
        Relation editedRelation;
        vector<string> queryParams;
        set<Tuple> rows;
        
        editedRelation = evaluateSingleQuery(queries[i].getParamList(), database.getRelationsMap()[queries[i].getName()]);
        
        printEditedRelation(queries[i], editedRelation);
    }
}

Relation Interpreter::evaluateSingleQuery(vector<string> queryParams, Relation editedRelation){
    // Possibly change this to be done all be reference
    for (unsigned int j = 0; j < queryParams.size(); j++){
        if (queryParams[j].at(0) == '\''){
            editedRelation = editedRelation.selectIndexValue(j, queryParams[j]);
        }
        else{
            for(unsigned int k = j+1; k < queryParams.size(); k++){
                if (queryParams[j] == queryParams[k]){
                    editedRelation = editedRelation.selectIndexIndex(k, j);
                }
            }
        }
    }
    
    editedRelation = evaluateQueriesProject(queryParams, editedRelation);
    editedRelation = evaluateQueriesRename(queryParams, editedRelation);
    
    return editedRelation;
}

Relation Interpreter::evaluateQueriesProject(vector<string> queryParams, Relation editedRelation){
    // check for duplicates here
    vector<int> indicesOfVariables;
    vector<string> variablesVector;
    
    for (unsigned int i = 0; i<queryParams.size(); i++){
        
        if(queryParams[i].at(0) != '\'' && !found(variablesVector, queryParams[i])){
            variablesVector.push_back(queryParams[i]);
            indicesOfVariables.push_back(i);
        }
    }
    
    return editedRelation.project(indicesOfVariables);
}

Relation Interpreter::evaluateQueriesRename(vector<string> queryParams, Relation editedRelation){
    vector<string> variableQueryParams;
    
    for (unsigned int i = 0; i<queryParams.size(); i++){
        if(queryParams[i].at(0) != '\''){
            variableQueryParams.push_back(queryParams[i]);
        }
    }
    
    
    return editedRelation.rename(variableQueryParams);
}

void Interpreter::printEditedRelation(Predicate query, Relation editedRelation){
    cout << query.getName() << "(";
    vector<string> queryParams = query.getParamList();
    set<Tuple> relationRows;
    

    for (unsigned int i = 0; i < queryParams.size(); i++){
        cout << queryParams[i];
        
        if (i != queryParams.size()-1){
            cout << ",";
        }
    }
    
    cout << ")? ";
        
    if (editedRelation.getRows().size() == 0) {
        cout << "No" << endl;
    }
    else{
        cout << "Yes(" << editedRelation.getRows().size() << ")" << endl;
        if (!allConstants(queryParams)){
            printEditedRelation2(editedRelation, queryParams, relationRows);
        }
    }
}

void Interpreter::printEditedRelation2(Relation editedRelation, vector<string> queryParams, set<Tuple> relationRows){
    unsigned int k = 0;
    set<Tuple> rows = editedRelation.getRows();
    
    for (auto row:rows){
        
        k = 0;
        cout << " ";
        for (unsigned int j = 0; k < row.size(); j++){
            if (queryParams[j].at(0) != '\''){
                if (row[0].at(0) != '\''){
                    break;
                }
                if ((j != 0 && queryParams[0] == queryParams[j])){
                    
                }
                else{
                    cout << " " << queryParams[j] << "=" << row[k];
                    k++;
                    if (k < row.size()){
                        cout << ",";
                    }
                }
            }
        }
        cout << endl;
    }
}

bool Interpreter::allConstants(vector<string> queryParams){
    bool allConst = true;
    
    for (unsigned int i = 0; i < queryParams.size(); i++){
        if (queryParams[i].at(0) != '\''){
            allConst = false;
        }
    }
    
    return allConst;
}

bool Interpreter::found(vector<string> variableQueryParams, string possibleInput){
    for (unsigned int i=0; i < variableQueryParams.size(); i++){
        if (variableQueryParams[i] == possibleInput){
            return true;
        }
    }
    
    return false;
}



