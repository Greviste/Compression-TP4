#include "common.h"
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <filesystem>
#include <map>

const unsigned UncompressedSize = 262159;

int main(int argc, char* argv[])
{
    std::string uncompressed_prefix = "uncompressed/back";
    std::string uncompressed_suffix = ".pgm";
    auto [ref, h, w] = charger<OCTET>("wifi.pgm");
    std::map<int, std::pair<double, double>> result;

    for (const auto& subdir : std::filesystem::directory_iterator{"compressed"})
    {
        if(!subdir.is_directory()) continue;
        double size = 0;
        for(const auto& f : std::filesystem::directory_iterator{subdir})
        {
            if(!f.is_regular_file()) continue;
            size += f.file_size();
        }

        auto [img, hh, ww] = charger<OCTET>(uncompressed_prefix + subdir.path().filename().string() + uncompressed_suffix);
        result[std::stoi(subdir.path().filename())] = std::make_pair(UncompressedSize/size, psnr(ref, img));
    }

    for(const auto& p : result)
    {
        std::cout << p.second.first << ' ' << p.second.second << std::endl;
    }

    return 0;
}