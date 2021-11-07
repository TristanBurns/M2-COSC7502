for seed in 2 42 462 3131 7270
do
    for sizen in 16 32 64 128 256 512 1024 2448 4036 8192 16384 32768
    do
        for filename in Parallel_1_${sizen}_${seed}*.txt 
        do
            echo $filename
            grep -Eo '[0-9]+' $filename -m 1 >> ", ">> preprocessed.txt
            #echo -e ", " >> preprocessed.txt
            #grep 'Runtime (microseconds), * ' $filename | cut -f2 -d,>> preprocessed.txt 
        done
        
    done
    echo -e "\n" >> preprocessed.txt
done

# sed -n 's/Runtime (microseconds), [0-9]+/p' Parallel_1_32768_7270_4_13h34m28s.txt

# echo "/Runtime (microseconds), 123153 a test string 20-Jul-2012" | grep -Eo -m1 '[0-9]+'
# echo "/Runtime (microseconds) 123153 a test string 20-Jul-2012" | grep -Eo 'Runtime (microseconds) [0-9]+'
# echo "This is 02G05 a test string 20-Jul-2012" | grep -Eo '[0-9]+G[0-9]+'

# grep -Eo '[0-9]+' Parallel_1_32768_7270_4_13h34m28s.txt -m 1