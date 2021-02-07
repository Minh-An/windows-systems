// HelloWin.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"

void printError(int errorCode);

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

    // Exercise: printing more information about the system and handle errors 
    TCHAR buffer[256] = TEXT("");
    DWORD size = sizeof(buffer);

    /* BASIC GetComputerName Function
    
    if (::GetComputerName(buffer, &size))
    {
        wprintf(TEXT("Computer Name: %s\n"), buffer);
    }
    else
    {
        printError(::GetLastError());
    }
    
    */

    TCHAR szDescription[8][32] = { TEXT("NetBIOS"),
        TEXT("DNS hostname"),
        TEXT("DNS domain"),
        TEXT("DNS fully-qualified"),
        TEXT("Physical NetBIOS"),
        TEXT("Physical DNS hostname"),
        TEXT("Physical DNS domain"),
        TEXT("Physical DNS fully-qualified") };
    int cnf = 0;
    for (cnf = 0; cnf < ComputerNameMax; cnf++)
    {
        if (!GetComputerNameEx((COMPUTER_NAME_FORMAT)cnf, buffer, &size))
        {
            printError(GetLastError());
            return 0;
        }
        else _tprintf(TEXT("%s: %s\n"), szDescription[cnf], buffer);

        size = _countof(buffer);
        ZeroMemory(buffer, size);
    }
}

void printError(int errorCode)
{
    LPWSTR text;

    DWORD dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;

    DWORD chars = ::FormatMessage(
        dwFlags,
        nullptr,
        errorCode,
        0,
        (LPWSTR)&text,
        0,
        nullptr
    );

    if (chars > 0) {
        printf("Error %d: %ws\n", errorCode, text);
        ::LocalFree(text);
    }
    else
    {
        printf("No such error exists.\n");
    }
}