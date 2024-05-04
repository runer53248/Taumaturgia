#pragma once
#include <fstream>
#include <iostream>

class Redirect {
public:
    Redirect(const char* name)
        : out{std::string(name) + std::string("_out.txt")} {
        std::cout.rdbuf(out.rdbuf());
    }
    ~Redirect() {
        std::cout.rdbuf(coutbuf);
    }

    std::ofstream out;
    std::streambuf* coutbuf = std::cout.rdbuf();
};
