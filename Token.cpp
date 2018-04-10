//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "Token.h"

Token::Token(string myType, string myValue, int myLineNum){
    type = myType;
    value = myValue;
    lineNum = myLineNum;
}

void Token::setType(string inType){
    type = inType;
}

void Token::setValue(string inVal){
    value = inVal;
}

void Token::setLineNum(int inLineNum){
    lineNum = inLineNum;
}

string Token::getType(){
    return type;
}

string Token::getValue(){
    return value;
}

int Token::getLineNum(){
    return lineNum;
}


