#include "nkpch.h"

#include "core/lexer.h"
#include "core/parser.h"

// #include <thread>

#include "system/file_system.h"

// void log_test(int i) { InfoLog("{}", i); }

int main(void) {
    auto file =
        nk::File::open("test_logs/test.txt", nk::FileMode::ReadAndWrite);

    for (auto line : file->read_all_lines()) {
        std::cout << line << std::endl;
    }

    // nk::LoggingSystem::init(nk::LoggingPriority::Trace);
    //
    // std::thread threads[10];
    //
    // for (i32 i = 0; i < 10; i++)
    //     threads[i] = std::thread(log_test, i);
    //
    // for (i32 i = 0; i < 10; i++)
    //     threads[i].join();

    // auto parser = new nk::Parser();
    // auto program = R"(
    //     "asdasd"
    // )";
    // auto ast = parser->parse(program);
    //
    // std::cout << ast->to_json().dump(4) << std::endl;
    //
    // delete ast;
    // delete parser;

    return 0;
}
