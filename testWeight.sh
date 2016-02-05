cd /afs/cern.ch/work/i/ihuntisa/WORK/RUTGERS/CMSSW_5_3_20/src/
#cmsenv
eval `scramv1 runtime -sh`
#Added by Ian
export X509_USER_PROXY=~/x509_user_proxy/proxy
voms-proxy-init --noregen
#</Ian>
cd /afs/cern.ch/work/i/ihuntisa/WORK/RUTGERS/CMSSW_5_3_20/src/MonteMacros/
echo "root -l -b -q ppWeight.C++"
echo "First = $FIRST and last file = $LAST"
root -b -q ppWeight.C+\(${FIRST},${LAST},3\)
echo "Done all jobs!"
