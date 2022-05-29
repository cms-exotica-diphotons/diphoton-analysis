#!/usr/bin/env python
'''
Fit histogram templates for diphoton analysis
'''
years = [2016, 2017, 2018]
# "gg" fakes are used for real photon contamination estimates
datasets = ["gg", "data"]
fake_types = ["average", "jetht", "doublemuon"]
regions = ["BB", "BE"]
regions_alternate = ["barrel", "endcap"]
for year in years:
    for dataset in datasets:
        for fake_type in fake_types:
            arguments = dataset + " " + str(year) +  " " + fake_type
            print("getFakePrediction.exe " + arguments)

for year in years:
    for region in regions:
            arguments = region + " " + str(year)
            print("makeHistograms.exe " + arguments)

for year in years:
    arguments = str(year)
    samples = {"old", "new"}
    for sample in samples:
        print("makeDatacards.exe " + arguments + " " + sample)

for year in years:
    for region in regions_alternate:
        arguments = region + " " + str(year)
        print("datadriven.exe " + arguments)

for year in years:
    for region in regions_alternate:
        arguments = region + " " + str(year)
        print("basicplots.exe " + arguments)
