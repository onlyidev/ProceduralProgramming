/*
Pirmoji idėja ir pirmasis "draft" buvo naudoti rekursiją, tačiau parašęs šią versiją supratau, kad tai nėra optimalu, kadangi naudajma daugiau atminties nei reikia (saugomi visi sekos nariai). Dėl to papildomos įvesties funkcijos atsisakiau ir viską aprašiau main funkcijoje. Programos naudojama atmintis - konstanta, o algoritmo sudėtingumas O(N). 
*/
#include <stdio.h>

int main() {
    int counter = 0, sum = 0, prev = 0, curr = 0, result; /*saugosime kiek skaičių sekoje turime bei jų sumą. Taip pat dabartinį ir prieš tai sekoje einančius skaičius. Vios sekos saugoti nereikia.*/

    printf("Įveskite skaičių seką, kiekvieną narį rašydami iš naujos eilutės:\n");


    for(;curr >= prev || counter < 2; ++counter) { /* Kol seka nemažėja arba turi mažiau nei 2 skaičius*/

        prev = curr;
        result = scanf("%d", &curr);

        if(getc(stdin) != '\n' || !result) { /*Input validation*/
            printf("Klaida. Jūsų paskutinė įvestis ignoruota, nes eilutėje buvo: 1) Daugiau negu vienas skaičius atskirtas tarpu; arba 2) Simbolis, kuris nėra skaičius; arba 3) Skaičius, nepriklausantis sveikųjų skaičių aibei.\n");


            /*Return to previous state*/
            --counter;
            curr=prev;

            while(getc(stdin) != '\n') 
                ;

            continue;
        } 

        sum += curr;
    }

    sum -= curr;
    --counter;

    printf("Sekos narių skaičius: %d,\n", counter); /*Pagal sąlygą, turime atspausdinti kiek seka turi narių (paskutinį narį, n, kuris mažesnis už narį n-1 taip pat laikome sekos nariu)*/

    printf("Jos aritmetinis vidurkis: %.3f\n", (double) sum/counter); /*Vidurkį pateikiame kaip realųjį skaičių*/

    return 0;

}
