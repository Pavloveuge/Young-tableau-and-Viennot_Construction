#include "YoungTable.h"

YoungTable::YoungTable(){
}

std::vector<std::vector<int>> YoungTable::GetTable(){
    return this->table;
}

std::ostream& operator<< (std::ostream &out, const YoungTable &table)
{
    std::vector<std::vector<int>> Data = table.table;
    for (int i = 0; i < Data.size(); i++){
        for (int j = 0; j < Data[i].size(); j++){
            out << Data[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}


void YoungTable::CreateImage(std::string path){
    QImage image(QSize(400,400),QImage::Format_RGB32);
    QPainter painter(&image);
    int CellSize = 30;
    //painter.setBrush(QBrush(Qt::green));
    painter.fillRect(QRectF(0,0,400,400),Qt::white);
    painter.setPen(QPen(Qt::black));
    std::vector<std::vector<int>> table = this->GetTable();
    for (int i = 0; i < (int)table.size(); i++){
        for (int j = 0; j < (int)table[i].size(); j++){
            painter.drawText(QRect(CellSize * j, CellSize * i,
                                   CellSize, CellSize),
                             Qt::AlignCenter, std::to_string(table[i][j]).c_str());
            painter.drawRect(CellSize * j, CellSize * i,
                             CellSize, CellSize);
        }
    }
    image.save(path.c_str());
}

std::vector<int> YoungTable::GetRow(int ind){
    return this->table[ind];
}

std::vector<int> YoungTable::AfterRow(int ind){
    std::vector<int> res = {};
    for (int i = ind; i < (int)this->table.size(); i++){
        for (int j = 0; j < (int)this->table[i].size(); j++){
            res.push_back(this->table[i][j] - 1);
        }
    }
    //std::sort(res.begin(), res.end());
    return res;
}

std::vector<int> YoungTable::GetColumn(int ind){
    std::vector<int> res = {};
    for (int i = 0; i < (int)this->table.size(); i++){
        if (this->table[i].size() > ind){
            res.push_back(table[i][ind]);
        }
    }
    return res;
}

int YoungTable::CntRows(){
    return (int)this->table.size();
}

int YoungTable::CntElems(){
    int cnt = 0;
    for (int i = 0; i < (int)this->table.size(); i++){
        cnt += (int)this->table[i].size();
    }
    return cnt;
}

YoungTable::~YoungTable(){
}
