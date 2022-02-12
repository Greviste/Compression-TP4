#include "common.h"
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>

std::tuple<double, double, double, double> rebuild_pixels(double bf, double mfv, double mfh, double hf)
{
    //mfv+mfh = a-d
    //mfv-mfh = b-c
    //2bf+mfv = a+b
    //2bf+mfh = a+c
    //hf+2bf+mfv+2bf+mfh+mfv+mfh = 4a = hf+4bf+2mfh+2mfv
    double a = (hf+4*bf+2*mfh+2*mfv)/4;
    double b = 2*bf+mfv-a;
    double c = 2*bf+mfh-a;
    double d = a - mfv - mfh;

    return {a,b,c,d};
}

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Usage: ImagePrefix ImageOut.pgm Q\n";
        exit (1) ;
    }
    std::string img_name = argv[1];
    int Q = atoi(argv[3]);

    std::vector<OCTET> bf, mfv, mfh, hf;
    int nH, nW;
    std::tie(bf, nH, nW) = charger<OCTET>(img_name + ".bf.pgm");
    std::tie(hf, std::ignore, std::ignore) = charger<OCTET>(img_name + ".hf.pgm");
    std::tie(mfh, std::ignore, std::ignore) = charger<OCTET>(img_name + ".mfh.pgm");
    std::tie(mfv, std::ignore, std::ignore) = charger<OCTET>(img_name + ".mfv.pgm");

    std::vector<OCTET> img(nH*nW*4);

    for(int i = 0; i < nH; ++i)
    {
        for(int j = 0; j < nW; ++j)
        {
            int index = i*nW+j;
            int large_index = i*2*nW*2+j*2;
            auto [a,b,c,d] = rebuild_pixels(bf[index], (mfv[index]-128.)*(Q/2), (mfh[index]-128.)*(Q/2), (hf[index]-128.)*Q);
            img[large_index] = round_clamped(a);
            img[large_index+1] = round_clamped(b);
            img[large_index+nW*2] = round_clamped(c);
            img[large_index+nW*2+1] = round_clamped(d);
        }
    }

    sauvegarder(argv[2], img, nH*2, nW*2);

    return 0;
}