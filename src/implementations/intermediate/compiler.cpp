//
// Created by Sid B on 06/01/26.
//

#include "../../headers/intermediate/compiler.h"

#include "../../headers/runtime/vm.h"

static const std::unordered_map<BLSL::OperatorType, BLSVM::Bytecode::OpCode> OPERATOR_OPCODE_MAP = {
    {BLSL::OperatorType::UNSIGNED_ADD, BLSVM::Bytecode::OpCode::UNSIGNED_ADD}
}; //TODO COMPLETE

BLSL::Compiler::Compiler()
    : _virtualRegisterCounter(0), _compileTimeSizeCounter(0)
{

}

void BLSL::Compiler::visit(ASTNode::Alloc *node)
{
    _variableMap.emplace(node->identifier, node->size);

    size_t index = _compileTimeSizes.contains(node->size) ? index = _compileTimeSizes[node->size] : _compileTimeSizeCounter++;

    BLSVM::Bytecode::instruction_t instruction = BLSVM::Bytecode::make_instruction(
        static_cast<BLSVM::Bytecode::opcode_t>(BLSVM::Bytecode::OpCode::ALLOC_STACK),
        static_cast<BLSVM::Bytecode::operand_t>(index & (~BLSVM::Bytecode::OPND_TYPE_MASK))
    );

    //TODO HEAP ALLOCATIONS!

    _outBuffer.emplace_back(instruction);
}

void BLSL::Compiler::visit(ASTNode::BinaryOperator *node)
{
    BLSVM::Bytecode::operand_t LHS;
    BLSVM::Bytecode::operand_t RHS;

    if (auto literal = dynamic_cast<ASTNode::Literal*>(node->left.get()))
    {

    }
    //TODO COMPLETE

    BLSVM::Bytecode::operand_t dest = static_cast<BLSVM::Bytecode::operand_t>(_virtualRegisterCounter++) | BLSVM::Bytecode::OPND_TYPE_MASK;

    BLSVM::Bytecode::instruction_t instruction = BLSVM::Bytecode::make_instruction(
        static_cast<BLSVM::Bytecode::opcode_t>()
    );
}
