#!/bin/bash

total=0

if ! [ $# -eq 2 ]; then
    echo "Two input parameters are required: the first is the number of clients to create and the second is the ip of the server to which they must connect."
    exit 1
fi

if ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "The number of clients to create must be a number."
    exit 1
fi

for ((i=1; i<=$1; i++))
do
    ./bin/client 0 $2 &

    total=$((total+1))

    sleep $(echo "scale=3; $RANDOM/32767*0.3" | bc -l)

    echo "CLIENTES CREADOS: $total"
    echo -e "\n"
done

exit 0