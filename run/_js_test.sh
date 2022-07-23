set -x
set -e
./js_run.sh _fs
./js_run.sh _regexp
./js_run.sh _sqlite
./js_run.sh _sha256
./js_run.sh _datetime
./js_run.sh _copy
./js_run.sh _math
# ./js_run.sh _console
# ./js_run.sh _server
