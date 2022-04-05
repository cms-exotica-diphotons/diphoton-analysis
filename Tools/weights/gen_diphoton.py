#! /usr/bin/env python

import ROOT
import sys

import lhapdf

from DataFormats.FWLite import Events, Handle

# Make VarParsing object
# https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideAboutPythonConfigFile#VarParsing_Example
from FWCore.ParameterSet.VarParsing import VarParsing
options = VarParsing ('python')
options.parseArguments()
print "Using output file " + options.outputFile
# Events takes either
# - single file name
# - list of file names
# - VarParsing options

# use Varparsing object
events = Events (options)

# create handle outside of loop
handle  = Handle ("std::vector<reco::GenParticle>")
handle_geneventinfo = Handle("GenEventInfoProduct")

# for now, label is just a tuple of strings that is initialized just
# like and edm::InputTag
label = ("prunedGenParticles")
label_geneventinfo = ("generator")

# define needed PDF sets
# CUEP8M1: Tune:pp 14, lhapdf6 code: 
# option 13 : NNPDF2.3 QCD+QED LO alpha_s(M_Z) = 0.130. 
# CP2: Tune:pp 14, with PDF:pSet=LHAPDF6:NNPDF31_lo_as_0130, lhapdf6 code: 315200, alpha_s = 0.13

# Create histograms, etc.
ROOT.gROOT.SetBatch()        # don't pop up canvases
ROOT.gROOT.SetStyle('Plain') # white background
regions = ["all", "BB", "BE"]
diphotonMassHists = {}
diphotonMassWeightedHists = {}
weightHists = {}
for region in regions:
    diphotonMassHists[region] = ROOT.TH1F ("diphoton_mass_" + region, "diphoton mass, " + region, 120, 0, 6000)
    diphotonMassWeightedHists[region] = ROOT.TH1F ("diphoton_mass_weighted_" + region, "diphoton mass (weighted), " + region, 120, 0, 6000)
    weightHists[region] = ROOT.TH1F ("weight_" + region, "weight, " + region, 200, 0, 2)

f = ROOT.TFile(options.outputFile, "recreate")

eta_max_BB = 1.4442
eta_min_BE = 1.566
eta_max_BE = 2.5


pset_23 = lhapdf.getPDFSet("NNPDF23_lo_as_0130_qed")
pdf_23 = pset_23.mkPDF(0)
print(pset_23.description)

pset_31 = lhapdf.getPDFSet("NNPDF31_lo_as_0130")
pdf_31 = pset_31.mkPDF(0)
print(pset_31.description)

# loop over events
for i, event in enumerate(events):
    if(i % 100 == 0):
        print("Processing event {}".format(i))
    # use getByLabel, just like in cmsRun
    event.getByLabel (label, handle)
    event.getByLabel (label_geneventinfo, handle_geneventinfo)
    # get the product
    genParticles = handle.product()
    geneventinfo = handle_geneventinfo.product()
    # use photons to make diphoton invariant mass
    numGenParticles = len(genParticles)
    if numGenParticles < 2: continue
    id1 = geneventinfo.pdf().id.first
    id2 = geneventinfo.pdf().id.second
    # skip gluon-gluon-initiated events
    if id1 == 21 and id2 == 21:
        continue
    x1 = geneventinfo.pdf().x.first
    x2 = geneventinfo.pdf().x.second
    pdf1 = geneventinfo.pdf().xPDF.first
    pdf2 = geneventinfo.pdf().xPDF.second
    q = geneventinfo.pdf().scalePDF
    alpha_qcd = geneventinfo.qScale()
    pdf23_1_lhapdf = pdf_23.xfxQ2(id1, x1, q*q)
    pdf23_2_lhapdf = pdf_23.xfxQ2(id2, x2, q*q)
    pdf31_1_lhapdf = pdf_31.xfxQ2(id1, x1, q*q)
    pdf31_2_lhapdf = pdf_31.xfxQ2(id2, x2, q*q)
    weight = (pdf31_1_lhapdf/pdf1)*(pdf31_2_lhapdf/pdf2)
    debug = False
    if debug:
        print("comparison with sample:")
        print("pdf23_1 (alpha_QCD, event value, LHAPDF value, ratio): ({}, {}, {}, {})".format(alpha_qcd, pdf1, pdf23_1_lhapdf, pdf23_1_lhapdf/pdf1))
        print("pdf23_2 (alpha_QCD, event value, LHAPDF value, ratio): ({}, {}, {}, {})".format(alpha_qcd, pdf2, pdf23_2_lhapdf, pdf23_2_lhapdf/pdf2))
        print("weights")
        print("pdf31_1 (alpha_QCD, event value, LHAPDF value, ratio): ({}, {}, {}, {})".format(alpha_qcd, pdf1, pdf31_1_lhapdf, pdf31_1_lhapdf/pdf1))
        print("pdf31_2 (alpha_QCD, event value, LHAPDF value, ratio): ({}, {}, {}, {})".format(alpha_qcd, pdf2, pdf31_2_lhapdf, pdf31_2_lhapdf/pdf2))
        print("weight: {}".format(weight))
    for outer in xrange (numGenParticles - 1):
        outerPhoton = genParticles[outer]
        for inner in xrange (outer + 1, numGenParticles):
            innerPhoton = genParticles[inner]
            if not innerPhoton.pdgId() == 22 or not outerPhoton.pdgId() == 22:
                continue
            if not innerPhoton.isHardProcess() or not outerPhoton.isHardProcess():
                continue
            inner4v = ROOT.TLorentzVector (innerPhoton.px(), innerPhoton.py(),
                                           innerPhoton.pz(), innerPhoton.energy())
            outer4v = ROOT.TLorentzVector (outerPhoton.px(), outerPhoton.py(),
                                           outerPhoton.pz(), outerPhoton.energy())
            mass = (inner4v + outer4v).M()
            eta1 = innerPhoton.eta()
            eta2 = outerPhoton.eta()
            diphotonMassHists["all"].Fill(mass)
            diphotonMassWeightedHists["all"].Fill(mass, weight)
            weightHists["all"].Fill(weight)
            isBarrel1 = abs(eta1) < eta_max_BB
            isBarrel2 = abs(eta2) < eta_max_BB
            isEndcap1 = eta_min_BE < abs(eta1) < eta_max_BE
            isEndcap2 = eta_min_BE < abs(eta2) < eta_max_BE
            if isBarrel1 and isBarrel2:
                diphotonMassHists["BB"].Fill(mass)
                diphotonMassWeightedHists["BB"].Fill(mass, weight)
                weightHists["BB"].Fill(weight)
            if (isBarrel1 and isEndcap2) or (isBarrel2 and isEndcap1):
                diphotonMassHists["BE"].Fill(mass)
                diphotonMassWeightedHists["BE"].Fill(mass, weight)
                weightHists["BE"].Fill(weight)

# make a canvas, draw, and save it
c1 = ROOT.TCanvas()
for region in regions:
    diphotonMassHists[region].Draw()
c1.Print ("diphoton_mass_py.png")
#c1.Print (options.outputFile)
f.mkdir("gen")
f.cd("gen")
for region in regions:
    diphotonMassHists[region].Write()
    diphotonMassWeightedHists[region].Write()
    weightHists[region].Write()
f.Write()
f.Close()
