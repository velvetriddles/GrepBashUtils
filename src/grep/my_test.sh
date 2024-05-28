#!/bin/bash

dir="tests"
succes=0
cmd="grep"
regexp="xxx"

flags="-e -i -v -c -l -n -h -s -o"

if ! [[ -f ./s21_grep ]]; then
  echo "No such file exe for testing :("
  exit 1
fi

for file in ${dir}/*; do
  index=$[ $index + 1 ]
  printf "Test ${file} with no flags "
  if diff -q <(./s21_grep ${regexp} ${file}) <(${cmd} ${regexp} ${file}) > /dev/null; then
    echo " OK!"
    succes=$[ $succes + 1 ]
  else
    echo " FAIL!"
  fi
  sleep 0.1
  
  for flag in ${flags}; do
    index=$[ $index + 1 ]
    printf "Test ${file} with "${flag}" "
    if diff -q <(./s21_grep ${flag} ${regexp} ${file}) <(${cmd} ${flag} ${regexp} ${file}) > /dev/null; then
      echo " OK!"
      succes=$[ $succes + 1 ]
    else
      echo " FAIL!"
    fi
    sleep 0.1
  done

done

for flag in ${flags}; do
    index=$[ $index + 1 ]
    printf "Test 2 files with "${flag}" "
    if diff -q <(./s21_grep ${flag} ${regexp} tests/test_1.dat tests/test_2.dat) <(${cmd} ${flag} ${regexp} tests/test_1.dat tests/test_2.dat) > /dev/null; then
      echo " OK!"
      succes=$[ $succes + 1 ]
    else
      echo " FAIL!"
    fi
    sleep 0.1
done

index=$[ $index + 1 ]
printf "Test 2 files with -f "
if diff -q <(./s21_grep -f tests/regex.txt tests/test_1.dat tests/test_2.dat) <(${cmd} -f tests/regex.txt tests/test_1.dat tests/test_2.dat) > /dev/null; then
  echo " OK!"
  succes=$[ $succes + 1 ]
else
  echo " FAIL!"
fi
sleep 0.1

echo "Success: ${succes}/${index}"
