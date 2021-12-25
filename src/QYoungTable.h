#ifndef QYOUNGTABLE_H
#define QYOUNGTABLE_H
#include "YoungTable.h"

class QYoungTable : public YoungTable{
public:
    QYoungTable();
    void AddElem(int elem, int pos);
    ~QYoungTable();
};

#endif // QYOUNGTABLE_H
