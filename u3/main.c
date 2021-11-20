/* 
    Liudas Kasperavičius
 */

 /* 
    Apie procesą: Klausimų proceso eigoje beveik nekilo, buvo įdomi puts funkcijos panaudojimo galimybė. neaiški situacija buvo, kai įvesties failas gale turi tuščių eilučių - feof identifikatorius tokiu atveju veikia kitaip, nei kai tuščių eilučių nėra. Taigi, teko parašyti savo funkciją isFileReadFinished, kuri tiesiogiai lygina failo deskriptorius (end pointer ir read pointer). Testavimui (ypač daliai apie tarpų invariantą) naudojau linux komandų seką:  cat ./read | grep ' ' -o | wc -l && cat ./out | grep ' ' -o | wc -l
  */

#include <stdio.h>
#include <stdlib.h>

char isLetter(char a) {
    return a != ' ' && a != '\n' && a != 0;
}

void printBuffer(char *buffer, FILE *f) {
    int i;
    for(i = 0; buffer[i] != 0; ++i)
        if(buffer[i] != -1)
            fputc(buffer[i], f);
}

void flagWord(char *buffer, int wordLength) {
    int i;
    for(i = 0; i < wordLength; ++i)
        buffer[i] = -1;
}

void getFileNamesByCommandLine(int argc, char **argv, FILE **in, FILE **out) {
    if(argc == 3) {
        if(!(*in = fopen(argv[1], "r")) ) {
            printf("Cannot open the input file. Check if it exists and has read permissions. Exiting.\n");
            exit(1);
        }

        if(!(*out = fopen(argv[2], "w")) ) {
            printf("Cannot create or open the output file. Exiting.\n");
            exit(1);
        }
    }
    else {
        printf("No input/output file provided.\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    FILE *input, *output;
    char buffer[256], ignoreBuffer[256];
    int wordLength;
    int i;

    getFileNamesByCommandLine(argc, argv, &input, &output);

    while(!feof(input)) {

        if(fgets(buffer, 255, input) == NULL)
            break;

        for(i = 0; buffer[i] != 0; ++i) {

            if(!isLetter(buffer[i])) 
                continue;

            else {
                sscanf(buffer+i, "%s%n", ignoreBuffer, &wordLength);

                if(wordLength % 2)
                    flagWord(buffer+i, wordLength);
                
                i += wordLength - 1;
            }
        }
        
        printBuffer(buffer, output);

    }

    printf("Output has been written to specified destination. Goodbye!\n");


    fclose(input);
    fclose(output);

    return 0;
}
/* 
 10. Parašyti funkciją, kuri iš duoto teksto išmeta žodžius, sudarytus iš nelyginio simbolių skaičiaus (tarpų skaičius turi likti nepakitęs).

 cat ./read | grep ' ' -o | wc -l && cat ./out | grep ' ' -o | wc -l  */