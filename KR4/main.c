#include <stdio.h>

double polynom(char *expr, double x) {
    int x0k = 0, x1k = 0, x2k = 0, x3k = 0, x4k = 0;
    int buffer = 0;
    int signFlag = 1; // 1 - plus, -1 - minus
    int hadX = 0; // 0 - false, 1 - true
    for(int i = 0; expr[i] != 0; i++) {
        char s = expr[i];
        if(s == '+' || s == '-') { // If current char is + or -
            // If before this + we had no X then save it to x0k
            if(hadX == 0) { // If previous number has no X
                x0k = buffer * signFlag;
                buffer = 0;
            }
            signFlag = (s == '-' ? (-1) : (1)); // If - then flag=-1 else flag=1
        } else if(s == 'x') { // When reached X
            if(buffer == 0) buffer = 1; // If buffer haven't collected anything then it's 1
            if(expr[i+1] == '^') { // Next symbol is pow()
                i += 2; // Skip ^ char
                s = expr[i];
                if(s == '2') x2k = buffer * signFlag;
                else if(s == '3') x3k = buffer * signFlag;
                else if(s == '4') x4k = buffer * signFlag;
            } else /* then it's pow(x, 1)*/ x1k = buffer * signFlag; // Don't need to skip symbols cause we'll have +, - or space after
            buffer = 0;
            hadX = 1;
        } else if(s >= '0' && s <= '9') { // Read only numbers
            hadX = 0; // If we're reading a number then previous symbol was number/+/-/space
            buffer = buffer * 10 + (s - '0');
        }
    }
    if(buffer != 0) x0k = buffer * signFlag;
    return x4k*(x*x*x*x) + x3k*(x*x*x) + x2k*(x*x) + x1k*x + x0k;
}

int main() {
    char *expr = "-2 + x - 3*x^2 +x^4 +5*x^3";
    double x = 3.14;
    printf("y(%f)=%s returns %f", x, expr, polynom(expr, x));
    return 0;
}
