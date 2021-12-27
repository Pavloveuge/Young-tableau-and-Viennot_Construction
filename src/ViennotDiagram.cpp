#include "ViennotDiagram.h"
#include <QDebug>

ViennotDiagram::ViennotDiagram(PYoungTable* PTable, QYoungTable* QTable, std::vector<int> permutation){
    this->PTable = PTable;
    this->QTable = QTable;
    this->permutation = permutation;
    this->SizeDiagram = 0;
}

std::vector<std::vector<std::vector<int>>> ViennotDiagram::descendOne(std::vector<int> pt, std::vector<std::vector<int>> points, int n, bool isVert,
                                                      std::vector<std::vector<int>> path, std::vector<std::vector<int>> nsp){
    std::vector<std::vector<int>> newPts;
    if (isVert){
        path.push_back(pt);
        for (int k = 0; k < (int) points.size(); k++){
            if (pt[0] == points[k][0]){
                if (k == 0){
                    newPts = std::vector<std::vector<int>>(points.begin() + 1, points.end());
                }
                else{
                    newPts = std::vector<std::vector<int>>(points.begin(), points.begin() + k);
                    newPts.insert(newPts.end(), points.begin() + k + 1, points.end());
                }
                path.push_back(points[k]);
                return descendOne(points[k], newPts, n, false, path, nsp);
            }
        }
    }
    else{
        for (int i = 0; i < (int)points.size(); i++){
            if (pt[1] > points[i][1]){
                path.push_back({points[i][0], pt[1]});
                path.push_back(points[i]);
                newPts = std::vector<std::vector<int>>(points.begin(), points.begin() + i);
                newPts.insert(newPts.end(), points.begin() + i + 1, points.end());
                nsp.push_back({points[i][0], pt[1]});
                return descendOne(points[i], newPts, n, false, path, nsp);
            }
        }
        path.push_back({n + 1, pt[1]});
        std::vector<std::vector<std::vector<int>>> res;
        res.push_back(path);
        res.push_back(points);
        res.push_back(nsp);
        return res;
    }
    std::vector<std::vector<std::vector<int>>> res;
    return res;
}


Container1 ViennotDiagram::descendAll(std::vector<std::vector<int>> points, int n, int i,
                                                      std::vector<std::vector<int>> nsp, std::vector<std::vector<std::vector<int>>> paths){
    if (i > n or (int)points.size() == 0){
        Container1 res(nsp, paths);
        return res;
    }
    else{
        std::vector<std::vector<std::vector<int>>> result = descendOne({i, n+ 1}, points, n);
        if (result.size() != 0){
            nsp.insert(nsp.end(), result[2].begin(), result[2].end());
            paths.push_back(result[0]);
            return descendAll(result[1], n, i + 1, nsp, paths);
        }
        else{
            return descendAll(points, n, i + 1, nsp, paths);
        }
    }
}

std::vector<std::vector<std::vector<std::vector<int>>>> ViennotDiagram::ViennotHelperPaths(std::vector<std::vector<int>> points, int n, std::vector<std::vector<std::vector<int>>> syt1,
                        std::vector<std::vector<std::vector<int>>> syt2, std::vector<std::vector<std::vector<std::vector<int>>>> paths){
    if (points.size() == 0){
        return paths;
    }
    else{
        Container1 step = descendAll(points, n);
        std::vector<std::vector<std::vector<int>>> tempPaths = step.second;
        paths.push_back(tempPaths);
        std::vector<std::vector<int>> syt1Part = {};
        std::vector<std::vector<int>> syt2Part = {};
        for (int i = 0; i < (int)tempPaths.size(); i++){
            syt1Part.push_back(tempPaths[i][0]);
        }
        for (int i = 0; i < (int)tempPaths.size(); i++){
            syt2Part.push_back(tempPaths[i][1]);
        }
        syt1.push_back(syt1Part);
        syt2.push_back(syt2Part);

        return ViennotHelperPaths(step.first, n, syt1, syt2, paths);
    }

}

void ViennotDiagram::CreateImages(std::string dir_path){
    int SizeCell = 30;
    this->SizeDiagram = SizeCell * (this->permutation.size() + 1);
    QImage image(QSize(SizeDiagram,SizeDiagram),QImage::Format_RGB32);
    QPainter painter(&image);
    painter.fillRect(QRectF(0,0,SizeDiagram,SizeDiagram),Qt::white);
    painter.setPen(QPen(Qt::black, 2));
    for (int i = 0; i <= this->SizeDiagram; i++){
            if (i % SizeCell == 0){
                painter.drawLine(i, 0, i, this->SizeDiagram);
                painter.drawLine(0, i, this->SizeDiagram, i);
            }
        }
    std::vector<std::vector<int>> coor;
        for (int i = 0; i < (int)this->permutation.size(); i++){
            coor.push_back({i + 1, this->permutation[i]});
        }
    std::vector<std::vector<std::vector<std::vector<int>>>> ans = this->ViennotHelperPaths(coor, (int)this->permutation.size());
    for (int i = 0; i < (int)ans.size(); i++){
        painter.setPen(QPen(Qt::GlobalColor(i + 7), 4));
        for (int j = 0; j < (int)ans[i].size(); j++){
            int x_start = ans[i][j][0][0], y_start = ans[i][j][0][1];
            for (int k = 0; k < (int)ans[i][j].size(); k++){
                painter.drawLine(x_start * SizeCell, this->SizeDiagram - y_start * SizeCell,
                                 ans[i][j][k][0] * SizeCell, this->SizeDiagram - ans[i][j][k][1] * SizeCell);
                x_start = ans[i][j][k][0]; y_start = ans[i][j][k][1];
            }
        }
        image.save((dir_path + "/" + std::to_string(i) + ".png").c_str());
    }
    //image.save((dir_path + "/" + std::to_string(i) + ".png").c_str());
}


void ViennotDiagram::CreateGif(std::string path_res){
    auto QTablefile = path_res + "/Vienno.gif";
    int delay = 75;
    GifWriter Gif;
    GifBegin(&Gif, QTablefile.c_str(), this->SizeDiagram, this->SizeDiagram, delay);
    for (int i = 0; i < QTable->CntRows(); i++){
        QImage* img = new QImage((path_res + "/" + std::to_string(i) + ".png").c_str());
        GifWriteFrame(&Gif, img->bits(), this->SizeDiagram, this->SizeDiagram, delay);
    }
    GifEnd(&Gif);
}
