# R-DUMPER

This C++ program is designed to create a dump of the physical memory (RAM) of the running process and save it to a binary file. The code utilizes the Windows API functions to read the process memory in chunks and write it to a file.

## Prerequisites
- This tool is intended to run on Windows operating systems.
- Ensure that you have the necessary privileges to open the process and read its memory.

## How to Use
1. Compile the code using a C++ compiler compatible with Windows.
2. Run the compiled executable.
3. The program will create a binary file named `ram_dump.bin` in the same directory as the executable.
4. Check the console output for the success message and any potential errors.

## Code Explanation
- The program first obtains a handle to the current process with the necessary privileges to read its memory.
- It then retrieves the minimum and maximum address range of the process using the `GetSystemInfo` function.
- A binary file named `ram_dump.bin` is created for writing the RAM dump.
- Memory is read in chunks of 4 KB using the specified `chunkSize`.
- The program iterates through the process's address space, querying each chunk's memory information.
- If the memory is readable, it is read using `ReadProcessMemory` and written to the file.
- Invalid or inaccessible memory regions are skipped.
- After processing all chunks, the file is closed, and the process handle is released.

## Error Handling
- The program checks for errors during the opening of the process, file writing, and memory reading.
- If an error occurs, an appropriate error message is displayed on the console.

## Note
- Modify the `chunkSize` variable as needed based on your requirements.

## Disclaimer
This tool is provided for educational and informational purposes only. Ensure compliance with legal and ethical standards when using this tool. The author is not responsible for any misuse or unintended consequences resulting from the use of this code.