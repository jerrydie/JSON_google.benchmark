#ifndef JSON_MODEL_HPP
#define JSON_MODEL_HPP

#include <ostream>
#include <vector>
#include <string>
#include <map>
#include <variant>
#include <type_traits>

namespace hse::model {

enum class node_type
{
    null,
    bool_,
    int_,
    float_,
    string,
    seq,
    map
};

class node;


using seq_t = std::vector<node>;
using map_t = std::map<std::string, node>;

class node
{
public:
    constexpr node() = default;
    using storage_t = std::variant<std::monostate, bool, std::int64_t, double, std::string, seq_t, map_t>;
    template<typename T, typename = std::enable_if_t<std::is_constructible_v<storage_t, T>>>
    constexpr node(T x): data_(std::move(x)){}

    constexpr node_type type() const noexcept
    {
        return static_cast<node_type>(data_.index());
    }

    template<node_type Type>
    constexpr auto& get() &
    {
        return std::get<static_cast<std::size_t>(Type)>(data_);
    }


    template<node_type Type>
    constexpr const auto& get() const&
    {
        return std::get<static_cast<std::size_t>(Type)>(data_);
    }

    template<node_type Type>
    constexpr auto&& get() &&
    {
        return std::get<static_cast<std::size_t>(Type)>(std::move(data_));
    }

    friend std::ostream& operator<<(std::ostream& out, const node& n)
    {
        n.display(out, 0);
        return out;
    }

    void display(std::ostream&, std::size_t) const;
private:
    
    storage_t data_;
};

class json: public node
{

public:
    json(): node(map_t{}){};
    json(map_t obj): node(std::move(obj)){};
};

}
#endif // JSON_MODEL_HPP

