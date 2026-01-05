#pragma once
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <memory>

#include "INode.h"
#include "Task.h"
#include "INodeFactory.h"


class connectionManagerError : public std::exception {
public:
    connectionManagerError(const std::string &msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};


class connectionsManager {
public:
    connectionsManager(INodeFactory &_nodeFactory)
        : nodeFactory(_nodeFactory), shutdown_flag(false) {}

    void addTask(std::unique_ptr<Task> task) {
        if (name2task.find(task->name()) != name2task.end()) {
            throw connectionManagerError("Task " + task->name() + " already exists");            
        }
        task->setShutdownFlag(&shutdown_flag);
        name2task[task->name()] = std::move(task);
    }

    void addConnection(const std::string& varName,
                        INode* source,
                        float* target,
                        const std::vector<Task*>& tasks,
                        int tasks_period_msec) {

        if (!source || !target) {
            throw connectionManagerError("Source and Target must be provided");
        }
        if (tasks.size() != 2) {
            throw connectionManagerError("There should be 2 tasks in the path");
        }

        for (auto& task: tasks) {
            if (name2task.find(task->name()) == name2task.end()) {
                throw connectionManagerError("Could not find task: " + task->name());
            }
        }
        std::string buffer_name = tasks[0]->name() + tasks[1]->name() + varName;

        name2messageBuffer[buffer_name] = nodeFactory.create();
        tasks[0]->addOutput(source, name2messageBuffer[buffer_name].get(), tasks_period_msec);
        tasks[1]->addInput(name2messageBuffer[buffer_name].get(), target);
    }

    void start() {
        std::cout << "starting all threads" << std::endl;
        for (const auto& pair: name2task) {
            pair.second->start();
        }
    }

    void stop() {
        std::cout << "stopping all threads" << std::endl;
        shutdown_flag = true;
    }

    void wait() {
        for (auto& pair : name2task) {
            pair.second->join();
        }
        std::cout << "all threads have joined" << std::endl;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Task>> name2task;
    std::unordered_map<std::string, std::unique_ptr<INode>> name2messageBuffer;
    INodeFactory &nodeFactory;
    std::atomic<bool> shutdown_flag;
};
