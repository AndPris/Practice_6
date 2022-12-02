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

void displayMatrix(short rows, short columns, float matrix[rows][columns], float members[]) {
    printf("\nYou have entered:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j <= columns; j++) {
            if(j == columns - 1) {
                printf("%gx%d = ", matrix[i][j], j+1);
            } else if (j == columns) {
                printf("%g\n", members[i]);
            }else {
                printf("%gx%d + ", matrix[i][j], j + 1);
            }
        }
    }
}

float det(short rows, short columns, float matrix[rows][columns]) {
    float determinant = 0;
    float temp[rows-1][columns-1];
    if (rows==1) {
        return matrix[0][0];
    }

    for(int i = 0; i < columns; i++) {
        for(int j = 1; j < rows; j++) {
            short shift = 0;
            for(int k = 0; k < columns; k++) {
                if(k != i) {
                    temp[j-1][k-shift] = matrix[j][k];
                } else {
                    shift = 1;
                }
            }
        }
      //  displayMatrix(rows-1, columns-1, temp);
        determinant += matrix[0][i]*pow((-1), i)*det(rows-1, columns-1, temp);
    }

    return determinant;
}

int main() {
    short equ, vars;
    float detCoefs;

    printf("Enter the number of equations:");
    inputPositive(&equ);
    printf("Enter the number of variables:");
    inputPositive(&vars);

    float coefs[equ][vars];
    float freem[equ];
    float roots[equ][vars];

    for(int i = 0; i < equ; i++) {
        for(int j = 0; j <= vars; j++) {
            if(j != vars) {
                printf("a%d%d=", i+1, j+1);
                noCharFloat(&coefs[i][j]);
            } else {
                printf("b%d=", i+1);
                noCharFloat(&freem[i]);
            }
        }
    }
    displayMatrix(equ, vars, coefs, freem);

    detCoefs = det(equ, vars, coefs);

    if (detCoefs==0) {
        printf("Impossible to calculate using Kramer's method!");
        return 0;
    }

    for(int i = 0; i < vars; i++) {
        for(int j = 0; j < equ; j++) {
            for(int k = 0; k < vars; k++) {
                if(k==i) {
                    roots[j][k] = freem[j];
                } else {
                    roots[j][k] = coefs[j][k];
                }
            }
        }

        printf("x%d = %g\n", i+1, det(equ, vars, roots) / detCoefs);
    }
    return 0;
}
