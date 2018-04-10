//  Copyright © 2018 Josh Spencer. All rights reserved.
//
// This class will:
// - Receive an input file from main.cpp
// - Pass the file onto the input reader (which will pass back a string containing the next valid (or undefined) token
// - Pass the received token into token type which will identify it and then return a correctly formatted string representing the token type

#include "Scanner.h"

Scanner::Scanner(){

}

vector<Token> Scanner::scan(string fileName){
    InputReader reader;
    bool done = false;
    string tempToken;
    int tempLineNum = 0;
    char charExplorer;
    string retString;

    reader.fileReceive(fileName);

   do{
       tempToken = reader.getNextToken();
       tempLineNum = reader.getLineNum();

       charExplorer = tempToken.at(0);

       // USE Switch STATEMENTS TO IDENTIFY TYPE
       switch (charExplorer) {
           case ',':
               tokenList.push_back(Token("COMMA", tempToken, tempLineNum));
               break;

           case '.':
               tokenList.push_back(Token("PERIOD", tempToken, tempLineNum));
               break;

           case '?':
               tokenList.push_back(Token("Q_MARK", tempToken, tempLineNum));
               break;

           case '(':
               tokenList.push_back(Token("LEFT_PAREN", tempToken, tempLineNum));
               break;

           case ')':
               tokenList.push_back(Token("RIGHT_PAREN", tempToken, tempLineNum));
               break;

           case ':':{
               if (tempToken.length() == 2) {
                   tokenList.push_back(Token("COLON_DASH", tempToken, tempLineNum));

               }
               else {
                   tokenList.push_back(Token("COLON", tempToken, tempLineNum));
               }
               break;
           }

           case '*':
               tokenList.push_back(Token("MULTIPLY", tempToken, tempLineNum));
               break;

           case '+':
               tokenList.push_back(Token("ADD", tempToken, tempLineNum));
               break;

           default:
               if(tempToken == "/xff"){
                   tokenList.push_back(Token("EOF", "", tempLineNum));
                   done = true;
               }
               else if (tempToken.at(0) == '\'' && tempToken.at(1) == '\''){
                   tokenList.push_back(Token("STRING", tempToken, tempLineNum));

               }
               else {
                   dfault(tempToken, tempLineNum);
               }
               break;
       }



   }while(!done);

    return tokenList;
}

void Scanner::dfault(string tempToken, int tempLineNum){
    if (tempToken == "Schemes"){
        tokenList.push_back(Token("SCHEMES", tempToken, tempLineNum));
    }
    else if (tempToken == "Facts"){
        tokenList.push_back(Token("FACTS", tempToken, tempLineNum));
    }
    else if (tempToken == "Rules"){
        tokenList.push_back(Token("RULES", tempToken, tempLineNum));
    }
    else if (tempToken == "Queries"){
        tokenList.push_back(Token("QUERIES", tempToken, tempLineNum));
    }
    else if (isalpha(tempToken.at(0))){
        tokenList.push_back(Token("ID", tempToken, tempLineNum));
    }
    else if(tempToken.at(0) == '\''){
        quote(tempToken, tempLineNum);
    }
    else{
        dfault2(tempToken, tempLineNum);
    }
}

void Scanner::quote(string tempToken, int tempLineNum){
    int temptLine = 0;
    for (unsigned int i = 0; i < tempToken.length(); i++){
      if (tempToken.at(i) == '\n'){
        temptLine++;
      }
    }
    if(tempToken.at(tempToken.length() - 1) == '\'' && tempToken.at(tempToken.length() - 2) != '\'' && tempToken.length() > 1){
        tokenList.push_back(Token("STRING", tempToken, tempLineNum - temptLine));
    }
    else {
        tokenList.push_back(Token("UNDEFINED", tempToken, tempLineNum - temptLine));
    }
}
void Scanner::dfault2(string tempToken, int tempLineNum){
    if (tempToken.at(0) == '^' && tempToken.length() == 1){
        tokenList.push_back(Token("UNDEFINED", tempToken, tempLineNum));
    }
    else if(tempToken.at(0)== '#' || (tempToken.at(0) == '^' && tempToken.at(1) == '#')){
        int numNewLines = 0;
        numNewLines = findNewLineinString(tempToken);
        if (tempToken.at(0) == '^' && tempToken.at(1) == '#'){
            tempToken.erase(0,1);
            tokenList.push_back(Token("UNDEFINED", tempToken, tempLineNum - numNewLines));
        }
        else {
            // Make a for-loop that checks for the number of new line characters
            tokenList.push_back(Token("COMMENT", tempToken, tempLineNum - numNewLines));
        }
    }
    else {
        tokenList.push_back(Token("UNDEFINED", tempToken, tempLineNum));
    }
}

int Scanner::findNewLineinString(string tempToken){
  int numNewLines = 0;

  for (unsigned int i = 0; i < tempToken.length(); i++){
      if (tempToken.at(i)=='\n'){
          numNewLines++;
      }
  }

  return numNewLines;
}

//string Scanner::toString(){
//    stringstream ss;
//    string retString;
//
//    for (unsigned int i = 0; i <tokenList.size(); i++){
//        ss << "(" << tokenList[i].getType()<< ",\"" << tokenList[i].getValue() << "\"," << tokenList[i].getLineNum() << ")" << endl;
//    }
//
//    ss << "Total Tokens = " << tokenList.size() << endl;
//    retString = ss.str();
//
//    return retString;
//}

