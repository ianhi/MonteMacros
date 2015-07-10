'''
Ian Hunt-Isaak
ihuntisa@oberlin.edu -Primary email un may 2017
ianhuntisaak@gmail.com - Permanent email

This file extracts the sum of cross section weights from the below section of the Jewel out.log file. SUM = sum of all cross sections. QCD =  f + f' -> f + f' cross section

          ==========================================================
           I                                      I                 I
           I  ISUB  Subprocess name               I  Maximum value  I
           I                                      I                 I
           ==========================================================
           I                                      I                 I
           I   11   f + f' -> f + f' (QCD)        I    3.0909D+05   I
           I   12   f + fbar -> f' + fbar'        I    6.6762D+03   I
           I   13   f + fbar -> g + g             I    3.1201D+03   I
           I   28   f + g -> f + g                I    3.4405D+05   I
           I   53   g + g -> f + fbar             I    2.5473D+03   I
           I   68   g + g -> g + g                I    5.2598D+04   I
           I                                      I                 I
           ==========================================================

'''
import sys
f = open('out.txt', 'w')
minFile=0
maxFile=11
skipSix=True
SUMString=""
QCDString=""

for fileNum in range(minFile,maxFile):
    SUM=0
    if skipSix and fileNum==6:
        SUMString+="-1,"
        continue
    print "\n\n\nFILE   :"+str(fileNum)+""
    File = open(str(fileNum)+'_25K.log')
    #104 gets first one
    #109 gets last one
    for i in range(0,103):
        File.readline()
    for i in range(0,6):
        line=File.readline().replace('D','E')
        if i==0:
            QCDString+=str(float(line[55:-2]))+","

        SUM+=float(line[55:-2])
        print float(line[55:-2])
    SUMString+=str(SUM)+","
print "SUM cross sections:"
print SUMString[:-1]#slice removes final comma
print "QCD cross sections:"
print QCDString[:-1]#slice removes final comma
