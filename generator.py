# -*- coding: utf-8 -*-

import sys
import os

import symbol
import manager

# Adding image_processing to the system path
sys.path.insert(0, os.path.dirname(os.path.realpath(__file__)) + '/music_textures')
from music_textures import monophony, homophony, piano_mono, piano_homo


# Function to generate the indicated number scores with corresponding music texture
def scoreGenerator(numScores: int, musicTexture: str, numBars: int, typeAgnostic: str):
    symbol.valueMode(musicTexture=musicTexture)

    print('Music texture: {}'. format(musicTexture))
    print('Generating {} scores of {} bars with {} agnostic encoding'.format(numScores, numBars, typeAgnostic))

    if musicTexture == 'mono':
        monophony.loop_generation(numScores=numScores, numBars=numBars, typeAgnostic=typeAgnostic)
    elif musicTexture == 'homo':
        homophony.loop_generation(numScores=numScores, numBars=numBars, typeAgnostic=typeAgnostic)
    # elif musicTexture == 'poly-ss':
    elif musicTexture == 'piano-mono':
        piano_mono.loop_generation(numScores=numScores, numBars=numBars, typeAgnostic=typeAgnostic)
    elif musicTexture == 'piano-homo':
        piano_homo.loop_generation(numScores=numScores, numBars=numBars, typeAgnostic=typeAgnostic)

    manager.preprareforOMR(musicTexture=musicTexture, typeAgnostic=typeAgnostic)

    return
