#pragma once

#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <map>

#include "crow_all.h"
#include "cpu.h"

void startCacheThread();

crow::json::wvalue getJson();


unsigned int getCpuCores();
double getCpuUssage();
double getMemUssage();
double getSwapUssage();
std::string getUptime();