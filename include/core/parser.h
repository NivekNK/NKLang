#pragma once

#include "core/defines.h"
#include "core/json.h"

namespace nk {
    struct Program {
        virtual ~Program() = default;
        virtual json to_json() const = 0;
    };

    struct NumericLiteral : public Program {
        i32 value;

        NumericLiteral(i32 value) : value(value) {}

        virtual json to_json() const override {
            return {
                {"type", "NumericLiteral"},
                {"value", value}
            };
        }
    };

    class Parser {
    public:
        Parser() = default;
        ~Parser();

        Program* parse(std::string string);

    private:
        std::string string;
    };
} // namespace nk
