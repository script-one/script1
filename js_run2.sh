./s1 -d prog/$1.s1 -o out/$1.js
deno run --import-map=sys/import_map.json -A --unstable out/$1.js
