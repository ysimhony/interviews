#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include "INode.h"

using namespace std;
using namespace chrono;

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

        // auto now = std::chrono::system_clock::now();
        // auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        // std::cout << now_ms.count() << ": " << *target << endl;          

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

        lastProcess = steady_clock::now();
    }

    virtual void process(){
        float tmp_float;
        ch1->read(tmp_float);
        ch2->write(tmp_float);

        lastProcess = steady_clock::now(); 
    }
    virtual bool canProcess(){
        if ((steady_clock::now() - lastProcess) >= chrono::milliseconds(periodMs)){
            return true;
        }

        return false;
    }        
private:    
    INode* ch1;
    INode* ch2;
    int periodMs = 0;
    steady_clock::time_point lastProcess;
};


class Task {
public:
    Task(int periodMs, string name)
        : period(periodMs), name_(move(name)) {}

    virtual ~Task() = default;

    const string& name() const { return name_; }

    void addInput(INode* ch, float* target) {
        inputs.push_back({ch, target});
    }

    void addOutput(INode* ch1, INode* ch2, int periodMs) {
        outputs.push_back({ch1, ch2, periodMs});
    }

    void start() {
        cout << "starting thread " << name_ << endl;
        worker = thread(&Task::run, this);
    }

    void join() {
        worker.join();
    }

protected:
    vector<OutputBinding> outputs;
    virtual void onTick(float t) = 0;
    int period;
    string name_;
    vector<InputBinding> inputs;
    thread worker;

    virtual void run() {
        auto start = chrono::steady_clock::now();

        while (true) {
            this_thread::sleep_for(
                chrono::milliseconds(period));

            // auto now = std::chrono::system_clock::now();
            // auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
            // std::cout << name_ << ":" << now_ms.count() << std::endl;  

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
    Task10() : Task(10, "Task10") {
        // osc1 = oscillator(chrono::_V2::steady_clock::now(), 1);
        // oscPI = oscillator(chrono::_V2::steady_clock::now(), M_PI);
    }

protected:
    // virtual void run() {
    //     auto start = chrono::steady_clock::now();

    //     while (true) {
    //         this_thread::sleep_for(
    //             chrono::milliseconds(period));

    //         auto now = std::chrono::system_clock::now();
    //         auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    //         std::cout << name_ << ":" << now_ms.count() << std::endl;  

    //         for (auto& in : inputs) {
    //             if (in.canProcess()){
    //                 in.process();
    //             }
    //         }

    //         for (auto& output: outputs) {
    //             if (output.canProcess()){
    //                 output.process();
    //             }
    //         }
    //     }
    // }
    void onTick(float t) override {
    //     static int tick = 0;
    //     float tmp_float;
    //     osc1.read(tmp_float);
    //     outputs[0].ch1->write(tmp_float);
    //     if (tick++ % 2 == 0)
    //         outputs[1].ch1->write(tmp_float);
    }
private:
    // oscillator osc1;
    // oscillator oscPI;
};

class Task20 : public Task {
public:
    Task20() : Task(20, "Task20") {
        // osc1 = oscillator(chrono::_V2::steady_clock::now(), 1);
        // oscPI = oscillator(chrono::_V2::steady_clock::now(), M_PI);
    }

protected:
    void onTick(float t) override {
    //     static int tick = 0;
    //     float tmp_float;
    //     osc1.read(tmp_float);
    //     outputs[0].ch1->write(tmp_float);
    //     if (tick++ % 2 == 0)
    //         outputs[1].ch1->write(tmp_float);
    }
private:
    // oscillator osc1;
    // oscillator oscPI;
};

class Task40 : public Task {
public:
    Task40() : Task(40, "Task40") {
        // osc1 = oscillator(chrono::_V2::steady_clock::now(), 1);
        // oscPI = oscillator(chrono::_V2::steady_clock::now(), M_PI);
    }

protected:
    void onTick(float t) override {
    //     static int tick = 0;
    //     float tmp_float;
    //     osc1.read(tmp_float);        
    //     outputs[0].ch1->write(tmp_float);
    //     if (tick++ % 2 == 0)
    //         outputs[1].ch1->write(tmp_float);
    }
private:
    // oscillator osc1;
    // oscillator oscPI;
};

