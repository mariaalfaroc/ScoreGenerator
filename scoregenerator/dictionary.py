# -*- coding: utf-8 -*-

import random

# -- INTERNAL REPRESENTATION GRAMMAR -- #

advance = '\n'
not_advance = '\t'
separator = ' '

durations = [
    4,  # whole
    2,  # half
    1,  # quarter
    0.5,  # eighth
    0.25  # sixteenth
]

clefs = ["clefG2", "clefF4", "clefC3", "clefC1", "clefG1", "clefC2", "clefC4"]

# Each Clef has 22 possibles absolute pitches
pitches = {
    "clefG2": ['E3', 'F3', 'G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4', 'G4', 'A4', 'B4', 'C5', 'D5', 'E5', 'F5', 'G5',
               'A5', 'B5', 'C6', 'D6', 'E6'],
    "clefF4": ['G1', 'A1', 'B1', 'C2', 'D2', 'E2', 'F2', 'G2', 'A2', 'B2', 'C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3',
               'C4', 'D4', 'E4', 'F4', 'G4'],
    "clefC3": ['F2', 'G2', 'A2', 'B2', 'C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4', 'G4', 'A4',
               'B4', 'C5', 'D5', 'E5', 'F5'],
    "clefC1": ['C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4', 'G4', 'A4', 'B4', 'C5', 'D5', 'E5',
               'F5', 'G5', 'A5', 'B5', 'C6'],
    "clefG1": ['G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4', 'G4', 'A4', 'B4', 'C5', 'D5', 'E5', 'F5', 'G5', 'A5', 'B5',
               'C6', 'D6', 'E6', 'F6', 'G6'],
    "clefC2": ['A2', 'B2', 'C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4', 'G4', 'A4', 'B4', 'C5',
               'D5', 'E5', 'F5', 'G5', 'A5'],
    "clefC4": ['D2', 'E2', 'F2', 'G2', 'A2', 'B2', 'C3', 'D3', 'E3', 'F3', 'G3', 'A3', 'B3', 'C4', 'D4', 'E4', 'F4',
               'G4', 'A4', 'B4', 'C5', 'D5']
}

# For each Key Signature, the accidentals are saved (type and pitches, respectively)
keys = ["cM", "gM", "dM", "aM", "eM", "bM", "fsM", "csM", "cfM", "gfM", "dfM", "afM", "efM", "bfM", "fM"]
accidentals = {
    "cM": ['', []],
    "gM": ['#', ['F']],
    "dM": ['#', ['F', 'C']],
    "aM": ['#', ['F', 'C', 'G']],
    "eM": ['#', ['F', 'C', 'G', 'D']],
    "bM": ['#', ['F', 'C', 'G', 'D', 'A']],
    "fsM": ['#', ['F', 'C', 'G', 'D', 'A', 'E']],
    "csM": ['#', ['F', 'C', 'G', 'D', 'A', 'E', 'B']],
    "cfM": ['-', ['B', 'E', 'A', 'D', 'G', 'C', 'F']],
    "gfM": ['-', ['B', 'E', 'A', 'D', 'G', 'C']],
    "dfM": ['-', ['B', 'E', 'A', 'D', 'G']],
    "afM": ['-', ['B', 'E', 'A', 'D']],
    "efM": ['-', ['B', 'E', 'A']],
    "bfM": ['-', ['B', 'E']],
    "fM": ['-', ['B']]
}
typeAcc = ["#", "-", "+"]

# Bar/measure duration in quarter notes
bars = [("M4/4", 4),
        ("M3/4", 3),
        ("M2/2", 4),
        ("M2/4", 2),
        ("M6/8", 3),
        ("M12/8", 6),
        ("M9/8", 4.5),
        ("M5/4", 5)]


# -- INTERNAL REPRESENTATION GRAMMAR -- #


# Function to choose the Clef
def chooseClef():
    # clefG2 -> 45 %
    # clefF4 -> 20 %
    # clefC3 -> 15 %
    # clefC1 -> 5 %
    # clefG1 -> 5 %
    # clefC2 -> 5 %
    # clefC4 -> 5 %
    return random.choices(clefs, weights=(45, 20, 15, 5, 5, 5, 5), k=1)[0]


# Function to choose the Time Signature
def chooseTimeSig():
    # 4/4  -> 50 %
    # 3/4  -> 25 %
    # 2/2  -> 12 %
    # 2/4  -> 5 %
    # 6/8  -> 2 %
    # 12/8 -> 2 %
    # 9/8  -> 2 %
    # 5/4  -> 2 %
    return random.choices(bars, weights=(50, 25, 12, 5, 2, 2, 2, 2), k=1)[0]


# Function to choose the Key
def chooseKey():
    return random.choices(keys, weights=(42, 10, 8, 6, 4, 1, 1, 1, 1, 1, 1, 4, 6, 8, 10), k=1)[0]
