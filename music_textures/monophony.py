# -*- coding: utf-8 -*-

import manager
import symbol
from dictionary import pitches, chooseClef, chooseKey, chooseTimeSig


def loop_generation(numScores: int, numBars: int, typeAgnostic: str):
    manager.create_folds()
    for i in range(numScores):
        scoreGenerator(i, numBars, typeAgnostic)
    return


def scoreGenerator(id: int, numBars: int, typeAgnostic: str):
    # Create OUT files
    manager.init(i=id, typeAgnostic=typeAgnostic)

    # Choose clef, key and time signature
    clef = chooseClef()
    manager.write_clef(clef)
    key = chooseKey()
    manager.write_key(key)
    timeSig = chooseTimeSig()  # Returns tuple of aspect (M*/*, duration in quarter notes)
    manager.write_timeSig(timeSig)

    # Instantiate initial values
    bar_accidentals = {}
    tie = 0  # No tie
    id_start, id_stop = 0, len(pitches[clef]) - 1  # Full range
    pitch = int((id_start + id_stop + 1) / 2)  # It corresponds to the pitch that falls on the third line of the staff

    for i in range(1, numBars + 1):
        lastbar = True if i == numBars else False
        manager.write_barLine(i)

        # Get bar duration
        duration = timeSig[1]
        while duration > 0:
            # Generate either a note or a silence
            s = symbol.generateSymbol(clef=clef, key=key, duration=duration, tie=tie, prevpitch=pitch, lastbar=lastbar,
                                      bar_accidentals=bar_accidentals, id_start=id_start, id_stop=id_stop)
            # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD = 0, DOT = 0]
            duration = duration - s[1]
            pitch = s[2]
            tie = s[3]
            manager.write_symbol(s=[s[0]], bar_accidentals=bar_accidentals)
        # We clear the temporal bar accidentals dictionary
        bar_accidentals.clear()

    # End of score
    manager.write_end()

    return


if __name__ == "__main__":
    # musicTexture = ['mono', 'homo', 'poly-ss', 'piano-mono', 'piano-homo']
    # typeAgnostic = ['standard', 'split']
    musicTexture, typeAgnostic = 'mono', 'standard'
    symbol.valueMode(musicTexture=musicTexture)
    loop_generation(numScores=4, numBars=6, typeAgnostic=typeAgnostic)
    manager.preprareforOMR(musicTexture=musicTexture, typeAgnostic=typeAgnostic)

