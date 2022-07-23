set -x
set -e
# export S1HOME=./
# export PYTHONPATH=$S1HOME/sys/
dart pub get
if [ "$(uname)" == "Darwin" ]; then
    pip3 install aiofile
    pip3 install asyncio
else
    pip install aiofile
    pip install asyncio
fi
