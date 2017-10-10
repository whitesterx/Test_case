#include "Calc.h"

using namespace std;

void Calc::setString(string s) {
    inputString = deleteWhiteSpaces(s);
    inputString = changeCommaToDot(inputString);
    inputString = changeUnarMinus(inputString);
    return;
}

string Calc::deleteWhiteSpaces(string& s) {
    return regex_replace(s, regex("\\s|\\t"),"");
}

string Calc::changeCommaToDot(string& s) {
    return regex_replace(s, regex("\\,"),".");
}
// change all unary minuses to '#' sign
string Calc::changeUnarMinus(string& s) {
    return regex_replace(regex_replace(s, regex("^\\-"),"\#"), regex("\\(\\-"), "\(\#");
}


bool Calc::isCorrect() {

    auto inStrBeginCorr = sregex_iterator(inputString.begin(), inputString.end(), notLex);
    auto inStrEndCorr = sregex_iterator();

    for(sregex_iterator i = inStrBeginCorr; i != inStrEndCorr; ++i) {
        if(!((i->str()).empty())) {
            errorSymbols += i->str();
        }
    }

    if(!errorSymbols.empty())
        errorString = templErrorString + errorSymbols;

    return errorSymbols.empty() ? true : false;
}
//parse tokens from string to vector
void Calc::parseTokens(vector<Token> &vec, string s) {

    auto inStrBegin = sregex_iterator(s.begin(), s.end(), lex);
    auto inStrEnd = sregex_iterator();

    for(sregex_iterator i = inStrBegin; i != inStrEnd; ++i) {
        smatch match = *i;
        string matchStr = match.str();

        Token tok;
        smatch m;
        if(regex_match(matchStr, m, regex("\\+"))) {
            tok.t = Plus;
            tok.n = 2;
        }
        else
        if(regex_match(matchStr, m, regex("\\-"))) {
            tok.t = Minus;
            tok.n = 2;
        }
        else
        if(regex_match(matchStr, m, regex("\\*"))) {
            tok.t = Mult;
            tok.n = 3;
        }
        else
        if(regex_match(matchStr, m, regex("\\/"))) {
            tok.t = Div;
            tok.n = 3;
        }
        else
        if(regex_match(matchStr, m, regex("\\("))) {
            tok.t = Open;
            tok.n = 0;
        }
        else
        if(regex_match(matchStr, m, regex("\\)"))) {
            tok.t = Close;
            tok.n = 1;
        }
        else
        if(regex_match(matchStr, m, regex("\\#"))) {
            tok.t = UnarMinus;
            tok.n = 4;
        }
        else {
            tok.t = Num;
            tok.n = stod(matchStr);
        }
        vec.push_back(tok);
    }
    return;
}
//using Deikstra algorithm to obtain reverse polish notation
void Calc::obtainRevPolsNote(vector<Token> &pol, const vector<Token> &vec) {
    stack<Token> tokenStack;

    for(auto i = vec.begin(); i != vec.end(); ++i) {
        switch(i->t) {
            case Num: {
                pol.push_back(*i);
                break;
            }
            case Open: {
                tokenStack.push(*i);
                break;
            }
            case Close: {
                while(tokenStack.top().t != Open) {
                    pol.push_back(tokenStack.top());
                    tokenStack.pop();
                }
                tokenStack.pop();
                break;
            }
            default: {
                if(tokenStack.empty())
                    tokenStack.push(*i);
                else {
                while(!tokenStack.empty() && tokenStack.top().n >= i->n) {
                    pol.push_back(tokenStack.top());
                    tokenStack.pop();
                }
                tokenStack.push(*i);
                }
                break;
            }
        }
     }

     while(!tokenStack.empty()) {
        pol.push_back(tokenStack.top());
        tokenStack.pop();
     }
     return;
}

//calculating result using stack
double Calc::evalRevPolsNote(const vector<Token> &pol) {

    double first = 0;
    double second = 0;
    double result = 0;

    stack<double> calcStack;

    for(auto i = pol.begin(); i != pol.end(); ++i) {
        if(i->t == Num)
            calcStack.push(i->n);
        else
        if(i->t == UnarMinus) {
            first = calcStack.top();
            calcStack.pop();
            calcStack.push(-first);
        }
        else {
            first = calcStack.top();
            calcStack.pop();
            second = calcStack.top();
            calcStack.pop();
            switch(i->t) {
                case Plus: {
                    result = second + first;
                    break;
                }
                case Minus: {
                    result = second - first;
                    break;
                }
                case Mult: {
                    result = second * first;
                    break;
                }
                case Div: {
                    if(first == 0) {
                        errorString = "Ошибка! Деление на 0";
                        throw overflow_error(errorString);
                    }
                    else
                        result = second / first;
                    break;
                }
            }
            calcStack.push(result);
        }
    }
    return calcStack.empty() ? 0 : result;
}


double Calc::evaluate() {

    vector<Token> tokenVec;
    vector<Token> polsVec;

    parseTokens(tokenVec, inputString);
    obtainRevPolsNote(polsVec, tokenVec);

    return evalRevPolsNote(polsVec);
}

string Calc::getErrorString() const {
    return errorString;
}
string Calc::getInputString() const {
    return inputString;
}
