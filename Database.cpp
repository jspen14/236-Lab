//
//  Database.cpp
//  LAB3
//
//  Created by Josh Spencer on 3/8/18.
//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Database.h"

void Database::addRelation(string name, Relation relation){
    relationsMap.insert(pair<string,Relation>(name,relation));
}

map<string, Relation>& Database::getRelationsMap(){
    return relationsMap;
}

int Database::getTupleCount(){
    updateTupleCount();
    return tupleCount;
}

void Database::updateTupleCount(){
    tupleCount = 0;
    
    for (auto rel:relationsMap){
        tupleCount = rel.second.getRows().size() + tupleCount;
    }
    
}
