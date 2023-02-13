from mpi4py import MPI
import random



comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

array=[]
for i in range(20):
    array.append(random.randint(0,40))

print(f"rank: {rank} random array : ",array)

element=[0,12,15,15,20]
chien=[]
for i in range(len(element)-1):
    chien.append(array[element[i]:element[i+1]])

bucket=[]
for i in range(size):
    data=comm.scatter(chien,root=i)
    bucket.append(data)

print(bucket)