one_file="1G"
one_count=10
two_file="10M"
two_count=1000
three_file="10M"
three_count=10
three_dir_count=100

rm -rf profiling
mkdir profiling

fallocate -l $one_file profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in $(seq 1 $one_count); do
        echo "cp profiling/temp profiling/dir/temp_$i"
    done
    echo "exit"
) > output.txt
rm output.txt

time ./a.out < <(
    echo "cp -r profiling/dir profiling/dir_copy"
    echo "mv profiling/dir profiling/dir_rename"
    echo "rm -r profiling/dir_rename"
    echo "rm -r profiling/dir_copy"
    echo "exit"
) > output.txt
rm output.txt
rm profiling/temp

fallocate -l $two_file profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in $(seq 1 $two_count); do
        echo "cp profiling/temp profiling/dir/temp_$i"
    done
    echo "exit"
) > output.txt
rm output.txt

time ./a.out < <(
    echo "cp -r profiling/dir profiling/dir_copy"
    echo "mv profiling/dir profiling/dir_rename"
    echo "rm -r profiling/dir_rename"
    echo "rm -r profiling/dir_copy"
    echo "exit"
) > output.txt
rm output.txt
rm profiling/temp

fallocate -l $three_file profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in $(seq 1 $three_count); do
        echo "cp profiling/temp profiling/dir/temp_$i"
    done
    dir="/dir"
    for i in $(seq 1 $three_dir_count); do
        echo "cp -r profiling${dir} profiling${dir}"
        dir="${dir}/dir"
    done
    echo "exit"
) > output.txt
rm output.txt

time ./a.out < <(
    echo "cp -r profiling/dir profiling/dir_copy"
    echo "mv profiling/dir profiling/dir_rename"
    echo "rm -r profiling/dir_rename"
    echo "rm -r profiling/dir_copy"
    echo "exit"
) > output.txt
rm output.txt

rm -rf profiling
