#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;
#pragma omp parallel
int main(int argc,char** argv){
    int number_proc;
    int rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &number_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    cout << rank;
    MPI_Finalize();
    return 0;
}