/* 
    This program was created by Liudas Kasperavičius, a VU PS 1st course student.
    Lecturers: Irmantas Radavičius, Linas Litvinas
    Part of the 2nd homework task, variant 2
    Note: this program was written before learning about dynamic memory, therefore there is a fixed array size limitation.
 */

 /* 
    Apie procesą: kilo klausimas, ką daryti su pasikartojančiais maksimumais / minimumais; nusprendžiau tokius pasikartojančius max/min įtraukti į matricos balno taško apibrėžimą. Sukurti ir parašyti patį algoritmą užtrukau apie valandą, tačiau vėliau aprašyti UI, validation'ą, refactor'inti kintamųjų vardus užtruko žymiai ilgiau, nei tikėjausi. Po to, testuodamas programą supratau, kad žymiai patogiau būtų tiesiog išvesi originalią matricą, kurioje balno taškai būtų kažkaip pažymėti, tad pridėjau ir šią dalį. Visko komentavimas ir dokumentavimas taip pat užtruko. Apytiksliai šiam darbui skyriau 4 valandas. Galiausiai testuojant atsirado "buffer overflow" (bent jau taip manau) problema, kurią teko spręsti naudojant 'm' scanf flag'ą, nors kompiliatorius dėl to ir truputį pyksta (warning message: ISO C does not support that flag).
  */

/* -------- Libraries -------- */
#include <stdio.h>

/* -------- Definitions -------- */

#define CAP                 1000
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* -------- UI Messages -------- */

#define MSG_NOT_A_NUMBER        "Your input was not a number."
#define MSG_NUMBER_TOO_LARGE    "Your input was too large."
#define MSG_NUMBER_TOO_SMALL    "Your input was too small."
#define MSG_ROW_IGNORED         "Entire row ignored."
#define MSG_TRY_AGAIN           "Please try again."
#define MSG_DESC                "This program will find all saddle points of a given square matrix whose dimensions are less than or equal to "
#define MSG_WARN                "Attention! This program can detect multiple saddle points in the same row/column. Therefore, in the case of a 2D plane, all points will be reported as saddle points. You are also expected to use the standart matrix notation, so in the event of an invalid character, the entire row of the matrix will be discarded to avoid alignment confusion."
#define MSG_OUTPUT              "Upon entering the matrix, the program will print all saddle points in RC (Row Column) form as well as print the original matrix with the saddle points highlighted. "
#define MSG_CRITICAL            "We have encountered a critical error. All information about the matrix is cleared. Please retry inputing the matrix."


/* -------- UI. Input and validation -------- */

/* 
    * handleInput: 
    This is the main UI function. It handles validation and input.
    @param *n the degree of the matrix
    @param matrix[CAP][CAP] a fixed size matrix
 */
void handleInput(int *n, int matrix[CAP][CAP]) {

    int i, j;
    char *c;
    i = j = 0;

    printf("Enter the size of a square matrix less than or equal to %d and hit ENTER: ", CAP);
    
    /* 
        A label is used instead of a wrap-around while loop. 
        It is also used because further code handles validation.
        If validation fails at any point, the code returns to the beginning of the validation.
        Therefore no confusing and unpredictable jumps occur here.
     */

    beginInput:

    while(scanf("%9d%m[^\n\t ]", n, &c) != 1)  {
        /* 
            If a number has more than 9 digits, it goes outside the bounds of a typical int and therefore is no longer considered a valid number.
         */
        printf("%s %s\n", MSG_NOT_A_NUMBER, MSG_TRY_AGAIN);
        scanf("%*[^\n]");
    }


    if(*n > CAP) {
        /* We cannot exceed the fixed bounds of the array */
        printf("%s %s\n", MSG_NUMBER_TOO_LARGE, MSG_TRY_AGAIN);
        goto beginInput;
    }
    else if(*n < 2) {
        /* A matrix of degree 1 has only one element and it is therefore it is impossible to determine weather a given point is a saddle point. */
        printf("%s %s\n", MSG_NUMBER_TOO_SMALL, MSG_TRY_AGAIN);
        goto beginInput;
    }

/* -------- Matrix degree validation passed -------- */

    printf("Okay, now enter the %d * %d matrix: \n", *n, *n);

    for(i = 0; i < *n; ++i) {
        for(j = 0; j < *n; ++j) {
            while(scanf("%9d%m[^\n\t ]", &matrix[i][j], &c) != 1) {
                /* 
                    !scanf possible buffer overflow? Fix - using assignment-allocation character 'm'. Not part of C ISO standart
                 */

                /* The user is expected to use standart matrix notation, therefore if an error is made, the entire row is negated in an attempt to alleviate confusion. */

                /* 
                printf("DEBUG: %d\n", i);
                 */
                printf("%s %s %s\n", MSG_NOT_A_NUMBER, MSG_ROW_IGNORED, MSG_TRY_AGAIN);
                scanf("%*[^\n]");
                j = 0;
            }
        }
    }
    
/* -------- Input complete -------- */

}


/* -------- Main Logic -------- */
/* 
    All helper functions are self-descriptive. Functions with prefix 'is' and return type of 'char' are used as boolean functions.
 */
char isMaxInRow(int matrix[CAP][CAP], int element, int rowNum, int dimension) {
    int i;
    int max = matrix[rowNum][0];

    for(i = 1; i < dimension; ++i)
        max = (max < matrix[rowNum][i] ? matrix[rowNum][i] : max);
    
    return max == element;
}

char isMinInRow(int matrix[CAP][CAP], int element, int rowNum, int dimension) {
    int i;
    int min = matrix[rowNum][0];

    for(i = 1; i < dimension; ++i)
        min = (min > matrix[rowNum][i] ? matrix[rowNum][i] : min);
    
    return min == element;
}

char isMaxInCol(int matrix[CAP][CAP], int element, int colNum, int dimension) {
    int i;
    int max = matrix[0][colNum];

    for(i = 1; i < dimension; ++i)
        max = (max < matrix[i][colNum] ? matrix[i][colNum] : max);
    
    return max == element;
}

char isMinInCol(int matrix[CAP][CAP], int element, int colNum, int dimension) {
    int i;
    int min = matrix[0][colNum];

    for(i = 1; i < dimension; ++i)
        min = (min > matrix[i][colNum] ? matrix[i][colNum] : min);
    
    return min == element;
}

void printCoords(int matrix_row, int matrix_col) {
    
    printf("Saddle point: R%d C%d\n", matrix_row+1, matrix_col+1);

}

char isPrinted(int **printed, int *element, int printedSize) {
    int **it;
    for(it = printed; it < printed + printedSize; ++it) {
        if(element == *it) return 1;
    }

    return 0;
}

int main() {

/* -------- Declare/Initialize variables -------- */
    int dimension = 0;
    int i, j; 
    int matrix[CAP][CAP];
    int *printed[CAP];
    int printedSize = 0;

/* -------- Input and logic -------- */

    printf("%s%d\n", MSG_DESC, CAP);
    printf("%s\n", MSG_OUTPUT);
    printf("\n%s\n\n", MSG_WARN);

    handleInput(&dimension, matrix);


    for(i = 0; i < dimension; ++i) {
        for(j = 0; j < dimension; ++j) {
            if(isMaxInRow(matrix, matrix[i][j], i, dimension) && isMinInCol(matrix, matrix[i][j], j, dimension)) {
                printCoords(i, j);
                printed[printedSize++] = &matrix[i][j];
                continue;
            }


            if(isMinInRow(matrix, matrix[i][j], i, dimension) && isMaxInCol(matrix, matrix[i][j], j, dimension)) {
                printCoords(i, j);
                printed[printedSize++] = &matrix[i][j];
            }
        }
    }

    /* 
        Check if any saddle points were printed
     */

    if(printedSize == 0) {
        printf("No saddle points found!\n");
        return 0;
    }
    /* 
        Print original matrix with saddle point highlighting
     */

    for(i = 0; i < dimension; ++i){
        for(j = 0; j < dimension; ++j) {
            if(isPrinted(printed, &matrix[i][j], printedSize))
                printf(ANSI_COLOR_RED);
            printf("% 9d " ANSI_COLOR_RESET, matrix[i][j]);
        }
        printf("\n\n");    
    }

    
    return 0;

}