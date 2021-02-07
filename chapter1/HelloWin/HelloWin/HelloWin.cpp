// HelloWin.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define BUILD_WINDOWS
#include "pch.h"

int main()
{
    SYSTEM_INFO si;
    ::GetNativeSystemInfo(&si);

    printf("Number of Logical Processors: %d \n", si.dwNumberOfProcessors);
    printf("Page size: %d Bytes \n", si.dwPageSize);
    printf("Processor Mask: 0x%p \n", (PVOID)si.dwActiveProcessorMask);
    printf("Min process address: 0x%p \n", si.lpMinimumApplicationAddress);
    printf("Max process address: 0x%p \n", si.lpMaximumApplicationAddress);

    //Number of Logical Processors : 8
    //Page size : 4096 Bytes
    //Processor Mask : 0x000000FF
    //Min process address : 0x00010000
    //Max process address : 0xFFFEFFFF

    OSVERSIONINFO vi = { sizeof(vi) };
    ::GetVersionEx(&vi);

    printf("Version: %d.%d.%d\n", vi.dwMajorVersion, vi.dwMinorVersion, vi.dwBuildNumber);
}
