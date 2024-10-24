#include "key.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>
#include <sstream>
#include <type_traits>


std::string Key::HexKey() const {
    std::ostringstream oss;
    for (size_t i = 0; i < TABLE_DIM; ++i) {
        for (size_t j = 0; j < TABLE_DIM; ++j) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast <int> (encTab_[i][j]);
        }
    }
    return oss.str();
}


bool Key::LoadTable(const char * filename)
{
    std::ifstream in(filename);
    if (!in) {
        return false;
    }
    in.read((char*)encTab_, TABLE_DIM*TABLE_DIM)
      .read((char*)decTab_, TABLE_DIM*TABLE_DIM);
    return true;

}


bool Key::SaveTable(const char * filename)
{
    std::ofstream out(filename);
    if (!out) {
        return false;
    }
    out.write((const char*)encTab_, TABLE_DIM*TABLE_DIM)
       .write((const char*)decTab_, TABLE_DIM*TABLE_DIM);
    return true;
}


void Key::UpdateKey()
{

    std::random_device d;
    std::seed_seq seed({d(), d(), d(), d(), d(), d()});
    std::mt19937 gen(seed);

    std::remove_const<decltype(TABLE_DIM)>::type j, randomIndex, i;

    for (j = 0; j < TABLE_DIM; ++j) {

        for (i = 0; i < TABLE_DIM; ++i) {
            decTab_[j][i] = encTab_[j][i] = i;
        }

        for (i = TABLE_DIM-1; i > 0; --i) {

            std::uniform_int_distribution<int> dist(0, i-1);

            randomIndex = dist(gen);

            std::swap(encTab_[j][i], encTab_[j][randomIndex]);
            //inverse
            decTab_[j][encTab_[j][i]] = i;

        } decTab_[j][encTab_[j][0]] = 0;
    }
}

