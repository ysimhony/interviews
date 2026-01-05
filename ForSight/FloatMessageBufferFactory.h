#pragma once
#include "INode.h"
#include "INodeFactory.h"
#include "floatMessageBuffer.h"

class FloatMessageBufferFactory : public INodeFactory {
public:
    std::unique_ptr<INode> create() override {
        return std::make_unique<floatMessageBuffer>();
    }         
};