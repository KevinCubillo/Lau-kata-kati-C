#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int isNeighbor(int cell1, int cell2){
    int centralCell = 3;

   if ((abs(cell1 - cell2) == 1 && abs(cell1 % 3 - cell2 % 3) == 0) ||
       (abs(cell1 - cell2) == 3 && abs(cell1 % 3 - cell2 % 3) <= 1) ||
       ((cell1 == centralCell || cell2 == centralCell) && abs(cell1 - cell2) <= 3) ||
       ((cell1 == centralCell - 1 || cell2 == centralCell - 1) && abs(cell1 - cell2) <= 2) ||
       ((cell1 == centralCell - 2 || cell2 == centralCell - 2) && abs(cell1 - cell2) <= 1)) {
            return 1;
    }
    return  0;
}

int main (){
   printf ("%d\n", isNeighbor(0, 2));
}