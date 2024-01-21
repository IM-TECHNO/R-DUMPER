#include <iostream>
#include <fstream>
#include <Windows.h>

int main() {
    // Obtain a handle to the entire physical memory
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());

    if (hProcess == NULL) {
        std::cerr << "Error opening process. Make sure you have the required privileges." << std::endl;
        return 1;
    }

    // Get the minimum and maximum address range of the process
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    LPVOID minAddress = sysInfo.lpMinimumApplicationAddress;
    LPVOID maxAddress = sysInfo.lpMaximumApplicationAddress;

    // Open a file for writing the RAM dump
    std::ofstream outFile("ram_dump.bin", std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        CloseHandle(hProcess);
        return 1;
    }

    // Define the chunk size (adjust as needed)
    const SIZE_T chunkSize = 4096;  // 4 KB

    // Read and write the memory content in chunks
    BYTE buffer[chunkSize];
    SIZE_T bytesRead;

    for (LPVOID address = minAddress; address < maxAddress; address = LPVOID(DWORD_PTR(address) + chunkSize)) {
        MEMORY_BASIC_INFORMATION memInfo;
        if (VirtualQueryEx(hProcess, address, &memInfo, sizeof(memInfo)) == sizeof(memInfo) &&
            (memInfo.State == MEM_COMMIT) &&
            (memInfo.Protect & (PAGE_READWRITE | PAGE_READONLY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_READ))) {
            // Memory is readable, proceed with reading
            if (ReadProcessMemory(hProcess, address, buffer, sizeof(buffer), &bytesRead)) {
                // Write the chunk to the file
                outFile.write(reinterpret_cast<char*>(buffer), bytesRead);
            } else {
                std::cerr << "Error reading process memory at address " << address << ". Error code: " << GetLastError() << std::endl;
            }
        } else {
            // Invalid or inaccessible memory, skip to the next chunk
           continue;
        }
    }

    // Close the file and handle
    outFile.close();
    CloseHandle(hProcess);

    std::cout << "RAM dump successful. Check 'ram_dump.bin'." << std::endl;

    return 0;
}
