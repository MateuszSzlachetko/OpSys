#!/bin/bash

# Część pierwsza

# while :; do
#     echo $(date "+%T")
#     sleep 1
# done

# Dla kolejnych wywołań
# ps -f -u exo i wyszukaniu pid skrypty
# wysyłanie mu sygnałów poleceniem
# kill -s signal_name pid
# zabijało proces z odpowiednim komunikatem

# Część druga

while :; do
    echo $(date "+%T")
    sleep 1
    trap 'echo Signal catched' 2 3 8 4
done

# W skrypcie wywołanym na diablo w Bourne shellu
# program wyłapywał sygnały jak widać na zdjęciu zad3.png
