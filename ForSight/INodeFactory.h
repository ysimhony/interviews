#pragma once
#include "INode.h"

class INodeFactory {
public:
    virtual ~INodeFactory() = default;
    virtual INode* create() = 0;
};