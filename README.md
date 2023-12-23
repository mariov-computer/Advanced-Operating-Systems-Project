# Advanced-Operating-Systems-Project
A semester-long project which was the culmination of CSE 4610, which was the overview, design, implementation, and security of operating systems. It dealt with file systems, I/O systems, and security distributed systems. Built in a Linux environment and this is how I personally compiled the project:
g++ -c sdisk.cpp
g++ -c block.cpp
g++ -c filesys.cpp
g++ -c shell.cpp
g++ -c table.cpp
g++ -c main5.cpp
g++ -o project8 sdisk.o block.o filesys.o shell.o table.o main5.o
./project8
