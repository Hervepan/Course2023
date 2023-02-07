declare -a array=( 1 0.50359129 0.383522564 0.300740669 0.267399966 0.296668353 )
for i in $(seq 0 5)
do 
    array[i]=$(echo "scale=5; 1/${array[i]}"| bc -l)
done
declare -a line=( $(cut -d"|" -f 1,2 random.txt | tr "\n" " ") ) 
for i in $(seq 0 5)
do 
    printf "%s|%s\n" ${line[i]} ${array[i]}
done 