rm -rf profiling
mkdir profiling

fallocate -l "1G" profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in {1..10}; do
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

fallocate -l "10M" profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in {1..1000}; do
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

fallocate -l "10M" profiling/temp
mkdir profiling/dir
./a.out < <(
    for i in {1..10}; do
        echo "cp profiling/temp profiling/dir/temp_$i"
    done
    dir="/dir"
    for i in {1..100}; do
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
