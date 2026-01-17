#include <iostream>

#include <print>
#include <format>

#include "headers/core/blsl.h"
#include "headers/intermediate/lexer.h"
#include "headers/intermediate/parser.h"

int main()
{
    BLSL::Lexer lexer;
    lexer.mount_source_from_file("../samples/expr.blsl");
    lexer.lex_to_file("../samples/out.blslex");

    lexer.mount_source_from_file("../samples/expr.blsl");
    auto lexOut = lexer.lex();


    BLSL::Parser parser(std::move(lexOut));

    BLSL::Node_t parseOut = parser.parse();

    BLSL::ASTNode::PrintVisitor visitor("../samples/out.blsparse");

    //std::print("AST:\n");

    parseOut->invite(visitor);

    std::println("-- End --");
}

