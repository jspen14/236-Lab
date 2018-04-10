// This class will:
// - Receive an input file from the scanner class
// - Parse through characters to find next token
// - Return token to scanner
//
// Data members:
// - numTokens (number of tokens read)
// - lineNum (current line)
#pragma once

#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class InputReader{
public:
    InputReader();
    ~InputReader(){
        in.close();
    }
    
    void fileReceive(string file);
    
    string getNextToken(); 
    
    string colon();
    
    string quote(char c);
    
    string hashtag(char c);
    
    string hashtagElse(char c);
    string dfault(char c);
    
    string dfaultElse(char c);
    
    void incLineNum();
    
    int getLineNum();
    
    
private:
    int lineNum = 1;
    string fileName;
    int numTokens = 0;
    ifstream in;
};
