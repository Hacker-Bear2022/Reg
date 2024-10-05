// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <string>
#include <fstream>
#include<atlstr.h>
#include <ShlObj.h>
#include <time.h>
#include <tuple>
#include <cwchar>
#include <stdexcept>
#include <map>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <atomic>
#include <functional>
#include <psapi.h>
#include <codecvt>
#include <locale>
#include <sys/stat.h>
#include<random>
#define ByteArr vector<byte>

using namespace std;

#include"配置.h"
#include "Socverification.h"
#pragma comment(lib, "ClientLib64.lib")//x64 VS2019依赖库