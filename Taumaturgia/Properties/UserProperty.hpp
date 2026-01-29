#pragma once
#include "Constructors.hpp"
#include "GetFeatures.hpp"
#include "Structs/PropertyData.hpp"
#include "Taumaturgia/Properties/access_features.hpp"

#include "Taumaturgia/Properties/Helpers/Tags.hpp"

namespace impl {

// MARK: UserProperty_

template <typename TYPE, typename T, isTag TAGS>
// requires(not std::is_reference_v<T>)
class UserProperty_;

template <typename TYPE, isTag TAGS>
struct PropertyFor {
    template <typename TARGET>
    using type = UserProperty_<TYPE, TARGET, TAGS>;
};  // may be specialized to replacing UserProperty_

// MARK: UserProperty_ for T

template <typename TYPE, typename T, isTag TAGS = Tags<>>
// requires(not std::is_reference_v<T>)
class UserProperty_ : public GetFeatures<UserProperty_<TYPE, T, TAGS>>,
                      public Constructors<UserProperty_<TYPE, T, TAGS>> {
public:
    using property_data = PropertyData<PropertyFor<TYPE, TAGS>::template type,
                                       T,
                                       TAGS>;             // ? should add TYPE into PropertyData?
    using improvement_of = UserProperty_<TYPE, T, TAGS>;  // will act like same type if TYPE and Tags are same
    using hold_type = TYPE;

    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::getType;
    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::haveTypeNum;
    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::getTypeTaged;
    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::getTypeOf;
    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::getTypeOfSignature;
    using GetFeatures<UserProperty_<TYPE, T, TAGS>>::getTaged;

    using Constructors<UserProperty_<TYPE, T, TAGS>>::Constructors;

    friend GetFeatures<UserProperty_<TYPE, T, TAGS>>;
};

}  // namespace impl

namespace impl::Test {
struct UserProperty_Test {};
using type = int;
using tested_type = UserProperty_<type, UserProperty_Test, Tags<>>;
using tested_tag = UserProperty_<type, tag, Tags<>>;

static_assert(trait_accessable<tested_type, type>);
static_assert(trait_accessable<tested_tag, type>);

static_assert(getType_able<tested_type, type>);

// static_assert(have_all_get_features_for_type<tested_type, type>);

}  // namespace impl::Test

#include "Helpers/derived_from_property.hpp"

template <typename TYPE, typename T, isTag TAGS = Tags<>>
using UserProperty = std::conditional_t<
    (trait_accessable<T, TYPE> and  //
     (is_getTypeTaged_valid<T, TYPE, TAGS>)),
    T,
    impl::UserProperty_<TYPE, T, TAGS>>;

template <typename TYPE, isTag TAGS = Tags<>>
struct UserPropertyAdapter {
    template <typename T>
    using apply = impl::UserProperty_<TYPE, T, TAGS>;

    template <typename T>
    using once = UserProperty<TYPE, T, TAGS>;
};

template <template <typename> typename property>
using property_t = Property_ordered<property>::hold_type;

// TODO: check is this needed?
// template <typename TYPE, typename T>
// struct UserStrategy_<TYPE, impl::UserProperty_<TYPE, T>> : public UserStrategy_<TYPE, T> {};  // forward eventualy implemented strategy
