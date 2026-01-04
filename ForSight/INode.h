#pragma once

class INode {
public:
    virtual ~INode() = default;
    virtual void write(float val) = 0;
    virtual bool read(float& out) = 0;
};
