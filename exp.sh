for seed in 42 3131 462 2 7270
do
    for migrants in 0 1 5 10 16 32 64
    do
        outputname="GA_${migrants}_1024_${seed}.txt"
        echo ${outputname}
        touch ${outputname}
        if [ $migrants -eq 0 ]
        then 
            sed -i '22 s/#define migration true/#define migration false/' main.cpp
            sed -i "23 s/#define migrants [0-9]\+/#define migrants ${migrants}/" main.cpp
            sed -i "17 s/#define seed [0-9]\+/#define seed ${seed}/" main.cpp 
        else
            sed -i '22 s/#define migration false/#define migration true/' main.cpp 
            sed -i "23 s/#define migrants [0-9]\+/#define migrants ${migrants}/" main.cpp
            sed -i "17 s/#define seed [0-9]\+/#define seed ${seed}/" main.cpp
        fi
        make
        mpiexec -n 4 ./GeneticAlgorithm >> ${outputname}
done
    done
   
