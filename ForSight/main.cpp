#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
#include <unistd.h>
#include <iomanip>
#include <sys/mman.h>
#include <fcntl.h>

#include "oscillator.h"
#include "floatMessageBuffer.h"
#include "schd.h"
#include <cstring>

using namespace std;
using namespace chrono;


#define NUM_OF_THREADS 3


vector<vector<unique_ptr<floatMessageBuffer>>> mb(NUM_OF_THREADS);
vector<vector<schd>> schds;




void task(int id, vector<float>& ranges, vector<float*>& out_vals) {

    // Calcualate sleep period for each thread based on the id
    int cycle_period_in_msec = pow(2, id) * 10;
    
    // Create oscillator for the 2 variables
    vector<unique_ptr<oscillator>> oscillators;
    oscillators.push_back(make_unique<oscillator>(steady_clock::now(), ranges[0]));
    oscillators.push_back(make_unique<oscillator>(steady_clock::now(), ranges[1]));

    while (true) {
        
        // sleep 
        this_thread::sleep_for(milliseconds(cycle_period_in_msec)); 
        
        // Read incoming messages and updating main storage
        for (int src_id=0, i=0; src_id<NUM_OF_THREADS; src_id++) {
            if (src_id==id) continue;
            mb[src_id][id]->read(out_vals[i++]);        
        }        

        // send messages to other threads
        for (int dst_id=0, i=0; dst_id<NUM_OF_THREADS; dst_id++) {
            if (dst_id==id) continue;

            if (schds[id][dst_id].can_send()) {
                float val = oscillators[i++]->read_val();
                mb[id][dst_id]->write(val); 
            }           
        }        
    }
}


int main() {

    // main storage
    float x=0, y=0, z=0;
    float roll=0, pitch=0, yaw=0;

    // initialize message buffers for each thread 
    for (auto& inner : mb)
        for (int i = 0; i < NUM_OF_THREADS; ++i)
            inner.push_back(make_unique<floatMessageBuffer>());

    // Initialize the inter-thread scheduler     
    for (int i=0; i<NUM_OF_THREADS; i++) {
        vector<schd> row;
        for (int j=0; j<NUM_OF_THREADS; j++)
            row.push_back(schd(i,j));
        schds.push_back(row);
    }

    vector<float> ranges_10 = { 1, M_PI};
    vector<float*> output_10 = { &x, &y };
    thread Task_10_thread(task, 0, ref(ranges_10), ref(output_10));

    vector<float> ranges_20 = { 1, M_PI};
    vector<float*> output_20 = { &z, &yaw };
    thread Task_20_thread(task, 1, ref(ranges_20), ref(output_20));
    
    vector<float> ranges_40 = { 1, M_PI};
    vector<float*> output_40 = { &roll, &pitch };
    thread Task_40_thread(task, 2, ref(ranges_40), ref(output_40));

    Task_10_thread.join();
    Task_20_thread.join();
    Task_40_thread.join();
    
    return 0;
}

