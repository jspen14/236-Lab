// This is going to check for all of the syntax and be the focus of lab 2
//
#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "DatalogProgram.h"
#include <sstream>

using namespace std;

class Parser{
public:
    Parser(){}
    
    ~Parser(){}
    
    void parse(vector<Token> tokenList, DatalogProgram &dp);
    
    void match(string expected);
    
    Predicate scheme();
    
    Predicate headPredicate();
    
    void idList(Predicate &tempPred);
    
    vector<Predicate> parseSchemeList();
    
    vector<Predicate> factList();
    
    Predicate fact();
    
    void stringList(Predicate &tempPred);
    
    void ruleList();
    
    Rule rule();
    
    Predicate predicate();
    
    void predicateList();
    
    Predicate rulePredicate();
    
    void rulePredicateList();
    
    void parameter();
    
    void parameterList(Predicate &tempPred);
    
    string parenEq(string inString);
    
    void ruleParameter();
    
    void ruleParameterList(Predicate &tempPred);
    
    void stringAdd(stringstream &ss);
    
    void expression();
    
    void op();
    
    Predicate query();
    
    vector<Predicate> queryList();
    
private:
    int index = 0;
    int factLine = 0;
    int ruleLine = 0;
    vector<Token> tokens;
    vector<Predicate> predList;
    vector<Rule> rulesList;
    vector<string> tempExpList;
};
