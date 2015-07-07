source /afs/cern.ch/project/eos/installation/cms/etc/setup.sh
eos rm root://eosuser.cern.ch://eos/user/i/ihuntisa/pthat_NO_Weight.png
eos rm root://eosuser.cern.ch://eos/user/i/ihuntisa/pthat_QCD_Weight.png
eos rm root://eosuser.cern.ch://eos/user/i/ihuntisa/pthat_SUM_Weight.png
eos rm root://eosuser.cern.ch://eos/user/i/ihuntisa/QCD_Weight_jtpt.png
eos rm root://eosuser.cern.ch://eos/user/i/ihuntisa/SUM_Weight_jtpt.png

xrdcp pthat_NO_Weight.png root://eosuser.cern.ch://eos/user/i/ihuntisa/
xrdcp pthat_QCD_Weight.png root://eosuser.cern.ch://eos/user/i/ihuntisa/
xrdcp pthat_SUM_Weight.png root://eosuser.cern.ch://eos/user/i/ihuntisa/
xrdcp QCD_Weight_jtpt.png root://eosuser.cern.ch://eos/user/i/ihuntisa/
xrdcp SUM_Weight_jtpt.png root://eosuser.cern.ch://eos/user/i/ihuntisa/
