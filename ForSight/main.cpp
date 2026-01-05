#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <iomanip>
#include <sys/mman.h>
#include <fcntl.h>
#include <cstring>
#include <unordered_map>
#include <memory>

#include "connectionsManager.h"
#include "oscillator.h"
#include "Task.h"
#include "FloatMessageBufferFactory.h"

int main() {
    // main storage
    float x=0, y=0, z=0;
    float roll=0, pitch=0, yaw=0;

    std::unique_ptr<Task> task10 = std::make_unique<Task>(10, "Task10");
    std::unique_ptr<Task> task20 = std::make_unique<Task>(20, "Task20");
    std::unique_ptr<Task> task40 = std::make_unique<Task>(40, "Task40");

    oscillator x_source(std::chrono::steady_clock::now(), 1);
    oscillator y_source(std::chrono::steady_clock::now(), 1);
    oscillator z_source(std::chrono::steady_clock::now(), 1);

    oscillator roll_source(std::chrono::steady_clock::now(), M_PI);
    oscillator pitch_source(std::chrono::steady_clock::now(), M_PI);
    oscillator yaw_source(std::chrono::steady_clock::now(), M_PI);

    try {
        FloatMessageBufferFactory factory;
        connectionsManager cm(factory);

        Task* p_task10 = task10.get();
        Task* p_task20 = task20.get();
        Task* p_task40 = task40.get();

        cm.addTask(std::move(task10));
        cm.addTask(std::move(task20));
        cm.addTask(std::move(task40));

        cm.addConnection("x", &x_source, &x, {p_task20, p_task10}, 20);
        cm.addConnection("y", &y_source, &y, {p_task40, p_task10}, 40);

        cm.addConnection("z", &z_source, &z, {p_task10, p_task20}, 20);
        cm.addConnection("yaw", &yaw_source, &yaw, {p_task40, p_task20}, 40);

        cm.addConnection("pitch", &pitch_source, &pitch, {p_task20, p_task40}, 40);
        cm.addConnection("roll", &roll_source, &roll, {p_task10, p_task40}, 40);

        cm.start();

        std::cout << "Tasks are running for 5 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));

        cm.stop();
        cm.wait();

        std::cout << "Process finished gracefully." << std::endl;
        return 0;

    } catch (const connectionManagerError &e) {
        std::cerr << "Application stopping due to connection manager error: " << std::endl << e.what() << std::endl;
        return 1;
    }
}
