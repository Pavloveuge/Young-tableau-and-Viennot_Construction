#include "RSK.h"

RSK::RSK(std::string path_per, std::string path_res){
    std::ifstream infile(path_per);
    int element;
    while (infile >> element)
    {
        permutation.push_back(element);
    }
    P = new PYoungTable;
    Q = new QYoungTable;
    int status;
    status = system((("mkdir -p " + path_res + "/PTables").c_str()));
    status = system((("mkdir -p " + path_res + "/QTables").c_str()));
    status = system((("mkdir -p " + path_res + "/Diagrams").c_str()));
    for (int i = 0; i < (int)permutation.size(); i++){
        int pos = P->AddElem(permutation[i]);
        P->CreateImage(path_res + "/PTables/PTable" + std::to_string(i) + ".png", this->permutation.size());
        Q->AddElem(i + 1, pos);
        Q->CreateImage(path_res + "/QTables/QTable" + std::to_string(i) + ".png", this->permutation.size());
    }
    this->CreateGif(path_res);
    ViennotDiagram* Diagram = new ViennotDiagram(P, Q, permutation);
    Diagram->CreateImages(path_res + "/Diagrams");
    Diagram->CreateGif(path_res);
    delete Diagram;
}

void RSK::CreateGif(std::string path_res){
    int size = 40 * this->permutation.size();
    auto QTablefile = path_res + "/QTable.gif";
    int delay = 75;
    GifWriter QGif;
    GifBegin(&QGif, QTablefile.c_str(), size, size, delay);
    for (int i = 0; i < (int)this->permutation.size(); i++){
        QImage* img = new QImage((path_res + "/QTables/QTable" + std::to_string(i) + ".png").c_str());
        GifWriteFrame(&QGif, img->bits(), size, size, delay);
    }
    GifEnd(&QGif);
    auto PTablefile = path_res + "/PTable.gif";
    GifWriter PGif;
    GifBegin(&PGif, PTablefile.c_str(), size, size, delay);
    for (int i = 0; i < (int)this->permutation.size(); i++){
        QImage* img = new QImage((path_res + "/PTables/PTable" + std::to_string(i) + ".png").c_str());
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
