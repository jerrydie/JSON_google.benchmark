
#ifndef JSON_PARSER_CUSTTOMSCANNER_HPP
#define JSON_PARSER_CUSTTOMSCANNER_HPP

#include <memory>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "json_model.hpp"
#include "json_parser.tab.hpp" //needed
#include "location.hh"



namespace hse::model{

    class CustomDriver; // needed

    class CustomScanner: public yyFlexLexer {

        using sem_t = CustomParser::semantic_type;
        using loc_t = CustomParser::location_type;

        std::unique_ptr<loc_t> loc_ptr = std::make_unique<loc_t>();
    public:
        CustomScanner(std::istream& in): yyFlexLexer(&in) {}

        int yylex(sem_t* lval, loc_t* location);

        loc_t* loc = loc_ptr.get();
        sem_t* yylval = nullptr;

};
}

#endif //JSON_PARSER_CUSTTOMSCANNER_HPP
