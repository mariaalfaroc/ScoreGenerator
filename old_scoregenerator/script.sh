#!/bin/bash

ejemplo=1

for (( c=1; c<=500; c++ ))
do  

    NC=5 #Number of compasses

    TP=`expr $RANDOM % 3` # From 0 to 2
    let TP+=1 # (1) normal distribution, (2) random walk, (3) logistic probability

    RL=3.75 # r variable for the logistic probability

    NAL=`expr $RANDOM % 101` # Percentage (from 0 to 100) of a note being altered
    NG=`expr $RANDOM % 101` # Percentage (from 0 to 100) of a musical unit being a chord or a tuplet


    if test $TP -eq 3
    then
        ./generador $ejemplo $NC $TP $RL $NAL $NG
    else
        ./generador $ejemplo $NC $TP $NAL $NG
    fi
    ./verovio $ejemplo.kern
    svg2pdf $ejemplo.svg $ejemplo.pdf
    let ejemplo+=1
done
