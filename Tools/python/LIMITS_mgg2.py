import sys;
from time       import gmtime, strftime

Beginning = strftime("%H:%M:%S",gmtime());

MASS      =sys.argv[2];
CHANNEL   =sys.argv[3];
YEAR      =sys.argv[4];
SIGNAL    =sys.argv[5];

print '\n\n\n','_'*40, MASS, CHANNEL, YEAR, SIGNAL,'_'*40;

SIGNAL_LIST=[ "ADDGRW","ADDHew","CWk" ];
SIGNAL_DROP=[ "ADDGRW","ADDHew","CWk" ]; SIGNAL_DROP.remove(SIGNAL); #print SIGNAL_DROP;

if SIGNAL=="ADDGRW" and MASS not in ["5000","6000","7000","8000","9000","10000","11000"] : sys.exit();
if SIGNAL=="ADDHew" and MASS not in ["6500","7000","7500","8000","9000","10000","11000"] : sys.exit();

if SIGNAL not in SIGNAL_LIST: print "\n ! WRONG SIGNAL INPUT ! \n";
#if MASS       not in ["2000","2500","3000","3500","4000","4500","5000","5500","6000","6500","7000","7500","8000","8500","9000","10000","11000","13000"]: print MASS,"mass not expected";

REBIN_FACTOR = 1;
DATA_TYPE='data'; #  'input="toys-asimov:0.0"'          'data'

#=============[ FUNCTION DEFINITIONS ]=============================
def histogramFilter(histName):
    if histName[0:2] not in CHANNEL: return False;
    if histName[2:4] not in YEAR   : return False;
    for i in SIGNAL_DROP:
        if i in histName           : return False;
    if SIGNAL in histName and MASS     not in histName: return False;
    if "CWk" in histName and histName.endswith("k"+MASS)==False: return False;
    #if "__PSEUDODATA"     in histName: return False;
    if "__DATA"        in histName : return False;
    if "energySigma"   in histName : return False;
    if "pileup"        in histName : return False;
    if "kfactorStat"   in histName : return False;
    if "Unpar"         in histName : return False;
    #if "dyNLO"  in histName: return False;
    #if "vgNLO"      in histName: return False;
    #if "ttgNLO"     in histName: return False;
    #if "w" is  histName[6:7]: return False;
    #if "other"       in histName: return False;
    #if SIGNAL in histName and SIGNAL in histName and MASS not in histName: return False
    #if "gg"       in histName: return False
    #if "gj"       in histName: return False
    #if "jj"       in histName: return False
    #if histName[:1]=="w"     : return False

    #if "eff"             in histName: return False
    #if "energyScaleGain" in histName: return False
    #if "energyScaleSyst" in histName: return False
    #if ("jj" and "plus" in histName) or ("jj" and "minus" in histName): return False;
    #"eff" or "energyScaleGain" or "energyScaleStat" or "energyScaleSyst" or "energySigma" or "pileup" in histName and "jj" in histName: return False;
    #for x in range(0,51):
    #    if 'pdf'+str(x) in histName: return False;
    #if "kfactorStat"     in histName: return False
    #if "diphotonkfactorScales" in histName: return False
    #if "fakesample"          in histName: return False
    #if SIGNAL=="CWk":        #________________[ Blinding above 1 TeV ]____________________
    #    vals = histName.get_values()                   #print "BEFORE ===>",vals[44],vals[45],vals[46] #print 'hist.get_x_low(0)', hist.get_x_low(0), hist.get_xmax()
    #    print "vals", vals;
