// Interpreter
/*
 - Have access to all schemes, facts, and queries
 - Make a Relation forEach Scheme
 - Make a Tuple forEach Fact
 - Evaluate each Query
 */

#pragma once
#include <string>
#include <vector>
#include "Tuple.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Relation.h"
#include "Scheme.h"
#include "Rule.h"
#include <map>
#include <iostream>
#include <set>

using namespace std;

class Interpreter{
public:
    void interpret(DatalogProgram dp);
    
    void createRelations(vector<Predicate> schemes, Database &database);
    
    void populateRelationsFromFacts(vector<Predicate> facts, Database &database);
    
    void populateRelationsFromRules(vector<Rule> rules, Database &database);
    
    void evaluateRule(Rule &rule, Database &database);
    
    void evaluateRulesProject(vector<string> const &ruleParams, Relation& formedRelation);
    
    Relation evaluateRulesRename(Relation& formedRelation, Database& database);
    
    void evaluateRulesUnion(Relation &formedRelation, Database &database, Rule &rule);
    
    void printRulesRow(Relation &formedRelation, Tuple &row);
    
    bool tupleFoundinDB(Tuple &row, Relation &formedRelation, Database &database);
    
    void printRulesHeader(Rule &rule);
    
    void evaluateQueries(vector<Predicate> queries, Database database);
    
    Relation evaluateSingleQuery(vector<string> queryParams, Relation editedRelation);
    
    Relation evaluateQueriesProject(vector<string> queryParams, Relation editedRelation);
    
    //void evaluateSingleQuery(Predicate query, Database database);
    Relation evaluateQueriesRename(vector<string> queryParams, Relation editedRelation);
    
    void printEditedRelation(Predicate query, Relation editedRelation);
    
    void printEditedRelation2(Relation editedRelation, vector<string> queryParams, set<Tuple> relationRows);

    bool allConstants(vector<string> queryParams);
    
    bool found(vector<string> variableQueryParams, string possibleInput);
    
    Relation sortRelation(Relation relationToSort);
    
    
private:
    
};
