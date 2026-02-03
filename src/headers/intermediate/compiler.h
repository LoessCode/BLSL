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


    class Compiler : public ASTNode::Visitor
    {
    private:
        size_t _virtualRegisterCounter;
        std::vector<BLSVM::Bytecode::instruction_t> _outBuffer;
        std::unordered_map<std::string, size_t> _variableMap;

        std::unordered_map<size_t, size_t> _compileTimeSizes;
        size_t _compileTimeSizeCounter;

    public:
        Compiler();
    public:
        void visit(ASTNode::Alloc *node) override;
        void visit(ASTNode::BinaryOperator *node) override;


    };
}


#endif //BLSLANG_COMPILER_H