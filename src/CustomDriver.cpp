#include <iostream>
#include "json_parser.tab.hpp"
#include "CustomDriver.hpp"

namespace hse::model{

    int CustomDriver::parse(std::istream& stream) {
        CustomScanner scanner( &stream );
        CustomParser parser( scanner, *this);
        return parser();
    }

}
