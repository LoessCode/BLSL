#include <iostream>

#include <print>
#include <format>

#include "headers/core/blsl.h"
#include "headers/intermediate/lexer.h"

int main()
{
    BLSL::Lexer lexer;
    lexer.mount_source_from_file("../samples/operators.blsl");
    // auto out = lexer.lex();

    lexer.lex_to_file("../samples/out.blslex");

}
