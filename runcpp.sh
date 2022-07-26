./s1 -m prog/$1.s1 -o out/$1.cpp
g++ --std=c++14 -fconcepts -I./sys/ out/$1.cpp -o out/$1
./out/$1
# deno run -A --unstable out/$1.js
