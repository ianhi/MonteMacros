#!bin/bash
i=0

while [ $i -lt 11 ]
do
cp ../outputs/${i}_numEvents25000/out.log ${i}_25K.log
let 'i++'
done
