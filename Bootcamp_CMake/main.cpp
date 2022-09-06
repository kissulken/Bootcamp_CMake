#include "src/TableProcessing.h"


int main()
{
    TableParsing obj("../datafile.csv", "../out.csv");
    obj.run();
    return 0;
}
