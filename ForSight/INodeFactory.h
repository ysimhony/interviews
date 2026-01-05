#pragma once
#include <memory>

#include "INode.h"

class INodeFactory {
public:
    virtual ~INodeFactory() = default;
    virtual std::unique_ptr<INode> create() = 0; 
};
  