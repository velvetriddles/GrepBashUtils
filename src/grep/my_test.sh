#!/bin/bash

dir="tests"
success=0
cmd="grep"
regexp="xxx"

flags="-e -i -v -c -l -n -h -s -o"
skip_flags="-e -f"

if ! [[ -f ./s21_grep ]]; then
  echo "No such file exe for testing :("
  exit 1
fi

index=0

# Тестирование отдельных флагов
for file in ${dir}/*; do
  index=$(( index + 1 ))
  printf "Test ${file} with no flags "
  if diff -q <(./s21_grep ${regexp} ${file}) <(${cmd} ${regexp} ${file}) > /dev/null; then
    echo " OK!"
    success=$(( success + 1 ))
  else
    echo " FAIL!"
  fi
  sleep 0.1
  
  for flag in ${flags}; do
    index=$(( index + 1 ))
    printf "Test ${file} with ${flag} "
    if diff -q <(./s21_grep ${flag} ${regexp} ${file}) <(${cmd} ${flag} ${regexp} ${file}) > /dev/null; then
      echo " OK!"
      success=$(( success + 1 ))
    else
      echo " FAIL!"
    fi
    sleep 0.1
  done
done

# Тестирование с двумя файлами для каждого флага
for flag in ${flags}; do
  if [[ ${skip_flags} =~ ${flag} ]]; then
    continue
  fi
  index=$(( index + 1 ))
  printf "Test 2 files with ${flag} "
  if diff -q <(./s21_grep ${flag} ${regexp} tests/test_1.dat tests/test_2.dat) <(${cmd} ${flag} ${regexp} tests/test_1.dat tests/test_2.dat) > /dev/null; then
    echo " OK!"
    success=$(( success + 1 ))
  else
    echo " FAIL!"
  fi
  sleep 0.1
done

# Тестирование с двумя файлами и флагом -f
index=$(( index + 1 ))
printf "Test 2 files with -f "
if diff -q <(./s21_grep -f tests/regex.txt tests/test_1.dat tests/test_2.dat) <(${cmd} -f tests/regex.txt tests/test_1.dat tests/test_2.dat) > /dev/null; then
  echo " OK!"
  success=$(( success + 1 ))
else
  echo " FAIL!"
fi
sleep 0.1

# Тестирование комбинаций флагов
flag_array=($flags)
num_flags=${#flag_array[@]}

# Тестирование комбинаций по два флага
for (( i = 0; i < num_flags; i++ )); do
  for (( j = i + 1; j < num_flags; j++ )); do
    flag_pair="${flag_array[i]} ${flag_array[j]}"
    if [[ ${skip_flags} =~ ${flag_array[i]} ]] || [[ ${skip_flags} =~ ${flag_array[j]} ]]; then
      continue
    fi
    index=$(( index + 1 ))
    printf "Test 2 files with ${flag_pair} "
    if diff -q <(./s21_grep ${flag_pair} ${regexp} tests/test_1.dat tests/test_2.dat) <(${cmd} ${flag_pair} ${regexp} tests/test_1.dat tests/test_2.dat) > /dev/null; then
      echo " OK!"
      success=$(( success + 1 ))
    else
      echo " FAIL!"
    fi
    sleep 0.1
  done
done

# Тестирование комбинаций по три флага
for (( i = 0; i < num_flags; i++ )); do
  for (( j = i + 1; j < num_flags; j++ )); do
    for (( k = j + 1; k < num_flags; k++ )); do
      flag_trio="${flag_array[i]} ${flag_array[j]} ${flag_array[k]}"
      if [[ ${skip_flags} =~ ${flag_array[i]} ]] || [[ ${skip_flags} =~ ${flag_array[j]} ]] || [[ ${skip_flags} =~ ${flag_array[k]} ]]; then
        continue
      fi
      index=$(( index + 1 ))
      printf "Test 2 files with ${flag_trio} "
      if diff -q <(./s21_grep ${flag_trio} ${regexp} tests/test_1.dat tests/test_2.dat) <(${cmd} ${flag_trio} ${regexp} tests/test_1.dat tests/test_2.dat) > /dev/null; then
        echo " OK!"
        success=$(( success + 1 ))
      else
        echo " FAIL!"
      fi
      sleep 0.1
    done
  done
done

echo "Success: ${success}/${index}"
