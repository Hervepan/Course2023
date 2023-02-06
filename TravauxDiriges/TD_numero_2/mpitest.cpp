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
    int send=0;
    int receive;
    MPI_Status status;
    if (rank==0){
        MPI_Ssend(&send,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Recv(&receive,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
        cout << receive;
    }else if(rank==1){
        MPI_Ssend(&send,1,MPI_INT,0,0,MPI_COMM_WORLD);
        MPI_Recv(&receive,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
        cout << receive;
    }
    MPI_Finalize();
    return 0;
}