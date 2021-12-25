#include "RSK.h"
#include "gif.h"

RSK::RSK(std::string path_per, std::string path_res){
    std::ifstream infile(path_per);
    int element;
    while (infile >> element)
    {
        permutation.push_back(element);
    }
    P = new PYoungTable;
    Q = new QYoungTable;

    for (int i = 0; i < (int)permutation.size(); i++){
        int pos = P->AddElem(permutation[i]);
        P->CreateImage(path_res + "/PTable" + std::to_string(i) + ".png");
        Q->AddElem(i + 1, pos);
        Q->CreateImage(path_res + "/QTable" + std::to_string(i) + ".png");
    }
    this->CreateGif(path_res);
    ViennotDiagram* Diagram = new ViennotDiagram(P, Q, permutation);
    Diagram->CreateImages("");
    delete Diagram;
}

void RSK::CreateGif(std::string path_res){
    int size = 400;
    auto QTablefile = path_res + "/QTable.gif";
    int delay = 50;
    GifWriter QGif;
    GifBegin(&QGif, QTablefile.c_str(), size, size, delay);
    for (int i = 0; i < (int)this->permutation.size(); i++){
        QImage* img = new QImage((path_res + "/QTable" + std::to_string(i) + ".png").c_str());
        GifWriteFrame(&QGif, img->bits(), size, size, delay);
    }
    GifEnd(&QGif);
    auto PTablefile = path_res + "/PTable.gif";
    GifWriter PGif;
    GifBegin(&PGif, PTablefile.c_str(), size, size, delay);
    for (int i = 0; i < (int)this->permutation.size(); i++){
        QImage* img = new QImage((path_res + "/PTable" + std::to_string(i) + ".png").c_str());
        GifWriteFrame(&PGif, img->bits(), size, size, delay);
    }
    GifEnd(&PGif);
}


std::ostream& operator<< (std::ostream &out, const RSK &table){
    out << "Tableau P:\n";
    out << *table.P;
    out << "Tableau Q:\n";
    out << *table.Q;
    return out;
}
