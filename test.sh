#!/bin/bash -e

root=$(dirname "$BASH_SOURCE")
g++ -std=c++20 "-I$root/algo" -O3 -DMOD=4611686018427387847 "${@:2}" "$root/tests/$1.cpp"
./a.out
