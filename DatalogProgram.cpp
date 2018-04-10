//
//  DatalogProgram.cpp
//  Parser
//
//  Created by Josh Spencer on 1/31/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "DatalogProgram.h"

void DatalogProgram::addSchemes(vector<Predicate> schemes){
    schemeList = schemes;
}

int DatalogProgram::getSchemesSize(){
    return schemeList.size();
}

void DatalogProgram::addFacts(vector<Predicate> facts){
    vector <string> tempPredList;
    factList = facts;

    for (unsigned int i = 0; i < factList.size(); i++){
        tempPredList = factList[i].getParamList();

        for (unsigned int j = 0; j < tempPredList.size(); j++){
            domain.insert(tempPredList[j]);
        }
    }
}

void DatalogProgram::addRules(vector<Rule> rules){
    ruleList = rules;
}



void DatalogProgram::addQueries(vector<Predicate> queries){
    queryList = queries;
}

int DatalogProgram::getQueriesSize(){
    return queryList.size();
}

//-------------------------------------------------------------//
void DatalogProgram::schemeToString(){
    vector <string> tempPredList;


    cout << "Schemes(" << schemeList.size() << "):" << endl;
    for (unsigned int i = 0; i < schemeList.size(); i++){
        cout << "  " << schemeList[i].getName() << "(";
        tempPredList = schemeList[i].getParamList();

        cout << tempPredList[0];

        for (unsigned int j = 1; j < tempPredList.size(); j++){
            cout << "," << tempPredList[j];
        }

        cout << ")" << endl;

    }
}

void DatalogProgram::factToString(){
    vector <string> tempPredList;


    cout << "Facts(" << factList.size() << "):" << endl;
    for (unsigned int i = 0; i < factList.size(); i++){
        cout << "  " << factList[i].getName() << "(";
        tempPredList = factList[i].getParamList();

        cout << tempPredList[0];

        for (unsigned int i = 1; i < tempPredList.size(); i++){
            cout << "," << tempPredList[i];
        }

        cout << ")." << endl;

    }
}

void DatalogProgram::ruleToString(){
    vector <string> tempPredList;
    vector <Predicate> childPreds;
    vector <string> childPredsList;

    cout << "Rules(" << ruleList.size() << "):" << endl;
    if (ruleList.size() != 0){
        for (unsigned int i = 0; i < ruleList.size(); i++){
            cout << "  " << ruleList[i].getHeadName() << "(";
            tempPredList = ruleList[i].getHeadParams();

            cout << tempPredList[0];

            for (unsigned int i = 1; i < tempPredList.size(); i++){
                cout << "," << tempPredList[i];
            }

            cout << ") :- ";

            childPreds = ruleList[i].getPredList();


            for (unsigned int j = 0; j < childPreds.size(); j++){
                cout << childPreds[j].getName() << "(";

                childPredsList = childPreds[j].getParamList();

                cout << childPredsList[0];

                for (unsigned int k = 1; k < childPredsList.size(); k++){
                    cout << "," << childPredsList[k];
                }

                cout << ")";

                if (j != childPreds.size() -1){
                    cout << ",";
                }
            }

            tempPredList.clear();
            childPreds.clear();
            childPredsList.clear();
            cout << "." << endl;

        }
    }
}

void DatalogProgram::queryToString(){
    vector<string> tempPredList;

    cout << "Queries(" << queryList.size() << "):" << endl;
    for (unsigned int i = 0; i < queryList.size(); i++){
        cout << "  " << queryList[i].getName() << "(";
        tempPredList = queryList[i].getParamList();

        cout << tempPredList[0];

        for (unsigned int i = 1; i < tempPredList.size(); i++){
            cout << "," << tempPredList[i];
        }
        cout << ")?" << endl;
    }
}

void DatalogProgram::domainToString(){
    cout << "Domain(" << domain.size() << "):" << endl;
    for (set<string>::iterator i = domain.begin(); i != domain.end(); i++) {
        cout << "  " << *i << endl;
    }
}

vector<Predicate> DatalogProgram::getSchemeList(){
    return schemeList;
}

vector<Predicate> DatalogProgram::getFactList(){
    return factList;
}

vector<Rule> DatalogProgram::getRuleList(){
    return ruleList;
}

vector<Predicate> DatalogProgram::getQueryList(){
    return queryList;
}
