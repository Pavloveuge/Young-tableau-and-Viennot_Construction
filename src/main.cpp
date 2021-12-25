#include <QLabel>
#include <QApplication>
#include <iostream>
#include "RSK.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RSK* A = new RSK(argv[1]); // либо просто сюда передать путь к файлу с перестановкой
    std::cout << *A;
    return 0;
    //return a.exec();
}
