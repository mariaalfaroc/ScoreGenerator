./bin/generador

for (( c=0; c<5; c++ ))
do 
    ./external/verovio "data/kern/"$c.kern -o "data/svg/"$c.svg
    if [ $(grep -o -i clef "data/svg/"$c.svg | wc -l) -eq 2 ]
    then 
        svg2png "data/svg/"$c.svg "data/png/"$c.png 
    else
        rm -rf "data/agnostic/"cod0_$c.txt
        rm -rf "data/agnostic/"cod1_$c.txt
        rm -rf "data/agnostic/"cod2_$c.txt
        rm -rf "data/agnostic/"cod3_$c.txt
        rm -rf "data/kern/"$c.kern
        rm -rf "data/svg/"$c.svg
    fi
done
