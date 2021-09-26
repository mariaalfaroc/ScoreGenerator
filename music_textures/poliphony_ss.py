# -*- coding: utf-8 -*-

import manager
import symbol
from dictionary import pitches, chooseClef, chooseKey, chooseTimeSig


# Two voices on a single staff
# Chords are not allowed, hence each voice itself is monophonic
# The lowest voice uses the lower half of the pitch range of the clef
# Therefore, the highest voice uses the upper half of the pitch range of the clef
# TODO
# The results are not at all convincing so other approaches
# such as all allowing beamed groups (which are not implemented yet)
# or changing the starting pitches of the voices
# or not allowing slurs


def loop_generation(numScores: int, numBars: int, typeAgnostic: str):
    manager.create_folds()
    for i in range(numScores):
        scoreGenerator(i, numBars, typeAgnostic)
    return


def scoreGenerator(id: int, numBars: int, typeAgnostic: str):
    # Create OUT files
    manager.polyss_init(i=id, typeAgnostic=typeAgnostic)

    # Choose clef, key and time signature
    clef = chooseClef()
    manager.write_polyssclef(clef)
    key = chooseKey()
    manager.write_polysskey(key)
    timeSig = chooseTimeSig()  # Returns tuple of aspect (M*/*, duration in quarter notes)
    manager.write_polysstimeSig(timeSig)

    manager.write_openspine()

    # Instantiate initial values
    bar_accidentals = {}
    tie1 = 0  # No tie
    tie2 = 0  # No tie
    id_start1, id_stop1 = 0,  int((len(pitches[clef]) - 1) / 2)  # Lower half
    id_start2, id_stop2 = id_stop1 + 1, int(len(pitches[clef]) - 1)  # Upper half
    pitch1 = int((id_start1 + id_stop1 + 1) / 2)  # It corresponds to the central pitch of the lower half
    pitch2 = int((id_start2 + id_stop2 + 1) / 2)  # It corresponds to the central pitch of the upper half

    for i in range(1, numBars + 1):
        lastbar = True if i == numBars else False
        manager.write_pianobarLine(i)

        # Get bar duration
        duration1 = timeSig[1]
        duration2 = timeSig[1]
        while duration1 > 0 or duration2 > 0:
            if duration1 == duration2:
                # Generate either a note or a silence on both staves
                s1 = symbol.generateSymbol(clef=clef, key=key, duration=duration1, tie=tie1, prevpitch=pitch1,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals, id_start=id_start1, id_stop=id_stop1)
                s2 = symbol.generateSymbol(clef=clef, key=key, duration=duration2, tie=tie2, prevpitch=pitch2,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals, id_start=id_start2, id_stop=id_stop2)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD = 0, DOT IF CHORD = 0]
                duration1 = duration1 - s1[1]
                duration2 = duration2 - s2[1]
                pitch1 = s1[2]
                pitch2 = s2[2]
                tie1 = s1[3]
                tie2 = s2[3]
                manager.write_pianosymbol(s1=[s1[0]], s2=[s2[0]], bar_accidentals1=bar_accidentals,
                                          bar_accidentals2=bar_accidentals)
            elif duration1 > duration2:
                # Generate either a note or a silence on the first staff
                s1 = symbol.generateSymbol(clef=clef, key=key, duration=duration1, tie=tie1, prevpitch=pitch1,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals, id_start=id_start1, id_stop=id_stop1)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD = 0, DOT = 0]
                duration1 = duration1 - s1[1]
                pitch1 = s1[2]
                tie1 = s1[3]
                manager.write_pianosymbol(s1=[s1[0]], s2=['.'], bar_accidentals1=bar_accidentals,
                                          bar_accidentals2=bar_accidentals)

            elif duration1 < duration2:
                # Generate either a note or a silence on the second staff
                s2 = symbol.generateSymbol(clef=clef, key=key, duration=duration2, tie=tie2, prevpitch=pitch2,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals, id_start=id_start2, id_stop=id_stop2)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD = 0, DOT = 0]
                duration2 = duration2 - s2[1]
                pitch2 = s2[2]
                tie2 = s2[3]
                manager.write_pianosymbol(s1=['.'], s2=[s2[0]], bar_accidentals1=bar_accidentals,
                                          bar_accidentals2=bar_accidentals)

        # We clear the temporal bar accidentals dictionary
        bar_accidentals.clear()

    # End of score
    manager.write_pianoend()

    return


if __name__ == "__main__":
    # musicTexture = ['mono', 'homo', 'poly-ss', 'piano-mono', 'piano-homo']
    # typeAgnostic = ['standard', 'split']
    musicTexture, typeAgnostic = 'poly-ss', 'standard'
    symbol.valueMode(musicTexture=musicTexture)
    loop_generation(numScores=4, numBars=6, typeAgnostic=typeAgnostic)
    manager.preprareforOMR(musicTexture=musicTexture, typeAgnostic=typeAgnostic)
