#!/bin/bash

while :; do
    echo $(date "+%T")
    sleep 1
    trap 'echo Signal catched' 2 3 8 4
done

# badając otwarte pliki poleceniem ls -l /proc/7536/fd
# możemy zauważyć plik 'pipe:[71065]'
# w programie środkowym są dwa takie pliki
# w programie pierwszym i ostatnim jeden
# numery są rosnące i na tej podstawie możemy stwierdzić
# który proces był pierwszy który środkowy, kolejny
# dla większej ilości procesów i który ostatni
# dla kilku potokowanych programów działa to tak samo