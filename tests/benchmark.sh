#!/usr/bin/env bash

clear

echo -e "Evaluating empty METAFONT program..."
echo "end" > .tmp.mf
var=$( { time mf .tmp.mf; } 2>&1 )
out=$(echo ${var} | egrep -o "real [^ ]*m[^ ]*s")
echo -e "METAFONT:\t\t"${out}
var=$( { time ./benchmark_mf .tmp.mf; } 2>&1 )
out=$(echo ${var} | egrep -o "real [^ ]*m[^ ]*s")
echo -e "Weaver Metafont:\t"${out}
rm .tmp.mf
