<p align="center">
  <a href=""><img src="https://i.imgur.com/Iu7CvC1.png" alt="PRAIG-logo" width="100"></a>
</p>

<h1 align="center">Optical music recognition for homophonic scores with neural networks and synthetic music generation</h1>

<h4 align="center">Full text available <a href="https://link.springer.com/article/10.1007/s13735-023-00278-5" target="_blank">here</a>.</h4>

<p align="center">
  <img src="https://img.shields.io/badge/python-3.9.0-orange" alt="Python">
  <img src="https://img.shields.io/static/v1?label=License&message=MIT&color=blue" alt="License">
</p>


<p align="center">
  <a href="#about">About</a> •
  <a href="#citations">Citations</a> •
  <a href="#acknowledgments">Acknowledgments</a> •
  <a href="#license">License</a>
</p>


## About

Music score generator implemented in Python. The developed system essentially provides two outputs: the expected transcription of the generated score in multiple encodings and the corresponding score image, both clean and artificially distorted. These outputs yield the necessary pairs for end-to-end deep learning Optical Music Recognition (OMR) systems.

For the generation process, three different methods of algorithmic composition are used to obtain compositions with diverse musical features:
1) **Random generation based on the normal distribution**. We employ the normal distribution to create a symmetric distribution centered around the pitch corresponding to the space surrounding the central line of the staff.
2) **Random walk**. A random walk is a mathematical formalization of a trajectory resulting from successive random steps. In this system, the random walk always begins at the central pitch of the pitch range determined for the system. There are three possible random steps, all equally likely, after emitting a pitch:
- One step forward: the following pitch is the next higher one from the previous.
- One step backward: the following pitch is the next lower one from the previous.
- No step: the following pitch remains the same as the previous.
3) **Sonification of the logistic equation**.

For complete details about the implementation, please refer to any of the [works](#citations) cited below.

There are two versions available:
- [`old_scoregenerator`](old_scoregenerator): It contains the score generator considering all three different methods of algorithmic composition.
- [`scoregenerator`](scoregenerator): This is a newer version that only uses the random walk algorithm for composition, as it has yielded the best results in end-to-end OMR transcription.

However, please bear in mind that neither of these versions is currently maintained.

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