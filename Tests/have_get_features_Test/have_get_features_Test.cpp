#include "Taumaturgia/Properties/Helpers/have_get_features.hpp"
#include <gtest/gtest.h>
#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

template <typename R>
struct TypeValidMethods {
private:
    R value{};

public:
    template <typename T, size_t S = 0, typename Self>
        requires(S == 0)
    decltype(auto) getType(this Self& self) {
        return (self.value);
    }

    template <size_t S = 0, typename Self>
        requires(S == 0)
    decltype(auto) getType(this Self& self) {
        return (self.value);
    }

    template <typename T, typename... Tags, typename Self>
        requires(sizeof...(Tags) == 0 and (std::same_as<T, R> or traits::helpers::convertible_to<R, T>))
    decltype(auto) getTypeTaged(this Self& self) {
        return (self.value);
    }

    template <size_t Skip = 0, typename... Tags, typename Self>
        requires(sizeof...(Tags) == 0 and Skip == 0)
    decltype(auto) getTaged(this Self& self) {
        return (self.value);
    }

    template <typename RETURN, typename... TTags, typename Self>
    decltype(auto) getTypeOf(this Self& self, [[maybe_unused]] list<RETURN, TTags...> signature) {
        return (self.value);
    }

    template <typename Signature, typename Self>
        requires have_getTypeOf_method<Self, Signature>
    decltype(auto) getTypeOfSignature(this Self& self) {
        return self.getTypeOf(Signature{});
    }
};

static_assert(have_getType_type_method<TypeValidMethods<int>, int>);
static_assert(have_getType_num_method<TypeValidMethods<int>, 0>);
static_assert(have_getType_type_num_method<TypeValidMethods<int>, int, 0>);
static_assert(have_getTypeTaged_method<TypeValidMethods<int>, int>);
static_assert(have_getTaged_method<TypeValidMethods<int>, 0>);
static_assert(have_getTypeOf_method<TypeValidMethods<int>, list<int>>);
static_assert(have_all_get_features_for_type<TypeValidMethods<int>, int>);

static_assert(have_getType_type_method<TypeValidMethods<Data<int, struct test_tag>>, int>);
static_assert(have_getType_num_method<TypeValidMethods<Data<int, struct test_tag>>, 0>);
static_assert(have_getType_type_num_method<TypeValidMethods<Data<int, struct test_tag>>, int, 0>);
static_assert(have_getTypeTaged_method<TypeValidMethods<Data<int, struct test_tag>>, int>);
static_assert(have_getTaged_method<TypeValidMethods<Data<int, struct test_tag>>, 0>);
static_assert(have_getTypeOf_method<TypeValidMethods<Data<int, struct test_tag>>, list<int>>);
static_assert(have_all_get_features_for_type<TypeValidMethods<Data<int, struct test_tag>>, int>);

using TypeValidMethods_2 = decltype(From::base<empty_type>  //
                                    | With::user_property<int>)::result_type;

static_assert(have_getType_type_method<TypeValidMethods_2, int>);
static_assert(have_getType_num_method<TypeValidMethods_2, 0>);
static_assert(have_getType_type_num_method<TypeValidMethods_2, int, 0>);
static_assert(have_getTypeTaged_method<TypeValidMethods_2, int>);
static_assert(have_getTaged_method<TypeValidMethods_2, 0>);
static_assert(have_getTypeOf_method<TypeValidMethods_2, list<int>>);
static_assert(have_all_get_features_for_type<TypeValidMethods_2, int>);

using TypeValidMethods_3 = decltype(From::base<empty_type>  //
                                    | With::user_property<int, struct test_tag>)::result_type;

static_assert(have_getType_type_method<TypeValidMethods_3, int>);
static_assert(have_getType_num_method<TypeValidMethods_3, 0>);
static_assert(have_getType_type_num_method<TypeValidMethods_3, int, 0>);
static_assert(have_getTypeTaged_method<TypeValidMethods_3, int, test_tag>);
static_assert(have_getTaged_method<TypeValidMethods_3, 0, test_tag>);
static_assert(have_getTypeOf_method<TypeValidMethods_3, list<int, test_tag>>);
static_assert(have_all_get_features_for_type<TypeValidMethods_3, int, test_tag>);

using TypeValidMethods_4 = decltype(From::base<empty_type>  //
                                    | With::user_property<int, struct test_tag, struct test_tag_2>)::result_type;

static_assert(have_getType_type_method<TypeValidMethods_4, int>);
static_assert(have_getType_num_method<TypeValidMethods_4, 0>);
static_assert(have_getType_type_num_method<TypeValidMethods_4, int, 0>);
static_assert(have_getTypeTaged_method<TypeValidMethods_4, int, test_tag, test_tag_2>);
static_assert(have_getTaged_method<TypeValidMethods_4, 0, test_tag, test_tag_2>);
static_assert(have_getTypeOf_method<TypeValidMethods_4, list<int, test_tag, test_tag_2>>);
static_assert(have_all_get_features_for_type<TypeValidMethods_4, int, test_tag, test_tag_2>);

using TypeValidMethods_5 = decltype(From::base<TypeValidMethods<int>>  //
                                    | With::user_property<int, struct test_tag>)::result_type;

using TypeValidMethods_6 = decltype(From::base<TypeValidMethods<Data<int>>>  //
                                    | With::user_property<int, struct test_tag>)::result_type;

using TypeValidMethods_7 = decltype(From::base<TypeValidMethods<Data<int, struct test_tag, struct test_tag_2>>>  //
                                    | With::user_property<int, struct test_tag, struct test_tag_2>)::result_type;

int main() {
    std::cout << parse_type_name<TypeValidMethods_5>() << '\n';
    std::cout << parse_type_name<TypeValidMethods_6>() << '\n';
    std::cout << parse_type_name<TypeValidMethods_7>() << '\n';

    // std::cout << name<TypeValidMethods_6>() << '\n';
    // using base_type = typename helpers::Scheme_ordered<TypeValidMethods_6>::base;
    // std::cout << name<base_type>() << '\n';
}
