#include <stdio.h>
#include <math.h>

void noCharInt(short *var) { //checking for characters
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
        noCharInt(variable);
        if((*variable) <= 0) {
            printf("Number should be higher than 0\n");
            cond = 1;
            fflush(stdin);
        }
    } while(cond);
}

void displayMatrix(short rows,float matrix[rows][rows], float members[]) {
    printf("\nYou have entered:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j <= rows; j++) {
            if(j == rows - 1) {
                printf("%gx%d = ", matrix[i][j], j+1);
            } else if (j == rows) {
                printf("%g\n", members[i]);
            }else {
                printf("%gx%d + ", matrix[i][j], j + 1);
            }
        }
    }
}

float det(short rows, float matrix[rows][rows]) {
    float determinant = 0;
    float temp[rows-1][rows-1];
    if (rows==1) {
        return matrix[0][0];
    }

    for(int i = 0; i < rows; i++) {
        for(int j = 1; j < rows; j++) {
            short shift = 0;
            for(int k = 0; k < rows; k++) {
                if(k != i) {
                    temp[j-1][k-shift] = matrix[j][k];
                } else {
                    shift = 1;
                }
            }
        }
        determinant += matrix[0][i]*pow((-1), i)*det(rows-1,temp);
    }

    return determinant;
}

int main() {
    short size;
    float detCoefs;

    printf("Enter the size of SLAR:");
    inputPositive(&size);

    float coefs[size][size];
    float freem[size];
    float roots[size][size];

    for(int i = 0; i < size; i++) {
        for(int j = 0; j <= size; j++) {
            if(j != size) {
                printf("a%d%d=", i+1, j+1);
                noCharFloat(&coefs[i][j]);
            } else {
                printf("b%d=", i+1);
                noCharFloat(&freem[i]);
            }
        }
    }
    displayMatrix(size, coefs, freem);

    detCoefs = det(size, coefs);

    if (detCoefs==0) {
        printf("Impossible to calculate using Kramer's method!");
        return 0;
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            for(int k = 0; k < size; k++) {
                if(k==i) {
                    roots[j][k] = freem[j];
                } else {
                    roots[j][k] = coefs[j][k];
                }
            }
        }

        printf("x%d = %g\n", i+1, det(size, roots) / detCoefs);
    }
    return 0;
}
