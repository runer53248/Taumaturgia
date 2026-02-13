#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Core {
    template <size_t S = 0, typename Self>
        requires(S == 0)
    decltype(auto) getType(this Self& self) {
        std::print("[A]");
        return (self.type);
    }

    template <typename TYPE, size_t S, typename Self>
        requires (std::same_as<TYPE, int> and S == 0)
    decltype(auto) getType(this Self& self) {
        std::print("[C]");
        return (self.type);
    }

    template <typename Self>
    decltype(auto) get_int(this Self& self) {
        std::print("[B]");
        return (self.type);
    }

private:
    int type{};
};

template <typename T>
    requires std::is_base_of_v<Core, T>
struct traits::CustomAccessType<int, T> {
    static constexpr decltype(auto) get(auto& el) {
        return (el.get_int());
    }
};

template <typename T1, typename T2>
    requires std::same_as<
        typename helpers::Scheme_ordered<T1>::base,
        typename helpers::Scheme_ordered<T2>::base>
struct sum_impl {
    using base = typename helpers::Scheme_ordered<T1>::base;

    using result =
        helpers::build_into_t<
            base,
            helpers::append_and_order_property_lists<
                typename helpers::Scheme_ordered<T1>::list_t,
                typename helpers::Scheme_ordered<T2>::list_t>>;
};

template <typename T1, typename T2>
using sum_type = sum_impl<T1, T2>::result;

template <auto T>
using as_type = decltype(T)::result_type;

int main() {
    using type1 = as_type<From::base<Core>                        //
                          | With::CureHealth                      //
                          | With::Damage                          //
                          | With::user_property<int, Tags<void>>  //
                          | With::user_property<int, Tags<int>>   //
                          | With::user_property<int>              //
                          >;
    using type2 = as_type<From::base<Core>                        //
                          | With::Health                          //
                          | With::Protection                      //
                          | With::user_property<int, Tags<int>>   //
                          | With::user_property<int, Tags<void>>  //
                          | With::user_property<int>              //
                          >;

    using result_type = sum_type<type1, type2>;

    std::println("{}", parse_type_name<result_type>());

    result_type type{unordered,
                     forTags<>(15),
                     forTags<Tags<void>>(25),
                     forTags<Tags<int>>(35)};

    std::println();
    std::println("[A] - Core::getType<0>");
    std::println("[B] - traits::CustomAccessType<int, T>");
    std::println("[C] - Core::getType<int, 0>");
    std::println();
    std::println(" getTypeTaged<int>(type)             {}", getTypeTaged<int>(type));
    std::println("[ ] getTypeTaged<int, Tags<void>>(type) {}", getTypeTaged<int, Tags<void>>(type));
    std::println("[ ] getTypeTaged<int, Tags<int>(type)   {}", getTypeTaged<int, Tags<int>>(type));
    std::println();
    std::println(" type.getType<6>()                   {}", type.getType<6>());
    std::println(" getType<6>(type)                    {}", getType<6>(type));
    std::println(" traits::accessType<int>::get(type)  {}", traits::accessType<int>::get(type));
    std::println(" type.getType<int, 2>()              {}", type.getType<int, 2>());
    std::println();

    using tp = as_tuple<result_type>;
    std::println("{}", name<tp>());
}
