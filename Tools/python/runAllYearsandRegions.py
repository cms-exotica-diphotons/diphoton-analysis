import ROOT
import argparse
import re
from itertools import imap

parser = argparse.ArgumentParser(description='Run Python Files for all years and Regions')
parser.add_argument('--filterAndRename', action='store_true', help='RunFiltering')
parser.add_argument('--removeDuplicates', action='store_true', help='RunFiltering')
parser.add_argument('--rebinHistograms', action='store_true', help='RunFiltering')
