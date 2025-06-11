#ifndef MEASURE_H
#define MEASURE_H

#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

template <typename Func, typename... Args>
void measureExecutionTime(Func func) {
    auto start = high_resolution_clock::now();
    unsigned long long result = func();
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Resultado: " << result << " | Tempo: " << duration << " microssegundos\n";
}

#endif // MEASURE_H
