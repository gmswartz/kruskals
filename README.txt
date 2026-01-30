PA 6: Kruskal's
Author: Grace Swartz (2414391, gswartz@chapman.edu)
Class: CPSC350-02
Files: input.txt, main.cpp, MinHeap.h, README.txt, WGraph.h, WGraph.cpp
Date Submitted: 12/5/24

Compiling command: g++ *.cpp -o A6.exe
Run command: ./A6.exe input.txt

!!! ERROR !!!
    - sometimes it gives weird compiling errors when I run it in docker, but it usually works eventually and always works when I don't run it through docker

References and Notes:
WGraph.h and WGraph.cpp base code:
    - Erik Linstead (provided in PA6 instructions with permission to use)
Info on vectors:
    - https://www.w3schools.com/cpp/cpp_vectors.asp
    - https://cplusplus.com/reference/vector/vector/
Info on pairs:
    - https://www.geeksforgeeks.org/pair-in-cpp-stl/
ChatGpt:
    - cited in line 121 of WGraph.cpp (I just needed help on the syntax of creating the min heap the way I wanted it)
MinHeap.h:
    - this was an in class code implementation of a min MinHeap
    - I decided to use this since the assignment said we could use other classes such as a priority queue, I just implemented it as a min heap