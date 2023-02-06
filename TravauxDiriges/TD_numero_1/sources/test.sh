#! /bin/bash

for j in 1024 2048 512 4096; do 
    ./test_product_matrice_blas.exe $j
done

# export LC_NUMERIC=C
# for ((i=1;i<34;i++)); do
# 	eval "element=\$(sed -n \"${i}p\" test.txt)"
# 	printf "|     %.2f     " $element
# 	if [[ $((i%4)) == 0 ]]; then
# 		printf "\n" 
# 	fi
# done	
