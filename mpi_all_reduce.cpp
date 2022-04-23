// mpic++ mpi_all_reduce.cpp -o mpi_all_reduce
// mpirun -np 4 mpi_all_reduce
#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int rank, size;
    int n = 1024;
    vector<int> a(n);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int final_result = 0, local_result = 0;

    for (int i = rank * n / size; i < (rank + 1) * n / size; i += 1)
        a[i] = i;

    for (int i = rank * n / size; i < (rank + 1) * n / size; i += 1)
        local_result += a[i];

    MPI_Allreduce(&local_result, &final_result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("process: %d, local_result: %d, final_result: %d\n", rank, local_result, final_result);

    MPI_Finalize();

    return 0;
}