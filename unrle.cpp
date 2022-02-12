#include "common.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

template<typename T>
T readVal(std::istream& stream, T& val)
{
    stream.read(reinterpret_cast<char*>(&val), sizeof(T));
    return !stream.fail();
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ImageIn.pgm.rle ImageOut.pgm\n"; 
        exit (1) ;
    }

    std::ifstream input(argv[1], std::ios_base::binary);
    int nH, nW;
    readVal(input, nH);
    readVal(input, nW);
    std::vector<OCTET> img;

    while(input)
    {
        OCTET val;
        unsigned char count;
        if(readVal(input, val) && readVal(input, count)) img.resize(img.size() + count, val);
    }
    if(img.size() != nH*nW)
    {
        std::cout << "Error! " << img.size() << " != " << nH << '*' << nW << std::endl;
        return -1;
    }

    sauvegarder(argv[2], img, nH, nW);

    return 0;
}