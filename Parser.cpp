//
//  Parser.cpp
//  Parser
//
//  Created by Josh Spencer on 2/1/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Parser.h"

void Parser::parse(vector<Token> tokenList, DatalogProgram &dp){
    tokens = tokenList;
    try {
        
        match("SCHEMES");
        match("COLON");
        dp.addSchemes(parseSchemeList());
        factLine = tokens[index].getLineNum();
        match("FACTS");
        match("COLON");
        predList.clear();
        dp.addFacts(factList());
        match("RULES");
        match("COLON");
        predList.clear();
        ruleList();
        dp.addRules(rulesList);
        match("QUERIES");
        match("COLON");
        predList.clear();
        dp.addQueries(queryList());
        ruleLine = tokens[index].getLineNum();
        match("EOF");
        
        if (dp.getSchemesSize() == 0){
            //cout << "Failure!" << endl;
            //cout << "  (FACTS,\"Facts\"," << factLine << ")" << endl;
        }
        else if (dp.getQueriesSize() == 0){
            //cout << "Failure!" << endl;
            //cout << "(EOF,\"\"," << ruleLine << ")" << endl;
        }
        else {
            //cout << "Success!" << endl;
            //dp.schemeToString();
            //dp.factToString();
            //dp.ruleToString();
            //dp.queryToString();
            //dp.domainToString();
        }
        // Possibly clear out vectors here
        
    } catch (Token badToken) {
        //cout << "Failure!" << endl;
        //cout << "  (" << badToken.getType() << ",\"" << badToken.getValue() <<
        //"\"," << badToken.getLineNum() << ")" << endl;
    }
    

}

void Parser::match(string expected){
    while (tokens[index].getType() == "COMMENT"){
        index++;
    }
    
    if (expected == tokens[index].getType()){
        index++;
    }
    else if (tokens[index].getType() == "COMMENT"){
        return;
    }
    else {
        throw tokens[index];
    }
}

Predicate Parser::scheme(){
    Predicate tempPred;
    tempPred = headPredicate();
    return tempPred;
}

Predicate Parser::headPredicate(){ // set up a parameter that will make this distinguish between scheme and rule (which both use headPredicate)
    Predicate tempPred;
    tempPred.setName(tokens[index].getValue());
    match("ID");            // Make a predicate here and set the head value
    match("LEFT_PAREN");
    tempPred.addParam(tokens[index].getValue());
    match("ID");            // addParam with this ID
    idList(tempPred);               // pass pointer to the Parameter to the idList and continue adding parameters, if they exist
    match("RIGHT_PAREN");
    // if this is scheme, DatalogProgamInstantiation.addScheme()
    // if this is rule, DatalogProgramInstantiation.addRule()
    return tempPred;
}

void Parser::idList(Predicate &tempPred){
    if(tokens[index].getType() == "COMMA") {
        match("COMMA");
        tempPred.addParam(tokens[index].getValue());
        match("ID"); // second parameter to end of param list
        idList(tempPred);
        // Once we get here, we're climbing out of recursion
    }
    else{
        return;
    }
}

vector<Predicate> Parser::parseSchemeList(){
    Predicate tempPred;
    
    while (tokens[index].getType() == "COMMENT"){
        index++;
    }
    
    if (tokens[index].getType() == "ID") {
        tempPred = scheme();
        predList.push_back(tempPred);
        parseSchemeList();
    }
    //predList.push_back(tempPred);
    return predList;
}

vector<Predicate> Parser::factList(){
    Predicate tempPred;
    
    while (tokens[index].getType() == "COMMENT"){
        index++;
    }
    
    if (tokens[index].getType() == "ID"){
        tempPred = fact();
        predList.push_back(tempPred);
        factList();
    }
    
    return predList;
}

Predicate Parser::fact(){
    Predicate tempPred;
    tempPred.setName(tokens[index].getValue());
    match("ID");
    match("LEFT_PAREN");
    tempPred.addParam(tokens[index].getValue());
    match("STRING");
    stringList(tempPred);
    match("RIGHT_PAREN");
    match ("PERIOD");
    
    return tempPred;
}

void Parser::stringList(Predicate &tempPred){
    if(tokens[index].getType() == "COMMA"){
        match("COMMA");
        tempPred.addParam(tokens[index].getValue());
        match("STRING");
        stringList(tempPred);
    }
}

void Parser::ruleList(){
    while (tokens[index].getType() == "COMMENT"){
        index++;
    }
    
    if (tokens[index].getType() == "ID"){
        rulesList.push_back(rule());
        ruleList();
    }
}

Rule Parser::rule(){
    Rule tempRule;
    
    tempRule.setHead(headPredicate());
    match("COLON_DASH");
    predList.push_back(rulePredicate()); // return first predicate
    rulePredicateList();
    match("PERIOD");
    tempRule.addPreds(predList);
    predList.clear(); // is his the right spot??
    return tempRule;
}

Predicate Parser::predicate(){
    Predicate tempPred;
    
    tempPred.setName(tokens[index].getValue());
    match("ID");
    match("LEFT_PAREN");
    tempPred.addParam(tokens[index].getValue());
    parameter();
    parameterList(tempPred);
    match("RIGHT_PAREN");
    
    return tempPred;
}

void Parser::predicateList(){
    if (tokens[index].getType() == "COMMA"){
        match("COMMA");
        predicate();
        predicateList();
    }
}

Predicate Parser::rulePredicate(){
    stringstream ss;
    Predicate tempPred;
    
    tempPred.setName(tokens[index].getValue());
    match("ID");
    if (tokens[index+1].getType() != "LEFT_PAREN"){
        match("LEFT_PAREN");
    }
    else{
        //while (tokens[index].getType() == "LEFT_PAREN"){
        expression();
        ss << "(";
        for (unsigned int i = 0; i < tempExpList.size(); i++){
            if (isalpha(tempExpList[i].at(0)) && isalpha(tempExpList[i].at(tempExpList[i].length() -1))){
                ss << "(" << tempExpList[i] << ")";
            }
            else if (isalpha(tempExpList[i].at(0)) && (tempExpList.at(1)== "*" || tempExpList.at(1)== "+")){
                ss << "(" << tempExpList[i];
            }
            else {
                ss << tempExpList[i];
            }
        }
        // have for loop that sets right number of )'
        tempPred.addParam(parenEq(ss.str()));
        tempExpList.clear();
        ss.str("");
        match("COMMA");
        //}
    }
    
    tempPred.addParam(tokens[index].getValue());
    ruleParameter();
    ruleParameterList(tempPred);
    match("RIGHT_PAREN");
    
    return tempPred;
}

void Parser::rulePredicateList(){
    if (tokens[index].getType() == "COMMA"){
        match("COMMA");
        predList.push_back(rulePredicate());
        rulePredicateList();
    }
}



void Parser::parameter(){
    if(tokens[index].getType() == "STRING"){
        // this needs to return or edit a parameter
        index++;
    }
    else if(tokens[index].getType() == "ID"){
        // this needs to return or edit a parameter ... PASS BY REFERENCE
        index++;
    }
    else{
        
        expression();
    }
}

void Parser::parameterList(Predicate &tempPred){
    string retString;
    stringstream ss;
    if(tokens[index].getType() == "COMMA"){
        match("COMMA");
        // put left paren fix here
        if (tokens[index].getType() == "LEFT_PAREN"){
            while (tokens[index].getType() == "LEFT_PAREN"){
                expression();
                for (int i = tempExpList.size()-1; i >= 0; i--){
                    if (tempExpList[i].at(tempExpList[i].length()-1) == '('){
                        tempExpList[i].pop_back();
                    }
                    ss << "(" << tempExpList[i];
                    if (i == 0){
                        ss << ")";
                    }
                }
            }
            retString = parenEq(ss.str());
            tempPred.addParam(retString);
            tempExpList.clear();
            ss.str("");
        }
        else {
            tempPred.addParam(tokens[index].getValue());
        }
        if (tokens[index].getType() != "RIGHT_PAREN"){
            parameter();
            parameterList(tempPred);
        }
    }
}

string Parser::parenEq(string inString){
    int numLeftParens = 0;
    int numRightParens = 0;
    int dif = 0;
    
    for (unsigned int i=0; i<inString.size(); i++){
        if (inString.at(i) == '('){
            numLeftParens++;
        }
        else if (inString.at(i) == ')'){
            numRightParens++;
        }
    }
    
    dif = numLeftParens - numRightParens;
    for (int i = 0; i < dif; i++){
        inString = inString + ")";
    }
    
    return inString;
}
void Parser::ruleParameter(){ // if you need to do a triple nested expression, simply add it here by passing in tempPred by reference and adding to it only if type = LP
    if(tokens[index].getType() == "STRING"){
        // this needs to return or edit a parameter
        index++;
    }
    else if(tokens[index].getType() == "ID"){
        // this needs to return or edit a parameter ... PASS BY REFERENCE
        index++;
    }
    else{
        expression();
    }
}

void Parser::ruleParameterList(Predicate &tempPred){ // this is what I changed to allow for associativity in rules
    stringstream ss;
    if(tokens[index].getType() == "COMMA"){
        match("COMMA");
        // if not equal to left paren
        if (tokens[index].getType() != "LEFT_PAREN"){
            tempPred.addParam(tokens[index].getValue());
        }
        // end if not equal to left paren
        parameter();
        if (tempExpList.size() != 0){ // this is where format
            stringAdd(ss);
            tempPred.addParam(parenEq(ss.str()));
            tempExpList.clear();
        }
        parameterList(tempPred);
    }
}

void Parser::stringAdd(stringstream &ss){
    ss << "(";
    for (unsigned int i = 0; i < tempExpList.size(); i++){
        if (isalpha(tempExpList[i].at(0)) && isalpha(tempExpList[i].at(tempExpList[i].length() -1))){
            ss << "(" << tempExpList[i] << ")";
        }
        else if (isalpha(tempExpList[i].at(0)) && (tempExpList.at(1)== "*" || tempExpList.at(1)== "+")){
            ss << "(" << tempExpList[i];
        }
        else {
            ss << tempExpList[i];
        }
    }
}


void Parser::expression(){ // make vec to add triply nested
    stringstream ss;
     // possibly ad for left associative
    match("LEFT_PAREN");
    
    if (tokens[index].getType() == "LEFT_PAREN"){
        expression();
    }
    else {
        ss << tokens[index].getValue();
        ruleParameter();
    }
    if (tokens[index].getType() == "COMMA"){
        //match("COMMA");
    }
    else{
        ss << tokens[index].getValue();
        op();
        if (tokens[index].getType() == "LEFT_PAREN"){
            if (tokens[index + 3].getType() == "LEFT_PAREN"){
                tempExpList.push_back(ss.str() + "(");
            }
            else{
                tempExpList.push_back(ss.str()); // does this work?? paren fix
            }
            expression();
        }
        else {
            ss << tokens[index].getValue(); // if right side is expression
            ruleParameter();
            // put a string stream that has adds parens
            tempExpList.push_back(ss.str());
            
        }
        match("RIGHT_PAREN");
    }
}

void Parser::op(){
    if (tokens[index].getType() == "ADD"){
        match("ADD");
    }
    else{ //(tokens[index].getType() == "MULTIPLY")
        match("MULTIPLY");
    }
}

Predicate Parser::query(){
    Predicate tempPred;
    
    tempPred = rulePredicate(); // mot recently changed
    match("Q_MARK");
    
    return tempPred;
}

vector<Predicate> Parser::queryList(){
    Predicate tempPred;
    
    while (tokens[index].getType() == "COMMENT"){
        index++;
    }
    
    if(tokens[index].getType() == "ID"){
        tempPred = query();
        predList.push_back(tempPred);
        queryList();
    }
    
    return predList;
}
