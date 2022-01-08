#ifndef VIENNOTDIAGRAM_H
#define VIENNOTDIAGRAM_H
#include <string>
#include <unordered_set>
#include <algorithm>
#include "gif.h"
#include "PYoungTable.h"
#include "QYoungTable.h"

struct Container1{
    std::vector<std::vector<int>> first;
    std::vector<std::vector<std::vector<int>>> second;
    Container1(std::vector<std::vector<int>> b, std::vector<std::vector<std::vector<int>>> c){
        first = b;
        second = c;
    }
};

class ViennotDiagram{
public:
    ViennotDiagram(PYoungTable* PTable, QYoungTable* QTable, std::vector<int> permutation);
    void CreateImages(std::string dir_path);
    void CreateGif(std::string path_res);
    std::vector<std::vector<std::vector<int>>> descendOne(std::vector<int> pt, std::vector<std::vector<int>> points, int n, bool isVert = true,
                                                          std::vector<std::vector<int>> path = {}, std::vector<std::vector<int>> nsp = {});
    Container1 descendAll(std::vector<std::vector<int>> points, int n, int i = 1,
                                                          std::vector<std::vector<int>> nsp = {}, std::vector<std::vector<std::vector<int>>> paths = {});
    std::vector<std::vector<std::vector<std::vector<int>>>> ViennotHelperPaths(std::vector<std::vector<int>> points, int n, std::vector<std::vector<std::vector<int>>> syt1 = {},
                            std::vector<std::vector<std::vector<int>>> syt2 = {}, std::vector<std::vector<std::vector<std::vector<int>>>> paths = {});
private:
    int SizeDiagram;
    PYoungTable* PTable;
    QYoungTable* QTable;
    std::vector<int> permutation;
};
#endif // VIENNOTDIAGRAM_H
