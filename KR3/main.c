#include <stdio.h>

char getHexFromInt(int number) { // Can be transformed to if-else-if for code size optimization
    switch(number) {
        case 15:
            return 'F';
        break;
        case 14:
            return 'E';
        break;
        case 13:
            return 'D';
        break;
        case 12:
            return 'C';
        break;
        case 11:
            return 'B';
        break;
        case 10:
            return 'A';
        break;
        default:
            return number;
        break;
    }
}

int checkAbbas(char matrix[8][8], int i, int j, int abbaState) {
    // abbaState: 0 - first A, 1 - first B, 2 - second B, 3 - second A
    if(abbaState > 3) return 1; // If recursion found second A then it's a solution
    if(i < 0 || i >= 8 || j < 0 || j >= 8) return 0; // If recursion went out of bounds then no solution
    char searchChar;
    if(abbaState == 0 || abbaState == 3) searchChar = 'A';
    else searchChar = 'B';
    int result = 0;
    if(matrix[i][j] == searchChar || getHexFromInt(matrix[i][j]) == searchChar) { // If current cell is a required char
        if(abbaState == 0) { // If this char was first A
            result += checkAbbas(matrix, i, j+1, abbaState+1); // Right
            result += checkAbbas(matrix, i+1, j, abbaState+1); // Down
            result += checkAbbas(matrix, i-1, j, abbaState+1); // Top (No recursion because first B won't go to the top)
            result += checkAbbas(matrix, i, j-1, abbaState+1); // Left (No recursion because first B won't go to the top. On the left it will see A and ignore it)
        } else if(abbaState == 1 || abbaState == 2) { // If this char was first or second B
            result += checkAbbas(matrix, i, j+1, abbaState+1); // Right
            result += checkAbbas(matrix, i+1, j, abbaState+1); // Down
            if(abbaState == 2) { // When it's second B it's safe to move in any direction
                result += checkAbbas(matrix, i-1, j, abbaState+1); // Go to the top if it's second B (avoids repeats)
                result += checkAbbas(matrix, i, j-1, abbaState+1); // Go to the left if it's second B (avoids repeats)
            }
        } else if(abbaState == 3) return 1;
    }
    return result;
}

int abba(int mas[8]) {
    char matrix[8][8] = {'0'};
    for(int i = 0; i < 8; i++) { // Take each number from mas[]
        int current = mas[i];
        for(int j = 1; j < 9; j++) { // Get hex digits
            int digit = current >> (32 - (4 * j));
            int hexDigit = digit & 0xF;
            matrix[i][j-1] = hexDigit;
        }
    }

    // Matrix output
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(matrix[i][j] >= 10) printf("%c", getHexFromInt(matrix[i][j]));
            else printf("%d", matrix[i][j]);
        }
        printf("\n");
    }

    // Count ABBAs
    int abbas = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            abbas += checkAbbas(matrix, i, j, 0);
        }
    }
    return abbas;
}

int main(int argc, char *argv[]) {
    int sample1[8] ={-1413863686, -1146374827, -1162027246, -1442185216, 184549376, 11534336, 655360, 179026592};
    int sample2[8] ={-1430650880, -1157627904, 3145728, -1442185216, 184549376, 11534336, 655360, 3840};
    printf("Found %d ABBAs in the sample", abba(sample1));
    return 0;
}
