
#ifndef JSON_PARSER_CUSTTOMSCANNER_HPP
#define JSON_PARSER_CUSTTOMSCANNER_HPP

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "json_parser.tab.hpp" //needed
#include "location.hh"
#include "json_model.hpp"

namespace hse::model{
    class CustomDriver; // needed
    class CustomScanner: public yyFlexLexer {
    public:
        CustomScanner(std::istream *in): yyFlexLexer(in) {
            loc = new CustomParser::location_type();
        }

        using FlexLexer::yylex;
        //hse::model::CustomParser::symbol_type yylex();
        int yylex(hse::model::CustomParser::semantic_type * lval, hse::model::CustomParser::location_type * location);

        CustomParser::semantic_type *yylval = nullptr;

        CustomParser::location_type *loc = nullptr;
};
}

#endif //JSON_PARSER_CUSTTOMSCANNER_HPP
