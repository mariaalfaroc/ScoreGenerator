# -*- coding: utf-8 -*-

import random

import manager
import symbol
from dictionary import pitches, chooseKey, chooseTimeSig


def loop_generation(numScores: int, numBars: int, typeAgnostic: str):
    manager.create_folds()
    for i in range(numScores):
        scoreGenerator(i, numBars, typeAgnostic)
    return


def chord_handle(s: list, clef: str, key: str, lastbar: bool, bar_accidentals: dict):
    chord = [s[0]]
    # A chord is starting
    # Choose randomly the number of the remaining notes forming the chord
    # CHORDS HAVE A MAXIMUM OF THREE NOTES due to development's limits
    chordNotes = random.choice([1, 2])
    lastnote = False
    while chordNotes > 0:
        if chordNotes == 1:
            lastnote = True
        s = symbol.generateChord(clef=clef, key=key, duration=s[1], tie=s[3], prevpitch=s[2], lastbar=lastbar, bar_accidentals=bar_accidentals, dot=s[-1], lastnote=lastnote)
        chord.append(s[0])
        chordNotes -= 1
    return chord, s, bar_accidentals


def scoreGenerator(id: int, numBars: int, typeAgnostic: str):
    # Create OUT files
    manager.piano_init(i=id, typeAgnostic=typeAgnostic)

    # Clefs are fixed to piano clefs
    # The order is conditioned to the appearance of a Humdrum **kern file
    # Staves are ordered from lowest to highest pitch
    clef1 = 'clefF4'
    clef2 = 'clefG2'
    manager.write_pianoclef(clef1, clef2)
    # Choose clef, key and time signature
    key = chooseKey()
    manager.write_pianokey(key)
    timeSig = chooseTimeSig()  # Returns tuple of aspect (M*/*, duration in quarter notes)
    manager.write_pianotimeSig(timeSig)

    # Instantiate initial values
    bar_accidentals1 = {}
    bar_accidentals2 = {}
    tie1 = 0  # No tie
    tie2 = 0  # No tie
    id_start1, id_stop1 = 0, len(pitches[clef1]) - 1  # Full range
    id_start2, id_stop2 = 0, len(pitches[clef2]) - 1  # Full range
    pitch1 = int((id_start1 + id_stop1 + 1) / 2)  # Pitch that falls on the third line of the staff
    pitch2 = int((id_start2 + id_stop2 + 1) / 2)  # Pitch that falls on the third line of the staff

    for i in range(1, numBars + 1):
        lastbar = True if i == numBars else False
        manager.write_pianobarLine(i)

        # Get bar duration
        duration1 = timeSig[1]
        duration2 = timeSig[1]
        while duration1 > 0 or duration2 > 0:
            if duration1 == duration2:
                # Generate either a note or a silence on both staves
                s1 = symbol.generateSymbol(clef=clef1, key=key, duration=duration1, tie=tie1, prevpitch=pitch1,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals1, id_start=id_start1, id_stop=id_stop1)
                s2 = symbol.generateSymbol(clef=clef2, key=key, duration=duration2, tie=tie2, prevpitch=pitch2,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals2, id_start=id_start2, id_stop=id_stop2)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD = 0, DOT IF CHORD = 1]
                pitch1 = s1[2]  # To keep harmony
                pitch2 = s2[2]  # To keep harmony

                # See if chord
                if s1[4] == 1 and s2[4] == 1:
                    # Both staves have a chord starting
                    chord1, s1, bar_accidentals1 = chord_handle(s=s1, clef=clef1, key=key, lastbar=lastbar,
                                                        bar_accidentals=bar_accidentals1)
                    chord2, s2, bar_accidentals2 = chord_handle(s=s2, clef=clef2, key=key, lastbar=lastbar,
                                                        bar_accidentals=bar_accidentals2)
                    manager.write_pianosymbol(s1=chord1, s2=chord2, bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)
                elif s1[4] == 1 and s2[4] != 1:
                    # Only the first staff has a chord starting
                    chord1, s1, bar_accidentals1 = chord_handle(s=s1, clef=clef1, key=key, lastbar=lastbar,
                                                                bar_accidentals=bar_accidentals1)
                    manager.write_pianosymbol(s1=chord1, s2=[s2[0]], bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)
                elif s1[4] != 1 and s2[4] != 1:
                    # None of them have a chord starting
                    manager.write_pianosymbol(s1=[s1[0]], s2=[s2[0]], bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)
                elif s1[4] != 1 and s2[4] == 1:
                    # Only the second staff has a chord starting
                    chord2, s2, bar_accidentals2 = chord_handle(s=s2, clef=clef2, key=key, lastbar=lastbar,
                                                                bar_accidentals=bar_accidentals2)
                    manager.write_pianosymbol(s1=[s1[0]], s2=chord2, bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)

                duration1 = duration1 - s1[1]
                duration2 = duration2 - s2[1]
                tie1 = s1[3]
                tie2 = s2[3]

            elif duration1 > duration2:
                # Generate either a note or a silence on the first staff
                s1 = symbol.generateSymbol(clef=clef1, key=key, duration=duration1, tie=tie1, prevpitch=pitch1,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals1, id_start=id_start1, id_stop=id_stop1)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD, DOT IF CHORD = 1]
                pitch1 = s1[2]  # To keep harmony

                # See if chord
                if s1[4] == 1:
                    chord1, s1, bar_accidentals1 = chord_handle(s=s1, clef=clef1, key=key, lastbar=lastbar,
                                                                bar_accidentals=bar_accidentals1)
                    manager.write_pianosymbol(s1=chord1, s2=['.'], bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)
                else:
                    manager.write_pianosymbol(s1=[s1[0]], s2=['.'], bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)

                duration1 = duration1 - s1[1]
                tie1 = s1[3]

            elif duration1 < duration2:
                # Generate either a note or a silence on the second staff
                s2 = symbol.generateSymbol(clef=clef2, key=key, duration=duration2, tie=tie2, prevpitch=pitch2,
                                           lastbar=lastbar,
                                           bar_accidentals=bar_accidentals2, id_start=id_start2, id_stop=id_stop2)
                # s = [INTERNAL REPRESENTATION, DURATION, PITCH, TIE, CHORD, DOT IF CHORD = 1]
                pitch2 = s2[2]  # To keep harmony

                # See if chord
                if s2[4] == 1:
                    chord2, s2, bar_accidentals2 = chord_handle(s=s2, clef=clef2, key=key, lastbar=lastbar,
                                                                bar_accidentals=bar_accidentals2)
                    manager.write_pianosymbol(s1=['.'], s2=chord2, bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)
                else:
                    manager.write_pianosymbol(s1=['.'], s2=[s2[0]], bar_accidentals1=bar_accidentals1,
                                              bar_accidentals2=bar_accidentals2)

                duration2 = duration2 - s2[1]
                tie2 = s2[3]

        # We clear the temporal bar accidentals dictionary
        bar_accidentals1.clear()
        bar_accidentals2.clear()

    # End of score
    manager.write_pianoend()

    return


if __name__ == "__main__":
    # musicTexture = ['mono', 'homo', 'poly-ss', 'piano-mono', 'piano-homo']
    # typeAgnostic = ['standard', 'split']
    musicTexture, typeAgnostic = 'piano-homo', 'split'
    symbol.valueMode(musicTexture=musicTexture)
    loop_generation(numScores=4, numBars=6, typeAgnostic=typeAgnostic)
    manager.preprareforOMR(musicTexture=musicTexture, typeAgnostic=typeAgnostic)
