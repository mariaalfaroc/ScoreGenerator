#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <random>
#include <vector>
#include <map>

using namespace std;

struct ClefData
{
    std::string pitch;
    std::string noteplace;
    std::string dotplace;
    int noteident;
    int stemdirection;
};

struct KeyDataKern
{
  std::string keysign;
  std::vector<int> keyident;

  KeyDataKern(const std::string& cosa, const std::vector<int>& coso)
  {
    keysign = cosa;
    keyident = coso;
  }
};

struct KeyDataAgnostic
{
    std::vector<std::string> keyAgnosticClefG2;
    std::vector<std::string> keyAgnosticClefF;
    std::vector<std::string> keyAgnosticClefC3; 
    std::vector<std::string> keyAgnosticClefC1; 
    std::vector<std::string> keyAgnosticClefG1;
    std::vector<std::string> keyAgnosticClefC2; 
    std::vector<std::string> keyAgnosticClefC4;  

    KeyDataAgnostic(const std::vector<std::string>& kClefG2, const std::vector<std::string>& kClefF, const std::vector<std::string>& kClefC3, const std::vector<std::string>& kClefC1, const std::vector<std::string>& kClefG1, const std::vector<std::string>& kClefC2, const std::vector<std::string>& kClefC4)
    {
        keyAgnosticClefG2 = kClefG2;
        keyAgnosticClefF = kClefF;
        keyAgnosticClefC3 = kClefC3;
        keyAgnosticClefC1 = kClefC1;
        keyAgnosticClefG1 = kClefG1;
        keyAgnosticClefC2 = kClefC2;
        keyAgnosticClefC4 = kClefC4;
    } 
};

class AlfaroGenerator4E
{
    public:
        AlfaroGenerator4E();
        void GenerateCorpus(string& ,int, int, float, int, int, int);

    private:
        string codificationh(int);
        string codificationv(int);
        string clef(int);
        string keysignature(int, vector<int>&, int);
        string compass (float&, int&, int&);
        string silence(float&, int);
        string clefG2 (int, string&, int&, string&, int&);
        string clefF (int, string&, int&, string&, int&);
        string clefC3 (int, string&, int&, string&, int&);
        string clefC1 (int, string&, int&, string&, int&);
        string clefG1 (int, string&, int&, string&, int&);
        string clefC2 (int, string&, int&, string&, int&);
        string clefC4 (int, string&, int&, string&, int&);
        string normaldistribution (int, float, float, string&, int&, string&, int, int, int&, int, int, int&);
        string randomwalk (int, string&, int&, string&, int&, int, int, int, int&);
        string logistic (int, string&, int&, string&, int, int, int&, int, int, int, float, float&, int&);
        string pitchgeneration (int, float, float, string&, int&, string&, int, int, int&, int, int, int, float, int, float&, int&);
        string alteration (int, int, string&, string, int, vector<int>);
        void tienote (int&, string&, string, int&, ofstream&, ofstream&, ofstream&, ofstream&);
        string note(float&, int, int, int, float, float, vector<int>, int, int&, int&, int, int, int, int, int, float, int, int&, float&);
        string tuplet(float&, int, int, int, float, float, vector<int>, int, int&, int&, int, int, int, int, int, float, int, int&, float&);
        string chords(float&, int, int, int, float, float, vector<int>, int, int&, int&, int, int, int, int, int, float, int, int&, float&);

        //void writeOnBuffers(const string&);

        vector<std::string> m_clefsKern;
        vector<std::string> m_clefsAgnostic;
        vector<ClefData> m_clefG2;
        vector<ClefData> m_clefF;
        vector<ClefData> m_clefC3;
        vector<ClefData> m_clefC1;
        vector<ClefData> m_clefG1;
        vector<ClefData> m_clefC2;
        vector<ClefData> m_clefC4;
        vector<std::string> m_keyaltAgnostic;
        vector<int> m_keyasign;
        vector<KeyDataKern> m_keyKern;
        vector<KeyDataAgnostic> m_keyAgnostic;
        map<std::string,int> map_alt;
        ofstream cod0;
        ofstream cod1;
        ofstream cod2;
        ofstream cod3;
};