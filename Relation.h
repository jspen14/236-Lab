//
#pragma once
#include <string>
#include <vector>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include <iostream>

using namespace std;

class Relation{
public:
    void setName(string inputName);
    
    void addColHeader(Scheme inputColHeader);
    
    void addTuple(Tuple inputRow);
    
    void addAllRows(set<Tuple> rowsToAdd);
    
    string getName();
    
    Scheme getColHeader(); // possibly edit to return value at index?
    
    set<Tuple> getRows(); //possibly edit to return single row?
    
    Relation selectIndexValue(int index, string value);
    
    Relation selectIndexIndex(int index1, int index2);
    
    Relation join(Relation& rel2);
    
    bool joinable(Tuple t1, Tuple t2, Scheme s1, Scheme s2);
    
    Tuple joinTuple(Tuple t1, Tuple t2, Scheme s1, Scheme s2);
    
    void makeColumnHeader (Scheme& rel1CH, Scheme rel2CH);
    
    Relation project(vector<int> indicesOfVariables);
    
    Relation rename(vector<string> namesOfVariables);
    
    bool found(Scheme rel1CH, string inputString);
    
private:
    string name;
    Scheme colHeader;
    set<Tuple> rows;
};
/* Relation_hpp */
