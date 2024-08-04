#pragma once
//包含一些通用的库，并且定义初始化函数、事件循环函数等

#include <windows.h>
#include <chrono>
#include <cmath>
#include <conio.h>
#include <easyx.h>
#include <iostream>
#include <fstream>
#include <mmsystem.h>
#include <algorithm>//算法库，之后好好看看用法
#include <string>
#include <thread>
#include <vector>
#include <graphics.h>
#pragma comment (lib,"Winmm.lib")
//常量定义
constexpr auto FPS = 40;
constexpr auto PI = 3.1415926;

using std::string;
using std::wstring;
using std::vector;
