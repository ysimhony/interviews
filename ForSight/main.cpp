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


// #define NUM_OF_THREADS 3


// vector<vector<unique_ptr<floatMessageBuffer>>> mb(NUM_OF_THREADS);
// vector<vector<schd>> schds;




// void task(int id, vector<float>& ranges, vector<float*>& out_vals) {

//     // Calcualate sleep period for each thread based on the id
//     int cycle_period_in_msec = pow(2, id) * 10;
    
//     // Create oscillator for the 2 variables
//     vector<unique_ptr<oscillator>> oscillators;
//     oscillators.push_back(make_unique<oscillator>(steady_clock::now(), ranges[0]));
//     oscillators.push_back(make_unique<oscillator>(steady_clock::now(), ranges[1]));

//     while (true) {
        
//         // sleep 
//         this_thread::sleep_for(milliseconds(cycle_period_in_msec)); 
        
//         // Read incoming messages and updating main storage
//         for (int src_id=0, i=0; src_id<NUM_OF_THREADS; src_id++) {
//             if (src_id==id) continue;
//             mb[src_id][id]->read(out_vals[i++]);        
//         }        

//         // send messages to other threads
//         for (int dst_id=0, i=0; dst_id<NUM_OF_THREADS; dst_id++) {
//             if (dst_id==id) continue;

//             if (schds[id][dst_id].can_send()) {
//                 float val = oscillators[i++]->read_val();
//                 mb[id][dst_id]->write(val); 
//             }           
//         }        
//     }
// }

// using TaskRef = reference_wrapper<Task>;


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

        return 0;

    } catch (const connectionManagerError &e) {
        std::cerr << "Application stopping due to connection manager error: " << endl << e.what() << std::endl;
        return 1;  // exit with error code
    }

    

}

