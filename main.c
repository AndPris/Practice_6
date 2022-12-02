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

void displayMatrix(short rows, short columns, float matrix[rows][columns]) {
    printf("\nYou have entered:\n");
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j <= columns; j++) {
            if(j == columns - 1) {
                printf("%gx%d%d = ", matrix[i][j], i+1, j+1);
            } else if (j == columns) {
                //printf("%g\n", members[i]);
            }else {
                printf("%gx%d%d + ", matrix[i][j], i + 1, j + 1);
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
        short shift = 0;
        for(int j = 1; j < rows; j++) {
            for(int k = 0; k < columns; k++) {
                if(k != i) {
                    temp[j-1][k-shift] = matrix[j][k];
                } else {
                    shift = 1;
                }
            }
        }
        displayMatrix(rows-1, columns-1, temp);
        determinant += matrix[0][i]*pow((-1), i)*det(rows-1, columns-1, temp);
        printf("det: %f\n", determinant);
    }

    return determinant;
}

int main() {
    short equ, vars;

    printf("Enter the number of equations:");
    inputPositive(&equ);
    printf("Enter the number of variables:");
    inputPositive(&vars);

    float coefs[equ][vars];
    float freem[equ];

    for(int i = 0; i < equ; i++) {
        for(int j = 0; j <= vars; j++) {
            if(j != vars) {
                printf("a%d%d=", i+1, j+1);
                noCharFloat(&coefs[i][j]);
            } else {
                printf("b%d%d=", i+1, j+1);
                noCharFloat(&freem[i]);
            }
        }
    }
    //displayMatrix(equ, vars, coefs, freem);
    printf("\ndet:  %g", det(equ, vars, coefs));
    return 0;
}
