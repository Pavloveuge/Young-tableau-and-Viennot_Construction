#ifndef YOUNGTABLE_H
#define YOUNGTABLE_H
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <QImage>
#include <QSize>
#include <QPainter>
#include <algorithm>

class YoungTable{
public:
    YoungTable();
    std::vector<std::vector<int>> GetTable();
    std::vector<int> GetRow(int ind);
    std::vector<int> GetColumn(int ind);
    std::vector<int> AfterRow(int ind);
    int CntRows();
    int CntElems();
    friend std::ostream& operator<< (std::ostream &out, const YoungTable &table);
    void CreateImage(std::string path);
    ~YoungTable();
protected:
    std::vector<std::vector<int>> table;
};
#endif // YOUNGTABLE_H
