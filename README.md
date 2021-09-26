# ScoreGenerator

**Music Score Generator implemented in Python**

It generates single-staff section scores of one of the following music textures:
- *monophonic*: only one note (per staff) is played at a time.
- *homophonic*: multiple notes can occur at the same time to build up a chord, but only as a single
voice.
- *polyphonic (single staff)*: multiple voices can appear in a single staff.
- *pianoform (monophonic)*: two staves (clefs fixed to piano clefs, i.e., ClefG2 and ClefF4), each exhibiting a single monophonic voice.
- *pianoform (homophonic)*: two staves (clefs fixed to piano clefs, i.e., ClefG2 and ClefF4), each exhibiting a single homophonic voice.

When run, it creates an output folder `OUT` in the main directory of the project.
In the `OUT` folder we find:
```
ScoreGenerator
│   ....  
└───OUT
    └───AGNOSTIC
            Stores the .txt files that contain the agnostic encoding of the scores.
            Calvo-Zaragoza, J.; Rizo, D. End-to-End Neural Optical Music Recognition of Monophonic Scores. 
            Appl. Sci. 2018, 8, 606.
    └───INTERNAL
            Stores the .txt files tha contain the internal encoding of the music generator.
            It follows a Humdrum **kern like style, where each line represent a music symbol of the score.
    └───KERN
            Stores the Humdrum **kern files of the scores. They are used to generate the scores' images.
            https://www.humdrum.org/guide/ch02/
    └───PNG
        Stores the .png files of the scores. The images are those of the full score. 
        The number of files corresponds to the one introduced in the command-line argument.
        └───CROPPED
            Stores the .png files of the scores that match the single-staff condition of End-to-End Optical Music Recognition Systems. When the script is run, an information message telling the amount of scores that do not match said condition is given.
            └───DISTORTED
                Stores the .png files of CROPPED but the images are distorted using the below reference distorter.
                Calvo - Zaragoza, J.; Rizo, D. Camera-PrIMuS: Neural end-to-end Optical Music Recognition on realistic monophonic scores. 
                In Proceedings of the 19th International Society for Music Information Retrieval Conference, Paris.2018, pp.248-255
```


Example of usage:
```python
python main.py -numS 4 -numB 4 -mode mono -typeAg standard
```
Arguments:
- numS, indicates the number of scores to generate
- numB, indicates the number of bars per score
- mode, indicates the music textures of the generated scores (choices are mono, homo, poly-ss, piano-mono, piano-homo)
- typeAg, indicates the separator used in the agnostic encoding between the two tokens that made up a single symbol (choices are standard (separator is ':') or split (separator is a blank space))

---

Requirements:
- OpenCV
- Verovio
- PgMagick
- CairoSVG
