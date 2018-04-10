// This class will:
// - Receive an input file from main.cpp
// - Pass the file onto the input reader (which will pass back a string containing the next valid (or undefined) token
// - Pass the received token into token type which will identify it and then return a correctly formatted string representing the token type
#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include "InputReader.h"
#include "Token.h"
#include <vector>

using namespace std;

class Scanner{

public:
    Scanner();
    ~Scanner(){

    }

    vector<Token> scan(string fileName);

    void dfault(string tempToken, int tempLineNum);

    void quote(string tempToken, int tempLineNum);

    int findNewLineinString(string tempToken);

    void dfault2(string tempToken, int tempLineNum);

    string toString();

private:
    vector<Token> tokenList;

};
