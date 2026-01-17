//
// Created by Sid B on 06/01/26.
//

#include "../../headers/intermediate/parser.h"

#include <print>

BLSL::Token BLSL::Parser::_peek() const
{
    if (_pos != _tokens->size())
    {
        return _tokens->at(_pos);
    }

    return _tokens->back();
}

BLSL::Token BLSL::Parser::_next()
{
    if (_pos != _tokens->size())
    {
        return _tokens->at(_pos++);
    }

    return _tokens->back();
}

std::expected<BLSL::OperatorType, BLSL::Token> BLSL::Parser::_peek_operator() const
{
    auto token = _peek();
    if (token.type == TokenType::OPERATOR)
    {
        return std::get<OperatorType>(token.subType);
    }

    return std::unexpected(token);
}

std::expected<BLSL::Node_t, BLSL::Token> BLSL::Parser::_get_atom()
{
    if (_peek().type == TokenType::LITERAL)
    {
        Token token = _next();
        ASTNode::Literal literal;
        literal.debugPos = token.debugPos;
        literal.value = token.value.value();
        literal.type = std::get<LiteralType>(token.subType);

        return std::make_unique<ASTNode::Literal>(literal);
    }

    if (_peek().type == TokenType::IDENTIFIER)
    {
        Token token = _next();
        ASTNode::Variable variable;
        variable.debugPos = token.debugPos;
        variable.identifier = token.value.value();

        return std::make_unique<ASTNode::Variable>(variable);
    }

    return std::unexpected(_peek());
}

std::expected<std::unique_ptr<BLSL::ASTNode::BinaryOperator>, BLSL::Token> BLSL::Parser::_get_operator()
{
    if (_peek().type == TokenType::OPERATOR)
    {
        Token token = _next();
        ASTNode::BinaryOperator op;
        op.debugPos = token.debugPos;
        op.type = std::get<OperatorType>(token.subType);

        return std::make_unique<ASTNode::BinaryOperator>(std::move(op));
    }
}


BLSL::Node_t BLSL::Parser::_parse_expression(int lowestPrecedence)
{
    Node_t LHS;

    if (_peek().type == TokenType::PUNCTUATOR)
    {
        if (std::get<PunctuatorType>(_peek().subType) == PunctuatorType::LPAREN)
        {
            _next();

            LHS = _parse_expression();
        }
        else
        {
            throw;
        }
    }
    else if (_peek().type == TokenType::OPERATOR)
    {
        if (PREFIX_PRECEDENCE.contains(std::get<OperatorType>(_peek().subType)))
        {
            auto token = _next();
            ASTNode::UnaryOperator unaryOperator;
            unaryOperator.debugPos = token.debugPos;
            unaryOperator.type = std::get<OperatorType>(token.subType);

            unaryOperator.right = _parse_expression(PREFIX_PRECEDENCE.at(std::get<OperatorType>(token.subType)));

            return std::make_unique<ASTNode::UnaryOperator>(std::move(unaryOperator));
        }
    }
    else
    {
        auto LHSExpected = _get_atom();
        if (!LHSExpected.has_value())
        {
            //TODO: Errors. std::print("{}", LHSExpected.error());
            throw;
        }

        LHS = std::move(LHSExpected.value());
    }



    while (true)
    {
        if (_peek().type == TokenType::PUNCTUATOR)
        {
            if (std::get<PunctuatorType>(_peek().subType) == PunctuatorType::RPAREN)
            {
                _next();
                break;
            }
        }

        auto opExpected = _peek_operator();
        if (!opExpected.has_value()) break;

        auto [leftPrecedence, rightPrecedence] = OPERATOR_PRECEDENCE.at(opExpected.value());
        if (leftPrecedence < lowestPrecedence) break;

        auto op = _get_operator().value();

        auto RHS = _parse_expression(rightPrecedence);

        op->left = std::move(LHS);
        op->right = std::move(RHS);

        LHS = std::move(op);

    }

    return std::move(LHS);
}

BLSL::Parser::Parser(std::unique_ptr<std::vector<Token>> in)
    : _tokens(std::move(in)), _pos(0)
{

}

BLSL::Node_t BLSL::Parser::parse()
{
    //TODO: Actual parser
    return _parse_expression();
}
