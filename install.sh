set -x
set -e
export S1HOME=./
export PYTHONPATH=$S1HOME/sys/
dart pub get
pip3 install aiofile
pip3 install asyncio
