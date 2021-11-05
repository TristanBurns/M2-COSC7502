islands=$1
migrants=1

sed -i "5 s/#SBATCH --ntasks=[0-9]\+/#SBATCH --ntasks=${islands}/" goslurm.sh
sed -i "6 s/#SBATCH --ntasks-per-node=[0-9]\+/#SBATCH --ntasks-per-node=${islands}/" goslurm.sh

#2448 4036 8192 16384 32768
#16 32 64 128 256 512 1024

for seed in 42 3131 462 2 7270
do
    for sizen in 16 32 64 128 256 512 1024
    do
        outputname="Parallel_${migrants}_${sizen}_${seed}_${islands}"
        echo ${outputname}
        sed -i "3 s/#SBATCH --job-name=\(.*\)/#SBATCH --job-name=${outputname}/" goslurm.sh
        sed -i "6 s/#SBATCH --ntasks-per-node=[0-9]\+/#SBATCH --ntasks-per-node=${islands}/" goslurm.sh
        sed -i "17 s/#define seed [0-9]\+/#define seed ${seed}/" main.cpp
        sed -i "15 s/#define n [0-9]\+/#define n ${sizen}/" main.cpp
        if [ $migrants -eq 0 ]
        then 
            sed -i '22 s/#define migration true/#define migration false/' main.cpp
            sed -i "23 s/#define migrants [0-9]\+/#define migrants ${migrants}/" main.cpp
        else
            sed -i '22 s/#define migration false/#define migration true/' main.cpp 
            sed -i "23 s/#define migrants [0-9]\+/#define migrants ${migrants}/" main.cpp 
        fi
       mpic++ -std=c++11 -g -O3 -funroll-loops -flto -fuse-linker-plugin functions.cpp main.cpp -o ${outputname}
       sleep 6
       sbatch goslurm.sh ${islands} 
       sleep 2
    done
done
   