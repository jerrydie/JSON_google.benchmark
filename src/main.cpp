#include "json_model.hpp"

#include <iostream>

int main()
{

    hse::model::node e{int64_t{42}};
    auto a = hse::model::map_t{
    {"a", true},
    {"bcd", int64_t{42}},
    {"de", -34.5},
    {"f", hse::model::seq_t{int64_t{12},{},int64_t{3},{},"hello"}},
    {"gh", hse::model::map_t{
            {"i", {}},
            {"jk", "test"}
        }
    }
   };
    hse::model::json my_data{a};

    std::cout << my_data;
}
