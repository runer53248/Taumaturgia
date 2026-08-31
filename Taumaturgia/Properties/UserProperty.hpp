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

template <typename TYPE, typename T, isTag TAGS = no_tag>
// requires(not std::is_reference_v<T>)
class UserProperty_ : public GetFeatures<UserProperty_<TYPE, T, TAGS>>,
                      public Constructors<UserProperty_<TYPE, T, TAGS>> {
private:
    using features_type = GetFeatures<UserProperty_<TYPE, T, TAGS>>;
    using constructors_type = Constructors<UserProperty_<TYPE, T, TAGS>>;

public:
    using property_data = PropertyData<PropertyFor<TYPE, TAGS>::template type,
                                       T,
                                       TAGS>;                                             // ? should add TYPE into PropertyData?
    using improvement_of = features_type::improvement_of;  // will act like same type if TYPE and Tags are same
    using hold_type = constructors_type::hold_type;

    using features_type::getType;
    using features_type::haveTypeNum;
    using features_type::getTypeTaged;
    using features_type::getTypeOf;
    using features_type::getTypeOfSignature;
    using features_type::getTaged;

    using constructors_type::Constructors;

    friend features_type;
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

template <typename TYPE, typename T, isTag TAGS = no_tag>
using UserProperty = std::conditional_t<
    (trait_accessable<T, TYPE> and  //
     (is_getTypeTaged_valid<T, TYPE, TAGS>)),
    T,
    impl::UserProperty_<TYPE, T, TAGS>>;

template <typename TYPE, isTag TAGS = no_tag>
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
