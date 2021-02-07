// HelloWin.cpp : This file contains the 'main' function. Program execution begins and ends there.

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

    // DEPRECATED GET VERSION FUNCTION

    OSVERSIONINFO vi = { sizeof(vi) };
    ::GetVersionEx(&vi);

    printf("Version: %d.%d.%d\n", vi.dwMajorVersion, vi.dwMinorVersion, vi.dwBuildNumber);

    // NEW GET VERSION FUNCTION
    // Based on KUSER_SHARED_DATA data struct mapped to every process to same address
    auto sharedUserData = (BYTE*)0x7FFE0000; // address to data struct
    ULONG* majorVer = (ULONG*)(sharedUserData + 0x26c); // major version offset
    ULONG* minorVer = (ULONG*)(sharedUserData + 0x270); // major version offset
    ULONG* buildNum = (ULONG*)(sharedUserData + 0x260); // major version offset (Windows 10)
    printf("Version: %d.%d.%d\n", *majorVer, *minorVer, *buildNum);
}
