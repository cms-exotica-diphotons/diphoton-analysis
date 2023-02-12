#! /bin/env python
''' Run limits for Unparticles diphoton analysis'''
import argparse
import os

parser = argparse.ArgumentParser()
parser.add_argument('-b', '--blind', action='store_true', help="Run with blinded data observation")
parser.add_argument('-c', '--combineCards', action='store_true', help="Create full datacards")
parser.add_argument('-d', '--directory', default="../../", help="Datacard directory.")
parser.add_argument('-r', '--runCombine', action='store_true', help="Run Combine AsymptoticLimits")
parser.add_argument('-g', '--gleanHarvesting', action='store_true', help="Run Combine Harvester CollectLimits")
parser.add_argument('-p', '--plotLimits', action='store_true', help="Run plotLimits from CombineHarvester")
parser.add_argument('-s', '--switchBin', action='store_true', help="Run on rebinned datacards")
parser.add_argument('-m', '--masscut', type=int, help="Masscut", default=2000)
args = parser.parse_args()

'''STEP1: Run Combine Cards'''
'''step1.a - combine cards with option -c with -b if with blinded'''
'''step1.b - runCombine with option -r or -b with blinded results'''
'''STEP2: Collect Limits in json files with option -g'''
'''STEP3: plotLimits with option -p'''

blind_data    = args.blind
create_cards  = args.combineCards
relative_path = args.directory
run_Combine   = args.runCombine
run_Harvester = args.gleanHarvesting
run_plotter   = args.plotLimits
run_rebinned  = args.switchBin
massCut       = args.masscut

#UnparToGG_Spin0_du1p1_LambdaU-8000_TuneCP2_13TeV_pythia8_2017_BE.dat

LambdaU_values = {'Spin0_du1p1' : {4000, 8000, 10000},
                  'Spin0_du1p5' : {2000, 2500, 3500},
                  'Spin0_du1p9' : {2000, 2500, 3500},
                  'Spin2_du1p1' : {2000, 2500, 3000},
                  'Spin2_du1p5' : {2000, 2500, 3000},
                  'Spin2_du1p9' : {2000, 2500, 3500}}

dimensions = []
dimensions.extend(['Spin0_du1p1', 'Spin0_du1p5', 'Spin0_du1p9', 'Spin2_du1p1', 'Spin2_du1p5', 'Spin2_du1p9'])
extraOptions = "--rMax 2"
if blind_data:
    extraOptions += " --run blind"
else:
    extraOptions += ' --text2workspace "--max-bin 20"'

regions = {"BB", "BE"}
years = {"2016", "2017", "2018"}
# # years = {"2017"}
# years = {"2018"}
for dimension in dimensions:
    for LambdaU_val in LambdaU_values[dimension]:
        name = 'UnparToGG_' + dimension + '_LambdaU-' + str(LambdaU_val) + '_TuneCP2_13TeV_pythia8'

        #outputdatacard = "datacards/" + name + "_combined_blinded.dat"
        outputdatacard = "datacards/" + name + "_combined.dat"

        if massCut is not None:
            outputdatacard = "datacards/" + name + "_m" + str(massCut) +  "_combined.dat"

        if blind_data:
            # insert blinded string
            index          = outputdatacard.find('.dat')
            outputdatacard = outputdatacard[:index] + '_blinded' + outputdatacard[index:]

            if run_rebinned:
                outputdatacard = outputdatacard[:index] + '_blinded_rebinned' + outputdatacard[index:]


        cmd = "combineCards.py "
        for year in years:
            for region in regions:
                inCardName = name + "_" + year + "_" + region + ".dat "

                if run_rebinned:
                    inCardName = name + "_rebinned_" + year + "_" + region + ".dat "

                if massCut is not None:
                    inCardName = name + "_m" + str(massCut) + "_" + year + "_" + region + ".dat "


                cmd += region + "_" + year + "=" + "datacards/" + inCardName
        cmd += " > " + outputdatacard

        if create_cards:
            print cmd
            os.system(cmd)
            cmd = "sed -i 's|datacards/datacards|datacards|g' " + outputdatacard  # What is this for?

        if run_Combine:
            runCombinecmd = 'combine -M AsymptoticLimits ' + outputdatacard + ' ' + extraOptions + ' -n ' + name + ' -m ' + str(LambdaU_val)
            print runCombinecmd
            os.system(runCombinecmd)


if run_Harvester:
    for dimension in dimensions:
        # combineTool.py -M CollectLimits higgsCombineUnparToGG_Spin0_du1p1_LambdaU*.AsymptoticLimits.m*.root -o limitsSpin0_du1p1_2018.json
        harvestCmd = "combineTool.py -M CollectLimits higgsCombineUnparToGG_" + dimension + '_LambdaU*.AsymptoticLimits.m*.root -o limits' + dimension + ".json"
        if blind_data:
            index          = harvestCmd.find('.dat')
            outputdatacard = harvestCmd[:index] + '_blinded' + harvestCmd[index:]

        print harvestCmd
        os.system(harvestCmd)

if run_plotter:
    for dimension in dimensions:
        # plotLimits.py limitsSpin0_du1p1_2018.json -o limitsSpin0_du1p1_2018 --x-title r#Lambda_{U} --scenario-label Spin0_du1p1
        jsonfilename = "limits" + dimension
        if blind_data:
            jsonfilename = jsonfilename + '_blinded'
        #plotCmd = "plotLimits.py " + jsonfilename + ".json -o " + jsonfilename + " --x-title r#Lambda_{U}"
        #plotCmd = "python plotlimitsCombine.py " + jsonfilename + ".json -o " + jsonfilename + " --x-title r#Lambda_{U}"
        plotCmd = "python plotlimitsCombine.py -i " + jsonfilename + ".json" 
        print plotCmd
        os.system(plotCmd)
