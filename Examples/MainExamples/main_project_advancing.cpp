#include "Introduction/parse_type_name.hpp"
#include "Usage/With.hpp"

struct Base {};

template <typename T>
using Integering = UserPropertyAdapter<int>::template once<T>;

namespace With {
[[maybe_unused]] constexpr Property<UserPropertyAdapter<int>::template once> Integer{};
}  // namespace With

int main() {
    // first version of adding properties
    using type_v1 = Damaging<Naming<Integering<Base>>>;

    // second version of adding properties
    using type_v2 = add_properties<Base,
                                   Property<Naming>,
                                   Property<Damaging>,
                                   Property<Integering>>;
    using type_v2b = add_properties_ordered<Base,
                                            Naming,
                                            Damaging,
                                            Integering>;

    // third versions of adding properties
    using type_v3a = decltype(From::base<Base>  //
                              | With::Name      //
                              | With::Damage    //
                              | With::Integer);
    using type_v3b = decltype(Base{}           //
                              | With::Name     //
                              | With::Damage   //
                              | With::Integer  //
                              | Create);
    list properties_list = With::Name | With::Damage | With::Integer;
    using type_v3c = decltype(Base{} | properties_list);

    [[maybe_unused]] type_v1 t1;
    [[maybe_unused]] type_v2 t2;
    [[maybe_unused]] type_v2b t2b;
    [[maybe_unused]] type_v3a::result_type t3a_1;
    [[maybe_unused]] auto t3a_2 = type_v3a::operator()();
    [[maybe_unused]] auto t3a_3 = type_v3a{}();
    [[maybe_unused]] type_v3b t3b;
    [[maybe_unused]] type_v3c t3c;

    using namespace std;

    cout << name<decltype(t1)>() << '\n';
    cout << name<decltype(t2)>() << '\n';
    cout << name<decltype(t2b)>() << '\n';
    cout << name<decltype(t3a_1)>() << '\n';
    cout << name<decltype(t3a_2)>() << '\n';
    cout << name<decltype(t3a_3)>() << '\n';
    cout << name<decltype(t3b)>() << '\n';
    cout << name<decltype(t3c)>() << '\n';

    static_assert(same_as<decltype(t1), decltype(t2)>);
    static_assert(same_as<decltype(t1), decltype(t2b)>);
    static_assert(same_as<decltype(t1), decltype(t3a_1)>);
    static_assert(same_as<decltype(t1), decltype(t3a_2)>);
    static_assert(same_as<decltype(t1), decltype(t3a_3)>);
    static_assert(same_as<decltype(t1), decltype(t3b)>);
    static_assert(same_as<decltype(t1), decltype(t3c)>);

    cout << parse_type_name<decltype(t1)>() << '\n';
}
