./s1 -d prog/$1.s1 -o out/$1.js
deno run -A --unstable out/$1.js
