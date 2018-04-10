//
#include "Relation.h"

void Relation::setName(string inputName){
    name = inputName;
}

void Relation::addColHeader(Scheme inputColHeader){
    colHeader = inputColHeader;
}

void Relation::addTuple(Tuple inputRow){
    rows.insert(inputRow);
}

void Relation::addAllRows(set<Tuple> rowsToAdd){
    rows = rowsToAdd;
}

string Relation::getName(){
    return name;
}

Scheme Relation::getColHeader(){
    return colHeader;
}

set<Tuple> Relation::getRows(){
    return rows;
}

Relation Relation::selectIndexValue(int index, string value){
    Relation relationToReturn;
    set<Tuple> rows;
    relationToReturn.setName(this->getName());
    relationToReturn.addColHeader(this->getColHeader());
    
    rows = this->getRows();
    
    for (auto row:rows) {
        if(row[index] == value){
            relationToReturn.addTuple(row);
        }
    }

    return relationToReturn;
}

Relation Relation::selectIndexIndex(int index1, int index2){
    Relation relationToReturn;
    set<Tuple> rows;
    relationToReturn.setName(this->getName());
    relationToReturn.addColHeader(this->getColHeader());
    
    rows = this->getRows();
    
    for (auto row:rows) {
        if(row[index1] == row[index2]){
            relationToReturn.addTuple(row);
        }
    }
    return relationToReturn;
}

Relation Relation::join(Relation& rel2){
    Relation returnRelation;
    set<Tuple> rel1Rows = this->getRows();
    set<Tuple> rel2Rows = rel2.getRows();
    Scheme rel1CH = this->getColHeader();
    Scheme rel2CH = rel2.getColHeader();
    
    for (auto rel1row:rel1Rows){
        for (auto rel2row:rel2Rows){
            if (joinable(rel1row, rel2row, rel1CH, rel2CH)){
                returnRelation.addTuple(joinTuple(rel1row, rel2row, rel1CH, rel2CH));
            }
        }
    }
    
    makeColumnHeader(rel1CH, rel2CH);
    
    returnRelation.addColHeader(rel1CH);


    return returnRelation;
}

bool Relation::joinable(Tuple t1, Tuple t2, Scheme s1, Scheme s2){
    for (unsigned int i = 0; i < s1.size(); i++){
        for (unsigned int j = 0; j < s2.size(); j++){
            if (s1[i] == s2[j]) {
                if (t1[i] != t2[j]) {
                    return false;
                }
            }
        }
    }
    return true;
}

Tuple Relation::joinTuple(Tuple rel1row, Tuple rel2row, Scheme rel1CH, Scheme rel2CH){
    Tuple returnTuple;
    
    for (unsigned int i = 0; i < rel1row.size(); i++){
        returnTuple.push_back(rel1row[i]);
    }
    
    for (unsigned int i = 0; i < rel2CH.size(); i++){
        if (!found(rel1CH, rel2CH[i])){
            rel1CH.push_back(rel2CH[i]);
            returnTuple.push_back(rel2row[i]);
        }
    }
    
    return returnTuple;
}

void Relation::makeColumnHeader(Scheme& rel1CH, Scheme rel2CH){
    for (unsigned int i = 0; i < rel2CH.size(); i++){
        if (!found(rel1CH, rel2CH[i])){
            rel1CH.push_back(rel2CH[i]);
        }
    }
}

Relation Relation::project(vector<int> indicesOfVariables){
    Relation relationToReturn;
    set<Tuple> rows;
    Scheme newColHeader;
    
    relationToReturn.setName(this->getName());
    
    if (indicesOfVariables.size() == 0){
        relationToReturn.addColHeader(this->getColHeader());
        relationToReturn.addAllRows(this->getRows());
        return relationToReturn;
    }
    
    for (unsigned int i = 0; i<indicesOfVariables.size(); i++){
        newColHeader.push_back(this->getColHeader()[indicesOfVariables[i]]);
    }
    
    relationToReturn.addColHeader(newColHeader);
    
    rows = this->getRows();
    
    
    for (auto row:rows){
        Tuple tuple;
        for (unsigned int j=0; j < indicesOfVariables.size(); j++){
            tuple.push_back(row[indicesOfVariables[j]]);
        }
        
        relationToReturn.addTuple(tuple);
    }
    
    return relationToReturn;
}



Relation Relation::rename(vector<string> namesOfVariables){
    Relation relationToReturn;
    Scheme newColHeader;

    for (unsigned int i=0; i < namesOfVariables.size(); i++){
        newColHeader.push_back(namesOfVariables[i]);
    }
    
    relationToReturn.setName(this->getName());
    relationToReturn.addColHeader(newColHeader);
    relationToReturn.addAllRows(this->getRows());
    
    return relationToReturn;
}

bool Relation::found(Scheme rel1CH, string inputString){
    unsigned long rel1Size = rel1CH.size();
    for (unsigned int i = 0; i < rel1Size; i++){
        if (rel1CH[i] == inputString){
            return true;
        }
    }
    return false;
}
