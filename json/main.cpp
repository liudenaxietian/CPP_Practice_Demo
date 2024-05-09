#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

int main(int argc, char *argv[])
{

    json j;

    if (argc == 1)
    {
        std::ifstream jfile("./config.json");
        jfile >> j;
    }else if(argc == 2){
        std::ifstream jfile(argv[1]);
        jfile>>j;
    }else{
        std::cout<<"ERROR: Parameters are too many!" <<std::endl;
        return -1;
    }

    float pi = j.at("pi");
    bool happy = j.at("happy");
    std::cout<<"pi: "<< pi <<std::endl;
    std::cout<<"happy:" << happy << std::endl; 

    return 0;
}