#pragma once

using order_list = taged_list<
    Living,
    Wearing,
    Damaging,
    Protecting,
    Healing,
    Restoring,
    Naming  // should be last property to add (used closest to type)
    >;
