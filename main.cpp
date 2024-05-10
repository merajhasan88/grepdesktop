#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>
#include <filesystem>

int main(int argc, char* argv[])
{
    std::string target;
    std::string folder_name;

    //if (argc != 4)
    //{
    //    std::cout << "Usage: " << argv[0] << " search_string filename\n";
      //  return 1;
    //}
    std::cout << "Enter something to find: ";
    std::getline(std::cin,target);
    std::cout << "Enter directory path ";
    std::cin >> folder_name;
    /*std::ifstream infile(argv[2]);
    if (!infile)
    {
        std::cout << "Cannot open " << argv[2] << '\n';
        return 1;
    }
    */
std::cout<<"Files in the directory are: "<<std::endl;
//for(auto &entry : std::filesystem::directory_iterator(argv[3])){
for(auto &entry : std::filesystem::directory_iterator(folder_name)){
std::filesystem::path filePath=entry.path();	
if(filePath.extension()==".csv" || filePath.extension()==".txt"
		|| filePath.extension()==".docx" || filePath.extension()==".doc"){
std::ifstream infile(entry.path());
    if (!infile)
    {
        std::cout << "Cannot open " << entry.path() << '\n';
        return 1;
    }
      int lineno = 0;
    std::string line;
    while (getline(infile, line))
    {
        ++lineno;
        auto pos = line.find(target);
        if (pos != std::string::npos){
            std::cout << lineno << ":" << pos << ": " << line << '\n';
	std::cout <<entry.path()<<std::endl;
	}

    }


//std::cout <<entry.path()<<std::endl;
}
}


  /*  int lineno = 0;
    std::string line;
    while (getline(infile, line))
    {
        ++lineno;
        auto pos = line.find(argv[1]);
        if (pos != std::string::npos)
            std::cout << lineno << ":" << pos << ": " << line << '\n';
    }
    */
    
}
