#include "common.h"
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>


int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: ImageIn.pgm ImageOutPrefix Q\n"; 
        exit (1) ;
    }
    int Q = atoi(argv[3]);

    auto [img, nH, nW] = charger<OCTET>(argv[1]);
    size_t sub_size = nH * nW / 4;

    std::vector<OCTET> bf(sub_size), mfv(sub_size), mfh(sub_size), hf(sub_size);

    for(int i = 0; i < nH / 2; ++i)
    {
        for(int j = 0; j < nW / 2; ++j)
        {
            int index = i*2*nW+j*2;
            int small_index = i*nW/2+j;
            double a=img[index],
            b=img[index+1],
            c=img[index+nW],
            d=img[index+nW+1];

            bf[small_index] = round_to_byte((a+b+c+d)/4);
            mfv[small_index] = round_offset_clamped((a+b-c-d)/*/2*//Q);
            mfh[small_index] = round_offset_clamped((a-b+c-d)/*/2*//Q);
            hf[small_index] = round_offset_clamped((a-b-c+d)/Q);
        }
    }

    std::string out_name = argv[2];
    sauvegarder(out_name+".bf.pgm", bf, nH/2, nW/2);
    sauvegarder(out_name+".hf.pgm", hf, nH/2, nW/2);
    sauvegarder(out_name+".mfv.pgm", mfv, nH/2, nW/2);
    sauvegarder(out_name+".mfh.pgm", mfh, nH/2, nW/2);

    return 0;
}