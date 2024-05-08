#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


int main(int argc, char* argv[])
{


    if (argc != 4)
    {
        std::cout << "Usage: " << argv[0] << " search_string filename\n";
        return 1;
    }

    std::ifstream infile(argv[2]);
    if (!infile)
    {
        std::cout << "Cannot open " << argv[2] << '\n';
        return 1;
    }
std::cout<<"Files in the directory are: "<<std::endl;
for(auto &entry : std::filesystem::directory_iterator(argv[3])){
std::cout <<entry.path()<<std::endl;
}


    int lineno = 0;
    std::string line;
    while (getline(infile, line))
    {
        ++lineno;
        auto pos = line.find(argv[1]);
        if (pos != std::string::npos)
            std::cout << lineno << ":" << pos << ": " << line << '\n';
    }
}
