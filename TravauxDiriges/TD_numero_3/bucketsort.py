from mpi4py import MPI
import itertools
import sys
import random
import statistics

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

list_size=int(sys.argv[1])
max_value=int(sys.argv[2])
quot=int(list_size/(size))

liste=[]

for i in range(list_size):
    liste.append(random.randint(0,max_value))
liste.sort()
bucket_border=[]
for i in range(1,size):
    bucket_border.append(liste[i*quot])

all_bucket=comm.allgather(bucket_border)
all_bucket=list(itertools.chain.from_iterable(all_bucket))
all_bucket.sort()

global_bucket_border=[]
for i in range(size-1): 
    global_bucket_border.append(statistics.mean(all_bucket[i*size:(i+1)*size]))

scatter=[]
start=0
end=0
for i in range(len(global_bucket_border)):
    while(liste[end]<global_bucket_border[i]): 
        end+=1
    scatter.append(liste[start:end])
    start=end
scatter.append(liste[end:])

bucket=[]
for i in range(size):
    data=comm.scatter(scatter,root=i)
    bucket.append(data)
bucket=list(itertools.chain.from_iterable(bucket))
bucket.sort()
sortedarray=comm.gather(bucket,0)
if rank==0:
    print(sortedarray)  