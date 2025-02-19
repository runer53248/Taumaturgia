#pragma once

auto type_4 =
    Empty{}                                    //
    | With::user_property<int>                 //
    | With::user_property<std::string>         //
    | With::user_property<std::string, Empty>  //
    | Create;                                  //
