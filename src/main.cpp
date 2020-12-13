#include "json_model.hpp"

#include <iostream>

int main()
{

    hse::model::json my_data = hse::model::generate_json(5);

    std::cout << my_data;
}
