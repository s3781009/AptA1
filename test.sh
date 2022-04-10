#!/bin/bash
if [  ! -f maze ]; then
exec g++ -Wall -Werror -std=c++14 -O -o a *.cpp
fi
for file in test/input/*; do 
printf "\n\n"
 echo "testing : $file"
  ./maze < $(pwd)/test/input/"$(basename "$file")" 
done