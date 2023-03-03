#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include "global.h"
using namespace std;
class Player
{
private:
    bool ships1[sizefield][sizefield] ={ 0 };
    bool ships2[sizefield][sizefield] ={ 0 };
    
public:
    void shipmanager();
    void hitmanager(vector<vector<char*>>&, vector<vector<char*>>&);
};

/*
    #include <chrono>
    long long GetCurrentTimeMillis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count();
    }

    // A sample function to simulate the time spent on deciding a move
    void DoSomething() {
        for (int i = 1; i <= 1000000000; ++i) {
                // do nothing
        }
    }


    Get the start time

    // Do something
    DoSomething();

    // Get the end time
    long long start = GetCurrentTimeMillis();
    long long end = GetCurrentTimeMillis();

    // Calculate the time spent
    long long timeSpent = end - start;

    // Output the time spent
    std::cout << "Time spent: " << timeSpent << " ms\n";

    return 0;
*/