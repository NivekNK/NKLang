#include "nkpch.h"

#include "core/parser.h"

int main(void) {
    std::string string = "42";
    nk::Parser parser;

    auto program = parser.parse(string);
    std::cout << program->to_json().dump(4) << std::endl;

    delete program;

    return 0;
}
