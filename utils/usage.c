#include "main.h"

int Usage(int count, int tablesize){
    double usage = (double)count / tablesize;

    return usage > 0.75;
}