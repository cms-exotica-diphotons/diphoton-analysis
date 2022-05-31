#!/usr/bin/env python
'''
Fit histogram templates for diphoton analysis
'''
years = [2016, 2017, 2018]
bins = {}
bins[2016] = [(0, 22), (23, 27), (28, 200)]
bins[2017] = [(0, 22), (23, 27), (28, 32), (33, 37), (38, 200)]
bins[2018] = bins[2017]

datasets = ["jetht", "doublemuon"]
variable = "sieie"
for dataset in datasets:
    for year in years:
        for bin in bins[year]:
            pu = str(bin[0]) + " " + str(bin[1])
            arguments = dataset + " " + variable + " " + str(year) +  " " + pu
            print("fakeRateCalculation.exe " + arguments)

for year in years:
    print("compare_pv.exe " + str(year))
    print("compare_pv_bin.exe " + str(year))
