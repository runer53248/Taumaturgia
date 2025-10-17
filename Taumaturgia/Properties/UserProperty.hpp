#pragma once
#include "GetFeatures.hpp"
#include "Constructors.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/access_features.hpp"

namespace impl {

// MARK: UserProperty_

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename TYPE, typename... Tags>
struct PropertyFor {
    template <typename TARGET>
    using type = UserProperty_<TYPE, TARGET, Tags...>;
};  // may be specialized to replacing UserProperty_

// MARK: UserProperty_ for T

template <typename TYPE, typename T, typename... Tags>
// requires(not std::is_reference_v<T>)
class UserProperty_ : public GetFeatures<UserProperty_<TYPE, T, Tags...>>,
                      public Constructors<UserProperty_<TYPE, T, Tags...>> {
public:
    using property_data = PropertyData<PropertyFor<TYPE, Tags...>::template type,
                                       T,
                                       Tags...>;             // ? should add TYPE into PropertyData?
    using improvement_of = UserProperty_<TYPE, T, Tags...>;  // will act like same type if TYPE and Tags are same
    using hold_type = TYPE;

    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::getType;
    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::haveTypeNum;
    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::getTypeTaged;
    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::getTypeOf;
    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::getTypeOfSignature;
    using GetFeatures<UserProperty_<TYPE, T, Tags...>>::getTaged;

    using Constructors<UserProperty_<TYPE, T, Tags...>>::Constructors;
};

}  // namespace impl

namespace impl::Test {
struct UserProperty_Test {};
using type = int;
using tested_type = UserProperty_<type, UserProperty_Test>;
using tested_tag = UserProperty_<type, tag>;

static_assert(trait_accessable<tested_type, type>);
static_assert(trait_accessable<tested_tag, type>);

static_assert(getType_able<tested_type, type>);

static_assert(have_all_get_features_for_type<tested_type, type>);

}  // namespace impl::Test

#include "Helpers/derived_from_property.hpp"

template <typename TYPE, typename T, typename... Tags>
using UserProperty = std::conditional_t<
    (trait_accessable<T, TYPE> and  //
     (is_getTypeTaged_valid<T, TYPE, Tags...>)),
    T,
    impl::UserProperty_<TYPE, T, Tags...>>;

template <typename TYPE, typename... Tags>
struct UserPropertyAdapter {
    template <typename T>
    using apply = impl::UserProperty_<TYPE, T, Tags...>;

    template <typename T>
    using once = UserProperty<TYPE, T, Tags...>;
};

template <template <typename> typename property>
using property_t = Property_ordered<property>::hold_type;

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
