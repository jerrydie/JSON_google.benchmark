%{
    #include <iostream>
    #include <string>
    #include <exception>
    #include "json_model.hpp"
    //#include "json.tab.h"
    enum class token {
	    	STRING,
	    	NUMBER,
	    	M_BEGIN,
	    	M_END,
	    	TRUE_,
	    	FALSE_,
	    	NULL_,
	    	S_BEGIN,
	    	S_END,
	    	COMMA,
	    	COLON
	};
    #define YY_DECL int yylex( hse::model::node::storage_t* yylval, void * )
%}
DIGIT1to9 [1-9]
DIGIT [0-9]
DIGITS {DIGIT}+
INT {DIGIT}|{DIGIT1to9}{DIGITS}|-{DIGIT}|-{DIGIT1to9}{DIGITS}
FRAC [.]{DIGITS}
EXP {E}{DIGITS}
E [eE][+-]?
HEX_DIGIT [0-9a-f]
NUMBER {INT}|{INT}{FRAC}|{INT}{EXP}|{INT}{FRAC}{EXP}
UNESCAPEDCHAR [ -!#-\[\]-~]
ESCAPEDCHAR \\[\"\\bfnrt/]
UNICODECHAR \\u{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}
CHAR {UNESCAPEDCHAR}|{ESCAPEDCHAR}|{UNICODECHAR}
CHARS {CHAR}+
DBL_QUOTE [\"]

%%

{DBL_QUOTE}{DBL_QUOTE} |
{DBL_QUOTE}{CHARS}{DBL_QUOTE} { //empty or not empty key or string
    yylval->emplace<std::string>(std::string (yytext));
    return static_cast<int>(token::STRING);
};

{NUMBER} { // int_ or float_
    std::string text (yytext);
    yylval->emplace<std::int64_t> (std::stoll (text)); // int + double!!!
    return static_cast<int>(token::NUMBER);
};

true { // bool_
    yylval->emplace<bool> (true);
    return static_cast<int>(token::TRUE_);
};

false { // bool_
    yylval->emplace<bool> (false);
    return static_cast<int>(token::FALSE_);
};

null { // NULL_
    //yylval->emplace<> (std::monostate);
    return static_cast<int>(token::NULL_);
};

\{ { // begin a map
    return static_cast<int>(token::M_BEGIN);
};

\} { // end a map
    return static_cast<int>(token::M_END);
};

\[ { // begin a seq
    return static_cast<int>(token::S_BEGIN);
};

\] { // end a seq
    return static_cast<int>(token::S_END);
};

, {
    return static_cast<int>(token::COMMA);
};

: {
    return static_cast<int>(token::COLON);
};

[ \t\n\r]+ ; // ignore whitespace

. { // other characters
    throw(std::invalid_argument("Unexpected token"));
};

%%




