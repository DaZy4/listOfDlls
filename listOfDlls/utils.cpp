#include "utils.hpp"

DWORD Utils::getPid(std::string processName) {
    HANDLE processSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 proc;
    proc.dwSize = sizeof(proc);

    if (!Process32First(processSnap, &proc)) return NULL;

    do {
        if (!strcmp(proc.szExeFile, processName.c_str()))
        {
            CloseHandle(processSnap);
            return proc.th32ProcessID;
        }
    } while (Process32Next(processSnap, &proc));

    CloseHandle(processSnap);
    return NULL;
}

void Utils::moduleList(DWORD processID)
{
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    printf("\nProcess ID: %u\n", processID);

    hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);
    if (!hProcess)
        return;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];

            if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
                std::cout << std::endl << szModName << std::endl;
        }
    } else
        std::cout << std::endl << "App has no loaded modules" << std::endl;

    CloseHandle(hProcess);
}