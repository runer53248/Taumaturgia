#pragma once
#include "Taumaturgia/Strategies/Helpers/Whom.hpp"
#include "Usage/Strategies.hpp"

#include "Taumaturgia/Strategies/Defaults/Behaviors/default_behaviors.hpp"
#include "Taumaturgia/Strategies/Defaults/DefaultGetStrategy.hpp"  //

#ifdef NO_PREMADE_STRATEGIES
#include "Usage/User/UserDefaultStrategies.hpp"
#else
#include "Usage/Premade/PremadeDefaultStrategies.hpp"
#endif
