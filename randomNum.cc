#include "randomNum.h"


int randomGenerate(int maxVal){
    srand((unsigned) time(0));
    return (rand() % maxVal);
}
