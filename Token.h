// This class will:
// - Receive a valid (or undefined) token from scanner
// - Identify it (with switch statement)
// - Return a properly formatted string with the tokens information
//
#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <string>


using namespace std;

class Token{
// enum
    // has all token types 
public:
    Token(string myType, string myValue, int myLineNum);
    
    ~Token(){
        
    }
    
    void setType(string inType);
    
    void setValue(string inVal);
    
    void setLineNum(int inLineNum);
    
    string getType();
    
    string getValue();
    
    int getLineNum();
    
private:
    string type;
    string value;
    int lineNum;
};
