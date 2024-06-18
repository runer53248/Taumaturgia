#pragma once
#include "Taumaturgia/Strategies/Helpers/Whom.hpp"
#include "Taumaturgia/Strategies/Strategies.hpp"

#include "Behaviors/default_behaviors.hpp"

#include "DefaultGetStrategy.hpp"  //

#ifdef NO_PREMADE_STRATEGIES
#include "Taumaturgia/User/UserDefaultStrategies.hpp"
#else
#include "Premade/PremadeDefaultStrategies.hpp"
#endif
