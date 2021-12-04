#!/bin/bash

day=$1
mkdir day${day}
cp "./template.cpp" "./day${day}/main.cpp"
cp "./test.sh" "./day${day}/test.sh"

# prepare the files
touch ./day${day}/input1.txt
touch ./day${day}/actual1.txt
curl https://adventofcode.com/2021/day/${day}/input --cookie "session=$SESSION" -o ./day${day}/input2.txt

# make test.sh executable
cd ./day${day}/
chmod +x test.sh