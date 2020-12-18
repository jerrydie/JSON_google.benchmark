%option c++
%{
    #include <iostream>
    #include <string>
    #include <exception>
    #include "json_model.hpp"
    #include "json_parser.tab.hpp"
    #include "CustomDriver.hpp"
    #include <sstream>
    
    #define yyterminate() return hse::model::CustomParser::symbol_type(hse::model::CustomParser::token::END, *loc)
    
%}

%option noyywrap nounput noinput batch debug
%option yyclass="hse::model::CustomScanner"


DIGIT1to9 [1-9]
DIGIT [0-9]
DIGITS {DIGIT}+
INT {DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC [.]{DIGITS}
EXP {E}{DIGITS}
E [eE][+-]?
HEX_DIGIT [0-9a-f]
FLOAT {INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}|{FRAC}
UNESCAPEDCHAR [ -!#-\[\]-~]
ESCAPEDCHAR \\[\"\\bfnrt/]
UNICODECHAR \\u{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}
CHAR {UNESCAPEDCHAR}|{ESCAPEDCHAR}|{UNICODECHAR}
CHARS {CHAR}+
DBL_QUOTE [\"]



%%

{DBL_QUOTE}{DBL_QUOTE} |
{DBL_QUOTE}{CHARS}{DBL_QUOTE} { //empty or not empty key or string
    std::string str(yytext);
    str.erase(str.begin());
    str.pop_back();
    return hse::model::CustomParser::make_STRING(str, *loc);
};

{INT} { // int64_t
    std::string text (yytext);
    return hse::model::CustomParser::make_INT(std::stoll (text), *loc);
};

{FLOAT} { // double
    std::string text (yytext);
    return hse::model::CustomParser::make_FLOAT(std::stod (text), *loc);
};

true { // bool
    return hse::model::CustomParser::make_TRUE_(true, *loc);
};

false { // bool
    return hse::model::CustomParser::make_FALSE_(false, *loc);
};

null { // null
    return hse::model::CustomParser::make_null(std::monostate{}, *loc);
};

\{ { // begin a map
    return hse::model::CustomParser::make_M_BEGIN(*loc);
};

\} { // end a map
    return hse::model::CustomParser::make_M_END(*loc);
};

\[ { // begin a seq
    return hse::model::CustomParser::make_S_BEGIN(*loc);
};

\] { // end a seq
    return hse::model::CustomParser::make_S_END(*loc);
};

, {
    return hse::model::CustomParser::make_COMMA(*loc);
};

: {
    return hse::model::CustomParser::make_COLON(*loc);
};

[ \t\n\r]+ ; // ignore whitespace

. { // other characters
    throw(std::invalid_argument("Unexpected token"));
};

%%




