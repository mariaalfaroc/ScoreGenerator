# -*- coding: utf-8 -*-

import argparse

from generator import scoreGenerator

INPUT_MODES = ['mono', 'homo', 'poly-ss', 'piano-mono', 'piano-homo']
INPUT_AG = ['standard', 'split']


def menu():
    """Parser for command-line arguments."""
    parser = argparse.ArgumentParser(description='Score Generator for End-to-End OMR')
    parser.add_argument('-numS', required=True, help='Number of scores to generate', type=int)
    parser.add_argument('-mode', required=True, help='Music texture of the scores', choices=INPUT_MODES, type=str)
    parser.add_argument('-numB', required=True, help='Number of bars/measures per score', type=int)
    parser.add_argument('-typeAg', required=True, help='Separator for the agnostic representation', choices=INPUT_AG,
                        type=str)
    parser.add_argument('-limitS', required=True, help='Number of maximum staves per page', type=int)
    return parser.parse_args()


# -- MAIN #

if __name__ == "__main__":
    # 1. Get command - line arguments
    args = menu()

    # 2. Generate
    scoreGenerator(numScores=args.numS,
                   musicTexture=args.mode,
                   numBars=args.numB,
                   typeAgnostic=args.typeAg,
                   nstaves=args.limitS
                   )
