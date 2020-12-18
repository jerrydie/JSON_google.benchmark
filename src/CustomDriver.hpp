#ifndef JSON_PARSER_CUSTOMDRIVER_HPP
#define JSON_PARSER_CUSTOMDRIVER_HPP
#include <string>
#include <iostream>
#include "json_model.hpp"
#include "json_parser.tab.hpp"
#include "CustomScanner.hpp"



namespace hse::model{
    class CustomDriver {
    public:
        CustomDriver(){}

        json result;

        int parse(std::istream& stream);
        hse::model::location location;

    };

}

/*#undef YY_DECL
#define YY_DECL hse::model::CustomParser::symbol_type yylex(hse::model::CustomDriver& driver)
YY_DECL;*/

#endif //JSON_PARSER_CUSTOMDRIVER_HPP
