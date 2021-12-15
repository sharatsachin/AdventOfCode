#!/bin/bash

clang-format  -style=file -i main.cpp

g++ -std=c++17 main.cpp -o main
chmod 744 main
echo -e "\n= output ="
./main small < input1.txt
echo -e "\n= actual ="
cat < actual1.txt
echo -e "\n=========="

echo -e "Do they agree?"
read inp
if [[ $inp = "y" ]]
then
    echo "= output =";
    ./main big < input2.txt;
fi