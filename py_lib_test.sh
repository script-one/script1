set -x
set -e
./py_lib.sh obj
./py_lib.sh calculus
./py_lib.sh rnd
./py_lib.sh vector
./py_lib.sh file
./py_lib.sh guid
./py_run.sh _calllib4
# ./py_run.sh _calllib