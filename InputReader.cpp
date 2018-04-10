//  Copyright © 2018 Josh Spencer. All rights reserved.
//

#include "InputReader.h"

InputReader::InputReader(){

}

void InputReader::fileReceive(string file){
    fileName = file;
    in.open(fileName);
}

string InputReader::getNextToken(){ // this will have a .txt file as parameter ... possibly just a string??
    //cout << fileName << "in inputReader func!! " << endl << endl;
    string nextToken;

    //bool done = false;

    char c = in.get();

    while (isspace(c)){

        if (c == '\n'){
            incLineNum();
        }
        else if (c == '\xff'){
            break;
        }
        c = in.get();
    }
    switch (c){
        case ',':
            nextToken = ",";
            break;
        case '.':
            nextToken = ".";
            break;
        case '?':
            nextToken = "?";
            break;
        case '(':
            nextToken = "(";
            break;
        case ')':
            nextToken = ")";
            break;
        case ':':{              // ADD if statement for :- use the .peek()
            nextToken = colon();
            break;
        }
        case '*':
            nextToken = "*";
            break;
        case '+':
            nextToken = "+";
            break;
        case '\'':{
            nextToken = quote(c);
            break;
        }
        case '#':{
            nextToken = hashtag(c);
            break;
        }

        case '\xff':
            nextToken = "/xff";
            break;

        default:
            nextToken = dfault(c);
    }


    return nextToken;
}

string InputReader::colon(){
    char c;
    string nextToken;
    c = in.peek();
    if (c == '-'){
        c = in.get();
        nextToken = ":-";
    }
    else{
        nextToken = ":";
    }

    return nextToken;
}

string InputReader::quote(char c){
    string nextToken;
    stringstream ss;
    bool prevQuote = false;
    bool done = false;

    while (!done){
        ss << c;


        c = in.get();
        char d = in.peek();

        if (prevQuote){
            prevQuote = false;
            continue;
        }
        if (d == '\xff'){ // IF UNTERMINATED STRING
            ss << c;
            incLineNum();
            nextToken = ss.str();
            // add here
            done = true;
        }
        else if (c == '\n'){
            incLineNum();
        }
        else if (c == '\''){

            if (d == '\''){ // IF DOUBLE QUOTE FOLLOWED BY MORE STRING
                prevQuote = true;
                continue;

            }
            else { // IF TERMINATED STRING
                ss << c;
                nextToken = ss.str();
                done = true;
            }
        }
    }
    return nextToken;
}

string InputReader::hashtag(char c){
    stringstream ss;
    string nextToken;
    char d;
    d = in.peek();
    bool done = false;

    if (d == '|'){
        ss << c;
        c = in.get();
        ss << c;

        while (!done){

            d = in.peek();

            if(c == '|' && d == '#'){
                //cout << "valid string" << endl;
                c = in.get();
                ss << c;
                nextToken = ss.str();
                done = true;
            }
            else if (d == '\xff'){
                //cout << "invalid string" << endl;
                nextToken = ss.str();
                nextToken = "^" + nextToken;
                done = true;
            }
            else {
                c = in.get();
                if (c == '\n'){
                    incLineNum();
                }
                ss << c;
            }
        }
    }
    else {
        nextToken = hashtagElse(c);
    }


    return nextToken;
}

string InputReader::hashtagElse(char c){
    string nextToken;
    stringstream ss;
    char d = in.peek();
    bool done = false;

    while (!done){
        ss << c;
        d = in.peek();
        if (d == '\n'){
            done = true;
            nextToken = ss.str();
            break;
        }
        else {
            c = in.get();
        }
    }

    return nextToken;
}

string InputReader::dfault(char c){
    string nextToken;

    if (!isalpha(c)){
       stringstream ss;
        ss << c;
        nextToken = ss.str();
        
    }
    else {
        nextToken = dfaultElse(c);
    }

    return nextToken;
}

string InputReader::dfaultElse(char c){
    stringstream ss;
    string nextToken;
    char d;
    bool done = false;

    while (!done){
        ss << c;
        d = in.peek();
        if (d == ' ' || !isalnum(d) || d == '\n'){
            done = true;
            nextToken = ss.str();
            break;
        }
        else {
            c = in.get();
        }
    }

    return nextToken;
}

void InputReader::incLineNum(){
    lineNum += 1;
}

int InputReader::getLineNum(){
    return lineNum;
}
