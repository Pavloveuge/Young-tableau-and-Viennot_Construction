#include "QYoungTable.h"

QYoungTable::QYoungTable(){

}

void QYoungTable::AddElem(int elem, int pos){
    if (table.size() == 0){
        table.push_back({elem});
    }
    else{
        if (pos == (int)table.size()){
            table.push_back({elem});
        }
        else{
            table[pos].push_back(elem);
        }
    }
}

QYoungTable::~QYoungTable(){

}
