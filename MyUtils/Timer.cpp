#include <iostream>
#include <chrono>
#include <algorithm>

// using chrono high_resolution_clock
using namespace std::chrono;
using hrc = high_resolution_clock;
#define ELAPSED(st, en)			( duration_cast<duration<double>>(en - st).count() )
#define ELAPSED_MS(st, en)		( duration_cast<duration<double, std::milli>>(en - st).count() )

int main()
{
    const int n = 1e8;
    int* A = new int[n];                        // make sure we put any I/O, memory allocation etc. out of timing
    for (int i = 0; i < n; i++) A[i] = n - i;   // generate data in array

    // test ground
    printf("Running sort on %d items ... ", n);
    hrc::time_point st = hrc::now();        // get start time point
    std::sort(A, A + n);
    hrc::time_point en = hrc::now();        // get end time point
    printf("done\n");
    double elapsed = ELAPSED_MS(st, en);

    printf("Elapsed: %.2f ms\n", elapsed);

    // cleanup
    delete[] A;
    return 0;
}
