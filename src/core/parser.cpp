#include "nkpch.h"

#include "core/parser.h"

namespace nk {
    Parser::~Parser() {}

    Program* Parser::parse(std::string string) {
        this->string = string;
        return new NumericLiteral(std::stoi(string));
    }
} // namespace nk
