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

#include "connectionsManager.h"
#include "oscillator.h"
#include "Task.h"
#include "FloatMessageBufferFactory.h"

using namespace std;
using namespace chrono;


int main() {
    // main storage
    float x=0, y=0, z=0;
    float roll=0, pitch=0, yaw=0;

    Task10 task10;
    Task20 task20;
    Task40 task40;

    oscillator x_source(steady_clock::now(), 1);
    oscillator y_source(steady_clock::now(), 1);
    oscillator z_source(steady_clock::now(), 1);

    oscillator roll_source(steady_clock::now(), M_PI);
    oscillator pitch_source(steady_clock::now(), M_PI);
    oscillator yaw_source(steady_clock::now(), M_PI);    

    try {

        FloatMessageBufferFactory factory;

        connectionsManager cm(factory);
        cm.addTask(&task10);
        cm.addTask(&task20);
        cm.addTask(&task40);

        cm.addConnection("x", &x_source, &x, {&task20, &task10}, 20);
        cm.addConnection("y", &y_source, &y, {&task40, &task10}, 40);

        cm.addConnection("z", &z_source, &z, {&task10, &task20}, 20);
        cm.addConnection("yaw", &yaw_source, &yaw, {&task40, &task20}, 40);

        cm.addConnection("pitch", &pitch_source, &pitch, {&task20, &task40}, 40);
        cm.addConnection("roll", &roll_source, &roll, {&task10, &task40}, 40);

        cm.start();

        // Let the tasks run for a while
        cout << "Tasks are running for 5 seconds..." << endl;
        this_thread::sleep_for(seconds(5));
        
         // Now, initiate the graceful shutdown
         cm.stop();

         // Wait for all threads to finish
         cm.wait();


        return 0;

    } catch (const connectionManagerError &e) {
        std::cerr << "Application stopping due to connection manager error: " << endl << e.what() << std::endl;
        return 1;  // exit with error code
    }

    

}

