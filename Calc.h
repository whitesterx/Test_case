#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

#include <regex>
#include <string>
#include <stack>
#include <clocale>


enum Tokens {Plus, Minus, Mult, Div, Open, Close, Num, UnarMinus};

//using n for number and for operations priority
struct Token {
    double n;
    Tokens t;
};

class Calc {
public:

    void setString(std::string);
    std::string getInputString() const;
    std::string getErrorString() const;
    double evaluate();
    bool isCorrect();

private:
// Regular expression for correct tokens
    const std::regex lex = std::regex("(\\d+\\.\\d{1,2})|(\\d+)|(\\+)|(\\-)|(\\*)|(\\/)|(\\()|(\\))|(\\#)");
// Regular expression to exclude non-correct symbols
    const std::regex notLex = std::regex("(\\d+\\.\\d{3,})|([\\+\\*\\-\\/\\#]{2,})|([^\\*\\d\\.\\+\\-\\/\\(\\)\\#])");

    const std::string templErrorString= "Некорректный ввод, строка содержит недопустимое выражение ";

    std::string inputString;
    std::string errorSymbols;
    std::string errorString;

    std::string deleteWhiteSpaces(std::string&);
    std::string changeCommaToDot(std::string&);
    std::string changeUnarMinus(std::string&);

    void parseTokens(std::vector<Token>&, std::string);
    void obtainRevPolsNote(std::vector<Token>&, const std::vector<Token>&);
    double evalRevPolsNote(const std::vector<Token>&);
};



#endif // CALC_H_INCLUDED
