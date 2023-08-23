#include "nkpch.h"

#include "core/lexer.h"
#include "core/parser.h"

int main(void) {
    nk::LoggingSystem::init(nk::LoggingPriority::Trace);

    auto parser = new nk::Parser();
    auto program = R"(
        "asdasd"
    )";
    auto ast = parser->parse(program);

    std::cout << ast->to_json().dump(4) << std::endl;

    delete ast;
    delete parser;

    return 0;
}
