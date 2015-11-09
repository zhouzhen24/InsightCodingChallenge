#!/bin/bash

mkdir -p build
cd build
cmake -G "Unix Makefiles" ..
make
cd ..
mkdir -p log
mkdir -p tweet_input
mkdir -p tweet_output
./insight tweets.txt 1>log/output.log 2>log/error.log
