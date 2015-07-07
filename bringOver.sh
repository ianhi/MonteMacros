#!bin/bash
i=1
while [ $i -lt 46 ]
do
xrdcp root://xrootd.cmsaf.mit.edu//store/user/rkunnawa/rootfiles/JetRAA/pp_mc_weights/weights_pp_${i}.root .

let 'i++'
done