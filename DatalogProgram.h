//
/*
 *  Must have a toString function
 */

#pragma once

#include <iostream>
#include <vector>
#include "Rule.h"
#include "Predicate.h"
#include <set>

using namespace std;

class DatalogProgram{
    
public:
    DatalogProgram(){}
    ~DatalogProgram(){}
    
    void addSchemes(vector<Predicate> schemes);
    
    int getSchemesSize();
    
    void addFacts(vector<Predicate> facts);
    
    void addRules(vector<Rule> rules);

    void addQueries(vector<Predicate> queries);
    
    int getQueriesSize();

//    void programToString();

    void schemeToString();

    void factToString();
    
    void ruleToString();

    void queryToString();
    
    void domainToString();
    
    vector<Predicate> getSchemeList();
    
    vector<Predicate> getFactList();
    
    vector<Rule> getRuleList();
    
    vector<Predicate> getQueryList();
    
private:
    vector<Predicate> schemeList;
    vector<Predicate> factList;
    vector<Rule> ruleList;
    vector<Predicate> queryList;
    set<string> domain;
};
