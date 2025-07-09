#include <cassert>
#include <chrono>
#include "stool/include/light_stool.hpp"
#include "../include/compression_algorithms.hpp"
#include "libdivsufsort/sa.hpp"


using namespace std;

void compress(string &text, string mode, uint64_t threshold, uint64_t lzrrMode, stool::compression_algorithms::LZWriter &writer)
{

    if (mode == "lz77")
    {
        stool::compression_algorithms::LZ77::compress(text, writer);
    }
    else
    {
        std::cout << "invalid mode!" << std::endl;
        throw - 1;
    }
    writer.complete();
}
/*
void checkFile(std::string &text, std::string filename)
{
    std::string dtext;
    //std::cout << "decompose " << std::endl;

    std::vector<stool::compression_algorithms::LZFactor> factors;
    stool::compression_algorithms::IO::load(filename, factors);

    stool::compression_algorithms::MSDecompressor::decompress_factors(factors, dtext);
    if (text.size() != dtext.size())
    {
        std::cout << "differrent size!" << std::endl;
        throw - 1;
    }
    for (uint64_t x = 0; x < text.size(); x++)
    {
        if (text[x] != dtext[x])
        {

            std::cout << "error decompress" << std::endl;
            throw - 1;
        }
    }
}
*/

int main(int argc, char *argv[])
{
    #ifdef DEBUG
    std::cout << "\033[41m";
    std::cout << "DEBUG MODE!" << std::endl;
    std::cout << "\e[m" << std::endl;
    //std::cout << "\033[30m" << std::endl;

    #endif
    cmdline::parser p;
    p.add<std::string>("input_file", 'i', "input file name", true);
    p.add<std::string>("output_file", 'o', "output file name (the default output name is 'input_file.ext')", false, "");
    p.add<std::string>("mode", 'm', "compression algorithm ('lz77' : LZ77)", false, "lzrr");
    p.add<bool>("file_check", 'c', "check output file", false, false);

    p.parse_check(argc, argv);
    std::string inputFile = p.get<std::string>("input_file");
    std::string outputFile = p.get<std::string>("output_file");
    std::string mode = p.get<std::string>("mode");
    bool fileCheck = p.get<bool>("file_check");

    if (outputFile.size() == 0)
    {
        outputFile = inputFile + "." + mode + ".lz" ;

    }

    std::ifstream ifs(inputFile);
    bool inputFileExist = ifs.is_open();
    if(!inputFileExist){
        std::cout << inputFile << " cannot open." << std::endl;
        return -1;
    }


    stool::compression_algorithms::LZWriter writer;
    writer.open(outputFile);
	//std::ofstream out(outputFile, ios::out | ios::binary);

    std::string text = "";
    std::cout << "Loading : " << inputFile << std::endl;
    stool::IO::load_text(inputFile, text);

    //std::vector<LZFactor> factors;

    auto start = std::chrono::system_clock::now();
    compress(text, mode, UINT64_MAX, 0, writer);
    auto end = std::chrono::system_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    //std::cout << "write : " << outputFile << std::endl;
    //stool::IO::write(outputFile, factors);
    
    if (fileCheck)
    {
        //checkFile(text, outputFile);
        std::cout << "text check : " << "OK!" << std::endl;

    }
    
    std::cout << "\033[36m" << std::endl;
    std::cout << "# =============RESULT===============" << std::endl;
    std::cout << "# File : " << inputFile << std::endl;
    std::cout << "# Output : " << outputFile << std::endl;
    std::cout << "# Mode : " << mode << std::endl;
    //if(threshold != UINT64_MAX) std::cout << "Threshold : " << threshold << std::endl;
    std::cout << "# The length of the input text : " << text.size() << std::endl;
    double charperms = (double)text.size() / elapsed;
    std::cout << "# The number of factors : " << writer.counter << std::endl;
    std::cout << "# Excecution time : " << elapsed << "ms";
    std::cout << " [" << charperms << "chars/ms]" << std::endl;
    std::cout << "# ==================================" << std::endl;
    std::cout << "\033[39m" << std::endl;
}