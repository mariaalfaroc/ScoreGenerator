<h1 align="center">Music Score Generator</h1>

<p align="center">
  <img src="https://img.shields.io/badge/python-3.9.0-orange" alt="Python">
  <img src="https://img.shields.io/static/v1?label=License&message=MIT&color=blue" alt="License">
</p>


<p align="center">
  <a href="#about">About</a> •
  <a href="#how-to-use">How To Use</a> •
  <a href="#citations">Citations</a> •
  <a href="#acknowledgments">Acknowledgments</a> •
  <a href="#license">License</a>
</p>


## About

Music score generator implemented in Python. It generates single-staff section scores of one of the following music textures:
- *monophonic*: only one note (per staff) is played at a time.
- *homophonic*: multiple notes can occur at the same time to build up a chord, but only as a single
voice.
- *polyphonic (single staff)*: multiple voices can appear in a single staff.
- *pianoform (monophonic)*: two staves (clefs fixed to piano clefs, i.e., ClefG2 and ClefF4), each exhibiting a single monophonic voice.
- *pianoform (homophonic)*: two staves (clefs fixed to piano clefs, i.e., ClefG2 and ClefF4), each exhibiting a single homophonic voice.

When run, it creates an output folder `OUT` in the main directory of the project.
In the `OUT` folder we find:
```
scoregenerator
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

## How To Use

To run the code, you'll need to meet certain requirements which are specified in the [`requirements`](requirements.txt) file. Once you have prepared your environment, follow this recipe:

```python
python main.py -numS 4 -numB 4 -mode mono -typeAg standard
```

The script above generates four scores, each containing four bars of monophonic music with the standard encoding separator. However, the generator is designed to offer flexibility in music generation. Feel free to experiment with different parameter values to create diverse musical compositions.

Here are the available command-line arguments:
- `numS`: Indicates the number of scores to generate.
- `numB`: Indicates the number of bars per score.
- `mode`: Specifies the music texture of the generated scores. Choices include:
  - `mono`: Monophonic texture.
  - `homo`: Homophonic texture.
  - `poly-ss`: Polyphonic texture.
  - `piano-mono`: Pianoform monophonic texture.
  - `piano-homo`: Pianoform homophonic texture.
- `typeAg`: Specifies the separator used in the agnostic encoding between the two tokens that make up a single symbol. Choices include:
  - `standard`: Separator is ':'.
  - `split`: Separator is a blank space.


## Citations

```bibtex
@inproceedings{alfaro2019approaching,
  title     = {{Approaching End-to-End Optical Music Recognition for Homophonic Scores}},
  author    = {Alfaro-Contreras, Mar{\'\i}a and Calvo-Zaragoza, Jorge and I{\~n}esta, Jos{\'e} M},
  booktitle = {{Proceedings of the 9th Iberian Conference on Pattern Recognition and Image Analysis}},
  pages     = {147--158},
  year      = {2019},
  publisher = {Springer},
  address   = {Madrid, Spain},
  month     = jul,
  doi       = {10.1007/978-3-030-31321-0_13},
}
@article{alfaro2023optical,
  title     = {{Optical music recognition for homophonic scores with neural networks and synthetic music generation}},
  author    = {Alfaro-Contreras, Mar{\'\i}a and I{\~n}esta, Jos{\'e} M and Calvo-Zaragoza, Jorge},
  journal   = {{International Journal of Multimedia Information Retrieval}},
  volume    = {12},
  number    = {1},
  pages     = {12--24},
  year      = {2023},
  publisher = {Springer},
  doi       = {10.1007/s13735-023-00278-5},
}
```

## Acknowledgments

This work is part of the I+D+i PID2020-118447RA-I00 ([MultiScore](https://sites.google.com/view/multiscore-project)) project, funded by MCIN/AEI/10.13039/501100011033.

## License
This work is under a [MIT](LICENSE) license.
