#!/bin/bash

cd flex/src
make
./a.out ../test/test.txt
cd ..
cd ..
cd shift-reduce
make
./a.out