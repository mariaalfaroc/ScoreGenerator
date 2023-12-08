#include "AlfaroGenerator4E.hpp"

void readConfig(int& ncompasses, int& typeofgen, float& rlogistic, int& naltered, int& ngroup, int& typecodification, int& numofGenerations)
{
    std::ifstream configfile("config/config.conf");
    std::string line;
    std::vector<std::string> data;
    data.reserve(7);
    if(configfile.is_open())
    {
        while (std::getline(configfile, line))
        {
            data.push_back(line);
        }

        ncompasses = atoi(data[0].c_str());
        typeofgen = atoi(data[1].c_str());
        rlogistic = atof(data[2].c_str());
        naltered = atoi(data[3].c_str());
        ngroup = atoi(data[4].c_str());
        typecodification = atoi(data[5].c_str());
        numofGenerations = atoi(data[6].c_str());

        configfile.close();
    }
    else
    {
        std::cout<<"Config file not found!"<<std::endl;
        exit(0);
    }

}

int main(int argc, char** argv)
{
    srand(time(NULL));
    AlfaroGenerator4E generator = AlfaroGenerator4E();

    std::string basename = "";
    int ncompasses = 0;
    int typeofgen = 0;
    float rlogistic = 0.f;
    int naltered = 0;
    int ngroup = 0;
    int typecodification = 0;
    int numOfGenerations = 0;

    readConfig(ncompasses, typeofgen, rlogistic, naltered, ngroup, typecodification, numOfGenerations);

    for(int i = 0; i< numOfGenerations; i++)
    {
        std::string filename = basename + std::to_string(i);
        //auto _ = std::async(std::launch::async ,MakeGeneration, generator, filename, ncompasses, typeofgen, rlogistic, naltered, ngroup, typecodification);
        generator.GenerateCorpus(filename, ncompasses, typeofgen, rlogistic, naltered, ngroup, typecodification);
        //std::cout<< i <<std::endl; //To know which score is generating. Very consuming-time operation.
    }

    //delete generator;
    //generator = nullptr;

    return 0;
}
