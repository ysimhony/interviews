#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "INode.h"
#include "Task.h"
#include "INodeFactory.h"

using namespace std;



class connectionManagerError : public exception {
public:
    connectionManagerError(const string &msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }

private:
    string message;
};


class connectionsManager {
public:
    connectionsManager(INodeFactory &_nodeFactory): nodeFactory(_nodeFactory){}

    void addTask(Task* task) {
        name2task[task->name()] = task;        
    }
    void addConnection(const string& varName,
                        INode* source, 
                        float* target, 
                        const vector<Task*>& tasks,
                        int tasks_period_msec) {
        
        if (!source || !target) {
            throw connectionManagerError("Source and Target must be provided");
            // exit(EXIT_FAILURE);
        }
        if (tasks.size() != 2) {
            throw connectionManagerError("There should be 2 tasks in the path");
        }
        
        for (auto& task: tasks) {
            if (name2task.find(task->name()) == name2task.end()) {
                throw connectionManagerError("Could not find task: " + task->name());
                // cerr << "Could not find task" << task->name() << endl;
            }
        }
        string buffer_name = tasks[0]->name() + tasks[1]->name() + varName;

        name2messageBuffer[buffer_name] = nodeFactory.create();
        tasks[0]->addOutput(source, name2messageBuffer[buffer_name], tasks_period_msec);
        tasks[1]->addInput(name2messageBuffer[buffer_name], target);
    }

    void start() {
        cout << "starting all threads" << endl;
        for (const auto& pair: name2task) {
            pair.second->start();
        }

        
        for (auto& pair : name2task) {
            pair.second->join();
        }        
    }
private:
    // vector<TaskRef> tasks_;
    unordered_map<string, Task*> name2task;
    unordered_map<string, INode*> name2messageBuffer;
    INodeFactory &nodeFactory;
};