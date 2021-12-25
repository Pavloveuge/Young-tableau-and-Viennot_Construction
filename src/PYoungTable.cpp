#include "PYoungTable.h"

PYoungTable::PYoungTable(){

}

int PYoungTable::AddElem(int elem){
    std::vector<int> res;
    if (table.size() == 0){
        table.push_back({elem});
        return 0;
    }
    for (int i = 0; i < (int)table.size(); i++){
        for (int j = 0; j < (int)table[i].size(); j++){
            if (elem < table[i][j]){
                std::swap(elem, table[i][j]);
                if ((int)table.size() == i + 1){
                    table.push_back({elem});
                    return i + 1;
                }
                break;
            }
            if (j == (int)table[i].size() - 1){
                table[i].push_back(elem);
                return i;
            }
        }
    }
    return 0;
}

PYoungTable::~PYoungTable(){

}
