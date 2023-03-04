#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <random>
#include <fstream>
#include <Windows.h>


constexpr const int sizefield = 10;
constexpr const char hit = '*';
constexpr const char destroyed = 'x'; // only for Pv und CvC
constexpr const char miss = 'o';
constexpr const char unused = '~';
constexpr const char ship = '#';
//constexpr const int ROWS = 20;
//constexpr const int COLS = 40;
//constexpr const int height = 50;
//constexpr const int width = 100;

// 4 * 1 block groﬂe dinger 
// 3 * 2 block lange dinger
// 2 * 3 block lange dinger
// 1 * 4 block langes ding
