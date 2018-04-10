// This class will create an instance of the Scanner class and pass it the inputted file name
// This class will then receive a string from the Scanner containing a correctly formatted string of all the tokens.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "InputReader.h"
#include "Token.h"
#include "Scanner.h"
#include "Predicate.h"
#include "Rule.h"
#include "Parser.h"
#include "Interpreter.h"
#include "DatalogProgram.h"

using namespace std;

int main(int argc, char *argv[]) {//int argc, char *argv[]
    string fileName;
    vector<Token> tokenList;
    
// LAB 1
    Scanner scan;
    tokenList = scan.scan("in30.txt"); // can change parameter to fileName

// LAB 2
    DatalogProgram dp;
    Parser parse;
    parse.parse(tokenList, dp);

// LAB 3
    Interpreter interpreter;
    interpreter.interpret(dp);

// LAB 4
    // Also in interpreter
    
    return 0;
}
