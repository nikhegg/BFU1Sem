#include <stdio.h>

int Calc(char *statement) {
    char op;
    int n1, n2, res;
    if(statement[1] == '=') {
        res = -1;
        n1 = statement[2] - '0';
        n2 = statement[4] - '0';
        op = statement[3];
    } else {
        if(statement[0] == 'x') {
            n1 = -1;
            n2 = statement[2] -'0';
            res = statement[4] - '0';
        } else if(statement[2] == 'x') {
            n1 = statement[0] - '0';
            n2 = -1;
            res = statement[4] - '0';
        } else if(statement[4] == 'x') {
            n1 = statement[0] - '0';
            n2 = statement[2] - '0';
            res = -1;
        }
        op = statement[1];
    }
    switch(op) {
        case '+':
            if(res == -1) return n1 + n2;
            else if(n1 == -1) return res-n2;
            else if(n2 == -1) return res-n1;
        break;
        case '-':
            if(res == -1) return n1-n2;
            else if(n1 == -1) return res+n2;
            else if(n2 == -1) return n1-res;
        break;
        case '*':
            if(res == -1) return n1*n2;
            else if(n1 == -1) return res/n2;
            else if(n2 == -1) return res/n1;
        break;
        case '/':
            if(res == -1) return n1/n2;
            else if(n1 == -1) return res*n2;
            else if(n2 == -1) return n1/res;
        break;
        default:
            return -1;
        break;
    }
}

int main(int argc, char *argv[]) {
    char *expressions[] = {"2+x=5", "x+2=5", "x-5=2", "5-x=2", "x=5*2", "6/2=x", "6/x=2", "x/2=3", "1+x=1", "1+x=2", "2+1=x", "x=1+2", "x+1=2", "x/2=2", "x/1=4", "1/x=1", "4/2=x", "x/4=2", "1*x=1", "2*8=x", "x*4=8", "x*2=2", "x/3=3", "9-x=0", "6-6=x"};
    int len = sizeof(expressions)/sizeof(char *);
    for(int i = 0; i < len; i++) {
        int calc = Calc(expressions[i]);
        printf("%s x=%d\n", expressions[i], calc == -1 ? ("-") : (calc));
    }
    return 0;
}
