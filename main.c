#include <stdio.h>
#include <math.h>
#include <malloc.h>

void noCharShort(short *var) { //checking for characters
    char cond, ch;
    do {
        cond = 0;
        scanf("%hd%c", var, &ch);

        if(ch != '\n') {
            printf("Invalid data\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);

}

void noCharFloat(float *var) { //checking for characters
    char cond, ch;
    do {
        cond = 0;
        scanf("%f%c", var, &ch);

        if(ch != '\n') {
            printf("Invalid data\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);

}

void inputPositive(short *variable) { // check for positive value
    char cond;
    do {
        cond = 0;
        noCharShort(variable);
        if((*variable) <= 0) {
            printf("Number should be higher than 0\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);
}

void displayMatrix(short n, float **matrix, float *members) {
    printf("\nYou have entered:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j <= n; j++) {
            if(j == n - 1) {
                printf("%gx%d = ", matrix[i][j], j+1);
            } else if (j == n) {
                printf("%g\n", members[i]);
            }else {
                printf("%gx%d + ", matrix[i][j], j + 1);
            }
        }
    }
}

int main() {
    short size, e;
    float **a, *b, *x, *xp, *delta, prop;

    printf("Enter the size of SLAR:");
    inputPositive(&size);
    printf("Enter precision:");
    inputPositive(&e);

    a = (float **) malloc(size * sizeof(float*));
    if(a==NULL) {
        printf("Impossible to allocate memory");
        return 0;
    }
    for(int i = 0; i < size; i++) {
        a[i] = (float*) malloc(size * sizeof(float));
        if(a[i]==NULL) {
            printf("Impossible to allocate memory");
            return 0;
        }
    }
    b = (float*) malloc(size * sizeof(float));
    if(b==NULL) {
        printf("Impossible to allocate memory");
        return 0;
    }
    x = (float*) malloc(size * sizeof(float));
    if(x==NULL) {
        printf("Impossible to allocate memory");
        return 0;
    }
    xp = (float*) malloc(size * sizeof(float));
    if(xp==NULL) {
        printf("Impossible to allocate memory");
        return 0;
    }
    delta = (float*) malloc(size * sizeof(float));
    if(delta==NULL) {
        printf("Impossible to allocate memory");
        return 0;
    }

    for(int i = 0; i < size; i++) {
        short cond;
        float sum;
        do {
            cond = 0;
            sum = 0;
            for(int j = 0; j < size; j++) {
                printf("a%d%d=", i+1, j+1);
                noCharFloat(&a[i][j]);
                if(i!=j) sum += a[i][j];
            }

            if(fabs(a[i][i]) <= fabs(sum) ) {
                cond = 1;
                printf("\n|a[%d][%d]| must be higher than absolute value of the sum of the other coefficients!\n", i+1, i+1);
                fflush(stdin);
            }
        } while (cond);

        printf("b%d=", i+1);
        noCharFloat(&b[i]);

        xp[i] = b[i]/a[i][i];
    }

    displayMatrix(size, a, b);

     do {
         prop = 0;
        for(int i = 0; i < size; i++) {
            float d = 0;
            for(int j = 0; j < size; j++) {
                if(i==j) continue;
                 d += a[i][j] * xp[j];
            }

            x[i] = (b[i] - d)/a[i][i];
            delta[i] = fabs(x[i] - xp[i]);
            xp[i] = x[i];
        }

        for(int i = 0; i < size; i++) {
            if(prop < delta[i]) prop = delta[i];
        }
    } while(prop >= (1.0 / pow(10, e)));

    for(int i = 0; i < size; i++) {
        printf("x%d = %.*f\n", i+1, e, x[i]);
    }

    for(int i = 0; i < size; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(x);
    free(xp);
    free(delta);
    return 0;
}
