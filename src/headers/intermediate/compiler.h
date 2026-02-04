//
// Created by Sid B on 06/01/26.
//

#ifndef BLSLANG_COMPILER_H
#define BLSLANG_COMPILER_H

#include <memory>

#include "astnodes.h"
#include "../core/blsbyc.h"

namespace BLSL
{
    namespace Precursor
    {
        enum class OperandType
        {
            VIRTUAL_REGISTER,
            COMPILE_TIME_SIZE,
            LITERAL,
            VARIABLE
        };
        struct Operand
        {
            OperandType type;
            size_t index;
        };
        struct Instruction
        {
            BLSVM::Bytecode::OpCode opCode;
            Operand a;
            Operand b;
            Operand c;
            BLSVM::Bytecode::flag_t flags;
        };

    }

    class Flattener : public ASTNode::Visitor
    {
    private:
        size_t _virtualRegisterIndex;
        std::vector<Precursor::Instruction> _precursorBuffer;

        std::unordered_map<std::string, std::pair<size_t, size_t>> _variableMap;           // Identifier, {size, index}
        size_t _variableIndex;

        std::unordered_map<std::string, size_t> _literalMap;             // Literal, index
        size_t _literalIndex;

        std::unordered_map<size_t, size_t> _compileTimeSizes;            // csz, index
        size_t _compileTimeSizeIndex;

    private:
        Precursor::Operand _traverse_expression(ASTNode::Node* node);

    public:
        Flattener();
    public:
        void visit(ASTNode::Alloc *node) override;
        void visit(ASTNode::BinaryOperator *node) override;


    };
}


#endif //BLSLANG_COMPILER_H