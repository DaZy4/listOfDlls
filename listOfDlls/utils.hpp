#pragma once

#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>

namespace Utils {
    DWORD getPid(std::string processName);
    void moduleList(DWORD processID);
}