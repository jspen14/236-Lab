//
//  Predicate.cpp
//  Parser
//
//  Created by Josh Spencer on 1/31/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Predicate.h"

void Predicate::setName(string tName){
    name = tName;
}

string Predicate::getName(){
    return name;
}

void Predicate::addParam(string param){
    paramList.push_back(param);
}

vector<string> Predicate::getParamList(){
    return paramList;
}

