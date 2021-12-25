#include "ViennotDiagram.h"

ViennotDiagram::ViennotDiagram(PYoungTable* PTable, QYoungTable* QTable, std::vector<int> permutation){
    this->PTable = PTable;
    this->QTable = QTable;
    this->permutation = permutation;
}


void ViennotDiagram::CreateImages(std::string dir_path){
    QImage image(QSize(420,420),QImage::Format_RGB32);
    QPainter painter(&image);
    painter.fillRect(QRectF(0,0,420,420),Qt::white);
    painter.setPen(QPen(Qt::black, 2));
    int SizeCell = 30;
    for (int i = 0; i <= SizeCell * this->permutation.size(); i++){
        if (i % SizeCell == 0){
            painter.drawLine(i, 0, i, SizeCell * this->permutation.size());
            painter.drawLine(0, i, SizeCell * this->permutation.size(), i);
        }
    }
    int ind[] = {7, 8, 9, 10}; // 7, 8, 9
    std::vector<int> per = this->permutation;
    std::vector<int> per_cp = this->permutation;
    std::vector<int> index = {};
    for (int i = 0; i < (int)this->permutation.size(); i++){
        index.push_back(i);
    }
    for (int i = 0; i < QTable->CntRows(); i++){ // QTable->CntRows()
        std::vector<int> skel(this->permutation.size(), this->permutation.size());
        painter.setPen(QPen(Qt::GlobalColor(ind[i]), 4));
        for (int j = 0; j < (int)index.size(); j++){ // (int)per_cp.size()
                int lenx = this->permutation.size() - index[j] - 1;
                int leny = this->permutation.size() - per[index[j]];
                for(int k = index[j] + 1; k < (int)per_cp.size(); k++){
                    if (per[index[j]] > per_cp[k]){
                        lenx = k - index[j];
                        leny = this->permutation.size() - per[index[j]];
                        if (lenx > 1){
                            per_cp[k] = this->permutation.size() + 1;
                        }
                        skel[index[j] + lenx] = per[index[j]];
                        break;
                    }
                }
                int shift = this->permutation.size() - skel[index[j]];
                leny = leny - shift;
                if (shift == 0){
                    painter.drawLine(index[j] * SizeCell, 0,
                                     index[j] * SizeCell, 30);
                }
                painter.drawLine(index[j] * SizeCell, shift * SizeCell + 30,
                                 index[j] * SizeCell, (shift + leny) * SizeCell + 30);
                painter.drawLine(index[j] * SizeCell, (shift + leny) * SizeCell + 30,
                                 (index[j] + lenx) * SizeCell, (shift + leny) * SizeCell + 30);
                if (index[j] + lenx == (int)this->permutation.size() - 1){
                    painter.drawLine((index[j] + lenx) * SizeCell, (shift + leny) * SizeCell + 30,
                                     (index[j] + lenx + 1) * SizeCell, (shift + leny) * SizeCell + 30);
                }
            }
        image.save((std::to_string(i) + ".png").c_str());
        per = {};
        index = QTable->AfterRow(i + 1);
        for (int k = 0; k < (int)skel.size(); k++){
            per.push_back(skel[k]);
        }
        per_cp = per;
        }
    /*
    Q - координата по x, начинаем рисовать прямую сверху вниз
    если в таблице P в этом столбце ниже есть значение, то на нём остановимся
    либо остановимся на соответстующей строке, исходя из значения в P
    */
}
