#!/bin/bash

dir="tests"
success=0
cmd="cat"

flags="-b --number-nonblank -e -E -n --number -s --squeeze-blank -t -T -v"

if ! [[ -f s21_cat ]]; then
  echo "Нет исполняемого файла для тестирования :("
  exit 1
fi

index=0

for file in ${dir}/*; do
  index=$((index + 1))
  printf "Тест ${file} без флагов "
  if diff -q <(./s21_cat ${file}) <(${cmd} ${file}) > /dev/null; then
    echo " УСПЕШНО!"
    success=$((success + 1))
  else
    echo " НЕУДАЧА!"
  fi
  sleep 0.1
  
  for flag in ${flags}; do
    index=$((index + 1))
    printf "Тест ${file} с флагом ${flag} "
    if diff -q <(./s21_cat ${flag} ${file}) <(${cmd} ${flag} ${file}) > /dev/null; then
      echo " УСПЕШНО!"
      success=$((success + 1))
    else
      echo " НЕУДАЧА!"
    fi
    sleep 0.1
  done
done

echo "Успешно: ${success}/${index}"
