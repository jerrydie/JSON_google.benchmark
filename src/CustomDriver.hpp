#ifndef JSON_PARSER_CUSTOMDRIVER_HPP
#define JSON_PARSER_CUSTOMDRIVER_HPP

#include "json_parser.tab.hpp"
#include "CustomScanner.hpp"
#include "json_model.hpp"
#include <string>


namespace hse::model{

    class CustomDriver {
    public:
        CustomDriver(){}

        json result;

        int parse(std::istream& stream);
        hse::model::location location;

        CustomParser* parser = nullptr;
        CustomScanner* scanner = nullptr;

    };

}
#undef YY_DECL
#define YY_DECL hse::model::CustomParser::symbol_type hse::model::CustomScanner::yylex(hse::model::CustomDriver& drv)

#endif //JSON_PARSER_CUSTOMDRIVER_HPP
