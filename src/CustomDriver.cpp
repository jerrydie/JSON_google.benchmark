
#include "CustomDriver.hpp"
#include "json_parser.tab.hpp"

namespace hse::model{

    int CustomDriver::parse(std::istream& stream) {
        delete scanner;
        scanner = new CustomScanner(&stream);
        delete parser;
        parser = new CustomParser( *scanner, *this);
        return (*parser)();
    }

}
