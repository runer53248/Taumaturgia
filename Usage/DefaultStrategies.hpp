#pragma once
#include "Taumaturgia/Strategies/Helpers/Whom.hpp"
#include "Strategies.hpp"

#include "default_behaviors.hpp"

#ifdef NO_PREMADE_STRATEGIES
#include "User/UserDefaultStrategies.hpp"
#else
#include "Premade/PremadeDefaultStrategies.hpp"
#endif

#include "Taumaturgia/Strategies/Defaults/DefaultGetterStrategy.hpp"  //
