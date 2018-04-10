// This class is going to hold Schemes, Facts, and Queries
/*
 *  Must have a toString function
 */

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include "Parameter.h"

using namespace std;

class Predicate{
public:
    Predicate(){}
    
    ~Predicate(){}
    
    void setName(string tName);
    
    string getName();
    
    void addParam(string param);
    
    vector<string> getParamList();
    
private:
    string name;
    vector<string> paramList;
};
