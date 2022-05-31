#!/usr/bin/env python
'''
Create templates for real photon contributions
'''
years = [2016, 2017, 2018]
bins = [(0, 200), (0, 22), (23, 27), (28, 32), (33, 37), (38, 200)]
datasets = ["jetht", "doublemuon"]
for year in years:
    for bin in bins:
        pu = str(bin[0]) + " " + str(bin[1])
        arguments = str(year) + " all " + pu + " false"
        print("real_templates.exe " + arguments)
        for dataset in datasets:
            arguments = str(year) + " " + dataset + " " + pu
            print("fake_templates.exe " + arguments)
