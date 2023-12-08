#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <random>

using namespace std;

string codificationh(int);
string codificationv(int);
string clef(int,int);
string keysignature(int, int [], int);
string compass (float&, int&, int&, int);
string silence(float&, int, int);
string clefG (int, string&, int&, string&);
string clefF (int, string&, int&, string&);
string clefC3 (int, string&, int&, string&);
string normaldistribution (int, float, float, string&, int&, string&, int, int, int&, int, int);
string randomwalk (int, string&, int&, string&, int&, int, int, int);
string logistic (int, string&, int&, string&, int, int, int&, int, int, int, float, float&);
string pitchgeneration (int, float, float, string&, int&, string&, int, int, int&, int, int, int, float, int, float&);
string alteration (int, int, string&, string, int, int [], int);
void tienote (int&, string&, string, int&, int);
string note(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);
string tuplet(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);
string chords(float&, int, int, int, float, float, int [], int, int&, int&, int, int, int, int, int, float, int, int&, float&, int);


int main(int argc, char** argv)
{
    srand (time(NULL)); //Initialize random seed
 
    string filename = argv[1]; //Name of the score
    filename += ".kern"; 

    ofstream file;
    file.open(filename.c_str(),ios::out); //We create the .kern file
    if(file.fail()){ //If any error happens
		cout << "The file could not be opened";
		exit(1);
	}

    int ncompasses = atoi(argv[2]); // Number of compasses that the score will have.
    
    int typeofgen = atoi(argv[3]); // Type of function to generate the pitch: (1) normal distribution , (2) random walk or (3) logistic probability
    float rlogistic;
    
    int naltered;
    int ngroup;
    int typecodification;
    if (typeofgen==3){
        rlogistic = atof(argv[4]); // r variable for the logistic function
        naltered = atoi(argv[5]); // Percentage (from 0 to 100) of a note being altered
        ngroup = atoi(argv[6]); // Percentage (from 0 to 100) of a musical unit being a chord or a tuplet
        typecodification = atoi(argv[7]); // Type of codification 
    }else{
        naltered = atoi(argv[4]); // Percentage (from 0 to 100) of a note being altered
        ngroup = atoi(argv[5]); // Percentage (from 0 to 100) of a musical unit being a chord or a tuplet
        typecodification = atoi(argv[6]); // Type of codification 
    }

    
    file << "**kern" << endl; //To initialice the .kern file
    
    int CL = rand()%3; //0-G Clef; 1-F Clef; 2-C Clef
    string choosenclef = clef(CL, typecodification);
    file << choosenclef << endl;

    int key;
    if (naltered==0){
        key = 0; //There will be no alteration for this case.
    }else{
        key = rand()%32;
    }
    int keyident[] = {0, 0, 0, 0, 0, 0, 0}; //To be able to identify a note belonging to this key signature.
    string keysign = keysignature(key, keyident, typecodification);
    file << keysign << endl;

    float compassdur;
    int N = rand()%200+1; //To decide the type of compass
    int M; //Type of compass
    string choosencompass = compass (compassdur, N, M, typecodification);
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
                choosensilence = silence(sum, M, typecodification);
            }
            file << choosensilence << endl;
            choosensilence.clear();  
        }else{
            string finalnote;
            while (finalnote.empty()){
                if (CHORNOTE < ngroup){
                    int TORC = rand()%2;
                    if (TORC==0){
                        finalnote = tuplet(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic, typecodification);
                    }else{
                        finalnote = chords(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic, typecodification);
                        CHORD = 0;
                        chordnote = 0;
                    }   
                }else{        
                    finalnote = note(sum, M, CL, naltered, mean, variance, keyident, key, TIE, starttie, BEAM, beamnote, CHORD, chordnote, typeofgen, rlogistic, counter, sampleint, xlogistic, typecodification);
                    BEAM = 0;
                    beamnote = 0; 
                }
            }
            file << finalnote << endl;
            finalnote.clear(); 
            counter = 0;           
        }
        string hseparation;
        hseparation = codificationh(typecodification);
        if (sum==compassdur){
            i = i+1;
            file << "=" << i << endl;
            cout << "verticalLine:L1"; //Bar
            
            sum=0;
            ncompasses = ncompasses-1;
            if (ncompasses!=0) cout << hseparation;
        }
    }

    file << "*-" <<endl; //End of the .kern file
    file.close(); //We close the .kern file

   return 0;
}

string codificationh(int typecodification){
    string hseparation;
    switch(typecodification){
        case 0:
        case 2:
            hseparation = " ";
            break;
        case 1:
        case 3:
            hseparation = "+";
            break;
    }
    return hseparation;
}

string codificationv(int typecodification){
    string vseparation;
    switch(typecodification){
        case 0:
        case 3:
            vseparation = "/";
            break;
        case 1:
        case 2:
            vseparation = " ";
            break;
    }
    return vseparation;
}

// Function to determine the clef //
string clef(int CL, int typecodification){
    // CL = rand()%3 meaning: 0-G Clef; 1-F Clef; 2-C3 Clef
    string choosenclef;
    string hseparation;
    hseparation = codificationh(typecodification);
    switch(CL){
        case 0:
            choosenclef = "*clefG2";
            cout << "clef.G:L2" << hseparation;
            
            break;
        case 1:
            choosenclef = "*clefF4";
            cout << "clef.F:L4" << hseparation;
            break;
        case 2:
            choosenclef = "*clefC3";
            cout << "clef.C:L3" << hseparation;
            break;
    }
    return choosenclef;
}

// Function to determine the keysignature //
string keysignature(int key, int keyident[], int typecodification){
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
    
    string keysign;
    string hseparation;
    hseparation = codificationh(typecodification);
    switch (key){
        case 0: //Do mayor, la menor -> Ninguna
        case 1: //Do mayor, la menor -> Ninguna
            keysign = "*k[]";
            break;
        case 2: //Sol mayor, mi menor -> 1 sostenido (fa)
        case 3: //Sol mayor, mi menor -> 1 sostenido (fa)
            keysign = "*k[f#]";
            keyident[0]=6;
            cout << "accidental.sharp:L5" << hseparation;
            break;
        case 4: //Re mayor, si menor -> 2 sostenidos (fa, do)
        case 5: //Re mayor, si menor -> 2 sostenidos (fa, do)
            keysign = "*k[f#c#]";
            keyident[0]=6;
            keyident[1]=3;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation;
            break;
        case 6: //La mayor, fa sostenido menor -> 3 sostenidos (fa, do, sol)
        case 7: //La mayor, fa sostenido menor -> 3 sostenidos (fa, do, sol)
            keysign = "*k[f#c#g#]";
            keyident[0]=6;
            keyident[1]=3;
            keyident[2]=7;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation << "accidental.sharp:S5" << hseparation;
            break;
        case 8: //Mi mayor, do sostenido menor -> 4 sostenidos (fa, do, sol, re)
        case 9: //Mi mayor, do sostenido menor -> 4 sostenidos (fa, do, sol, re)
            keysign = "*k[f#c#g#d#]";
            keyident[0]=6;
            keyident[1]=3;
            keyident[2]=7;
            keyident[3]=4;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation << "accidental.sharp:S5" << hseparation << "accidental.sharp:L4" << hseparation;
            break;
        case 10: //Si mayor, sol sostenido menor -> 5 sostenidos (fa, do, sol, re, la)
        case 11: //Si mayor, sol sostenido menor -> 5 sostenidos (fa, do, sol, re, la)
            keysign = "*k[f#c#g#d#a#]";
            keyident[0]=6;
            keyident[1]=3;
            keyident[2]=7;
            keyident[3]=4;
            keyident[4]=1;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation << "accidental.sharp:S5" << hseparation << "accidental.sharp:L4" << hseparation << "accidental.sharp:S2" << hseparation;
            break;
        case 12: //Fa sostenido mayor, re sostenido menor -> 6 sostenidos (fa, do, sol, re, la, mi)
        case 13: //Fa sostenido mayor, re sostenido menor->	6 sostenidos (fa, do, sol, re, la, mi)
            keysign = "*k[f#c#g#d#a#e#]";
            keyident[0]=6;
            keyident[1]=3;
            keyident[2]=7;
            keyident[3]=4;
            keyident[4]=1;
            keyident[5]=5;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation << "accidental.sharp:S5" << hseparation << "accidental.sharp:L4" << hseparation << "accidental.sharp:S2" << hseparation << "accidental.sharp:S4" << hseparation;
            break;
        case 14: //Do sostenido mayor, la sostenido menor -> 7 sostenidos (fa, do, sol, re, la, mi, si)
        case 15: //Do sostenido mayor, la sostenido menor -> 7 sostenidos (fa, do, sol, re, la, mi, si)
            keysign = "*k[f#c#g#d#a#e#b#]";
            keyident[0]=6;
            keyident[1]=3;
            keyident[2]=7;
            keyident[3]=4;
            keyident[4]=1;
            keyident[5]=5;
            keyident[6]=2;
            cout << "accidental.sharp:L5" << hseparation << "accidental.sharp:S3" << hseparation << "accidental.sharp:S5" << hseparation << "accidental.sharp:L4" << hseparation << "accidental.sharp:S2" << hseparation << "accidental.sharp:S4" << hseparation << "accidental.sharp:L3" << hseparation;
            break;
        case 16: //Fa mayor, re menor -> 1 bemol (si)
        case 17: //Fa mayor, re menor -> 1 bemol (si)
            keysign = "*k[b-]";
            keyident[0]=2;
            cout << "accidental.flat:L3" << hseparation;
            break;
        case 18: //Si bemol mayor, sol menor -> 2 bemoles (si, mi)
        case 19: //Si bemol mayor, sol menor -> 2 bemoles (si, mi)
            keysign = "*k[b-e-]";
            keyident[0]=2;
            keyident[1]=5;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation;
            break;
        case 20: //Mi bemol mayor, do menor -> 3 bemoles (si, mi, la)
        case 21: //Mi bemol mayor, do menor -> 3 bemoles (si, mi, la)
            keysign = "*k[b-e-a-]";
            keyident[0]=2;
            keyident[1]=5;
            keyident[2]=1;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation << "accidental.flat:S2" << hseparation;
            break;
        case 22: //La bemol mayor, fa menor -> 4 bemoles (si, mi, la, re)
        case 23: //La bemol mayor, fa menor -> 4 bemoles (si, mi, la, re)
            keysign = "*k[b-e-a-d-]";
            keyident[0]=2;
            keyident[1]=5;
            keyident[2]=1;
            keyident[3]=4;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation << "accidental.flat:S2" << hseparation << "accidental.flat:L4" << hseparation;
            break;
        case 24: //Re bemol mayor, si bemol menor -> 5 bemoles (si, mi, la, re, sol)
        case 25: //Re bemol mayor, si bemol menor -> 5 bemoles (si, mi, la, re, sol)
            keysign = "*k[b-e-a-d-g-]";
            keyident[0]=2;
            keyident[1]=5;
            keyident[2]=1;
            keyident[3]=4;
            keyident[4]=7;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation << "accidental.flat:S2" << hseparation << "accidental.flat:L4" << hseparation << "accidental.flat:L2" << hseparation;
            break;
        case 26: //Sol bemol mayor, mi bemol menor	-> 6 bemoles (si, mi, la, re, sol, do)
        case 27: //Sol bemol mayor, mi bemol menor	-> 6 bemoles (si, mi, la, re, sol, do)
            keysign = "*k[b-e-a-d-g-c-]";
            keyident[0]=2;
            keyident[1]=5;
            keyident[2]=1;
            keyident[3]=4;
            keyident[4]=7;
            keyident[5]=3;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation << "accidental.flat:S2" << hseparation << "accidental.flat:L4" << hseparation << "accidental.flat:L2" << hseparation << "accidental.flat:S3" << hseparation;
            break;
        case 28: //Do bemol mayor, la bemol menor -> 7 bemoles (si, mi, la, re, sol, do, fa)
        case 29: //Do bemol mayor, la bemol menor -> 7 bemoles (si, mi, la, re, sol, do, fa)
            keysign = "*k[b-e-a-d-g-c-f-]";
            keyident[0]=2;
            keyident[1]=5;
            keyident[2]=1;
            keyident[3]=4;
            keyident[4]=7;
            keyident[5]=3;
            keyident[6]=6;
            cout << "accidental.flat:L3" << hseparation << "accidental.flat:S4" << hseparation << "accidental.flat:S2" << hseparation << "accidental.flat:L4" << hseparation << "accidental.flat:L2" << hseparation << "accidental.flat:S3" << hseparation << "accidental.flat:S1" << hseparation;
            break;
        case 30: //Sin alteraciones
        case 31: //Sin alteraciones
            keysign = "*k[]";
            break;  
    }  
     
    return keysign;
}

// Function to determine compass (metric) //
string compass (float &compassdur, int &N, int &M, int typecodification){
    string choosencompass;
    string hseparation;
    string vseparation;
    hseparation = codificationh(typecodification);
    vseparation = codificationv(typecodification);
    if (N < 101){ //50% of chance of for this compass
            compassdur = 4;
            M = 1;
            int met = rand()%2;
            if (met==1){ //50% of chance of using this notation
                choosencompass = "*M4/4";
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << "digit.4:L2" << vseparation << "digit.4:L4" << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }else{      //50% of chance of using this other notation
                choosencompass = "*M4/4\n*met(c)";
                cout << "metersign.C:L3" << hseparation;
            }            
    }else{
        if (N < 151){ //25% of chance of for this compass
            compassdur = 3;
            M = 3;
            choosencompass = "*M3/4";
            if (typecodification==2) cout << "vertical.start" << hseparation;
            cout << "digit.4:L2" << vseparation << "digit.3:L4" << hseparation;
            if (typecodification==2) cout << "vertical.end" << hseparation;
        }else{
            if (N < 175){ //12% of chance of for this compass
                compassdur = 4;
                M = 2;
                int met = rand()%2;
                if (met==1){ //50% of chance of using this notation
                    choosencompass = "*M2/2";
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "digit.2:L2" << vseparation << "digit.2:L4" << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                }else{      //50% of chance of using this other notation
                    choosencompass = "*M2/2\n*met(c|)";
                    cout << "metersign.Ccut:L3" << hseparation;
                }
                
            }else{
                if (N < 185){ //5% of chance of for this compass
                    compassdur = 2;
                    M = 4;
                    choosencompass = "*M2/4";
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "digit.4:L2" << vseparation << "digit.2:L4" << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                }else{
                    switch(N){
                        case 185: //2% of chance of for this compass   
                        case 186:   
                        case 187:
                        case 188: 
                            compassdur = 3;
                            M = 5;
                            choosencompass = "*M6/8";
                            if (typecodification==2) cout << "vertical.start" << hseparation;
                            cout << "digit.8:L2" << vseparation << "digit.6:L4" << hseparation;
                            if (typecodification==2) cout << "vertical.end" << hseparation;
                            break;
                        case 189: //2% of chance of for this compass  
                        case 190:   
                        case 191:
                        case 192:
                            compassdur = 6;
                            M = 6;
                            choosencompass = "*M12/8";
                            if (typecodification==2) cout << "vertical.start" << hseparation;
                            cout << "digit.8:L2" << vseparation << "digit.12:L4" << hseparation;
                            if (typecodification==2) cout << "vertical.end" << hseparation;
                            break;
                        case 193: //2% of chance of for this compass
                        case 194:   
                        case 195:
                        case 196:
                            compassdur = 4.5;
                            M = 7;
                            choosencompass = "*M9/8";
                            if (typecodification==2) cout << "vertical.start" << hseparation;
                            cout << "digit.8:L2" << vseparation << "digit.9:L4" << hseparation;
                            if (typecodification==2) cout << "vertical.end" << hseparation;
                            break;
                        case 197: //2% of chance of for this compass
                        case 198:   
                        case 199:
                        case 200:
                            compassdur = 5;
                            M = 8;
                            choosencompass = "*M5/4";
                            if (typecodification==2) cout << "vertical.start" << hseparation;
                            cout << "digit.4:L2" << vseparation << "digit.5:L4" << hseparation;
                            if (typecodification==2) cout << "vertical.end" << hseparation;
                            break;
                    }
                }
            }
        }

    }
      
    return choosencompass;
}

// Function to determine the type of silence //
string silence(float &sum, int M, int typecodification){
    string choosensilence;
    string hseparation;
    hseparation = codificationh(typecodification);
    int TS = rand()%5; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth;
    int DOT = rand()%20; //To decide if it's going to be dotted or not
    switch(TS){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosensilence = "1.r";
                    cout << "rest.whole:L4" << hseparation << "dot:S3" << hseparation;
                    sum+=6;
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosensilence = "1r";
                    cout << "rest.whole:L4" << hseparation;
                    sum+=4;
                }
            }
            break;
        case 1:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosensilence = "2.r";
                    cout << "rest.half:L3" << hseparation << "dot:S3" << hseparation;
                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosensilence = "2r";
                    cout << "rest.half:L3" << hseparation;
                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosensilence = "4.r";
                    cout << "rest.quarter:L3" << hseparation << "dot:S3" << hseparation;
                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosensilence = "4r";
                    cout << "rest.quarter:L3" << hseparation;
                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosensilence = "8.r";
                    cout << "rest.eighth:L3" << hseparation << "dot:S3" << hseparation;
                    sum+=0.75;
                }
            }else{
                if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                    choosensilence = "8r";
                    cout << "rest.eighth:L3" << hseparation;
                    sum+=0.5;
                }
            }
            break;
        case 4:
            //We are not going to have a dotted rest sixteenth because we do not have thirty-second notes to complete the duration of compass just in case.
            choosensilence = "16r";
            cout << "rest.sixteenth:L3" << hseparation;
            sum+=0.25;
        break;
    }

    return choosensilence;
}

// Template for pitches in clef G //
string clefG (int sampleint, string &noteplace, int &noteident, string &dotplace){
    string pitch;
    switch (sampleint){
        case 0:
            pitch = "G";
            noteplace = "S-2";
            dotplace = "S-2";
            noteident = 7;
            break;
        case 1:
            pitch = "A";
            noteplace = "L-1";
            dotplace = "S-1";
            noteident = 1;
            break;
        case 2:
            pitch = "B";
            noteplace = "S-1";
            dotplace = "S-1"; 
            noteident = 2;           
            break;
        case 3:
            pitch = "c";
            noteplace = "L0";
            dotplace = "S0";
            noteident = 3;
            break;
        case 4:
            pitch = "d";
            noteplace = "S0";
            dotplace = "S0";
            noteident = 4;
            break;
        case 5:
            pitch = "e";
            noteplace = "L1";
            dotplace = "S1";
            noteident = 5;
            break;
        case 6:
            pitch = "f";
            noteplace = "S1";
            dotplace = "S1";
            noteident = 6;
            break;
        case 7:
            pitch = "g";
            noteplace = "L2";
            dotplace = "S2";
            noteident = 7;
            break;
        case 8:
            pitch = "a";
            noteplace = "S2";
            dotplace = "S2";
            noteident = 1;
            break;
        case 9:
            pitch = "b";
            noteplace = "L3";
            dotplace = "S3";
            noteident = 2;
            break;
        case 10:
            pitch = "cc";
            noteplace = "S3";
            dotplace = "S3";
            noteident = 3;
            break;
        case 11:
            pitch = "dd";
            noteplace = "L4";
            dotplace = "S4";
            noteident = 4;
            break;
        case 12:
            pitch = "ee";
            noteplace = "S4";
            dotplace = "S4";
            noteident = 5;
            break;
        case 13:
            pitch = "ff";
            noteplace = "L5";
            dotplace = "S5";
            noteident = 6;
            break;
        case 14:
            pitch = "gg";
            noteplace = "S5";
            dotplace = "S5";
            noteident = 7;
            break;
        case 15:
            pitch = "aa";
            noteplace = "L6";
            dotplace = "S6";
            noteident = 1;
            break;
        case 16:
            pitch = "bb";
            noteplace = "S6";
            dotplace = "S6";
            noteident = 2;
            break;
        case 17:
            pitch = "ccc";
            noteplace = "L7";
            dotplace = "S7";
            noteident = 3;
            break;
    }

    return pitch;
}

// Template for pitches in clef F //
string clefF (int sampleint, string &noteplace, int &noteident, string &dotplace){
    string pitch;
    switch (sampleint){
        case 0:
            pitch = "BBB";
            noteplace = "S-2";
            dotplace = "S-2";
            noteident = 2;
            break;
        case 1:
            pitch = "CC";
            noteplace = "L-1";
            dotplace = "S-1";
            noteident = 3;
            break;
        case 2:
            pitch = "DD";
            noteplace = "S-1";
            dotplace = "S-1";
            noteident = 4;
            break;
        case 3:
            pitch = "EE";
            noteplace = "L0";
            dotplace = "S0";
            noteident = 5;
            break;
        case 4:
            pitch = "FF";
            noteplace = "S0";
            dotplace = "S0";
            noteident = 6;
            break;
        case 5:
            pitch = "GG";
            noteplace = "L1";
            dotplace = "S1";
            noteident = 7;
            break;
        case 6:
            pitch = "AA";
            noteplace = "S1";
            dotplace = "S1";
            noteident = 1;
            break;
        case 7:
            pitch = "BB";
            noteplace = "L2";
            dotplace = "S2";
            noteident = 2;
            break;
        case 8:
            pitch = "C";
            noteplace = "S2";
            dotplace = "S2";
            noteident = 3;
            break;
        case 9:
            pitch = "D";
            noteplace = "L3";
            dotplace = "S3";
            noteident = 4;
            break;
        case 10:
            pitch = "E";
            noteplace = "S3";
            dotplace = "S3";
            noteident = 5;
            break;
        case 11:
            pitch = "F";
            noteplace = "L4";
            dotplace = "S4";
            noteident = 6;
            break;
        case 12:
            pitch = "G";
            noteplace = "S4";
            dotplace = "S4";
            noteident = 7;
            break;
        case 13:
            pitch = "A";
            noteplace = "L5";
            dotplace = "S5";
            noteident = 1;
            break;
        case 14:
            pitch = "B";
            noteplace = "S5";
            dotplace = "S5";
            noteident = 2;
            break;
        case 15:
            pitch = "c";
            noteplace = "L6";
            dotplace = "S6";
            noteident = 3;
            break;
        case 16:
            pitch = "d";
            noteplace = "S6";
            dotplace = "S6";
            noteident = 4;
            break;
        case 17:
            pitch = "e";
            noteplace = "L7";
            dotplace = "S7";
            noteident = 5;
            break;
    }

    return pitch;
}

// Template for pitches in clef C3 //
string clefC3 (int sampleint, string &noteplace, int &noteident, string &dotplace){
    string pitch;
    switch (sampleint){
        case 0:
            pitch = "AA";
            noteplace = "S-2";
            dotplace = "S-2";
            noteident = 1;
            break;
        case 1:
            pitch = "BB";
            noteplace = "L-1";
            dotplace = "S-1";
            noteident = 2;
            break;
        case 2:
            pitch = "C";
            noteplace = "S-1";
            dotplace = "S-1";
            noteident = 3;
            break;
        case 3:
            pitch = "D";
            noteplace = "L0";
            dotplace = "S0";
            noteident = 4;
            break;
        case 4:
            pitch = "E";
            noteplace = "S0";
            dotplace = "S0";
            noteident = 5;
            break;
        case 5:
            pitch = "F";
            noteplace = "L1";
            dotplace = "S1";
            noteident = 6;
            break;
        case 6:
            pitch = "G";
            noteplace = "S1";
            dotplace = "S1";
            noteident = 7;
            break;
        case 7:
            pitch = "A";
            noteplace = "L2";
            dotplace = "S2";
            noteident = 1;
            break;
        case 8:
            pitch = "B";
            noteplace = "S2";
            dotplace = "S2";
            noteident = 2;
            break;
        case 9:
            pitch = "c";
            noteplace = "L3";
            dotplace = "S3";
            noteident = 3;
            break;
        case 10:
            pitch = "d";
            noteplace = "S3";
            dotplace = "S3";
            noteident = 4;
            break;
        case 11:
            pitch = "e";
            noteplace = "L4";
            dotplace = "S4";
            noteident = 5;
            break;
        case 12:
            pitch = "f";
            noteplace = "S4";
            dotplace = "S4";
            noteident = 6;
            break;
        case 13:
            pitch = "g";
            noteplace = "L5";
            dotplace = "S5";
            noteident = 7;
            break;
        case 14:
            pitch = "a";
            noteplace = "S5";
            dotplace = "S5";
            noteident = 1;
            break;
        case 15:
            pitch = "b";
            noteplace = "L6";
            dotplace = "S6";
            noteident = 2;
            break;
        case 16:
            pitch = "cc";
            noteplace = "S6";
            dotplace = "S6";
            noteident = 3;
            break;
        case 17:
            pitch = "dd";
            noteplace = "L7";
            dotplace = "S7";
            noteident = 4;
            break;
    }

    return pitch;
}

// Function that chooses the pitch of a note based on a normal distribution //
string normaldistribution (int CL, float mean, float variance, string &noteplace, int &noteident,  string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote){
    float sample;
    string pitch;
    
    //Random device class instance, source of 'true' randomness for initializing random seed
    std::random_device rd; 

    //Mersenne twister PRNG, initialized with seed from previous random device instance
    std::mt19937 gen(rd()); 

    //Instance of class std::normal_distribution with specific mean and stddev
    std::normal_distribution<float> d(mean, variance); 

    //Get random number with normal distribution using gen as random source
    sample = d(gen);
    sampleint = static_cast<int>(sample+0.5);
    if (sampleint>17){
        sampleint = 17;
    }


    if (BEAM == 1){
        int nextbeam = rand()%1;
        if (beamnote<9){
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


    switch (CL){
        case 0:
            pitch = clefG(sampleint, noteplace, noteident, dotplace);
            break;
        case 1:
            pitch = clefF(sampleint, noteplace, noteident, dotplace);
            break;
        case 2:
            pitch = clefC3(sampleint, noteplace, noteident, dotplace);
            break;
    }

    return pitch;
}


// Function that chooses the pitch of a note based on "random walk" //
string randomwalk (int CL, string &noteplace, int &noteident,  string &dotplace, int &sampleint, int CHORD, int chordnote, int counter){  
    string pitch;
    int rw = rand()%3; //0 (minus 1),; 1 (stays the same); 2 (plus 1)
    int limit = rand()%2; //0 - Absorbent limit ; 1 - Reflective limit

    if (counter==1){
        sampleint = 8;
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
            if (sampleint>17){ 
                if (limit==0){
                    sampleint = 17; //Absorbent limit
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


    switch (CL){
        case 0:
            pitch = clefG(sampleint, noteplace, noteident, dotplace);
            break;
        case 1:
            pitch = clefF(sampleint, noteplace, noteident, dotplace);
            break;
        case 2:
            pitch = clefC3(sampleint, noteplace, noteident, dotplace);
            break;
    }

    return pitch;
}


// Function that chooses the pitch of a note based on a logistic probability//
string logistic (int CL, string &noteplace, int &noteident,  string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote, int counter, float rlogistic, float &xlogistic){
    string pitch;
    
    if (counter==1){
        sampleint = 8;
        xlogistic = 0.5; 
    }else{
        xlogistic = rlogistic*xlogistic*(1-xlogistic); //Always between 0 and 1.
        sampleint = (static_cast<int>(xlogistic+0.5))*17;
        if (sampleint<4){ //We limit to notes appearing in the staff. Because of the jumps.
            sampleint = 4;
        }
        if (sampleint>14){
            sampleint = 14;
        }
    }
    
    if (BEAM == 1){
        int nextbeam = rand()%1;
        if (beamnote<9){
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

    switch (CL){
        case 0:
            pitch = clefG(sampleint, noteplace, noteident, dotplace);
            break;
        case 1:
            pitch = clefF(sampleint, noteplace, noteident, dotplace);
            break;
        case 2:
            pitch = clefC3(sampleint, noteplace, noteident, dotplace);
            break;
    }

    return pitch;
}


// Function to determine which method of pitch generation is choosen //
string pitchgeneration (int CL, float mean, float variance, string &noteplace, int &noteident,  string &dotplace, int BEAM, int beamnote, int &sampleint, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, float &xlogistic){
    string pitch;
    switch(typeofgen){
        case 1:
            pitch = normaldistribution (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote);
            break;
        case 2:
            pitch = randomwalk (CL, noteplace, noteident, dotplace, sampleint, CHORD, chordnote, counter);
            break;
        case 3:
            pitch = logistic (CL, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, counter, rlogistic, xlogistic);
            break;
    }
    return pitch;
}


// Function to determine the alteration of a note //
string alteration (int naltered, int key, string &finalnote, string noteplace, int noteident, int keyident[],int typecodification){
    string accidental;

    int AL = rand()%101; //From 0 to 100: to decide the alteration of the note
    int TAL = rand()%2; //0-Sharp; 1-Flat
    int CAL = 0;
    
    for(int i=0; i<7; i++){
        if(noteident==keyident[i]){
            if(key>1&&key<16){ //Sharp alteracion in key signature
                if (AL < naltered){
                    finalnote += "#";
                    accidental = "";
                    CAL = 1; 
                }else{ 
                    finalnote += "n";
                    accidental = "accidental.natural:" + noteplace; 
                    CAL = 1;
                }
            }else{
                if(key>15&&key<30){ //Flat alteracion in key signature
                    if (AL < naltered){  
                        finalnote += "-";
                        accidental = ""; 
                        CAL =1 ;  
                    }else{ 
                        finalnote += "n";
                        accidental = "accidental.natural:" + noteplace; 
                        CAL = 1;
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
                accidental = "accidental.sharp:" + noteplace; 
            }else{
                finalnote += "-";
                accidental = "accidental.flat:" + noteplace;
            }
        }
    }
     
    return accidental;   
}


// Function to tie a note //
void tienote (int &starttie, string &finalnote, string noteplace, int &TIE, int typecodification){
    int end = 0;
    
    string vseparation;
    vseparation = codificationv(typecodification);

    int conttie = rand()%10;
    if (starttie==0&&TIE==1){
        finalnote = "(" + finalnote; //Start of the tie/slur
        cout << "slur.start:" << noteplace << vseparation;
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
        cout << "slur.end:" << noteplace << vseparation;
        starttie = 0;
        TIE = rand()%10;
    }
    return;
}

// Function to determine a note //
string note(float &sum, int M, int CL, int naltered, float mean, float variance, int keyident[], int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic, int typecodification){
    string choosennote;
    string pitch;
    string finalnote;
    string noteplace;
    string dotplace;
    string accidental;
    string hseparation;
    string vseparation;
    hseparation = codificationh(typecodification);
    vseparation = codificationv(typecodification);
    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%8; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth; 5-Two beamed 8th; 6-Two beamed 16th; 7-Four beamed 16th
    int DOT = rand()%20; //To decide if it's going to be dotted or not

   
    switch(TN){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosennote = "1.";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    cout << "note.whole:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    cout << "dot:" << dotplace << hseparation; 

                    sum+=6; 
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosennote = "1";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }

                    cout << "note.whole:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                     
                    sum+=4; 
                }
            }
            break;
        case 1:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosennote = "2.";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    cout << "note.half:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    cout << "dot:" << dotplace << hseparation;

                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosennote = "2";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }

                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    cout << "note.half:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;

                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosennote = "4.";
                   
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    cout << "note.quarter:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    cout << "dot:" << dotplace << hseparation;

                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosennote = "4";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    
                    cout << "note.quarter:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;

                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosennote = "8.";
                     
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 

                    cout << "note.eighth:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    cout << "dot:" << dotplace << hseparation;

                    sum+=0.75;
                }
            }else{
                if(((M==5||M==6||M==7)&&(sum==1||sum==2.5))||((M==6||M==7)&&sum==4)||(M==6&&sum==5.5)||((M==1||M==3||M==4||M==8)&&(sum==0.5||sum==1.5))||((M==1||M==3||M==8)&&sum==2.5)||((M==1||M==8)&&sum==3.5)||(M==8&&sum==4.5)){
                    choosennote = "8";
                    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    finalnote = choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;

                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }

                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }

                    cout << "note.eighth:" << noteplace << hseparation;
                    if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    
                    sum+=0.5;
                }
            }
            break;
        case 4:
            if(((M==5||M==6||M==7)&&(sum==1.25||sum==2.75))||((M==6||M==7)&&sum==4.25)||(M==6&&sum==5.75)||((M==1||M==3||M==4||M==8)&&(sum==0.75||sum==1.75))||((M==1||M==3||M==8)&&sum==2.75)||((M==1||M==8)&&sum==3.75)||(M==8&&sum==4.75)){
                //We are not going to have a dotted note sixteenth because we do not have thirty-second notes to complete the duration of compass just in case.
                choosennote = "16";

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;

                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                if (TIE==1){ //The note is tied
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                cout << "note.sixteenth:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
            
                sum+=0.25;
            }
            break;
        case 5:
            if(((M==1||M==3||M==4||M==8)&&(sum==0||sum==1))||((M==1||M==3||M==8)&&sum==2)||((M==1||M==8)&&sum==3)||(M==8&&sum==4)){
                choosennote = "8";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;
                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cout << "note.beamedRight1:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;


                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                finalnote += choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;
                finalnote += "J";
                if (TIE==1){ //The note is tied
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }
                cout << "note.beamedLeft1:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                      
                sum+=1;
            }
            break;
        case 6:
            if(((M==5||M==6||M==7)&&(sum==0||sum==1.5))||((M==6||M==7)&&sum==3)||(M==6&&sum==4.5)){
                choosennote = "16";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;
                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cout << "note.beamedRight2:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                finalnote += choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;
                finalnote += "J";
                if (TIE==1){ //The note is tied
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }
                cout << "note.beamedLeft2:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
                    
                sum+=0.5;
            }
            break;    
        case 7:
            if(((M==1||M==3||M==4||M==8)&&(sum==0||sum==1))||((M==1||M==3||M==8)&&sum==2)||((M==1||M==8)&&sum==3)||(M==8&&sum==4)){
                choosennote = "16";
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;
                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }
                finalnote = finalnote + "L" + "\n";
                cout << "note.beamedRight2:" << noteplace << hseparation;
                if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;

                for(int b=0; b<3; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;
                    if (b==0||b==1){
                        finalnote += "\n";
                        cout << "note.beamedBoth2:" << noteplace << hseparation;
                    }else{
                        finalnote += "J";
                        if (TIE==1){ //The note is tied
                            if (typecodification==2) cout << "vertical.start" << hseparation;
                            tienote (starttie, finalnote, noteplace, TIE, typecodification);
                            endtie = 1;
                        }
                        cout << "note.beamedLeft2:" << noteplace << hseparation;
                        if (typecodification==2&&endtie==1) cout << "vertical.end" << hseparation;
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


// Function to determine a tuplet. They are not going to be dotted. They cannot start a tie.//
string tuplet(float &sum, int M, int CL, int naltered, float mean, float variance, int keyident[], int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic, int typecodification){
    string choosennote;
    string pitch;
    string finalnote;
    string noteplace;
    string dotplace;
    string accidental;
    string hseparation;
    string vseparation;
    hseparation = codificationh(typecodification);
    vseparation = codificationv(typecodification);
    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%4; //0-Half; 1-Quarter; 2-Eighth; 3-Sixteenth

   
    switch(TN){
        case 0:
            if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                choosennote = "3";
                
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;

                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                finalnote = finalnote + "\n";
                if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                cout << "note.half:" << noteplace << vseparation;
                cout << "bracket.start:S6" << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;


                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;
                    if (b==0){
                        finalnote += "\n";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.half:" << noteplace << vseparation;
                        cout << "digit3:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }else{
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.half:" << noteplace << vseparation;
                        cout << "bracket.end:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }                    
                }
                    
                sum+=4;
            }
            break;
        case 1:
            if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                choosennote = "6";

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;

                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                finalnote = finalnote + "\n";
                if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                cout << "note.quarter:" << noteplace << vseparation;
                cout << "bracket.start:S6" << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;

                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;
                    if (b==0){
                        finalnote += "\n";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.quarter:" << noteplace << vseparation;
                        cout << "digit3:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }else{
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.quarter:" << noteplace << vseparation;
                        cout << "bracket.end:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }                    
                }
     
                sum+=2;
            }
            break;
        case 2:
            if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                choosennote = "12"; 
                    
                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;

                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                finalnote = finalnote + "L" + "\n";
                if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                cout << "note.eighth:" << noteplace << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;

                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;
                    if (b==0){
                        finalnote += "\n";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.eighth:" << noteplace << vseparation;
                        cout << "digit3:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }else{
                        finalnote += "J";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.eighth:" << noteplace << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }                    
                }
                    
                sum+=1;
            }
            break;
        case 3:
            if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                choosennote = "24";

                pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                beamnote = sampleint;
                BEAM = 1;
                finalnote = choosennote + pitch;
                accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                if(accidental!="") cout << accidental << hseparation;

                if (starttie==1&&TIE==0){//Force the tie to end
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    tienote (starttie, finalnote, noteplace, TIE, typecodification);
                    endtie = 1;
                }

                finalnote = finalnote + "L" + "\n";
                if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                cout << "note.sixteenth:" << noteplace << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;

                for(int b=0; b<2; b++){
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    beamnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    if(accidental!="") cout << accidental << hseparation;
                    if (b==0){
                        finalnote += "\n";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.sixteenth:" << noteplace << vseparation;
                        cout << "digit3:S6" << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }else{
                        finalnote += "J";
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << "note.sixteenth:" << noteplace << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }                    
                }

                sum+=0.5;
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

// Function to code chords //
string chords(float &sum, int M, int CL, int naltered, float mean, float variance, int keyident[], int key, int &TIE, int &starttie, int BEAM, int beamnote, int CHORD, int chordnote, int typeofgen, float rlogistic, int counter, int &sampleint, float &xlogistic, int typecodification){
    string choosennote;
    string pitch;
    string finalnote;
    string noteplace;
    string noteaux1;
    string noteaux2;
    string noteaux3;
    string dotplace;
    string dotaux1;
    string dotaux2;
    string dotaux3;
    string accidental1;
    string accidental2;
    string accidental3;
    string hseparation;
    string vseparation;
    hseparation = codificationh(typecodification);
    vseparation = codificationv(typecodification);

    int endtie = 0; 
    int noteident; //To identify the pitch of a note
    int TN = rand()%5; //0-Whole; 1-Half; 2-Quarter; 3-Eighth; 4-Sixteenth
    int DOT = rand()%20; //To decide if it's going to be dotted or not
   

    switch(TN){
        case 0:
            if (DOT==10){ //There is only a 5% chance of this happening: DOTTED.
                if(M==6&&sum==0){
                    choosennote = "1.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    

                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.whole:" << noteaux3 << vseparation << "note.whole:" << noteaux2 << vseparation << "note.whole:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "dot:" << dotaux3 << vseparation << "dot:" << dotaux2 << vseparation << "dot:" << dotaux1 << hseparation; 
                    if (typecodification==2) cout << "vertical.end" << hseparation;

                    
                    sum+=6;
                }
            }else{
                if((M==1&&sum==0)||(M==2&&sum==0)||(M==6&&sum<=2)||(M==7&&sum<=0.5)||(M==8&&sum<=1)){
                    choosennote = "1";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";


                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    

                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.whole:" << noteaux3 << vseparation << "note.whole:" << noteaux2 << vseparation << "note.whole:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    
                    
                    sum+=4;
                }

            }
            break;
        case 1:
            if (DOT==10){
                if((M==1&&sum<=1)||(M==2&&sum<=1)||(M==3&&sum==0)||(M==5&&sum==0)||(M==6&&sum<=3)||(M==7&&sum<=1.5)||(M==8&&sum<=2)){
                    choosennote = "2.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
            

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);


                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.half:" << noteaux3 << vseparation << "note.half:" << noteaux2 << vseparation << "note.half:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "dot:" << dotaux3 << vseparation << "dot:" << dotaux2 << vseparation << "dot:" << dotaux1 << hseparation; 
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    
                    
                    sum+=3;
                }
            }else{
                if((M==1&&sum<=2)||(M==2&&sum<=2)||(M==3&&sum<=1)||(M==4&&sum==0)||(M==5&&sum<=1)||(M==6&&sum<=4)||(M==7&&sum<=2.5)||(M==8&&sum<=3)){
                    choosennote = "2";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);


                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.half:" << noteaux3 << vseparation << "note.half:" << noteaux2 << vseparation << "note.half:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    
                    
                    sum+=2;
                }
            }
            break;
        case 2:
            if (DOT==10){
                if((M==1&&sum<=2.5)||(M==2&&sum<=2.5)||(M==3&&sum<=1.5)||(M==4&&sum<=0.5)||(M==5&&sum<=1.5)||(M==6&&sum<=4.5)||(M==7&&sum<=3)||(M==8&&sum<=3.5)){
                    choosennote = "4.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    

                    
                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.quarter:" << noteaux3 << vseparation << "note.quarter:" << noteaux2 << vseparation << "note.quarter:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "dot:" << dotaux3 << vseparation << "dot:" << dotaux2 << vseparation << "dot:" << dotaux1 << hseparation; 
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    

                    sum+=1.5;
                }
            }else{
                if((M==1&&sum<=3)||(M==2&&sum<=3)||(M==3&&sum<=2)||(M==4&&sum<=1)||(M==5&&sum<=2)||(M==6&&sum<=5)||(M==7&&sum<=3.5)||(M==8&&sum<=4)){
                    choosennote = "4";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    


                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.quarter:" << noteaux3 << vseparation << "note.quarter:" << noteaux2 << vseparation << "note.quarter:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;

                    
                    sum+=1;
                }
            }
            break;
        case 3:
            if (DOT==10){
                if((M==1&&sum<=3.25)||(M==2&&sum<=3.25)||(M==3&&sum<=2.25)||(M==4&&sum<=1.25)||(M==5&&sum<=2.25)||(M==6&&sum<=5.25)||(M==7&&sum<=3.75)||(M==8&&sum<=4.25)){
                    choosennote = "8.";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    dotaux1 = dotplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                     

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    dotaux2 = dotplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    dotaux3 = dotplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                     


                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.eighth:" << noteaux3 << vseparation << "note.eighth:" << noteaux2 << vseparation << "note.eighth:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    if (typecodification==2) cout << "vertical.start" << hseparation;
                    cout << "dot:" << dotaux3 << vseparation << "dot:" << dotaux2 << vseparation << "dot:" << dotaux1 << hseparation; 
                    if (typecodification==2) cout << "vertical.end" << hseparation;

                    
                    sum+=0.75;
                }
            }else{
                if((M==1&&sum<=3.5)||(M==2&&sum<=3.5)||(M==3&&sum<=2.5)||(M==4&&sum<=1.5)||(M==5&&sum<=2.5)||(M==6&&sum<=5.5)||(M==7&&sum<=4)||(M==8&&sum<=4.5)){
                    choosennote = "8";
                    
                    CHORD = 1;    
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux1 = noteplace;
                    chordnote = sampleint;
                    finalnote = choosennote + pitch;
                    accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    CHORD = 2;
                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux2 = noteplace;
                    chordnote = sampleint;
                    finalnote += choosennote + pitch;
                    accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
                    finalnote += " ";
                    

                    pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
                    noteaux3 = noteplace;
                    finalnote += choosennote + pitch;
                    accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);



                    if (accidental1!=""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << vseparation<< accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << vseparation << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1!=""&&accidental2==""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental1 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2!=""&accidental3==""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental2 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    if (accidental1==""&&accidental2==""&accidental3!=""){
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        cout << accidental3 << hseparation;
                        if (typecodification==2) cout << "vertical.end" << hseparation;
                    }
                    
                    if (starttie==1&&TIE==0){//Force the tie to end
                        if (typecodification==2) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    }
                    if (TIE==1){ //The note is tied
                        if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                        tienote (starttie, finalnote, noteplace, TIE, typecodification);
                        endtie = 1;
                    } 
                    
                    if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                    cout << "note.eighth:" << noteaux3 << vseparation << "note.eighth:" << noteaux2 << vseparation << "note.eighth:" << noteaux1 << hseparation;
                    if (typecodification==2) cout << "vertical.end" << hseparation;
                    
                      
                    sum+=0.5;
                }

            }
            break;
        case 4:
            //We are not going to have a dotted note sixteenth chord because we do not have thirty-second notes to complete the duration of compass just in case.        
            choosennote = "16";
                    
            CHORD = 1;    
            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
            noteaux1 = noteplace;
            chordnote = sampleint;
            finalnote = choosennote + pitch;
            accidental1 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
            finalnote += " ";


            CHORD = 2;
            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
            noteaux2 = noteplace;
            chordnote = sampleint;
            finalnote += choosennote + pitch;
            accidental2 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);
            finalnote += " ";


            pitch = pitchgeneration (CL, mean, variance, noteplace, noteident, dotplace, BEAM, beamnote, sampleint, CHORD, chordnote, typeofgen, rlogistic, counter, xlogistic);
            noteaux3 = noteplace;
            finalnote += choosennote + pitch;
            accidental3 = alteration (naltered, key, finalnote, noteplace, noteident, keyident, typecodification);



            if (accidental1!=""&&accidental2!=""&accidental3!=""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental3 << vseparation <<accidental2 << vseparation << accidental1 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1!=""&&accidental2!=""&accidental3==""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental2 << vseparation<< accidental1 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1!=""&&accidental2==""&accidental3!=""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental3 << vseparation << accidental1 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1==""&&accidental2!=""&accidental3!=""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental3 << vseparation << accidental2 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1!=""&&accidental2==""&accidental3==""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental1 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1==""&&accidental2!=""&accidental3==""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental2 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
            if (accidental1==""&&accidental2==""&accidental3!=""){
                if (typecodification==2) cout << "vertical.start" << hseparation;
                cout << accidental3 << hseparation;
                if (typecodification==2) cout << "vertical.end" << hseparation;
            }
                    
            if (starttie==1&&TIE==0){//Force the tie to end
                if (typecodification==2) cout << "vertical.start" << hseparation;
                tienote (starttie, finalnote, noteplace, TIE, typecodification);
                endtie = 1;
            }
            if (TIE==1){ //The note is tied
                if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
                tienote (starttie, finalnote, noteplace, TIE, typecodification);
                endtie = 1;
            } 
                    
            if (typecodification==2&&endtie==0) cout << "vertical.start" << hseparation;
            cout << "note.sixteenth:" << noteaux3 << vseparation << "note.sixteenth:" << noteaux2 << vseparation << "note.sixteenth:" << noteaux1 << hseparation;
            if (typecodification==2) cout << "vertical.end" << hseparation;
            
                    
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