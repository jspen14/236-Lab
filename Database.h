//
//  Database.hpp
//  LAB3
//
//  Created by Josh Spencer on 3/8/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#pragma once
#include <map>
#include <set>
#include <string>
#include "Relation.h"
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Database{
public:
    void addRelation(string name, Relation relation);
    
    map<string,Relation>& getRelationsMap();
    
    int getTupleCount();
    
    void updateTupleCount();
    
private:
    map<string, Relation> relationsMap;
    int tupleCount = 0;
};
/* Database_hpp */
