#include <stdio.h>
#define size 4
// Кулдышев Никита 4 АДМО
int main(int argc, char *argv[]) {
    int array[size][size] = {0};
    int i = 0;
    int j = 0;
    array[0][0] = 1;
    int num = 2;
    while(array[size-1][size-1] == 0) { // While the last element is "null" (zero)
        // Go To Bottom
        if(i < size-1 && array[i+1][j] == 0) {
            i++;
            array[i][j] = num;
            num++;
        }

        // Go To Top Right
        while(i-1 >= 0 && j+1 < size && array[i-1][j+1] == 0) {
            i--;
            j++;
            array[i][j] = num;
            num++;
        }
        // Go To Right
        if(j < size-1 && array[i][j+1] == 0) {
            j++;
            array[i][j] = num;
            num++;
        }
        // Go To Left Bottom
        while(i+1 < size && j-1 >= 0 && array[i+1][j-1] == 0) {
            i++;
            j--;
            array[i][j] = num;
            num++;
        }
    }

    // Output
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(array[i][j] < 10) printf(" %d  ", array[i][j]); // If xэ[1;9] then print "_N_" (_ - space)
            else printf("%d  ", array[i][j]); // Else if x>10 then print "N "
        }
        printf("\n\n"); // Divide lines
    }
    return 0;
}
