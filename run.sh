export S1HOME=./
export PYTHONPATH=$S1HOME/sys/
# ref https://stackoverflow.com/questions/407184/how-to-check-the-extension-of-a-filename-in-a-bash-script
if [ "${1: -3}" == ".js" ]
then
    deno run -A --import-map=$S1HOME/sys/import-map.json $1
elif [ "${1: -3}" == ".py" ]
then
    if [ "$(uname)" == "Darwin" ]; then
       python3 $1
    else
       python $1
    fi
elif [ "${1: -5}" == ".dart" ]
then
    dart $1
fi
