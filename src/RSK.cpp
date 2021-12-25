#include "RSK.h"
#include "gif.h"

RSK::RSK(std::string path){
    std::ifstream infile(path);
    int element;
    while (infile >> element)
    {
        permutation.push_back(element);
    }
    P = new PYoungTable;
    Q = new QYoungTable;

    for (int i = 0; i < (int)permutation.size(); i++){
        int pos = P->AddElem(permutation[i]);
        P->CreateImage("PTable" + std::to_string(i) + ".png");
        Q->AddElem(i + 1, pos);
        Q->CreateImage("QTable" + std::to_string(i) + ".png");
    }
    this->CreateGif();
    ViennotDiagram* Diagram = new ViennotDiagram(P, Q, permutation);
    Diagram->CreateImages("");
    delete Diagram;
}

void RSK::CreateGif(){
    int size = 400;
    auto fileName = "QTable.gif";
    int delay = 50;
    GifWriter g;
    GifBegin(&g, fileName, size, size, delay);
    for (int i = 0; i < (int)this->permutation.size(); i++){
        QImage* img = new QImage(("QTable" + std::to_string(i) + ".png").c_str());
        GifWriteFrame(&g, img->bits(), size, size, delay);
    }
    GifEnd(&g);
}


std::ostream& operator<< (std::ostream &out, const RSK &table){
    out << "Tableau P:\n";
    out << *table.P;
    out << "Tableau Q:\n";
    out << *table.Q;
    return out;
}
