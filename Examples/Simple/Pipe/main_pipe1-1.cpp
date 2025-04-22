#define CUSTOM_ORDER_LIST

#ifdef CUSTOM_ORDER_LIST
#define ORDER_LIST_PATH "Examples/Simple/Pipe/custom_order_list.hpp"
#endif

#include "Usage/With.hpp"
#include "default_values.hpp"
#include "print.hpp"

struct Example {
    auto getFloat(size_t index = 0) { return float_[index % 2]; }
    auto getOtherDamage() { return dmg_; }

    template <typename RETURN, size_t SIZE = 0>
    constexpr decltype(auto) getType(this auto&& self) {
        if constexpr (std::same_as<RETURN, std::string>) {
            return (self.test_);
        } else if constexpr (std::same_as<RETURN, float>) {
            return (self.float_[SIZE % 2]);
        } else {
            return;
        }
    }

private:
    Damage dmg_{50, DamageType::Divine};
    std::array<float, 2> float_{3.1113f, 0.5f};
    std::string test_{"ok"};
};

int main() {
    {
        auto create_type =
            From::base<Example>           //
            | With::Damage                //
            | With::Name                  //
            | With::Protection            //
            | With::Protection            //
            | With::property<Protecting>  //
            | With::Health                // not in priority order
            | With::user_property<int>    //
            ;

        auto type = create_type(  // order as property priority
            Name{"Type"},
            Health{300, 300},
            Damage{5, DamageType::Physical},
            Protection{10, BodyLocation::Legs},
            15);

        type = create_type(
            unordered,  // order ignored
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical},
            Health{300, 300},
            Name{"Type"});

        std::cout << "create_type= " << name<decltype(create_type)>() << '\n'
                  << '\n';

        std::cout << '\n';
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "int        = " << trait<int>::get(type) << '\n';
        std::cout << "float      = " << trait<float>::get(type) << '\n';
        std::cout << "string     = " << trait<std::string>::get(type) << '\n';

        std::cout << "float acces= " << trait_accessable<decltype(type), float> << '\n';

        std::cout << "float 0    = " << type.getType<float, 0>() << '\n';
        std::cout << "float 1    = " << type.getType<float, 1>() << '\n';
        std::cout << "string     = " << type.getType<std::string>() << '\n';
#ifndef NO_PREMADE_PROPERTIES
        std::cout << "Name       = " << type.getName() << '\n';
        std::cout << "Health     = " << type.getHealth() << '\n';
        std::cout << "Damage     = " << type.getDamage() << '\n';
        std::cout << "Protection = " << type.getProtection() << '\n';
#else
        std::cout << "Name       = " << type.getType<Name>() << '\n';
        std::cout << "Health     = " << type.getType<Health>() << '\n';
        std::cout << "Damage     = " << type.getType<Damage>() << '\n';
        std::cout << "Protection = " << type.getType<Protection>() << '\n';
#endif
        std::cout << "int        = " << type.getType<int>() << '\n';
        std::cout << "float 0    = " << type.getFloat(0) << '\n';
        std::cout << "float 1    = " << type.getFloat(1) << '\n';
        std::cout << "dmg other  = " << type.getOtherDamage() << '\n';
        std::cout << '\n';
    }

    {
        auto create_type =
            From::base<Example>                    //
            | WithUnordered::Damage                //
            | WithUnordered::Name                  //
            | WithUnordered::Protection            //
            | WithUnordered::Protection            //
            | WithUnordered::property<Protecting>  //
            | WithUnordered::Health                // not in priority order
            | WithUnordered::user_property<int>    //
            ;

        auto type = create_type(  // ordered as given in create_type
            Damage{5, DamageType::Physical},
            Name{"Type"},
            Protection{10, BodyLocation::Legs},
            Health{300, 300},
            15);

        type = create_type(  // ordered as given in create_type (variation)
            Name{"Type"},
            Damage{5, DamageType::Physical},
            Protection{10, BodyLocation::Legs},
            Health{300, 300},
            15);

        type = create_type(
            unordered,  // order ignored
            15,
            Protection{10, BodyLocation::Legs},
            Damage{5, DamageType::Physical},
            Health{300, 300},
            Name{"Type"});

        std::cout << "create_type= " << name<decltype(create_type)>() << '\n'
                  << '\n';

        std::cout << '\n';
        std::cout << "type       = " << name<decltype(type)>() << '\n';
        std::cout << "Name       = " << trait<Name>::get(type) << '\n';
        std::cout << "Health     = " << trait<Health>::get(type) << '\n';
        std::cout << "Damage     = " << trait<Damage>::get(type) << '\n';
        std::cout << "Protection = " << trait<Protection>::get(type) << '\n';
        std::cout << "int        = " << trait<int>::get(type) << '\n';
        std::cout << "float      = " << trait<float>::get(type) << '\n';
        std::cout << "string     = " << trait<std::string>::get(type) << '\n';

        std::cout << "float acces= " << trait_accessable<decltype(type), float> << '\n';

        std::cout << "float 0    = " << type.getType<float, 0>() << '\n';
        std::cout << "float 1    = " << type.getType<float, 1>() << '\n';
        std::cout << "string     = " << type.getType<std::string>() << '\n';
#ifndef NO_PREMADE_PROPERTIES
        std::cout << "Name       = " << type.getName() << '\n';
        std::cout << "Health     = " << type.getHealth() << '\n';
        std::cout << "Damage     = " << type.getDamage() << '\n';
        std::cout << "Protection = " << type.getProtection() << '\n';
#else
        std::cout << "Name       = " << type.getType<Name>() << '\n';
        std::cout << "Health     = " << type.getType<Health>() << '\n';
        std::cout << "Damage     = " << type.getType<Damage>() << '\n';
        std::cout << "Protection = " << type.getType<Protection>() << '\n';
#endif
        std::cout << "int        = " << type.getType<int>() << '\n';
        std::cout << "float 0    = " << type.getFloat(0) << '\n';
        std::cout << "float 1    = " << type.getFloat(1) << '\n';
        std::cout << "dmg other  = " << type.getOtherDamage() << '\n';
        std::cout << '\n';
    }
}
