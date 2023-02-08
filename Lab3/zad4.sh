#!/bin/bash

# Skrypt jak w zadaniu nr 3

# przy testach polecenie fg %./zad4 było bardziej
# podobne, przy bg proces nie reagował na ponowne Ctrl+Z
# wysyłanie kill -s SIGSTOP pid i kill -s SIGCONT pid
# działało poprawnie


while :; do
    echo $(date "+%T")
    sleep 1
done