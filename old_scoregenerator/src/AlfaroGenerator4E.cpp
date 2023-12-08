#include "AlfaroGenerator4E.hpp"

AlfaroGenerator4E::AlfaroGenerator4E()
{

    //Clef Data
    m_clefsKern = {"*clefG2", "*clefF4", "*clefC3", "*clefC1", "*clefG1", "*clefC2", "*clefC4"};
    m_clefsAgnostic = {"clef.G:L2", "clef.F:L4", "clef.C:L3", "clef.C:L1", "clef.G:L1", "clef.C:L2", "clef.C:L4"};

    m_clefG2 = {{"E", "S-3", "S-3", 5, 0}, {"F", "L-2", "S-2", 6, 0},
                {"G", "S-2", "S-2", 7, 0}, {"A", "L-1", "S-1", 1, 0},
                {"B", "S-1", "S-1", 2, 0}, {"c", "L0", "S0", 3, 0},
                {"d", "S0", "S0", 4, 0}, {"e", "L1", "S1", 5, 0},
                {"f", "S1", "S1", 6, 0}, {"g", "L2", "S2", 7, 0},
                {"a", "S2", "S2", 1, 0}, {"b", "L3", "S3", 2, 1},
                {"cc", "S3", "S3", 3, 2}, {"dd", "L4", "S4", 4, 2},
                {"ee", "S4", "S4", 5, 2}, {"ff", "L5", "S5", 6, 2},
                {"gg", "S5", "S5", 7, 2}, {"aa", "L6", "S6", 1, 2},
                {"bb", "S6", "S6", 2, 2}, {"ccc", "L7", "S7", 3, 2},
                {"ddd", "S7", "S7", 4, 2}, {"eee", "L8", "S8", 5, 2}};
    
    m_clefF = { {"GGG", "S-3", "S-3", 7, 0}, {"AAA", "L-2", "S-2", 1, 0},
                {"BBB", "S-2", "S-2", 2, 0}, {"CC", "L-1", "S-1", 3, 0},
                {"DD", "S-1", "S-1", 4, 0}, {"EE", "L0", "S0", 5, 0},
                {"FF", "S0", "S0", 6, 0}, {"GG", "L1", "S1", 7, 0},
                {"AA", "S1", "S1", 1, 0}, {"BB", "L2", "S2", 2, 0},
                {"C", "S2", "S2", 3, 0}, {"D", "L3", "S3", 4, 1},
                {"E", "S3", "S3", 5, 2}, {"F", "L4", "S4", 6, 2},
                {"G", "S4", "S4", 7, 2}, {"A", "L5", "S5", 1, 2},
                {"B", "S5", "S5", 2, 2}, {"c", "L6", "S6", 3, 2},
                {"d", "S6", "S6", 4, 2}, {"e", "L7", "S7", 5, 2},
                {"f", "S7", "S7", 6, 2}, {"g", "L8", "S8", 7, 2}};
    
    m_clefC3 = {{"FF", "S-3", "S-3", 6, 0}, {"GG", "L-2", "S-2", 7, 0},
                {"AA", "S-2", "S-2", 1, 0}, {"BB", "L-1", "S-1", 2, 0},
                {"C", "S-1", "S-1", 3, 0}, {"D", "L0", "S0", 4, 0},
                {"E", "S0", "S0", 5, 0}, {"F", "L1", "S1", 6, 0},
                {"G", "S1", "S1", 7, 0}, {"A", "L2", "S2", 1, 0},
                {"B", "S2", "S2", 2, 0}, {"c", "L3", "S3", 3, 1},
                {"d", "S3", "S3", 4, 2}, {"e", "L4", "S4", 5, 2},
                {"f", "S4", "S4", 6, 2}, {"g", "L5", "S5", 7, 2},
                {"a", "S5", "S5", 1, 2}, {"b", "L6", "S6", 2, 2},
                {"cc", "S6", "S6", 3, 2}, {"dd", "L7", "S7", 4, 2},
                {"ee", "S7", "S7", 5, 2}, {"ff", "L8", "S8", 6, 2}};

    m_clefC1 = {{"C", "S-3", "S-3", 3, 0}, {"D", "L-2", "S-2", 4, 0},
                {"E", "S-2", "S-2", 5, 0}, {"F", "L-1", "S-1", 6, 0},
                {"G", "S-1", "S-1", 7, 0}, {"A", "L0", "S0", 1, 0},
                {"B", "S0", "S0", 2, 0}, {"c", "L1", "S1", 3, 0},
                {"d", "S1", "S1", 4, 0}, {"e", "L2", "S2", 5, 0},
                {"f", "S2", "S2", 6, 0}, {"g", "L3", "S3", 7, 1},
                {"a", "S3", "S3", 1, 2}, {"b", "L4", "S4", 2, 2},
                {"cc", "S4", "S4", 3, 2}, {"dd", "L5", "S5", 4, 2},
                {"ee", "S5", "S5", 5, 2}, {"ff", "L6", "S6", 6, 2},
                {"gg", "S6", "S6", 7, 2}, {"aa", "L7", "S7", 1, 2},
                {"bb", "S7", "S7", 2, 2}, {"ccc", "L8", "S8", 3, 2}};

    m_clefG1 = {{"G", "S-3", "S-3", 7, 0}, {"A", "L-2", "S-2", 1, 0},
                {"B", "S-2", "S-2", 2, 0}, {"c", "L-1", "S-1", 3, 0},
                {"d", "S-1", "S-1", 4, 0}, {"e", "L0", "S0", 5, 0},
                {"f", "S0", "S0", 6, 0}, {"g", "L1", "S1", 7, 0},
                {"a", "S1", "S1", 1, 0}, {"b", "L2", "S2", 2, 0},
                {"cc", "S2", "S2", 3, 0}, {"dd", "L3", "S3", 4, 1},
                {"ee", "S3", "S3", 5, 2}, {"ff", "L4", "S4", 6, 2},
                {"gg", "S4", "S4", 7, 2}, {"aa", "L5", "S5", 1, 2},
                {"bb", "S5", "S5", 2, 2}, {"ccc", "L6", "S6", 3, 2},
                {"ddd", "S6", "S6", 4, 2}, {"eee", "L7", "S7", 5, 2},
                {"fff", "S7", "S7", 6, 2}, {"ggg", "L8", "S8", 7, 2}};

    m_clefC2 = {{"AA", "S-3", "S-3", 1, 0}, {"BB", "L-2", "S-2", 2, 0},
                {"C", "S-2", "S-2", 3, 0}, {"D", "L-1", "S-1", 4, 0},
                {"E", "S-1", "S-1", 5, 0}, {"F", "L0", "S0", 6, 0},
                {"G", "S0", "S0", 7, 0}, {"A", "L1", "S1", 1, 0},
                {"B", "S1", "S1", 2, 0}, {"c", "L2", "S2", 3, 0},
                {"d", "S2", "S2", 4, 0}, {"e", "L3", "S3", 5, 1},
                {"f", "S3", "S3", 6, 2}, {"g", "L4", "S4", 7, 2},
                {"a", "S4", "S4", 1, 2}, {"b", "L5", "S5", 2, 2},
                {"cc", "S5", "S5", 3, 2}, {"dd", "L6", "S6", 4, 2},
                {"ee", "S6", "S6", 5, 2}, {"ff", "L7", "S7", 6, 2},
                {"gg", "S7", "S7", 7, 2}, {"aa", "L8", "S8", 1, 2}};

    m_clefC4 = {{"DD", "S-3", "S-3", 4, 0}, {"EE", "L-2", "S-2", 5, 0},
                {"FF", "S-2", "S-2", 6, 0}, {"GG", "L-1", "S-1", 7, 0},
                {"AA", "S-1", "S-1", 1, 0}, {"BB", "L0", "S0", 2, 0},
                {"C", "S0", "S0", 3, 0}, {"D", "L1", "S1", 4, 0},
                {"E", "S1", "S1", 5, 0}, {"F", "L2", "S2", 6, 0},
                {"G", "S2", "S2", 7, 0}, {"A", "L3", "S3", 1, 1},
                {"B", "S3", "S3", 2, 2}, {"c", "L4", "S4", 3, 2},
                {"d", "S4", "S4", 4, 2}, {"e", "L5", "S5", 5, 2},
                {"f", "S5", "S5", 6, 2}, {"g", "L6", "S6", 7, 2},
                {"a", "S6", "S6", 1, 2}, {"b", "L7", "S7", 2, 2},
                {"cc", "S7", "S7", 3, 2}, {"dd", "L8", "S8", 4, 2}};
                
    //Key Signature Data
    m_keyaltAgnostic = {"accidental.sharp:", "accidental.flat:"};
    m_keyasign = {0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,0,0};
    
    m_keyKern = {   
        KeyDataKern("*k[]", std::vector<int>{0,0,0,0,0,0,0}), 
        KeyDataKern("*k[f#]", std::vector<int>{6,0,0,0,0,0,0}),
        KeyDataKern("*k[f#c#]", std::vector<int>{6,3,0,0,0,0,0}),
        KeyDataKern("*k[f#c#g#]", std::vector<int>{6,3,7, 0,0,0,0}), 
        KeyDataKern("*k[f#c#g#d#]", std::vector<int>{6,3,7,4,0,0,0}),
        KeyDataKern("*k[f#c#g#d#a#]", std::vector<int>{6,3,7,4,1,0,0}),
        KeyDataKern("*k[f#c#g#d#a#e#]", std::vector<int>{6,3,7,4,1,5,0}),
        KeyDataKern("*k[f#c#g#d#a#e#b#]", std::vector<int>{6,3,7,4,1,5,2}), 
        KeyDataKern("*k[b-]", std::vector<int>{2,0,0,0,0,0,0}), 
        KeyDataKern("*k[b-e-]", std::vector<int>{2,5,0,0,0,0,0}),
        KeyDataKern("*k[b-e-a-]", std::vector<int>{2,5,1,0,0,0,0}),
        KeyDataKern("*k[b-e-a-d-]", std::vector<int>{2,5,1,4,0,0,0}), 
        KeyDataKern("*k[b-e-a-d-g-]", std::vector<int>{2,5,1,4,7,0,0}), 
        KeyDataKern("*k[b-e-a-d-g-c-]", std::vector<int>{2,5,1,4,7,3,0}), 
        KeyDataKern("*k[b-e-a-d-g-c-f-]", std::vector<int>{2,5,1,4,7,3,6})
    };
    
    m_keyAgnostic = {  
        KeyDataAgnostic(std::vector<std::string>{""}, std::vector<std::string>{""}, std::vector<std::string>{""}, std::vector<std::string>{""}, std::vector<std::string>{""}, std::vector<std::string>{""}, std::vector<std::string>{""}), 
        KeyDataAgnostic(std::vector<std::string>{"L5"}, std::vector<std::string>{"L4"}, std::vector<std::string>{"S4"}, std::vector<std::string>{"S2"}, std::vector<std::string>{"L4"}, std::vector<std::string>{"S3"}, std::vector<std::string>{"L2"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3"}, std::vector<std::string>{"L4","S2"}, std::vector<std::string>{"S4","L3"}, std::vector<std::string>{"S2","L1"}, std::vector<std::string>{"L4","S2"}, std::vector<std::string>{"S3","L2"}, std::vector<std::string>{"L2","L4"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3","S5"}, std::vector<std::string>{"L4","S2","S4"}, std::vector<std::string>{"S4","L3","L5"}, std::vector<std::string>{"S2","L1","L3"}, std::vector<std::string>{"L4","S2","S4"}, std::vector<std::string>{"S3","L2","L4"}, std::vector<std::string>{"L2","L4","S2"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3","S5","L4"}, std::vector<std::string>{"L4","S2","S4","L3"}, std::vector<std::string>{"S4","L3","L5","S3"}, std::vector<std::string>{"S2","L1","L3","S1"}, std::vector<std::string>{"L4","S2","S4","L3"}, std::vector<std::string>{"S3","L2","L4","S2"}, std::vector<std::string>{"L2","L4","S2","S4"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3","S5","L4","S2"}, std::vector<std::string>{"L4","S2","S4","L3","S1"}, std::vector<std::string>{"S4","L3","L5","S3","L2"}, std::vector<std::string>{"S2","L1","L3","S1","S3"}, std::vector<std::string>{"L4","S2","S4","L3","S1"}, std::vector<std::string>{"S3","L2","L4","S2","S4"}, std::vector<std::string>{"L2","L4","S2","S4","L3"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3","S5","L4","S2","S4"}, std::vector<std::string>{"L4","S2","S4","L3","S1","S3"}, std::vector<std::string>{"S4","L3","L5","S3","L2","L4"}, std::vector<std::string>{"S2","L1","L3","S1","S3","L2"}, std::vector<std::string>{"L4","S2","S4","L3","S1","S3"}, std::vector<std::string>{"S3","L2","L4","S2","S4","L3"}, std::vector<std::string>{"L2","L4","S2","S4","L3","L5"}), 
        KeyDataAgnostic(std::vector<std::string>{"L5","S3","S5","L4","S2","S4","L3"}, std::vector<std::string>{"L4","S2","S4","L3","S1","S3","L2"}, std::vector<std::string>{"S4","L3","L5","S3","L2","L4","S2"}, std::vector<std::string>{"S2","L1","L3","S1","S3","L2","L4"}, std::vector<std::string>{"L4","S2","S4","L3","S1","S3","L2"}, std::vector<std::string>{"S3","L2","L4","S2","S4","L3","L5"}, std::vector<std::string>{"L2","L4","S2","S4","L3","L5","S3"}), 
        KeyDataAgnostic(std::vector<std::string>{"L3"}, std::vector<std::string>{"L2"}, std::vector<std::string>{"S2"}, std::vector<std::string>{"L4"}, std::vector<std::string>{"L2"}, std::vector<std::string>{"S1"}, std::vector<std::string>{"S3"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4"}, std::vector<std::string>{"L2","S3"}, std::vector<std::string>{"S2","L4"}, std::vector<std::string>{"L4","L2"}, std::vector<std::string>{"L2","S3"}, std::vector<std::string>{"S1","L3"}, std::vector<std::string>{"S3","L5"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4","S2"}, std::vector<std::string>{"L2","S3","S1"}, std::vector<std::string>{"S2","L4","L2"}, std::vector<std::string>{"L4","L2","S3"}, std::vector<std::string>{"L2","S3","S1"}, std::vector<std::string>{"S1","L3","L1"}, std::vector<std::string>{"S3","L5","L3"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4","S2","L4"}, std::vector<std::string>{"L2","S3","S1","L3"}, std::vector<std::string>{"S2","L4","L2","S3"}, std::vector<std::string>{"L4","L2","S3","S1"}, std::vector<std::string>{"L2","S3","S1","L3"}, std::vector<std::string>{"S1","L3","L1","S2"}, std::vector<std::string>{"S3","L5","L3","S4"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4","S2","L4","L2"}, std::vector<std::string>{"L2","S3","S1","L3","L1"}, std::vector<std::string>{"S2","L4","L2","S3","S1"}, std::vector<std::string>{"L4","L2","S3","S1","L3"}, std::vector<std::string>{"L2","S3","S1","L3","L1"}, std::vector<std::string>{"S1","L3","L1","S2","L4"}, std::vector<std::string>{"S3","L5","L3","S4","S2"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4","S2","L4","L2","S3"}, std::vector<std::string>{"L2","S3","S1","L3","L1","S2"}, std::vector<std::string>{"S2","L4","L2","S3","S1","L3"}, std::vector<std::string>{"L4","L2","S3","S1","L3","L1"}, std::vector<std::string>{"L2","S3","S1","L3","L1","S2"}, std::vector<std::string>{"S1","L3","L1","S2","L4","L2"}, std::vector<std::string>{"S3","L5","L3","S4","S2","L4"}),
        KeyDataAgnostic(std::vector<std::string>{"L3","S4","S2","L4","L2","S3","S1"}, std::vector<std::string>{"L2","S3","S1","L3","L1","S2","S0"}, std::vector<std::string>{"S2","L4","L2","S3","S1","L3","L1"}, std::vector<std::string>{"L4","L2","S3","S1","L3","L1","S2"}, std::vector<std::string>{"L2","S3","S1","L3","L1","S2","S0"}, std::vector<std::string>{"S1","L3","L1","S2","L4","L2","S3"}, std::vector<std::string>{"S3","L5","L3","S4","S2","L4","L2"})     
    };

    //Alteration Data
    map_alt["S-3"]= 0; map_alt["L-2"]= 0; map_alt["S-2"]= 0; map_alt["L-1"]= 0; map_alt["S-1"]= 0; map_alt["L0"]= 0; map_alt["S0"]= 0; 
    map_alt["L1"]= 0; map_alt["S1"]= 0; map_alt["L2"]= 0; map_alt["S2"]= 0; map_alt["L3"]= 0; map_alt["S3"]= 0; map_alt["L4"]= 0; map_alt["S4"]= 0; 
    map_alt["L5"]= 0; map_alt["S5"]= 0; map_alt["L6"]= 0; map_alt["S6"]= 0; map_alt["L7"]= 0; map_alt["S7"]= 0; map_alt["L8"]= 0;
}

void AlfaroGenerator4E::GenerateCorpus(string& c_filename, int c_ncompasses, int c_typeofgen, float c_rlogistic, int c_naltered, int c_ngroup, int c_typecodification)
{
    string filename = "data/kern/" + c_filename;
    string filenamecod0 = "data/agnostic/cod0_" + c_filename + ".txt";
    string filenamecod1 = "data/agnostic/cod1_" + c_filename + ".txt";
    string filenamecod2 = "data/agnostic/cod2_" + c_filename + ".txt";
    string filenamecod3 = "data/agnostic/cod3_" + c_filename + ".txt";
    filename += ".kern"; 
    
    ofstream file;
    file.open(filename.c_str(),ios::out); //We create the .kern file
    cod0.open(filenamecod0.c_str(),ios::out); //We create the .txt file for codification 0
    cod1.open(filenamecod1.c_str(),ios::out); //We create the .txt file for codification 1
    cod2.open(filenamecod2.c_str(),ios::out); //We create the .txt file for codifitacion 2
    cod3.open(filenamecod3.c_str(),ios::out); //We create the .txt file for codifitacion 3
    if(file.fail()){ //If any error happens
		cout << "[Error] Kern file could not be opened";
		exit(1);
	}
    if(cod0.fail()){ //If any error happens
		cout << "[Error] Cod 0 file could not be opened";
		exit(1);
	}
    if(cod1.fail()){ //If any error happens
		cout << "[Error] Cod 1 file could not be opened";
		exit(1);
	}
    if(cod2.fail()){ //If any error happens
		cout << "[Error] Cod 2 file could not be opened";
		exit(1);
	}
    if(cod3.fail()){ //If any error happens
		cout << "[Error] Cod 3 file could not be opened";
		exit(1);
	}

    int ncompasses = c_ncompasses; //Number of compasses that the score will have.
    
    int typeofgen = c_typeofgen; //Type of function to generate the pitch: (1) normal distribution , (2) random walk or (3) logistic probability
    float rlogistic;
    
    int naltered;
    int ngroup;
    int typecodification;
    if (typeofgen==3){
        rlogistic = c_rlogistic; //r variable for the logistic function
        naltered = c_naltered; //Percentage (from 0 to 100) of a note being altered
        ngroup = c_ngroup; //Percentage (from 0 to 100) of a musical unit being a chord or a tuplet
    }else{
        naltered = c_naltered; //Percentage (from 0 to 100) of a note being altered
        ngroup = c_ngroup; //Percentage (from 0 to 100) of a musical unit being a chord or a tuplet
    }

    
    file << "**kern" << endl; //To initialice the .kern file
    
    int CL = rand()%7; //0-G2Clef; 1-FClef; 2-C3Clef; 3-C1Clef; 4-G1Clef; 5-C2Clef; 6-C4Clef
    string choosenclef = clef(CL);
    file << choosenclef << endl;

    int key;
    if (naltered==0){
        key = 0; //There will be no alteration for this case.
    }else{
        key = rand()%32;
    }
    std::vector<int> keyident; //To be able to identify a note belonging to this key signature.
    string keysign = keysignature(key, keyident, CL);
    file << keysign << endl;

    float compassdur;
    int N = rand()%200+1; //To decide the type of compass
    int M; //Type of compass
    string choosencompass = compass (compassdur, N, M);
    file << choosencompass << endl;

    float mean = 8.5; //For the normal distribution used to choose the note
    float variance = 5.34; //For the normal distribution used to choose the note

    float sum = 0;
    file << "=1-" <<endl; //First bar (styled invisible)

    int TIE = rand()%10; //To decide if it's going to be tied or not
    int starttie = 0;

    int NORS; //To decide if we have a note or a silence
    int CHORNOTE; //To decide if chord or note
    int CHORD;
    int chordnote;
    int BEAM;
    int beamnote;
    
    int sampleint; 
    float xlogistic;
    int counter = 1;

    int i = 1; //Compass counter
    while(ncompasses!=0){
        NORS = rand()%10; //From 0 to 9, to decide if we have a note or a silence
        CHORNOTE = rand()%101; //From 0 to 100: to decide if chord or note
        CHORD = 0;
        chordnote = 0;
        BEAM = 0;
        beamnote = 0;
        if (NORS==9){ //10% chance of having a silence
            string choosensilence;
            while (choosensilence.empty()){
                choosensilence = silence(sum, M);
            }
            file << choosensilence << endl;
            choosensilence.clear();  
        }else{
            string finalnote;
            while (finalnote.empty()){
                if (CHORNOTE < ngroup){
                    int TORC = rand()%2;
                    if (TORC==0){
                        finalnote = tuplet(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic);
                    }else{   
                        finalnote = chords(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic);
                        CHORD = 0;
                        chordnote = 0;
                    }   
                }else{        
                    finalnote = note(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic);
                    BEAM = 0;
                    beamnote = 0; 
                }
            }
            file << finalnote << endl;
            finalnote.clear(); 
            counter = 0;           
        }
        string hseparation0 = codificationh(0);  //Equal for type 0 and 2
        string hseparation1 = codificationh(1);  //Equal for type 1 and 3
        if (sum==compassdur){
            i = i+1;
            file << "=" << i << endl;
            cod0 << "verticalLine:L1"; //Bar
            cod1 << "verticalLine:L1"; //Bar
            cod2 << "verticalLine:L1"; //Bar
            cod3 << "verticalLine:L1"; //Bar
            
            sum=0;
            map_alt["S-3"]= 0; map_alt["L-2"]= 0; map_alt["S-2"]= 0; map_alt["L-1"]= 0; map_alt["S-1"]= 0; map_alt["L0"]= 0; map_alt["S0"]= 0; 
            map_alt["L1"]= 0; map_alt["S1"]= 0; map_alt["L2"]= 0; map_alt["S2"]= 0; map_alt["L3"]= 0; map_alt["S3"]= 0; map_alt["L4"]= 0; map_alt["S4"]= 0; 
            map_alt["L5"]= 0; map_alt["S5"]= 0; map_alt["L6"]= 0; map_alt["S6"]= 0; map_alt["L7"]= 0; map_alt["S7"]= 0; map_alt["L8"]= 0;
            ncompasses = ncompasses-1;
            if (ncompasses!=0){
                cod0 << hseparation0;
                cod1 << hseparation1;
                cod2 << hseparation0;
                cod3 << hseparation1;
            }
        }
    }

    file << "*-" <<endl; //End of the .kern file
    file.close(); //We close the .kern file
    cod0.close(); //We close the .txt file for codification 0
    cod1.close(); //We close the .txt file for codification 1
    cod2.close(); //We close the .txt file for codification 2
    cod3.close(); //We close the .txt file for codification 3
}

string AlfaroGenerator4E::codificationh(int typecodification){
    if(typecodification == 0 || (typecodification%2) == 0)
        return " ";
    return " + ";
}

string AlfaroGenerator4E::codificationv(int typecodification){
    if(typecodification < 1 || typecodification > 2)
        return " / ";
    return " ";
}

string AlfaroGenerator4E::clef(int CL){
    //CL = rand()%7 meaning: 0-G2Clef; 1-FClef; 2-C3Clef; 3-C1Clef; 4-G1Clef; 5-C2Clef; 6-C4Clef
    string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    string hseparation1 = codificationh(1);  //Equal for type 1 and 3

    string agnosticCLef = m_clefsAgnostic.at(CL);

    cod0 << agnosticCLef << hseparation0;
    cod1 << agnosticCLef << hseparation1;
    cod2 << agnosticCLef << hseparation0;
    cod3 << agnosticCLef << hseparation1;
    
    return m_clefsKern.at(CL);
}

string AlfaroGenerator4E::keysignature(int key, std::vector<int>& keyident, int CL){
    //key = rand()%32 meaning:
    //0-Do mayor (C); 1-La menor (a)
    //2-Sol mayor (G); 3-Mi menor (e)
    //4-Re mayor (D); 5-Si menor (b)
    //6-La mayor (A); 7-Fa sostenido menor (f#)
    //8-Mi mayor (E); 9-Do sostenido menor (c#)
    //10-Si mayor (B); 11-Sol sostenido menor (g#)
    //12-Fa sostenido mayor (F#); 13-Re sostenido menor (d#)
    //14-Do sostenido mayor (C#); 15-La sostenido menor (a#)
    //16-Fa mayor (F); 17-Re menor (d)
    //18-Si bemol mayor (Bb); 19-Sol menor (g)
    //20-Mi bemol mayor (Eb); 21-Do menor (c)
    //22-La bemol mayor (Ab); 23-Fa menor (f)
    //24-Re bemol mayor (Db); 25-Si bemol menor (bb)
    //26-Sol bemol mayor (Gb); 27-Mi bemol menor (eb)
    //28-Do bemol mayor (Cb); 29-La bemol menor (ab)
    //30-Sin alteraciones; 31-Sin alteraciones

    int keyasign = m_keyasign.at(key);

    KeyDataKern l_keykern = m_keyKern[keyasign];
    std::string keysign = l_keykern.keysign;
    keyident = l_keykern.keyident;

    KeyDataAgnostic l_keyagnostic = m_keyAgnostic[keyasign];
    vector<std::string> accidentalplace;
    if (CL==0) accidentalplace = l_keyagnostic.keyAgnosticClefG2;
    if (CL==1) accidentalplace = l_keyagnostic.keyAgnosticClefF;
    if (CL==2) accidentalplace = l_keyagnostic.keyAgnosticClefC3;
    if (CL==3) accidentalplace = l_keyagnostic.keyAgnosticClefC1;
    if (CL==4) accidentalplace = l_keyagnostic.keyAgnosticClefG1;
    if (CL==5) accidentalplace = l_keyagnostic.keyAgnosticClefC2;
    if (CL==6) accidentalplace = l_keyagnostic.keyAgnosticClefC4;

    string keyaccagnostic = "";
    if (key>1&&key<16) keyaccagnostic = m_keyaltAgnostic.at(0); //Sharp
    if (key>15&&key<30) keyaccagnostic = m_keyaltAgnostic.at(1); //Flat

    string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    string hseparation1 = codificationh(1);  //Equal for type 1 and 3

    for (std::size_t i = 0; i < accidentalplace.size(); i++) {
        cod0 << keyaccagnostic << accidentalplace[i] << hseparation0;
        cod1 << keyaccagnostic << accidentalplace[i] << hseparation1;
        cod2 << keyaccagnostic << accidentalplace[i] << hseparation0;
        cod3 << keyaccagnostic << accidentalplace[i] << hseparation1;
    }

    return keysign;
}

string AlfaroGenerator4E::compass (float &compassdur, int &N, int &M){
    string choosencompass;
    string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    string hseparation1 = codificationh(1);  //Equal for type 1 and 3
    string vseparation0 = codificationv(0);  //Equal for type 0 and 3
    string vseparation1 = codificationv(1);  //Equal for type 1 and 2
    if (N < 101){ //50% of chance of for this compass
            compassdur = 4;
            M = 1;
            int met = rand()%2;
            if (met==1){ //50% of chance of using this notation
                choosencompass = "*M4/4";
                cod0 << "digit.4:L4" << vseparation0 << "digit.4:L2" << hseparation0;
                cod1 << "digit.4:L4" << vseparation1 << "digit.4:L2" << hseparation1;
                cod2 << "vertical.start" << hseparation0 << "digit.4:L4" << vseparation1 << "digit.4:L2" << hseparation0 << "vertical.end" << hseparation0;
                cod3 << "digit.4:L4" << vseparation0 << "digit.4:L2" << hseparation1;
            }else{      //50% of chance of using this other notation
                choosencompass = "*M4/4\n*met(c)";
                cod0 << "metersign.Ct:L3" << hseparation0;
                cod1 << "metersign.Ct:L3" << hseparation1;
                cod2 << "metersign.Ct:L3" << hseparation0;
                cod3 << "metersign.Ct:L3" << hseparation1;
            }            
    }else{
        if (N < 151){ //25% of chance of for this compass
            compassdur = 3;
            M = 3;
            choosencompass = "*M3/4";
            cod0 << "digit.3:L4" << vseparation0 << "digit.4:L2" << hseparation0;
            cod1 << "digit.3:L4" << vseparation1 << "digit.4:L2" << hseparation1;
            cod2 << "vertical.start" << hseparation0 << "digit.3:L4" << vseparation1 << "digit.4:L2" << hseparation0 << "vertical.end" << hseparation0;
            cod3 << "digit.3:L4" << vseparation0 << "digit.4:L2" << hseparation1;
        }else{
            if (N < 175){ //12% of chance of for this compass
                compassdur = 4;
                M = 2;
                int met = rand()%2;
                if (met==1){ //50% of chance of using this notation
                    choosencompass = "*M2/2";
                    cod0 << "digit.2:L4" << vseparation0 << "digit.2:L2" << hseparation0;
                    cod1 << "digit.2:L4" << vseparation1 << "digit.2:L2" << hseparation1;
                    cod2 << "vertical.start" << hseparation0 << "digit.2:L4" << vseparation1 << "digit.2:L2" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.2:L4" << vseparation0 << "digit.2:L2" << hseparation1;
                }else{      //50% of chance of using this other notation
                    choosencompass = "*M2/2\n*met(c|)";
                    cod0 << "metersign.Ccut:L3" << hseparation0;
                    cod1 << "metersign.Ccut:L3" << hseparation1;
                    cod2 << "metersign.Ccut:L3" << hseparation0;
                    cod3 << "metersign.Ccut:L3" << hseparation1;
                }
                
            }else{
                if (N < 185){ //5% of chance of for this compass
                    compassdur = 2;
                    M = 4;
                    choosencompass = "*M2/4";
                    cod0 << "digit.2:L4" << vseparation0 << "digit.4:L2" << hseparation0;
                    cod1 << "digit.2:L4" << vseparation1 << "digit.4:L2" << hseparation1;
                    cod2 << "vertical.start" << hseparation0 << "digit.2:L4" << vseparation1 << "digit.4:L2" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.2:L4" << vseparation0 << "digit.4:L2" << hseparation1;
                }else{
                    switch(N){
                        case 185: //2% of chance of for this compass   
                        case 186:   
                        case 187:
                        case 188: 
                            compassdur = 3;
                            M = 5;
                            choosencompass = "*M6/8";
                            cod0 << "digit.6:L4" << vseparation0 << "digit.8:L2" << hseparation0;
                            cod1 << "digit.6:L4" << vseparation1 << "digit.8:L2" << hseparation1;
                            cod2 << "vertical.start" << hseparation0 << "digit.6:L4" << vseparation1 << "digit.8:L2" << hseparation0 << "vertical.end" << hseparation0;
                            cod3 << "digit.6:L4" << vseparation0 << "digit.8:L2" << hseparation1;
                            break;
                        case 189: //2% of chance of for this compass  
                        case 190:   
                        case 191:
                        case 192:
                            compassdur = 6;
                            M = 6;
                            choosencompass = "*M12/8";
                            cod0 << "digit.12:L4" << vseparation0 << "digit.8:L2" << hseparation0;
                            cod1 << "digit.12:L4" << vseparation1 << "digit.8:L2" << hseparation1;
                            cod2 << "vertical.start" << hseparation0 << "digit.12:L4" << vseparation1 << "digit.8:L2" << hseparation0 << "vertical.end" << hseparation0;
                            cod3 << "digit.12:L4" << vseparation0 << "digit.8:L2" << hseparation1;
                            break;
                        case 193: //2% of chance of for this compass
                        case 194:   
                        case 195:
                        case 196:
                            compassdur = 4.5;
                            M = 7;
                            choosencompass = "*M9/8";
                            cod0 << "digit.9:L4" << vseparation0 << "digit.8:L2" << hseparation0;
                            cod1 << "digit.9:L4" << vseparation1 << "digit.8:L2" << hseparation1;
                            cod2 << "vertical.start" << hseparation0 << "digit.9:L4" << vseparation1 << "digit.8:L2" << hseparation0 << "vertical.end" << hseparation0;
                            cod3 << "digit.9:L4" << vseparation0 << "digit.8:L2" << hseparation1;
                            break;
                        case 197: //2% of chance of for this compass
                        case 198:   
                        case 199:
                        case 200:
                            compassdur = 5;
                            M = 8;
                            choosencompass = "*M5/4";
                            cod0 << "digit.5:L4" << vseparation0 << "digit.4:L2" << hseparation0;
                            cod1 << "digit.5:L4" << vseparation1 << "digit.4:L2" << hseparation1;
                            cod2 << "vertical.start" << hseparation0 << "digit.5:L4" << vseparation1 << "digit.4:L2" << hseparation0 << "vertical.end" << hseparation0;
                            cod3 << "digit.5:L4" << vseparation0 << "digit.4:L2" << hseparation1;
                            break;
                    }
                }
            }
        }

    }
      
    return choosencompass;
}

string AlfaroGenerator4E::silence(float &sum, int M){
    string choosensilence;
    string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    string hseparation1 = codificationh(1);  //Equal for type 1 and 3
    int TS = rand()%5; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth;
    int DOT = rand()%20; //To decide if it's going to be dotted or not
    switch(TS){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosensilence = "1.r";
                    cod0 << "rest.whole:L4" << hseparation0 << "dot:S3" << hseparation0;
                    cod1 << "rest.whole:L4" << hseparation1 << "dot:S3" << hseparation1;
                    cod2 << "rest.whole:L4" << hseparation0 << "dot:S3" << hseparation0;
                    cod3 << "rest.whole:L4" << hseparation1 << "dot:S3" << hseparation1;
                    sum+=6;
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosensilence = "1r";
                    cod0 << "rest.whole:L4" << hseparation0;
                    cod1 << "rest.whole:L4" << hseparation1;
                    cod2 << "rest.whole:L4" << hseparation0;
                    cod3 << "rest.whole:L4" << hseparation1;
                    sum+=4;
                }
            }
            break;
        case 1:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosensilence = "2.r";
                    cod0 << "rest.half:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod1 << "rest.half:L3" << hseparation1 << "dot:S3" << hseparation1;
                    cod2 << "rest.half:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod3 << "rest.half:L3" << hseparation1 << "dot:S3" << hseparation1;
                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosensilence = "2r";
                    cod0 << "rest.half:L3" << hseparation0;
                    cod1 << "rest.half:L3" << hseparation1;
                    cod2 << "rest.half:L3" << hseparation0;
                    cod3 << "rest.half:L3" << hseparation1;
                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosensilence = "4.r";
                    cod0 << "rest.quarter:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod1 << "rest.quarter:L3" << hseparation1 << "dot:S3" << hseparation1;
                    cod2 << "rest.quarter:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod3 << "rest.quarter:L3" << hseparation1 << "dot:S3" << hseparation1;
                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosensilence = "4r";
                    cod0 << "rest.quarter:L3" << hseparation0;
                    cod1 << "rest.quarter:L3" << hseparation1;
                    cod2 << "rest.quarter:L3" << hseparation0;
                    cod3 << "rest.quarter:L3" << hseparation1;
                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosensilence = "8.r";
                    cod0 << "rest.eighth:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod1 << "rest.eighth:L3" << hseparation1 << "dot:S3" << hseparation1;
                    cod2 << "rest.eighth:L3" << hseparation0 << "dot:S3" << hseparation0;
                    cod3 << "rest.eighth:L3" << hseparation1 << "dot:S3" << hseparation1;
                    sum+=0.75;
                }
            }else{
                if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                    choosensilence = "8r";
                    cod0 << "rest.eighth:L3" << hseparation0;
                    cod1 << "rest.eighth:L3" << hseparation1;
                    cod2 << "rest.eighth:L3" << hseparation0;
                    cod3 << "rest.eighth:L3" << hseparation1;
                    sum+=0.5;
                }
            }
            break;
        case 4:
            //We are not going to have a dotted rest sixteenth because we do not have thirty-second notes to complete the duration of compass just in case.
            choosensilence = "16r";
            cod0 << "rest.sixteenth:L3" << hseparation0;
            cod1 << "rest.sixteenth:L3" << hseparation1;
            cod2 << "rest.sixteenth:L3" << hseparation0;
            cod3 << "rest.sixteenth:L3" << hseparation1;
            sum+=0.25;
        break;
    }

    return choosensilence;
}

//Template for pitches in clef G2 //
string AlfaroGenerator4E::clefG2 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefG2[sampleint];

    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef F //
string AlfaroGenerator4E::clefF (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefF[sampleint];

    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef C3 //
string AlfaroGenerator4E::clefC3 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefC3[sampleint];
    
    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef C1 //
string AlfaroGenerator4E::clefC1 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefC1[sampleint];
    
    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef G1 //
string AlfaroGenerator4E::clefG1 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefG1[sampleint];

    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef C2 //
string AlfaroGenerator4E::clefC2 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefC2[sampleint];
    
    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

//Template for pitches in clef C4 //
string AlfaroGenerator4E::clefC4 (int sampleint, std::string &noteplace, int &noteident, std::string &dotplace, int &stemdirection){
    ClefData l_clef = m_clefC4[sampleint];
    
    noteplace = l_clef.noteplace;
    noteident = l_clef.noteident;
    dotplace = l_clef.dotplace;
    stemdirection = l_clef.stemdirection;
    return l_clef.pitch;
}

string AlfaroGenerator4E::normaldistribution (int CL, float mean, float variance, std::string &noteplace, int &noteident,  std::string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote, int &stemdirection){
    float sample;
    std::string pitch;
    
    //Random device class instance, source of 'true' randomness for initializing random seed
    std::random_device rd; 

    //Mersenne twister PRNG, initialized with seed from previous random device instance
    std::mt19937 gen(rd()); 

    //Instance of class std::normal_distribution with specific mean and stddev
    std::normal_distribution<float> d(mean, variance); 

    //Get random number with normal distribution using gen as random source
    sample = d(gen);
    sampleint = static_cast<int>(sample+0.5);
    if (sampleint>21){
        sampleint = 21;
    }


    if (BEAM == 1){
        int nextbeam = rand()%1;
        if (beamnote<11){
            sampleint = beamnote + nextbeam;
        }else{
            sampleint = beamnote - nextbeam;
        }
    }

    if (CHORD==1){
        if (sampleint<4){
            sampleint += 7;
        }
    }

    if (CHORD==2){
        sampleint = chordnote - 2;
    }
    
    //If for some reason sampleint is out of range, we force it to be at the limits
    if (sampleint<0){
        sampleint = 0;
    }
    
    if (sampleint>21){
        sampleint = 21;
    }

    if (CL==0) pitch = clefG2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==1) pitch = clefF(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==2) pitch = clefC3(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==3) pitch = clefC1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==4) pitch = clefG1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==5) pitch = clefC2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==6) pitch = clefC4(sampleint, noteplace, noteident, dotplace, stemdirection);

    return pitch;
}

string AlfaroGenerator4E::randomwalk (int CL, std::string &noteplace, int &noteident,  std::string &dotplace, int &sampleint, int CHORD, int chordnote, int counter, int &stemdirection){  
    std::string pitch;
    int rw = rand()%3; //0 (minus 1),; 1 (stays the same); 2 (plus 1)
    int limit = rand()%2; //0 - Absorbent limit ; 1 - Reflective limit

    if (counter==1){
        sampleint = 10;
    }else{
        switch (rw){
        case 0:
            sampleint = sampleint - 1;
            if (sampleint<0){
                if (limit==0){
                    sampleint = 0; //Absorbent limit
                }else{
                    sampleint = sampleint + 2; //Reflective limit
                }
            }
            break;
        case 1:
            sampleint = sampleint;
            break;
        case 2:
            sampleint = sampleint + 1;
            if (sampleint>21){ 
                if (limit==0){
                    sampleint = 21; //Absorbent limit
                }else{
                    sampleint = sampleint - 2; //Reflective limit
                }
            }
            break;
        } 
    }
    
  
    if (CHORD==1){
        if (sampleint<4){
            sampleint += 7;
        }
    }

    if (CHORD==2){
        sampleint = chordnote - 2;
    }
    
    //If for some reason sampleint is out of range, we force it to be at the limits
    if (sampleint<0){
        sampleint = 0;
    }
    
    if (sampleint>21){
        sampleint = 21;
    }

    if (CL==0) pitch = clefG2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==1) pitch = clefF(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==2) pitch = clefC3(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==3) pitch = clefC1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==4) pitch = clefG1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==5) pitch = clefC2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==6) pitch = clefC4(sampleint, noteplace, noteident, dotplace, stemdirection);

    return pitch;
}

string AlfaroGenerator4E::logistic (int CL, std::string &noteplace, int &noteident,  std::string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote, int counter, float rlogistic, float &xlogistic, int &stemdirection){
    std::string pitch;
    
    if (counter==1){
        sampleint = 10;
        xlogistic = 0.5; 
    }else{
        xlogistic = rlogistic*xlogistic*(1-xlogistic); //Always between 0 and 1.
        sampleint = (static_cast<int>(xlogistic+0.5))*17;
        if (sampleint<6){ //We limit to notes appearing in the staff. Because of the jumps.
            sampleint = 6;
        }
        if (sampleint>16){
            sampleint = 16;
        }
    }
    
    if (BEAM == 1){
        int nextbeam = rand()%1;
        if (beamnote<11){
            sampleint = beamnote + nextbeam;
        }else{
            sampleint = beamnote - nextbeam;
        }
    }

    if (CHORD==1){
        if (sampleint<4){
            sampleint += 7;
        }
    }

    if (CHORD==2){
        sampleint = chordnote - 2;
    }
    
    //If for some reason sampleint is out of range, we force it to be at the limits
    if (sampleint<0){
        sampleint = 0;
    }
    
    if (sampleint>21){
        sampleint = 21;
    }

    if (CL==0) pitch = clefG2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==1) pitch = clefF(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==2) pitch = clefC3(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==3) pitch = clefC1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==4) pitch = clefG1(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==5) pitch = clefC2(sampleint, noteplace, noteident, dotplace, stemdirection);
    if (CL==6) pitch = clefC4(sampleint, noteplace, noteident, dotplace, stemdirection);

    return pitch;
}

string AlfaroGenerator4E::pitchgeneration (int CL, float mean, float variance, std::string &noteplace, int &noteident,  std::string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, float &xlogistic, int &stemdirection){
    std::string pitch;
    switch(typeofgen){
        case 1:
            pitch = normaldistribution (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, stemdirection);
            break;
        case 2:
            pitch = randomwalk (CL, noteplace, noteident, dotplace, sampleint, CHORD, chordnote, counter, stemdirection);
            break;
        case 3:
            pitch = logistic (CL, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, counter, rlogistic, xlogistic, stemdirection);
            break;
    }
    return pitch;
}

string AlfaroGenerator4E::alteration (int naltered, int key, std::string &finalnote, std::string noteplace, int noteident, std::vector<int> keyident){
    std::string accidental;

    int AL = rand()%101; //From 0 to 100: to decide the alteration of the note
    int TAL = rand()%2; //0-Sharp; 1-Flat
    int CAL = 0;

    int altident = map_alt.at(noteplace);

    for(int i=0; i<7; i++){
        if(noteident==keyident[i]){
            if(key>1&&key<16){ //Sharp alteration in key signature
                if (AL < naltered){
                    finalnote += "#";
                    if (altident==3){ //If there is a 3, the alteration of the key signature was put as natural.
                        accidental = "accidental.sharp:" + noteplace; 
                    }else if (altident==1){
                        accidental = "";
                    }
                    CAL = 1; 
                    map_alt[noteplace]= 1;
                }else{ 
                    finalnote += "n";
                    accidental = "accidental.natural:" + noteplace; 
                    CAL = 1;
                    map_alt[noteplace]= 3;
                }
            }else{
                if(key>15&&key<30){ //Flat alteration in key signature
                    if (AL < naltered){  
                        finalnote += "-";                        
                        if (altident==3){ //If there is a 3, the alteration of the key signature was put as natural.
                            accidental = "accidental.flat:" + noteplace; 
                        }else if (altident==2){
                            accidental = "";
                        }
                        CAL =1 ; 
                        map_alt[noteplace]= 2;
                    }else{ 
                        finalnote += "n";
                        accidental = "accidental.natural:" + noteplace; 
                        CAL = 1;
                        map_alt[noteplace]= 3;
                    }
                }
            }
            break; //To break the loop once it has found the pitch of the note.
        }
    }

    if (CAL==0){
        if (AL < naltered){
            if (TAL==0){
                finalnote += "#";
                if (altident!=1){ //If there is a 1, it means the note has been already altered (sharp) in the compass.
                    accidental = "accidental.sharp:" + noteplace; 
                }else{
                    accidental = "";
                }
                map_alt[noteplace]= 1;
            }else{
                finalnote += "-";
                if (altident!=2){ //If there is a 2, it means the note has been already altered (flat) in the compass.
                    accidental = "accidental.flat:" + noteplace;
                }else{
                    accidental = "";
                }
                map_alt[noteplace]= 2;
            }
        }else{
            if (altident==1||altident==2){
                accidental = "accidental.natural:" + noteplace; 
                map_alt[noteplace]= 3; //We take off the alteration. 
            }else{
                accidental = "";
            }
        }
    }

    return accidental;   
}

void AlfaroGenerator4E::tienote (int &starttie, std::string &finalnote, std::string noteplace, int &TIE, ofstream &cod0, ofstream &cod1, ofstream &cod2, ofstream &cod3){
    int end = 0;
    
    std::string vseparation0 = codificationv(0);  //Equal for type 0 and 3
    std::string vseparation1 = codificationv(1);  //Equal for type 1 and 2

    int conttie = rand()%10;
    if (starttie==0&&TIE==1){
        finalnote = "(" + finalnote; //Start of the tie/slur
        cod0 << "slur.start:" << noteplace << vseparation0;
        cod1 << "slur.start:" << noteplace << vseparation1;
        cod2 << "slur.start:" << noteplace << vseparation1;
        cod3 << "slur.start:" << noteplace << vseparation0;
        if (conttie<8){ //80% of chance of being just two notes tied
            starttie = 1; //The tie/slur ends.
            TIE = 0;
            end = 1;
        }else{
            starttie = 1; 
        }
    }
    if (starttie==1&&TIE==1){
        if (conttie<8){ //Stop the tie/slur
            TIE = 0;
        }
    }
    if (starttie==1&&TIE==0&&end==0){
        finalnote += ")"; //End of the tie
        cod0 << "slur.end:" << noteplace << vseparation0;
        cod1 << "slur.end:" << noteplace << vseparation1;
        cod2 << "slur.end:" << noteplace << vseparation1;
        cod3 << "slur.end:" << noteplace << vseparation0;
        starttie = 0;
        TIE = rand()%10;
    }
    return;
}

string AlfaroGenerator4E::note(float &sum, int M, int CL, int naltered, float mean, float variance, std::vector<int> keyident, int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic){
    std::string choosennote;
    std::string pitch;
    std::string finalnote;
    std::string noteplace;
    std::string dotplace;
    std::string accidental;
    std::string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    std::string hseparation1 = codificationh(1);  //Equal for type 1 and 3
    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%8; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth; 5-Two beamed 8th; 6-Two beamed 16th; 7-Four beamed 16th
    int DOT = rand()%20; //To decide if it's going to be dotted or not
    int stemdirection;

    switch(TN){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosennote = "1.";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){
                        cod0 << accidental << hseparation0;
                        cod1 << accidental << hseparation1;
                        cod2 << accidental << hseparation0;
                        cod3 << accidental << hseparation1;
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    cod0 << "note.whole:" << noteplace << hseparation0;
                    cod1 << "note.whole:" << noteplace << hseparation1;
                    cod2 << "note.whole:" << noteplace << hseparation0;
                    cod3 << "note.whole:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    cod0 << "dot:" << dotplace << hseparation0; 
                    cod1 << "dot:" << dotplace << hseparation1; 
                    cod2 << "dot:" << dotplace << hseparation0; 
                    cod3 << "dot:" << dotplace << hseparation1; 

                    sum+=6; 
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosennote = "1";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }

                    cod0 << "note.whole:" << noteplace << hseparation0;
                    cod1 << "note.whole:" << noteplace << hseparation1;
                    cod2 << "note.whole:" << noteplace << hseparation0;
                    cod3 << "note.whole:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                     
                    sum+=4; 
                }
            }
            break;
        case 1:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosennote = "2.";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    cod0 << "note.half:" << noteplace << hseparation0;
                    cod1 << "note.half:" << noteplace << hseparation1;
                    cod2 << "note.half:" << noteplace << hseparation0;
                    cod3 << "note.half:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    cod0 << "dot:" << dotplace << hseparation0; 
                    cod1 << "dot:" << dotplace << hseparation1; 
                    cod2 << "dot:" << dotplace << hseparation0; 
                    cod3 << "dot:" << dotplace << hseparation1; 

                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosennote = "2";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }

                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    cod0 << "note.half:" << noteplace << hseparation0;
                    cod1 << "note.half:" << noteplace << hseparation1;
                    cod2 << "note.half:" << noteplace << hseparation0;
                    cod3 << "note.half:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;

                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosennote = "4.";
                   
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    cod0 << "note.quarter:" << noteplace << hseparation0;
                    cod1 << "note.quarter:" << noteplace << hseparation1;
                    cod2 << "note.quarter:" << noteplace << hseparation0;
                    cod3 << "note.quarter:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    cod0 << "dot:" << dotplace << hseparation0; 
                    cod1 << "dot:" << dotplace << hseparation1; 
                    cod2 << "dot:" << dotplace << hseparation0; 
                    cod3 << "dot:" << dotplace << hseparation1; 

                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosennote = "4";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    
                    cod0 << "note.quarter:" << noteplace << hseparation0;
                    cod1 << "note.quarter:" << noteplace << hseparation1;
                    cod2 << "note.quarter:" << noteplace << hseparation0;
                    cod3 << "note.quarter:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;

                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosennote = "8.";
                     
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 

                    cod0 << "note.eighth:" << noteplace << hseparation0;
                    cod1 << "note.eighth:" << noteplace << hseparation1;
                    cod2 << "note.eighth:" << noteplace << hseparation0;
                    cod3 << "note.eighth:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    cod0 << "dot:" << dotplace << hseparation0; 
                    cod1 << "dot:" << dotplace << hseparation1; 
                    cod2 << "dot:" << dotplace << hseparation0; 
                    cod3 << "dot:" << dotplace << hseparation1; 

                    sum+=0.75;
                }
            }else{
                if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                    choosennote = "8";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 

                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }

                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }

                    cod0 << "note.eighth:" << noteplace << hseparation0;
                    cod1 << "note.eighth:" << noteplace << hseparation1;
                    cod2 << "note.eighth:" << noteplace << hseparation0;
                    cod3 << "note.eighth:" << noteplace << hseparation1;
                    if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    
                    sum+=0.5;
                }
            }
            break;
        case 4:
            //We are not going to have a dotted note sixteenth because we do not have thirty-second notes to complete the duration of compass just in case.
            choosennote = "16";

            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
            finalnote = choosennote + pitch;
            accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
            if(accidental!=""){                         
                cod0 << accidental << hseparation0;                         
                cod1 << accidental << hseparation1;                         
                cod2 << accidental << hseparation0;                         
                cod3 << accidental << hseparation1;                     
            } 

            if (starttie==1&&TIE==0){//Force the tie to end
                cod2 << "vertical.start" << hseparation0;
                tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                endtie = 1;
            }

            if (TIE==1){ //The note is tied
                if (endtie==0) cod2 << "vertical.start" << hseparation0;
                tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                endtie = 1;
            }

            cod0 << "note.sixteenth:" << noteplace << hseparation0;
            cod1 << "note.sixteenth:" << noteplace << hseparation1;
            cod2 << "note.sixteenth:" << noteplace << hseparation0;
            cod3 << "note.sixteenth:" << noteplace << hseparation1;
            if (endtie==1) cod2 << "vertical.end" << hseparation0;
            
            sum+=0.25;
            
            break;
        case 5:
            if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                choosennote = "8";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidental!=""){                         
                    cod0 << accidental << hseparation0;                         
                    cod1 << accidental << hseparation1;                         
                    cod2 << accidental << hseparation0;                         
                    cod3 << accidental << hseparation1;                     
                } 
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cod0 << "note.beamedRight1:" << noteplace << hseparation0;
                cod1 << "note.beamedRight1:" << noteplace << hseparation1;
                cod2 << "note.beamedRight1:" << noteplace << hseparation0;
                cod3 << "note.beamedRight1:" << noteplace << hseparation1;
                if (endtie==1) cod2 << "vertical.end" << hseparation0;


                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                finalnote += choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidental!=""){                         
                    cod0 << accidental << hseparation0;                         
                    cod1 << accidental << hseparation1;                         
                    cod2 << accidental << hseparation0;                         
                    cod3 << accidental << hseparation1;                     
                } 
                finalnote += "J";
                if (TIE==1){ //The note is tied
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }
                cod0 << "note.beamedLeft1:" << noteplace << hseparation0;
                cod1 << "note.beamedLeft1:" << noteplace << hseparation1;
                cod2 << "note.beamedLeft1:" << noteplace << hseparation0;
                cod3 << "note.beamedLeft1:" << noteplace << hseparation1;
                if (endtie==1) cod2 << "vertical.end" << hseparation0;
                      
                sum+=1;
            }
            break;
        case 6:
            if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                choosennote = "16";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidental!=""){                         
                    cod0 << accidental << hseparation0;                         
                    cod1 << accidental << hseparation1;                         
                    cod2 << accidental << hseparation0;                         
                    cod3 << accidental << hseparation1;                     
                } 
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cod0 << "note.beamedRight2:" << noteplace << hseparation0;
                cod1 << "note.beamedRight2:" << noteplace << hseparation1;
                cod2 << "note.beamedRight2:" << noteplace << hseparation0;
                cod3 << "note.beamedRight2:" << noteplace << hseparation1;
                if (endtie==1) cod2 << "vertical.end" << hseparation0;

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                finalnote += choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidental!=""){                         
                    cod0 << accidental << hseparation0;                         
                    cod1 << accidental << hseparation1;                         
                    cod2 << accidental << hseparation0;                         
                    cod3 << accidental << hseparation1;                     
                } 
                finalnote += "J";
                if (TIE==1){ //The note is tied
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }
                cod0 << "note.beamedLeft2:" << noteplace << hseparation0;
                cod1 << "note.beamedLeft2:" << noteplace << hseparation1;
                cod2 << "note.beamedLeft2:" << noteplace << hseparation0;
                cod3 << "note.beamedLeft2:" << noteplace << hseparation1;
                if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    
                sum+=0.5;
            }
            break;    
        case 7:
            if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                choosennote = "16";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidental!=""){                         
                    cod0 << accidental << hseparation0;                         
                    cod1 << accidental << hseparation1;                         
                    cod2 << accidental << hseparation0;                         
                    cod3 << accidental << hseparation1;                     
                } 
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cod0 << "note.beamedRight2:" << noteplace << hseparation0;
                cod1 << "note.beamedRight2:" << noteplace << hseparation1;
                cod2 << "note.beamedRight2:" << noteplace << hseparation0;
                cod3 << "note.beamedRight2:" << noteplace << hseparation1;
                if (endtie==1) cod2 << "vertical.end" << hseparation0;

                for(int b=0; b<3; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    if(accidental!=""){                         
                        cod0 << accidental << hseparation0;                         
                        cod1 << accidental << hseparation1;                         
                        cod2 << accidental << hseparation0;                         
                        cod3 << accidental << hseparation1;                     
                    } 
                    if (b==0||b==1){
                        finalnote += "\n";
                        cod0 << "note.beamedBoth2:" << noteplace << hseparation0;
                        cod1 << "note.beamedBoth2:" << noteplace << hseparation1;
                        cod2 << "note.beamedBoth2:" << noteplace << hseparation0;
                        cod3 << "note.beamedBoth2:" << noteplace << hseparation1;
                    }else{
                        finalnote += "J";
                        if (TIE==1){ //The note is tied
                            cod2 << "vertical.start" << hseparation0;
                            tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                            endtie = 1;
                        }
                        cod0 << "note.beamedLeft2:" << noteplace << hseparation0;
                        cod1 << "note.beamedLeft2:" << noteplace << hseparation1;
                        cod2 << "note.beamedLeft2:" << noteplace << hseparation0;
                        cod3 << "note.beamedLeft2:" << noteplace << hseparation1;
                        if (endtie==1) cod2 << "vertical.end" << hseparation0;
                    }                    
                }
                    
                sum+=1;
            }
            break;
    }
    choosennote.clear();
    pitch.clear();
    noteplace.clear();
    dotplace.clear();
    accidental.clear();
    return finalnote;
}

string AlfaroGenerator4E::tuplet(float &sum, int M, int CL, int naltered, float mean, float variance, std::vector<int> keyident, int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic){
    std::string choosennote;
    std::string pitch;
    std::string finalnote;
    std::string noteplace;
    std::string dotplace;
    std::string accidental;
    std::string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    std::string hseparation1 = codificationh(1);  //Equal for type 1 and 3
    std::string vseparation0 = codificationv(0);  //Equal for type 0 and 3
    std::string vseparation1 = codificationv(1);  //Equal for type 1 and 2
    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%4; //0-Half; 1-Quarter; 2-Eighth; 3-Sixteenth
    int stemdirection;

    //To identify whether the digit for the tuplets is above or below the note heads
    std::string noteaux1;
    std::string noteaux2;
    std::string noteaux3;
    std::string accidentalaux1;
    std::string accidentalaux2;
    std::string accidentalaux3;
    int stemaux1;
    int stemaux2;
    int stemaux3;

    switch(TN){
        case 0:
            if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                choosennote = "3";
                
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                noteaux1 = noteplace;
                stemaux1 = stemdirection;
                accidentalaux1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidentalaux1!=""){                         
                    cod0 << accidentalaux1 << hseparation0;                         
                    cod1 << accidentalaux1 << hseparation1;                         
                    cod2 << accidentalaux1 << hseparation0;                         
                    cod3 << accidentalaux1 << hseparation1;                     
                } 
                
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }

                finalnote = finalnote + "\n";
                if (endtie==0) cod2 << "vertical.start" << hseparation0;
                                
                
                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                     
                    if (b==0){
                        finalnote += "\n";
                        noteaux2 = noteplace;
                        accidentalaux2 = accidental;
                        stemaux2 = stemdirection;
                    }else{
                        noteaux3 = noteplace;
                        accidentalaux3 = accidental;
                        stemaux3 = stemdirection;
                    }                    
                }

                if (stemaux1 + stemaux2 + stemaux3 <= 2){
                    //First note
                    cod0 << "bracket.start:S6" << vseparation0 << "note.half:" << noteaux1 << hseparation0;
                    cod1 << "bracket.start:S6" << vseparation1 << "note.half:" << noteaux1 << hseparation1;
                    cod2 << "bracket.start:S6" << vseparation1 << "note.half:" << noteaux1 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "bracket.start:S6" << vseparation0 << "note.half:" << noteaux1 << hseparation1;

                    //Second note
                    if(accidentalaux2!=""){                         
                        cod0 << accidentalaux2 << hseparation0;                         
                        cod1 << accidentalaux2 << hseparation1;                         
                        cod2 << accidentalaux2 << hseparation0;                         
                        cod3 << accidentalaux2 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "digit.3:S6" << vseparation0 << "note.half:" << noteaux2 << hseparation0;
                    cod1 << "digit.3:S6" << vseparation1 << "note.half:" << noteaux2 << hseparation1;
                    cod2 << "digit.3:S6" << vseparation1 << "note.half:" << noteaux2 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.3:S6" << vseparation0 << "note.half:" << noteaux2 << hseparation1;

                    //Third note
                    if(accidentalaux3!=""){                         
                        cod0 << accidentalaux3 << hseparation0;                         
                        cod1 << accidentalaux3 << hseparation1;                         
                        cod2 << accidentalaux3 << hseparation0;                         
                        cod3 << accidentalaux3 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "bracket.end:S6" << vseparation0 << "note.half:" << noteaux3 << hseparation0;
                    cod1 << "bracket.end:S6" << vseparation1 << "note.half:" << noteaux3 << hseparation1;
                    cod2 << "bracket.end:S6" << vseparation1 << "note.half:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "bracket.end:S6" << vseparation0 << "note.half:" << noteaux3 << hseparation1;
                }else{
                    //First note
                    cod0 << "note.half:" << noteaux1 << vseparation0 << "bracket.start:S-1" << hseparation0;
                    cod1 << "note.half:" << noteaux1 << vseparation1 << "bracket.start:S-1" << hseparation1;
                    cod2 << "note.half:" << noteaux1 << vseparation1 << "bracket.start:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.half:" << noteaux1 << vseparation0 << "bracket.start:S-1" << hseparation1;

                    //Second note
                    if(accidentalaux2!=""){                         
                        cod0 << accidentalaux2 << hseparation0;                         
                        cod1 << accidentalaux2 << hseparation1;                         
                        cod2 << accidentalaux2 << hseparation0;                         
                        cod3 << accidentalaux2 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.half:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation0;
                    cod1 << "note.half:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation1;
                    cod2 << "note.half:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.half:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation1;

                    //Third note
                    if(accidentalaux3!=""){                         
                        cod0 << accidentalaux3 << hseparation0;                         
                        cod1 << accidentalaux3 << hseparation1;                         
                        cod2 << accidentalaux3 << hseparation0;                         
                        cod3 << accidentalaux3 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.half:" << noteaux3 << vseparation0 << "bracket.end:S-1" << hseparation0;
                    cod1 << "note.half:" << noteaux3 << vseparation1 << "bracket.end:S-1" << hseparation1;
                    cod2 << "note.half:" << noteaux3 << vseparation1 << "bracket.end:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.half:" << noteaux3 << vseparation0 << "bracket.end:S-1" << hseparation1;
                }
                    
                sum+=4;
            }
            break;
        case 1:
            if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                choosennote = "6";

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                noteaux1 = noteplace;
                stemaux1 = stemdirection;
                accidentalaux1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidentalaux1!=""){                         
                    cod0 << accidentalaux1 << hseparation0;                         
                    cod1 << accidentalaux1 << hseparation1;                         
                    cod2 << accidentalaux1 << hseparation0;                         
                    cod3 << accidentalaux1 << hseparation1;                     
                } 
                
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }

                finalnote = finalnote + "\n";
                if (endtie==0) cod2 << "vertical.start" << hseparation0;
                                
                
                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                     
                    if (b==0){
                        finalnote += "\n";
                        noteaux2 = noteplace;
                        accidentalaux2 = accidental;
                        stemaux2 = stemdirection;
                    }else{
                        noteaux3 = noteplace;
                        accidentalaux3 = accidental;
                        stemaux3 = stemdirection;
                    }                    
                }

                if (stemaux1 + stemaux2 + stemaux3 <= 2){
                    //First note
                    cod0 << "bracket.start:S6" << vseparation0 << "note.quarter:" << noteaux1 << hseparation0;
                    cod1 << "bracket.start:S6" << vseparation1 << "note.quarter:" << noteaux1 << hseparation1;
                    cod2 << "bracket.start:S6" << vseparation1 << "note.quarter:" << noteaux1 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "bracket.start:S6" << vseparation0 << "note.quarter:" << noteaux1 << hseparation1;

                    //Second note
                    if(accidentalaux2!=""){                         
                        cod0 << accidentalaux2 << hseparation0;                         
                        cod1 << accidentalaux2 << hseparation1;                         
                        cod2 << accidentalaux2 << hseparation0;                         
                        cod3 << accidentalaux2 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "digit.3:S6" << vseparation0 << "note.quarter:" << noteaux2 << hseparation0;
                    cod1 << "digit.3:S6" << vseparation1 << "note.quarter:" << noteaux2 << hseparation1;
                    cod2 << "digit.3:S6" << vseparation1 << "note.quarter:" << noteaux2 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.3:S6" << vseparation0 << "note.quarter:" << noteaux2 << hseparation1;

                    //Third note
                    if(accidentalaux3!=""){                         
                        cod0 << accidentalaux3 << hseparation0;                         
                        cod1 << accidentalaux3 << hseparation1;                         
                        cod2 << accidentalaux3 << hseparation0;                         
                        cod3 << accidentalaux3 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "bracket.end:S6" << vseparation0 << "note.quarter:" << noteaux3 << hseparation0;
                    cod1 << "bracket.end:S6" << vseparation1 << "note.quarter:" << noteaux3 << hseparation1;
                    cod2 << "bracket.end:S6" << vseparation1 << "note.quarter:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "bracket.end:S6" << vseparation0 << "note.quarter:" << noteaux3 << hseparation1;
                }else{
                    //First note
                    cod0 << "note.quarter:" << noteaux1 << vseparation0 << "bracket.start:S-1" << hseparation0;
                    cod1 << "note.quarter:" << noteaux1 << vseparation1 << "bracket.start:S-1" << hseparation1;
                    cod2 << "note.quarter:" << noteaux1 << vseparation1 << "bracket.start:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.quarter:" << noteaux1 << vseparation0 << "bracket.start:S-1" << hseparation1;

                    //Second note
                    if(accidentalaux2!=""){                         
                        cod0 << accidentalaux2 << hseparation0;                         
                        cod1 << accidentalaux2 << hseparation1;                         
                        cod2 << accidentalaux2 << hseparation0;                         
                        cod3 << accidentalaux2 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.quarter:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation0;
                    cod1 << "note.quarter:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation1;
                    cod2 << "note.quarter:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.quarter:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation1;

                    //Third note
                    if(accidentalaux3!=""){                         
                        cod0 << accidentalaux3 << hseparation0;                         
                        cod1 << accidentalaux3 << hseparation1;                         
                        cod2 << accidentalaux3 << hseparation0;                         
                        cod3 << accidentalaux3 << hseparation1;                     
                    }
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.quarter:" << noteaux3 << vseparation0 << "bracket.end:S-1" << hseparation0;
                    cod1 << "note.quarter:" << noteaux3 << vseparation1 << "bracket.end:S-1" << hseparation1;
                    cod2 << "note.quarter:" << noteaux3 << vseparation1 << "bracket.end:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.quarter:" << noteaux3 << vseparation0 << "bracket.end:S-1" << hseparation1;
                }
     
                sum+=2;
            }
            break;
        case 2:
            if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                choosennote = "12"; 
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                noteaux1 = noteplace;
                stemaux1 = stemdirection;
                accidentalaux1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidentalaux1!=""){                         
                    cod0 << accidentalaux1 << hseparation0;                         
                    cod1 << accidentalaux1 << hseparation1;                         
                    cod2 << accidentalaux1 << hseparation0;                         
                    cod3 << accidentalaux1 << hseparation1;                     
                } 
                
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }

                finalnote = finalnote + "L" + "\n";
                
                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                     
                    if (b==0){
                        finalnote += "\n";
                        noteaux2 = noteplace;
                        accidentalaux2 = accidental;
                        stemaux2 = stemdirection;
                    }else{
                        finalnote += "J";
                        noteaux3 = noteplace;
                        accidentalaux3 = accidental;
                        stemaux3 = stemdirection;
                    }                    
                }

                //First note
                cod0 << "note.beamedRight1:" << noteaux1 << hseparation0;
                cod1 << "note.beamedRight1:" << noteaux1 << hseparation1;
                cod2 << "note.beamedRight1:" << noteaux1 << hseparation0;
                cod3 << "note.beamedRight1:" << noteaux1 << hseparation1;

                //Second note
                if(accidentalaux2!=""){                         
                    cod0 << accidentalaux2 << hseparation0;                         
                    cod1 << accidentalaux2 << hseparation1;                         
                    cod2 << accidentalaux2 << hseparation0;                         
                    cod3 << accidentalaux2 << hseparation1;                     
                }

                if (stemaux1 + stemaux2 + stemaux3 <= 2){
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "digit.3:S6" << vseparation0 << "note.beamedBoth1:" << noteaux2 << hseparation0;
                    cod1 << "digit.3:S6" << vseparation1 << "note.beamedBoth1:" << noteaux2 << hseparation1;
                    cod2 << "digit.3:S6" << vseparation1 << "note.beamedBoth1:" << noteaux2 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.3:S6" << vseparation0 << "note.beamedBoth1:" << noteaux2 << hseparation1;
                }else{
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.beamedBoth1:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation0;
                    cod1 << "note.beamedBoth1:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation1;
                    cod2 << "note.beamedBoth1:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.beamedBoth1:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation1;

                    
                }
                //Third note
                if(accidentalaux3!=""){                         
                    cod0 << accidentalaux3 << hseparation0;                         
                    cod1 << accidentalaux3 << hseparation1;                         
                    cod2 << accidentalaux3 << hseparation0;                         
                    cod3 << accidentalaux3 << hseparation1;                     
                }
                cod0 << "note.beamedLeft1:" << noteaux3 << hseparation0;
                cod1 << "note.beamedLeft1:" << noteaux3 << hseparation1;
                cod2 << "note.beamedLeft1:" << noteaux3 << hseparation0;
                cod3 << "note.beamedLeft1:" << noteaux3 << hseparation1;
                    
                sum+=1;
            }
            break;
        case 3:
            if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                choosennote = "24";

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                noteaux1 = noteplace;
                stemaux1 = stemdirection;
                accidentalaux1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                if(accidentalaux1!=""){                         
                    cod0 << accidentalaux1 << hseparation0;                         
                    cod1 << accidentalaux1 << hseparation1;                         
                    cod2 << accidentalaux1 << hseparation0;                         
                    cod3 << accidentalaux1 << hseparation1;                     
                } 
                
                if (starttie==1&&TIE==0){//Force the tie to end
                    cod2 << "vertical.start" << hseparation0;
                    tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                    endtie = 1;
                }

                finalnote = finalnote + "L" + "\n";                
                
                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                     
                    if (b==0){
                        finalnote += "\n";
                        noteaux2 = noteplace;
                        accidentalaux2 = accidental;
                        stemaux2 = stemdirection;
                    }else{
                        finalnote += "J";
                        noteaux3 = noteplace;
                        accidentalaux3 = accidental;
                        stemaux3 = stemdirection;
                    }                    
                }

                //First note
                cod0 << "note.beamedRight2:" << noteaux1 << hseparation0;
                cod1 << "note.beamedRight2:" << noteaux1 << hseparation1;
                cod2 << "note.beamedRight2:" << noteaux1 << hseparation0;
                cod3 << "note.beamedRight2:" << noteaux1 << hseparation1;

                //Second note
                if(accidentalaux2!=""){                         
                    cod0 << accidentalaux2 << hseparation0;                         
                    cod1 << accidentalaux2 << hseparation1;                         
                    cod2 << accidentalaux2 << hseparation0;                         
                    cod3 << accidentalaux2 << hseparation1;                     
                }

                if (stemaux1 + stemaux2 + stemaux3 <= 2){
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "digit.3:S6" << vseparation0 << "note.beamedBoth2:" << noteaux2 << hseparation0;
                    cod1 << "digit.3:S6" << vseparation1 << "note.beamedBoth2:" << noteaux2 << hseparation1;
                    cod2 << "digit.3:S6" << vseparation1 << "note.beamedBoth2:" << noteaux2 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "digit.3:S6" << vseparation0 << "note.beamedBoth2:" << noteaux2 << hseparation1;    
                }else{
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.beamedBoth2:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation0;
                    cod1 << "note.beamedBoth2:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation1;
                    cod2 << "note.beamedBoth2:" << noteaux2 << vseparation1 << "digit.3:S-1" << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.beamedBoth2:" << noteaux2 << vseparation0 << "digit.3:S-1" << hseparation1;                    
                }

                //Third note
                if(accidentalaux3!=""){                         
                    cod0 << accidentalaux3 << hseparation0;                         
                    cod1 << accidentalaux3 << hseparation1;                         
                    cod2 << accidentalaux3 << hseparation0;                         
                    cod3 << accidentalaux3 << hseparation1;                     
                }
                cod0 << "note.beamedLeft2:" << noteaux3 << hseparation0;
                cod1 << "note.beamedLeft2:" << noteaux3 << hseparation1;
                cod2 << "note.beamedLeft2:" << noteaux3 << hseparation0;
                cod3 << "note.beamedLeft2:" << noteaux3 << hseparation1;

                sum+=0.5;
            }
            break;
    }

    choosennote.clear();
    pitch.clear();
    noteplace.clear();
    dotplace.clear();
    accidental.clear();
    noteaux1.clear();
    noteaux2.clear();
    noteaux3.clear();
    accidentalaux1.clear();
    accidentalaux2.clear();
    accidentalaux3.clear();
    
    return finalnote;
}

string AlfaroGenerator4E::chords(float &sum, int M, int CL, int naltered, float mean, float variance, std::vector<int> keyident, int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic){
    std::string choosennote;
    std::string pitch;
    std::string finalnote;
    std::string noteplace;
    std::string noteaux1;
    std::string noteaux2;
    std::string noteaux3;
    std::string dotplace;
    std::string dotaux1;
    std::string dotaux2;
    std::string dotaux3;
    std::string accidental1;
    std::string accidental2;
    std::string accidental3;
    std::string hseparation0 = codificationh(0);  //Equal for type 0 and 2
    std::string hseparation1 = codificationh(1);  //Equal for type 1 and 3
    std::string vseparation0 = codificationv(0);  //Equal for type 0 and 3
    std::string vseparation1 = codificationv(1);  //Equal for type 1 and 2

    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%5; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth
    int DOT = rand()%20; //To decide if it's going to be dotted or not
    int stemdirection;
   

    switch(TN){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosennote = "1.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    

                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.whole:" << noteaux1 << vseparation0 << "note.whole:" << noteaux2 << vseparation0 << "note.whole:" << noteaux3 << hseparation0;
                    cod1 << "note.whole:" << noteaux1 << vseparation1 << "note.whole:" << noteaux2 << vseparation1 << "note.whole:" << noteaux3 << hseparation1;
                    cod2 << "note.whole:" << noteaux1 << vseparation1 << "note.whole:" << noteaux2 << vseparation1 << "note.whole:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.whole:" << noteaux1 << vseparation0 << "note.whole:" << noteaux2 << vseparation0 << "note.whole:" << noteaux3 << hseparation1;
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation0; 
                    cod1 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation1; 
                    cod2 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation0 << "vertical.end" << hseparation0; 
                    cod3 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation1; 

                    
                    sum+=6;
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosennote = "1";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";


                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    

                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 <<accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 <<accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 <<accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 <<accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.whole:" << noteaux1 << vseparation0 << "note.whole:" << noteaux2 << vseparation0 << "note.whole:" << noteaux3 << hseparation0;
                    cod1 << "note.whole:" << noteaux1 << vseparation1 << "note.whole:" << noteaux2 << vseparation1 << "note.whole:" << noteaux3 << hseparation1;
                    cod2 << "note.whole:" << noteaux1 << vseparation1 << "note.whole:" << noteaux2 << vseparation1 << "note.whole:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.whole:" << noteaux1 << vseparation0 << "note.whole:" << noteaux2 << vseparation0 << "note.whole:" << noteaux3 << hseparation1;
                    
                    
                    sum+=4;
                }

            }
            break;
        case 1:
            if (DOT==10){
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosennote = "2.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
            

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);


                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.half:" << noteaux1 << vseparation0 << "note.half:" << noteaux2 << vseparation0 << "note.half:" << noteaux3 << hseparation0;
                    cod1 << "note.half:" << noteaux1 << vseparation1 << "note.half:" << noteaux2 << vseparation1 << "note.half:" << noteaux3 << hseparation1;
                    cod2 << "note.half:" << noteaux1 << vseparation1 << "note.half:" << noteaux2 << vseparation1 << "note.half:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.half:" << noteaux1 << vseparation0 << "note.half:" << noteaux2 << vseparation0 << "note.half:" << noteaux3 << hseparation1;
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation0; 
                    cod1 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation1; 
                    cod2 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation0 << "vertical.end" << hseparation0; 
                    cod3 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation1; 
                    
                    
                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosennote = "2";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);


                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.half:" << noteaux1 << vseparation0 << "note.half:" << noteaux2 << vseparation0 << "note.half:" << noteaux3 << hseparation0;
                    cod1 << "note.half:" << noteaux1 << vseparation1 << "note.half:" << noteaux2 << vseparation1 << "note.half:" << noteaux3 << hseparation1;
                    cod2 << "note.half:" << noteaux1 << vseparation1 << "note.half:" << noteaux2 << vseparation1 << "note.half:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.half:" << noteaux1 << vseparation0 << "note.half:" << noteaux2 << vseparation0 << "note.half:" << noteaux3 << hseparation1;
                    
                    
                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosennote = "4.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    

                    
                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 <<accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.quarter:" << noteaux1 << vseparation0 << "note.quarter:" << noteaux2 << vseparation0 << "note.quarter:" << noteaux3 << hseparation0;
                    cod1 << "note.quarter:" << noteaux1 << vseparation1 << "note.quarter:" << noteaux2 << vseparation1 << "note.quarter:" << noteaux3 << hseparation1;
                    cod2 << "note.quarter:" << noteaux1 << vseparation1 << "note.quarter:" << noteaux2 << vseparation1 << "note.quarter:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.quarter:" << noteaux1 << vseparation0 << "note.quarter:" << noteaux2 << vseparation0 << "note.quarter:" << noteaux3 << hseparation1;
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation0; 
                    cod1 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation1; 
                    cod2 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation0 << "vertical.end" << hseparation0; 
                    cod3 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation1; 
                    

                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosennote = "4";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    


                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.quarter:" << noteaux1 << vseparation0 << "note.quarter:" << noteaux2 << vseparation0 << "note.quarter:" << noteaux3 << hseparation0;
                    cod1 << "note.quarter:" << noteaux1 << vseparation1 << "note.quarter:" << noteaux2 << vseparation1 << "note.quarter:" << noteaux3 << hseparation1;
                    cod2 << "note.quarter:" << noteaux1 << vseparation1 << "note.quarter:" << noteaux2 << vseparation1 << "note.quarter:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.quarter:" << noteaux1 << vseparation0 << "note.quarter:" << noteaux2 << vseparation0 << "note.quarter:" << noteaux3 << hseparation1;

                    
                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosennote = "8.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                     

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                     


                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.eighth:" << noteaux1 << vseparation0 << "note.eighth:" << noteaux2 << vseparation0 << "note.eighth:" << noteaux3 << hseparation0;
                    cod1 << "note.eighth:" << noteaux1 << vseparation1 << "note.eighth:" << noteaux2 << vseparation1 << "note.eighth:" << noteaux3 << hseparation1;
                    cod2 << "note.eighth:" << noteaux1 << vseparation1 << "note.eighth:" << noteaux2 << vseparation1 << "note.eighth:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.eighth:" << noteaux1 << vseparation0 << "note.eighth:" << noteaux2 << vseparation0 << "note.eighth:" << noteaux3 << hseparation1;
                    cod2 << "vertical.start" << hseparation0;
                    cod0 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation0; 
                    cod1 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation1; 
                    cod2 << "dot:" << dotaux1 << vseparation1 << "dot:" << dotaux2 << vseparation1 << "dot:" << dotaux3 << hseparation0 << "vertical.end" << hseparation0; 
                    cod3 << "dot:" << dotaux1 << vseparation0 << "dot:" << dotaux2 << vseparation0 << "dot:" << dotaux3 << hseparation1;

                    
                    sum+=0.75;
                }
            }else{
                if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                    choosennote = "8";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);



                    if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3!=""){
                        cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                        cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                        cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                        cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
                    }
                    if (accidental1!=""&&accidental2==""&&accidental3==""){
                        cod0 << accidental1 << hseparation0;
                        cod1 << accidental1 << hseparation1;
                        cod2 << accidental1 << hseparation0;
                        cod3 << accidental1 << hseparation1;
                    }
                    if (accidental1==""&&accidental2!=""&&accidental3==""){
                        cod0 << accidental2 << hseparation0;
                        cod1 << accidental2 << hseparation1;
                        cod2 << accidental2 << hseparation0;
                        cod3 << accidental2 << hseparation1;
                    }
                    if (accidental1==""&&accidental2==""&&accidental3!=""){
                        cod0 << accidental3 << hseparation0;
                        cod1 << accidental3 << hseparation1;
                        cod2 << accidental3 << hseparation0;
                        cod3 << accidental3 << hseparation1;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (endtie==0) cod2 << "vertical.start" << hseparation0;
                        tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                        endtie = 1;
                    } 
                    
                    if (endtie==0) cod2 << "vertical.start" << hseparation0;
                    cod0 << "note.eighth:" << noteaux1 << vseparation0 << "note.eighth:" << noteaux2 << vseparation0 << "note.eighth:" << noteaux3 << hseparation0;
                    cod1 << "note.eighth:" << noteaux1 << vseparation1 << "note.eighth:" << noteaux2 << vseparation1 << "note.eighth:" << noteaux3 << hseparation1;
                    cod2 << "note.eighth:" << noteaux1 << vseparation1 << "note.eighth:" << noteaux2 << vseparation1 << "note.eighth:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
                    cod3 << "note.eighth:" << noteaux1 << vseparation0 << "note.eighth:" << noteaux2 << vseparation0 << "note.eighth:" << noteaux3 << hseparation1;
                    
                      
                    sum+=0.5;
                }

            }
            break;
        case 4:
            //We are not going to have a dotted note sixteenth chord because we do not have thirty-second notes to complete the duration of compass just in case.        
            choosennote = "16";
                    
            CHORD = 1;    
            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
            noteaux1 = noteplace;
            chordnote = sampleint;
            finalnote = choosennote + pitch;
            accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
            finalnote += " ";


            CHORD = 2;
            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
            noteaux2 = noteplace;
            chordnote = sampleint;
            finalnote += choosennote + pitch;
            accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);
            finalnote += " ";


            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic, stemdirection);
            noteaux3 = noteplace;
            finalnote += choosennote + pitch;
            accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident);



            if (accidental1!=""&&accidental2!=""&&accidental3!=""){
                cod0 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                cod1 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                cod3 << accidental1 << vseparation0 << accidental2 << vseparation0 << accidental3 << hseparation1;
            }
            if (accidental1!=""&&accidental2!=""&&accidental3==""){
                cod0 << accidental1 << vseparation0 << accidental2 << hseparation0;
                cod1 << accidental1 << vseparation1 << accidental2 << hseparation1;
                cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental2 << hseparation0 << "vertical.end" << hseparation0;
                cod3 << accidental1 << vseparation0 << accidental2 << hseparation1;
            }
            if (accidental1!=""&&accidental2==""&&accidental3!=""){
                cod0 << accidental1 << vseparation0 << accidental3 << hseparation0;
                cod1 << accidental1 << vseparation1 << accidental3 << hseparation1;
                cod2 << "vertical.start" << hseparation0 << accidental1 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                cod3 << accidental1 << vseparation0 << accidental3 << hseparation1;
            }
            if (accidental1==""&&accidental2!=""&&accidental3!=""){
                cod0 << accidental2 << vseparation0 << accidental3 << hseparation0;
                cod1 << accidental2 << vseparation1 << accidental3 << hseparation1;
                cod2 << "vertical.start" << hseparation0 << accidental2 << vseparation1 << accidental3 << hseparation0 << "vertical.end" << hseparation0;
                cod3 << accidental2 << vseparation0 << accidental3 << hseparation1;
            }
            if (accidental1!=""&&accidental2==""&&accidental3==""){
                cod0 << accidental1 << hseparation0;
                cod1 << accidental1 << hseparation1;
                cod2 << accidental1 << hseparation0;
                cod3 << accidental1 << hseparation1;
            }
            if (accidental1==""&&accidental2!=""&&accidental3==""){
                cod0 << accidental2 << hseparation0;
                cod1 << accidental2 << hseparation1;
                cod2 << accidental2 << hseparation0;
                cod3 << accidental2 << hseparation1;
            }
            if (accidental1==""&&accidental2==""&&accidental3!=""){
                cod0 << accidental3 << hseparation0;
                cod1 << accidental3 << hseparation1;
                cod2 << accidental3 << hseparation0;
                cod3 << accidental3 << hseparation1;
            }
                    
            if (starttie==1&&TIE==0){//Force the tie to end
                cod2 << "vertical.start" << hseparation0;
                tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                endtie = 1;
            }
            if (TIE==1){ //The note is tied
                if (endtie==0) cod2 << "vertical.start" << hseparation0;
                tienote (starttie, finalnote, noteplace, TIE, cod0, cod1, cod2, cod3);
                endtie = 1;
            } 
                    
            if (endtie==0) cod2 << "vertical.start" << hseparation0;
            cod0 << "note.sixteenth:" << noteaux1 << vseparation0 << "note.sixteenth:" << noteaux2 << vseparation0 << "note.sixteenth:" << noteaux3 << hseparation0;
            cod1 << "note.sixteenth:" << noteaux1 << vseparation1 << "note.sixteenth:" << noteaux2 << vseparation1 << "note.sixteenth:" << noteaux3 << hseparation1;
            cod2 << "note.sixteenth:" << noteaux1 << vseparation1 << "note.sixteenth:" << noteaux2 << vseparation1 << "note.sixteenth:" << noteaux3 << hseparation0 << "vertical.end" << hseparation0;
            cod3 << "note.sixteenth:" << noteaux1 << vseparation0 << "note.sixteenth:" << noteaux2 << vseparation0 << "note.sixteenth:" << noteaux3 << hseparation1;
            
                    
            sum+=0.25;
            break;
    }

    choosennote.clear();
    pitch.clear();
    noteplace.clear();
    noteaux1.clear();
    noteaux2.clear();
    noteaux3.clear();
    dotplace.clear();
    dotaux1.clear();
    dotaux2.clear();
    dotaux3.clear();
    accidental1.clear();
    accidental2.clear();
    accidental3.clear();
    return finalnote;
}

