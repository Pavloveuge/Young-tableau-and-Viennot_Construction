#include <QLabel>
#include <QApplication>
#include <iostream>
#include "RSK.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RSK* A = new RSK("/home/eugene/permutation.txt", "/home/eugene/res"); //  path to permutation and to dir for results
    std::cout << *A;
    return 0;
    //return a.exec();
}
