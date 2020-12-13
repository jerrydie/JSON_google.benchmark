#include "json_model.hpp"
#include <ostream>
#include <variant>
#include <random>
#include <limits>
#include <string>

namespace hse::model {

namespace  {
    struct display_visitor
    {
        constexpr static std::size_t spaces = 4;
        std::ostream& os;
        std::size_t indent;

        void operator()(std::monostate)
        {
            os << "null";
        }

        template<typename T>
        void operator()(const T& x)
        {
            os << x;
        }

        void operator()(const std::string& s)
        {
            // TODO: escaped sequenses
            os << '"' << s << '"';
        }

        void operator()(const seq_t& s)
        {
            bool first = true;
            os << '[';
            for(auto& e:s)
            {
                os << (first?"":",");
                first = false;

                os << '\n';
                do_indent(indent+spaces);
                e.display(os, indent+spaces);
            }

            if (!first)
            {
                os << "\n";
                do_indent(indent);
            }
            os << ']';
        }

        void operator()(const map_t& s)
        {
            bool first = true;
            os << '{';
            for(auto& [k, v]:s)
            {
                os << (first?"":",");
                first = false;

                os << '\n';
                do_indent(indent+spaces);
                os << '"' << k << "\": ";
                v.display(os, indent+spaces);
            }
            if (!first)
            {
                os << "\n";
                do_indent(indent);
            }
            os << '}';
        }

        void do_indent(std::size_t n)
        {
            for(std::size_t i=0; i<n; ++i)
                os << ' ';
        }

    };
}

void node::display(std::ostream& out, std::size_t indent) const
{
    std::visit(display_visitor{out, indent}, data_);
}


static std::mt19937 prng(std::random_device{}());

bool generate_bool()
{
    std::uniform_int_distribution<std::size_t> distrib(0,1);
    return distrib(prng);
}

std::int64_t generate_int()
{
    std::uniform_int_distribution<std::int64_t> distrib(std::numeric_limits<std::int64_t>::min());
    return distrib(prng);
}

double generate_float()
{
    std::uniform_real_distribution<double> distrib(
                std::numeric_limits<double>::min(),
                std::numeric_limits<double>::max()
                );
    return distrib(prng);
}

std::size_t random_lenght(std::size_t low=0, std::size_t up=10)
{
    using udistr_t = std::uniform_int_distribution<std::size_t>;
    static udistr_t pick_lenght(low, up);
    return pick_lenght(prng);
}

std::string generate_string()
{
    static std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    using udistr_t = std::uniform_int_distribution<std::string::size_type>;

    static udistr_t pick_char(0, alphabet.size() - 1);

    std::size_t length = random_lenght();
    std::string result;
    result.reserve(length);

    for(std::size_t i = 0; i<length; ++i)
    {
        result += alphabet[pick_char(prng)];
    }

    return result;
}

node generate_node(std::size_t current_depth, std::size_t max_depth);

seq_t generate_seq(std::size_t current_depth, std::size_t max_depth)
{
    std::size_t length = random_lenght();
    seq_t result;

    result.reserve(length);

    for(std::size_t i = 0; i<length; ++i)
    {
        result.push_back(generate_node(current_depth, max_depth));
    }

    return result;
}

map_t generate_map(std::size_t current_depth, std::size_t max_depth=5, std::size_t elements=0)
{
    std::size_t length = (elements==0?random_lenght():elements);
    map_t result;

    for(std::size_t i = 0; i<length; ++i)
    {
        result[std::to_string(i)] = generate_node(current_depth, max_depth);
    }

    return result;
}

node generate_node(std::size_t current_depth, std::size_t max_depth)
{
    std::size_t add_seq_and_map = (current_depth<=max_depth?2:0);
    std::uniform_int_distribution<std::size_t> distrib(static_cast<std::size_t>(node_type::null),
                                                       static_cast<std::size_t>(node_type::string)+add_seq_and_map);
    node_type gen_type = static_cast<node_type>(distrib(prng));

    switch (gen_type) {
    case node_type::null:   return node{};
    case node_type::bool_:  return node{generate_bool()};
    case node_type::int_:   return node{generate_int()};
    case node_type::float_: return node{generate_float()};
    case node_type::string: return node{generate_string()};
    // cases below availabe only if current_depth <= max_depth
    case node_type::seq:    return node{generate_seq(++current_depth, max_depth)};
    case node_type::map:    return node{generate_map(++current_depth, max_depth)};

    default:
        throw std::logic_error("error with generator");
    }
}

extern json generate_json(std::size_t elements, std::size_t max_depth)
{
    return json{generate_map(0, max_depth, elements)};
}



}
