#!/bin/bash

i=0;

while :; do
    echo "Komunikat nr $i" > FIFO
    ((i++))
    sleep 1
done