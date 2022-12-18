#include <stdio.h>
#include <math.h>
#define N 4

float traverse_clockwise(float coord[], int n) {
   float p = 0; // Result
   float vectors[50][3] = {0}; // Max 50 dots => max 50 vectors
   // Vars to find the center of our figure
   float xS = 0, yS = 0;
   float startX, startY; // Radius vector sample
   for(int i = 0; i < n*2; i+=2) { // We need all Xs and Ys together to find middle
       xS += coord[i];
       yS += coord[i+1];
   }
   // Finding center
   xS /= n; // Find average X by diving Xs sum to coord amount
   yS /= n; // Find average Y by diving Ys sum to coord amount
   // Get sample radius vector relatively to 1st coordinate
   startX = coord[0] - xS;
   startY = coord[1] - yS;
   vectors[0][0] = coord[0];
   vectors[0][1] = coord[1];
   for(int i = 2; i < n*2; i+= 2) { // Use radius vector sample to understand which are on the left side and which are on the right side
        vectors[i/2][0] = coord[i];
        vectors[i/2][1] = coord[i+1];
        vectors[i/2][2] = (
            ((coord[i+1] - yS) - (coord[i] - xS) * startY / startX) > 0 ? (180) : (0) // +180deg if it's on the right side of radius vector sample
        ) + acosf(
                (startX * (coord[i] - xS) + startY * (coord[i+1] - yS))
                * (sqrt((powf((coord[i] - xS), 2) + powf((coord[i+1] - yS), 2)))
                / sqrtf((powf(startX, 2) + powf(startY, 2))))
        ) * (180/3.14);// Count vectors multiplication via (vect(a), vect(b))
   }
   for(int i = 0; i < n-1; i++) { // Sort the dots
        for(int j = i+1; j < n; j++) {
            if(vectors[j][0] <= vectors[i][0]) {
                float cX = vectors[i][0];
                float cY = vectors[i][1];
                float cA = vectors[i][2];
                vectors[i][0] = vectors[j][0];
                vectors[i][1] = vectors[j][1];
                vectors[i][2] = vectors[j][2];
                vectors[j][0] = cX;
                vectors[j][1] = cY;
                vectors[j][2] = cA;
            }
        }
   }
   for(int i = 0; i < n-1; i++) p += sqrtf(powf(vectors[i+1][0] - vectors[i][0], 2) + powf(vectors[i+1][1] - vectors[i][1], 2)); // vectLen = sqrt(x^2 + y^2)
   p += sqrtf(powf(vectors[0][0] - vectors[n-1][0], 2) + powf(vectors[0][1] - vectors[n-1][1], 2)); // Count "edge" vectors (0 and n-1)
   return p;
}

int main(int argc, char *argv[]) {
    float rect[] = {1,5,7,1,7,5,1,1};
    float star[] = {3.97,0.82, 2.26, 3.69, 5.39, 2.16, 2.03, 2.11,5.36,4.06};
    float enneagon[] ={76, 67.1, -8.3, 18, 55, 93.3, 77, 33, 21.3, 99, -20, 50, -8.3, 82, 55, 6.7,  21.3, 0.76};
    float result = traverse_clockwise(rect, N);
    printf("Perimeter is %f", result);
    return 0;
}
