echo == JavaScript ==
./s1 -m prog/$1.s1 -o out/$1.js
./run.sh out/$1.js
echo == Python ==
./s1 -m prog/$1.s1 -o out/$1.py
./run.sh out/$1.py
echo == Dart ==
./s1 -m prog/$1.s1 -o out/$1.dart
./run.sh out/$1.dart
