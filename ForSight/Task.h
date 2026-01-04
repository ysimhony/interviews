#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include "INode.h"

class IBinding {
public:
    virtual ~IBinding() = default;
    virtual void process() = 0;
    virtual bool canProcess() = 0;
};

class InputBinding: public IBinding {
public:
    InputBinding(INode* _node, float* _target):
        node(_node), target(_target){}

    virtual void process(){
        node->read(*target);
    }
    virtual bool canProcess(){
        return true;
    }
private:
    INode* node;
    float* target;

};

class OutputBinding {
public:
    OutputBinding(INode* _ch1, INode* _ch2, int _periodMs):
        ch1(_ch1), ch2(_ch2), periodMs(_periodMs){

        lastProcess = std::chrono::steady_clock::now();
    }

    virtual void process(){
        float tmp_float;
        ch1->read(tmp_float);
        ch2->write(tmp_float);

        lastProcess = std::chrono::steady_clock::now(); 
    }
    virtual bool canProcess(){
        if ((std::chrono::steady_clock::now() - lastProcess) >= std::chrono::milliseconds(periodMs)){
            return true;
        }

        return false;
    }        
private:    
    INode* ch1;
    INode* ch2;
    int periodMs = 0;
    std::chrono::steady_clock::time_point lastProcess;
};


class Task {
public:
    Task(int periodMs, std::string name)
        : period(periodMs), name_(move(name)) {}

    virtual ~Task() = default;

    const std::string& name() const { return name_; }

    void addInput(INode* ch, float* target) {
        inputs.push_back({ch, target});
    }

    void addOutput(INode* ch1, INode* ch2, int periodMs) {
        outputs.push_back({ch1, ch2, periodMs});
    }

    void start() {
        std::cout << "starting thread " << name_ << std::endl;
        worker = std::thread(&Task::run, this);
    }

    void join() {
        worker.join();
    }

protected:
    std::vector<OutputBinding> outputs;
    int period;
    std::string name_;
    std::vector<InputBinding> inputs;
    std::thread worker;

    virtual void run() {
        auto start = std::chrono::steady_clock::now();

        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(period));

            for (auto& in : inputs) {
                if (in.canProcess()){
                    in.process();
                }
            }

            for (auto& output: outputs) {
                if (output.canProcess()){
                    output.process();
                }
            }
        }
    }


};

class Task10 : public Task {
public:
    Task10() : Task(10, "Task10") {}

protected:
};

class Task20 : public Task {
public:
    Task20() : Task(20, "Task20") {}

protected:
};

class Task40 : public Task {
public:
    Task40() : Task(40, "Task40") {}

protected:
};

