// mpic++ test_work.cpp -o test_work --std=c++17
// mpirun -np 4 test_work
#include <iostream>
#include <chrono>
#include <mpi.h>

using namespace std;


int main(int argc, char* argv[]) {
    int rank, size;
    long long n = 10000000;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    auto start = chrono::steady_clock::now();

    double final_result = 0, local_result = 0;

    for (long long i = rank; i < n; i += size)
        local_result += (double) 1 / (n - i);

    MPI_Reduce(&local_result, &final_result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    int time = chrono::duration_cast<chrono::milliseconds>(diff).count();
    if (rank == 0)
        printf("final_result: %.20lf\nmilliseconds: %d", final_result, time);

    MPI_Finalize();

    return 0;
}