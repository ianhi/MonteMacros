#!bin/bash
i=0
echo "med1" >med1Filelist.txt
while [ $i -lt 100 ]
do
    echo "root://eosuser.cern.ch://eos/user/i/ihuntisa/Jewel/med1/JewelDijet_${i}_numEvent1000.root" >> med1Filelist.txt
    let 'i++'
done
cat med1Filelist.txt

