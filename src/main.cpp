#include <QLabel>
#include <QApplication>
#include <iostream>
#include "RSK.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc == 1){
        exit(0);
    }
    RSK* A = new RSK(argv[1],
                     argv[2]); //  path to permutation and to dir for results
    std::cout << *A;
    return 0;
    //return a.exec();
}
