#ifndef VIENNOTDIAGRAM_H
#define VIENNOTDIAGRAM_H
#include <string>
#include "PYoungTable.h"
#include "QYoungTable.h"

class ViennotDiagram{
public:
    ViennotDiagram(PYoungTable* PTable, QYoungTable* QTable, std::vector<int> permutation);
    void CreateImages(std::string dir_path);
private:
    PYoungTable* PTable;
    QYoungTable* QTable;
    std::vector<int> permutation;
};
#endif // VIENNOTDIAGRAM_H
