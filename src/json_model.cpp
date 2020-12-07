#include "json_model.hpp"
#include <ostream>
#include <variant>

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

}
