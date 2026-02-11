#include <boost/pfr.hpp>
#include <print>
#include <utility>
#include "Examples/PreetyPrint/preety_print_types.hpp"
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Core {
    template <size_t S = 0>
        requires(S == 0)
    decltype(auto) getType(this auto& self) {
        return (self.type);
    }
    template <typename T>
    decltype(auto) getType(this auto& self) = delete;

private:
    int type;
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
    using type1 = as_type<From::base<Core>                       //
                          | With::CureHealth                      //
                          | With::Damage                          //
                          | With::user_property<int, Tags<void>>  //
                          | With::user_property<int, Tags<int>>   //
                          | With::user_property<int>   //
                          >;
    using type2 = as_type<From::base<Core>                       //
                          | With::Health                          //
                          | With::Protection                      //
                          | With::user_property<int, Tags<int>>   //
                          | With::user_property<int, Tags<void>>  //
                          | With::user_property<int>  //
                          >;

    using result_type = sum_type<type1, type2>;

    std::println("{}", parse_type_name<result_type>());

    result_type type{unordered,
                     forTags<>(15),
                     forTags<Tags<void>>(25),
                     forTags<Tags<int>>(35)};

    std::println("{}", getTypeTaged<int>(type));
    std::println("{}", getTypeTaged<int, Tags<void>>(type));
    std::println("{}", getTypeTaged<int, Tags<int>>(type));
}
