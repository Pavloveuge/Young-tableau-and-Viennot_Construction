#ifndef PYOUNGTABLE_H
#define PYOUNGTABLE_H
#include "YoungTable.h"

class PYoungTable : public YoungTable{
public:
    PYoungTable();
    int AddElem(int elem);
    ~PYoungTable();
};
#endif // PYOUNGTABLE_H
