//
// Created by Sid B on 06/01/26.
//

#include "../../headers/intermediate/compiler.h"

#include "../../headers/runtime/vm.h"

static const std::unordered_map<BLSL::OperatorType, BLSVM::Bytecode::OpCode> OPERATOR_OPCODE_MAP = {
    {BLSL::OperatorType::UNSIGNED_ADD, BLSVM::Bytecode::OpCode::UNSIGNED_ADD}
}; //TODO COMPLETE

BLSL::Compiler::Compiler()
    : _virtualRegisterCount(0), _variableCount(0), _literalCount(0), _compileTimeSizeCount(0)
{

}

void BLSL::Compiler::visit(ASTNode::Alloc *node)
{
    if (_variableMap.contains(node->identifier)) throw std::runtime_error("Variable mapping already exists"); //TODO THROW

    _variableMap[node->identifier] = {node->size, _variableCount};

    Precursor::Instruction instruction = {
        BLSVM::Bytecode::OpCode::ALLOC_STACK,
        {Precursor::VARIABLE, _variableCount++}
    };

    _precursorBuffer.emplace_back(instruction);
}

void BLSL::Compiler::visit(ASTNode::BinaryOperator *node)
{
    
}



