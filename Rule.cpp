//
//  Rules.cpp
//  Parser
//
//  Created by Josh Spencer on 1/31/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Rule.h"

void Rule::setHead(Predicate hName){
    head = hName;
}

string Rule::getHeadName(){
    return head.getName();
}

vector<string> Rule::getHeadParams(){
    return head.getParamList();
}

vector<Predicate> Rule::getPredList(){
    return predList;
}

void Rule::addPreds(vector<Predicate> tPredList){
    // set predicate values
    predList = tPredList;
}


