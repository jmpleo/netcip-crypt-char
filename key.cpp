#include "key.h"
#include "types.h"

#include <fstream>
#include <random>

void Table::SetRandomTable()
{
    GenerateTables();
}
bool Table::LoadTable(const char * filename)
{
    std::ifstream in(filename);
    if (!in) {
        return false;
    }
    in.read((char*)encTab_, TABLE_DIM*TABLE_DIM)
      .read((char*)decTab_, TABLE_DIM*TABLE_DIM);
    return true;

}
bool Table::SaveTable(const char * filename)
{
    std::ofstream out(filename);
    if (!out) {
        return false;
    }
    out.write((const char*)encTab_, TABLE_DIM*TABLE_DIM)
       .write((const char*)decTab_, TABLE_DIM*TABLE_DIM);
    return true;
}
void Table::GenerateTables()
{
    int j, randomIndex, i;
    std::random_device d;
    std::seed_seq seed({d(), d(), d(), d(), d(), d()});
    std::mt19937 gen(seed);
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

