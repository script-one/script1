set -x
set -e
# install dart package
./install.sh
# run & test
./runs1.sh hello
./runs1.sh while
./runs1.sh sum
./runs1.sh fn
./runs1.sh for
./runs1.sh if
./runs1.sh matrix
./runs1.sh map
./runs1.sh mt
./runs1.sh class
./runs1.sh global
./runs1.sh cond
./runs1.sh try
./runs1.sh lambda
./runs1.sh lambda
./runs1.sh lambda
./runs1.sh lambda
# library build
./libs1.sh obj 
./libs1.sh calculus 
./libs1.sh rnd 
./libs1.sh vector 
./libs1.sh file 
./libs1.sh guid 
./libs1.sh obj
# call library
./runs1.sh _calllib
# deno only
./runjs.sh _copy
./runjs.sh _math
./runjs.sh _sha256
./runjs.sh _datetime
./runjs.sh _regexp
./runjs.sh _fs
./runjs.sh _sqlite
./runjs.sh _console
./runjs.sh _server
# remove generated data
rm *.db
