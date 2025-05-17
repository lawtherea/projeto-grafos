#!/bin/bash

# Caminho para o executável
exe=../carraghan_pardalos/carraghan_pardalos.exe

cd ../carraghan_pardalos

echo "Testando algoritmo de Carraghan-Pardalos"
for i in caso{1..20}.txt
 do
    echo -e "\e[33mInstância $i\e[0m";
    base=$(basename $i .txt)
    gabarito="${base}-gabarito.txt"
    $exe -f $i > temp
    diff -w temp $gabarito > /dev/null
    if [ $? -eq 0 ]; then
        echo -e "\e[32mOK\e[0m"
    else
        echo -e "\e[31mErro\e[0m"
    fi
    rm temp
 done 