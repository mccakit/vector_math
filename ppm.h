#pragma once
#include <string>
#include <vector>
#include <fstream>

namespace my_std
{
    template<typename T>
    using dynamic_array = std::vector<T>;
}

class PPM
{
public:
    PPM(const int image_size):
        image_data{static_cast<long long unsigned int>(image_size), std::vector<std::string>(image_size)},
        image_header{3},
        image_size{image_size}
    {
        const std::string image_size_name{std::to_string(image_size)};
        image_header[0] = "P3";
        image_header[1] = image_size_name + " " + image_size_name;
        image_header[2] = "255";
        for (int row{0}; row < image_size; ++row)
        {
            for (int col{0}; col < image_size; ++col)
            {
                image_data[row][col] = "255 255 255";
            }
        }
    }

    my_std::dynamic_array<my_std::dynamic_array<std::string> > image_data{};
    my_std::dynamic_array<std::string> image_header{};
    int image_size{};

    std::string& operator ()(const int row, const int col)
    {
        return image_data[image_size - 1 - col][row];
    }

    void save(const std::string& filename)
    {
        std::fstream file{};
        file.open(filename + ".ppm", std::ios::out);
        for (auto& header_line: image_header)
        {
            file << header_line << "\n";
        }
        for (auto& row: image_data)
        {
            for (auto& pixel: row)
            {
                file << pixel << "\n";
            }
        }
    }
};

