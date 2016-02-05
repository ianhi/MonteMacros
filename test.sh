eval `scramv1 runtime -sh`
export X509_USER_PROXY=~/x509_user_proxy/proxy
voms-proxy-init --noregen
cd /afs/cern.ch/work/i/ihuntisa/WORK/RUTGERS/CMSSW_5_3_20/src/MonteMacros/
echo "root -l -b -q ppData.C++"
echo "============BEGIN MACRO============"
#root -b <<EOF
#.x ppDataTESTSEG.C();
#.q
#EOF
eval 'root ppDataTESTSEG.C+\(6,9\) -b -q'



