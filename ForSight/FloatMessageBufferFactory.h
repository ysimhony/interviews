#pragma once
#include "INode.h"
#include "INodeFactory.h"
#include "floatMessageBuffer.h"

class FloatMessageBufferFactory : public INodeFactory {
public:
    INode* create() override {
        return new floatMessageBuffer();
    }
};