#include "common.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

template<typename T>
void writeVal(std::ostream& stream, T val)
{
    stream.write(reinterpret_cast<char*>(&val), sizeof(T));
}


int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ImageIn.pgm ImageOut.pgm.rle\n"; 
        exit (1) ;
    }

    auto [img, nH, nW] = charger<OCTET>(argv[1]);
    
    std::ofstream output(argv[2], std::ios_base::binary);
    writeVal(output, nH);
    writeVal(output, nW);
    OCTET last_val = img[0];
    unsigned char count = 0;
    for(OCTET val : img)
    {
        if(val != last_val || count == 255)
        {
            writeVal(output, last_val);
            writeVal(output, count);
            last_val = val;
            count = 1;
        }
        else
        {
            ++count;
        }
    }
    writeVal(output, last_val);
    writeVal(output, count);
    return 0;
}