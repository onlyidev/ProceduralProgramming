/* 
    This program was created by Liudas Kasperavičius, a VU PS 1st course student.
    Lecturers: Irmantas Radavičius, Linas Litvinas
    Part of the 2nd homework task, variant 2
    Note: this program was written before learning about dynamic memory, therefore there is a fixed array size limitation.
 */

 /* 
    Apie procesą: kilo klausimas, ką daryti su pasikartojančiais maksimumais / minimumais; nusprendžiau tokius pasikartojančius max/min įtraukti į matricos balno taško apibrėžimą. Sukurti ir parašyti patį algoritmą užtrukau 2-3 valandas, tačiau vėliau aprašyti UI, validation'ą, refactor'inti kintamųjų vardus užtruko žymiai ilgiau, nei tikėjausi. Po to, testuodamas programą supratau, kad žymiai patogiau būtų tiesiog išvesi originalią matricą, kurioje balno taškai būtų kažkaip pažymėti, tad pridėjau ir šią dalį. Visko komentavimas ir dokumentavimas taip pat užtruko. Apytiksliai šiam darbui skyriau 5-6 valandas. Galiausiai testuojant atsirado "buffer overflow" (bent jau taip manau) problema, kurią teko spręsti naudojant 'm' scanf flag'ą, nors kompiliatorius dėl to ir truputį pyksta (warning message: ISO C does not support that flag).
  */

/* -------- Libraries -------- */
#include <stdio.h>
#include <limits.h>

/* -------- Definitions -------- */

#define CAP                 1000
#define INF                 INT_MAX
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* -------- Messages -------- */

#define MSG_NOT_A_NUMBER        "Your input was not a number."
#define MSG_NUMBER_TOO_LARGE    "Your input was too large."
#define MSG_NUMBER_TOO_SMALL    "Your input was too small."
#define MSG_ROW_IGNORED         "Entire row ignored."
#define MSG_TRY_AGAIN           "Please try again."
#define MSG_DESC                "This program will find all saddle points of a given square matrix whose dimensions are less than or equal to "
#define MSG_WARN                "Attention! This program can detect multiple saddle points in the same row/column. Therefore, in the case of a 2D plane, all points will be reported as saddle points. You are also expected to use the standart matrix notation, so in the event of an invalid character, the entire row of the matrix will be discarded to avoid alignment confusion."
#define MSG_OUTPUT              "Upon entering the matrix, the program will print all saddle points in RC (Row Column) form as well as print the original matrix with the saddle points highlighted. "
#define MSG_CRITICAL            "We have encountered a critical error. All information about the matrix is cleared. Please retry inputing the matrix."

/* -------- Custom structures -------- */

struct _PointerArray {

    /* A pointer array structure stores an array of pointers and it's effective size in one place.
        Array of pointers will be used to store the possible saddle points for easier coordinate calculation.
     */

    int size;
    int *arr[CAP];
} _PointerArray_def = {0};

struct _MinMax {

    /* The min/max structure holds both the minimum and the maximum in one place. Will be used to characterize a column or a row of a matrix. */

    int max;
    int min;
} _MinMax_def = {-INF, INF};

/* Type definitions for syntactic sugar */

typedef struct _MinMax MinMax;
typedef struct _PointerArray PointerArray;

/* -------- Helper functions -------- */

/* 
    * maxNumberInArray: 

    Finds maximum number in an array of integers

    @param *arr One-dimensional array in which the search will take place
    @param size The effective size of a one-dimensional array
 */
int maxNumberInArray(int *arr, int size) {
    int i, max = -INF;
    for(i = 0; i < size; ++i) /* Iterate through entire array and search for a maximum */
        max = (max < arr[i] ? arr[i] : max);
    return max;
}

/* 
    * minNumberInArray: 

    Finds minimum number in an array of integers

    @param *arr One-dimensional array in which the search will take place
    @param size The effective size of a one-dimensional array
 */
int minNumberInArray(int *arr, int size) {
    int i, min = INF;
    for(i = 0; i < size; ++i) /* Iteratre through entire array and searcg for a minimum */
        min = (min > arr[i] ? arr[i] : min);
    return min;
}

/* 
    * removeFromPointerArray:  
    ! Deprecated 
    Removes an element from a PointerArray type array at a given index
    Uses a basic removal algorithm

    @param *arr A pointer to a PointerArray type variable
    @param index Index of the element to be removed
 */
void removeFromPointerArray(PointerArray *arr, int index) {
    
    /* *arr is a pointer to a structer, thus the pointer syntax (->) is used. */

    for(;index < arr->size-1; ++index)
        arr->arr[index] = arr->arr[index+1];

    --arr->size;
}

/* 
    * isPrinted: 
    Returns 0 or 1 depending on weather the element is found in the PointerArray
    Used in the last stage of printing saddle points to avoid repeats (the case of a plane)

    @param arr The PointerArray of already printed elements
    @param *element Element of the main matrix
 */
char isPrinted(PointerArray arr, int *element) {
    int i;

    for(i = 0; i < arr.size; ++i)
        if(arr.arr[i] == element)
            return 1;
    return 0;
}


/* 
    * outputCoordinates: 
    Outputs the coordinates of a given pointer in a given array in Row Column form.
    @param *pointer pointer to the element of the *mainArr
    @param *mainArr the array at which the *pointer lives
 */
void outputCordinates(int *pointer, int *mainArr) {
    /* Pointer arythmetic is used to get the offset */
    int offset = pointer - mainArr;
    printf("Saddle point: (R%d; C%d)\n", offset / CAP + 1, (int) (offset % CAP) + 1);
}

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



int main() {

/* -------- Declare/Initialize variables -------- */
    int dimension = 0;
    int i, j; 
    int matrix[CAP][CAP];
    PointerArray minInRow, maxInRow, minInCol, maxInCol, printed;
    MinMax currRowExtremums = _MinMax_def, colExtremums[CAP];

    minInRow = maxInRow = minInCol = maxInCol = printed = _PointerArray_def;

/* -------- Input and logic -------- */

    printf("%s%d\n", MSG_DESC, CAP);
    printf("%s\n", MSG_OUTPUT);
    printf("\n%s\n\n", MSG_WARN);

    handleInput(&dimension, matrix);

    for(i = 0; i < dimension; ++i) {
        /* This loop finds the minimum and maximum VALUES of individual rows and columns. */
        currRowExtremums.max = maxNumberInArray(matrix[i], dimension);
        currRowExtremums.min = minNumberInArray(matrix[i], dimension);
        
        for(j = 0; j < dimension; ++j) { /* Columns require a special loop, because they are not themselves an array */
            if(i == 0) colExtremums[j] = _MinMax_def;

            /* Next two lines save the pointer to an element if it is a maximum or mimium in it's row */
            if(matrix[i][j] == currRowExtremums.min) minInRow.arr[minInRow.size++] = &matrix[i][j];
            if(matrix[i][j] == currRowExtremums.max) maxInRow.arr[maxInRow.size++] = &matrix[i][j];

            colExtremums[j].max = (colExtremums[j].max < matrix[i][j] ? matrix[i][j] : colExtremums[j].max);
            colExtremums[j].min = (colExtremums[j].min > matrix[i][j] ? matrix[i][j] : colExtremums[j].min);
        }

    }

    /* Next loop saves a pointer to an element if it is a maximum or a minimum in it's column */

    for(i = 0; i < dimension; ++i)
        for(j = 0; j < dimension; ++j) {
            if(matrix[j][i] == colExtremums[i].min) minInCol.arr[minInCol.size++] = &matrix[j][i];
            if(matrix[j][i] == colExtremums[i].max) maxInCol.arr[maxInCol.size++] = &matrix[j][i];
        }
    
    /* Next we have two cases where a saddle point could be discovered: 
        1) maximum in row and minimum in column
        2) maximum in column and minimum in row

        Since we saved pointers and each element has a unique address, if it is a saddle we can cross-reference it.
     */

    for(i = 0; i < minInRow.size; ++i) {
        for(j = 0; j < maxInCol.size; ++j){
            if(minInRow.arr[i] == maxInCol.arr[j]) {
                outputCordinates(minInRow.arr[i],(int*) matrix);
                printed.arr[printed.size++] = minInRow.arr[i];
                
                break;
                /* removeFromPointerArray(&Col, j);
                --j; */
            }
        }
    }

    for(i = 0; i < minInCol.size; ++i) {
        for(j = 0; j < maxInRow.size; ++j){
            if(minInCol.arr[i] == maxInRow.arr[j]) {
                if(!isPrinted(printed, minInCol.arr[i])){
                    outputCordinates(minInCol.arr[i], (int*) matrix);
                    printed.arr[printed.size++] = minInCol.arr[i];    
                }
                break;
                /* removeFromPointerArray(&Row, j);
                --j; */
            }
        }
    }

    /* 
        Print original matrix with saddle point highlighting
     */

    if(printed.size == 0) {
        printf("No saddle points found!\n");
        return 0;
    }

    for(i = 0; i < dimension; ++i){
        for(j = 0; j < dimension; ++j) {
            if(isPrinted(printed, &matrix[i][j]))
                printf(ANSI_COLOR_RED);
            printf("% 9d " ANSI_COLOR_RESET, matrix[i][j]);
        }
        printf("\n\n");    
    }

    
    return 0;

}