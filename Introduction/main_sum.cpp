#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Core {
    template <size_t S = 0, typename Self>
        requires(S < 2)
    decltype(auto) getType(this Self& self) {
        std::print("[A]");
        if constexpr (S == 0) {
            return (self.i);
        } else {
            return (self.f);
        }
    }

    template <typename TYPE, size_t S = 0, typename Self>
        requires(boost::mp11::mp_contains<list<int, float>, TYPE>::value and S == 0)
    decltype(auto) getType(this Self& self) {
        std::print("[B]");
        if constexpr (std::same_as<TYPE, int>) {
            return (self.i);
        } else {
            return (self.f);
        }
    }

    template <typename Self>
    decltype(auto) get_int(this Self& self) {
        std::print("[C]");
        return (self.i);
    }
    template <typename Self>
    decltype(auto) get_float(this Self& self) {
        std::print("[C]");
        return (self.f);
    }

private:
    int i{1};
    float f{1.1f};
};

template <typename T>
    requires std::is_base_of_v<Core, T>
struct HoldTypes<T> {
    using types = list<int, float>;
};

template <typename TYPE, typename T>
    requires std::is_base_of_v<Core, T>
struct traits::CustomAccessType<TYPE, T> {
    static constexpr decltype(auto) get(auto& el)
        requires std::same_as<TYPE, int>
    {
        return (el.get_int());
    }

    static constexpr decltype(auto) get(auto& el)
        requires std::same_as<TYPE, float>
    {
        return (el.get_float());
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
                     forTags<>(33.333f),
                     forTags<>(15),
                     forTags<Tags<void>>(25),
                     forTags<Tags<int>>(35)};

    std::println();
    std::println("[A] - Core::getType<0>");
    std::println("[B] - Core::getType<int, 0>");
    std::println("[C] - traits::CustomAccessType<int, T>");
    std::println();
    std::println(" getTypeTaged<int>(type)              {}", getTypeTaged<int>(type));
    std::println("[ ] getTypeTaged<int, Tags<void>>(type)  {}", getTypeTaged<int, Tags<void>>(type));
    std::println("[ ] getTypeTaged<int, Tags<int>(type)    {}", getTypeTaged<int, Tags<int>>(type));
    std::println();
    std::println(" type.getType<6>()                    {}", type.getType<6>());
    std::println(" getType<6>(type)                     {}", getType<6>(type));
    std::println(" getType<7>(type)                     {}", getType<7>(type));
    std::println("---");
    std::println(" type.getType<int, 2>()               {}", type.getType<int, 2>());
    std::println("[ ] getType<int, 0>(type)                {}", getType<int, 0>(type));
    std::println("[ ] getType<int, 1>(type)                {}", getType<int, 1>(type));
    std::println(" getType<int, 2>(type)                {}", getType<int, 2>(type));
    std::println(" getType<float, 0>(type)              {}", getType<float, 0>(type));
    std::println("---");
    std::println(" traits::accessType<int>::get(type)   {}", traits::accessType<int>::get(type));
    std::println(" traits::accessType<float>::get(type) {}", traits::accessType<float>::get(type));
    std::println("---");
    std::println();

    using tp = as_tuple<result_type>;
    std::println("as_tuple<result_type> : {}", name<tp>());
    std::println("as_tuple<Core>        : {}", name<as_tuple<Core>>());
    std::println("---");
    std::println("getType_index_limit<result_type> = {}", getType_index_limit<result_type>);
    std::println("std::tuple_size_v<tp>            = {}", std::tuple_size_v<tp>);
    std::println();

    Core core{};
    std::println("getType_index_limit<Core>  :    {}", getType_index_limit<Core>);
    std::println("---");
    std::println(" getType<0>(core)       {}", getType<0>(core));
    std::println(" getType<1>(core)       {}", getType<1>(core));
    std::println(" getType<2>(core)       {}", getType<2>(core));
    std::println(" getType<3>(core)       {}", getType<3>(core));
    std::println("---");
    std::println(" getType<int>(core)     {}", getType<int>(core));
    std::println(" getType<float>(core)   {}", getType<float>(core));
}
