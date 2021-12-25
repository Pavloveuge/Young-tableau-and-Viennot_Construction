#ifndef RSK_H
#define RSK_H
#include <string>
#include <vector>
#include "PYoungTable.h"
#include "QYoungTable.h"
#include "ViennotDiagram.h"

class RSK{
public:
    RSK(std::string path_per, std::string path_res);
    friend std::ostream& operator<< (std::ostream &out, const RSK &table);
    void CreateGif(std::string path_res);
    ~RSK();
private:
    std::vector<int> permutation;
    PYoungTable* P;
    QYoungTable* Q;
};

#endif // RSK_H
