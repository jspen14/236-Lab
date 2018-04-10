// This class will contain Rule objects
/*
 *  Must have a toString function
 */

#pragma once

#include <iostream>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule{
public:
    Rule(){}
    
    ~Rule(){}
    
    void setHead(Predicate hName);
    
    string getHeadName();
    
    vector<string> getHeadParams();
    
    void addPreds(vector<Predicate> tPredList);
    
    vector<Predicate> getPredList();
    
private:
    Predicate head;
    vector<Predicate> predList;
};
