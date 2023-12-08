//
// Created by Usuario on 10/12/2019.
//

#ifndef SCOREGENERATOR_ALFAROGENERATOR_H
#define SCOREGENERATOR_ALFAROGENERATOR_H


#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <random>
#include <vector>
#include <optional>

struct ClefData
{
    std::string pitch;
    std::string noteplace;
    std::string dotplace;
    int noteident;
};

class AlfaroGenerator
{
public:
    AlfaroGenerator();
    void GenerateScore(std::string&, int, int, float, int, int, int);

private:
    std::string codificationh(int);
    std::string codificationv(int);
    std::string clef(int,int);
    std::string keysignature(int, int [], int);
    std::string compass (float&, int&, int&, int);
    std::string silence(float&, int, int);
    std::string clefG (int, std::string&, int&, std::string&);
    std::string clefF (int, std::string&, int&, std::string&);
    std::string clefC3 (int, std::string&, int&, std::string&);
    std::string normaldistribution (int, float, float, std::string&, int&, std::string&, int, int, int&, int, int);
    std::string randomwalk (int, std::string&, int&, std::string&, int&, int, int, int);
    std::string logistic (int, std::string&, int&, std::string&, int, int, int&, int, int, int, float, float&);
    std::string pitchgeneration (int, float, float, std::string&, int&, std::string&, int, int, int&, int, int, int, float, int, float&);
    std::string alteration (int, int, std::string&, std::string, int, int [], int);
    void tienote (int&, std::string&, std::string, int&, int);
    std::string note(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);
    std::string tuplet(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);
    std::string chords(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);

    std::vector<std::string> m_clefsKern;
    std::vector<std::string> m_clefsAgnostic;
    
    std::vector<ClefData> m_clefG;
    std::vector<ClefData> m_clefF;
    std::vector<ClefData> m_clefC3;
    
    std::ofstream m_agnosticStream;
};


#endif //SCOREGENERATOR_ALFAROGENERATOR_H
