#include <stdio.h>

int findSum(int n);

int main() {   
     /*Skaičius iš ekrano*/
    int n;
   
    printf("n: ");  
    
     /*gauname skaičių n*/
    scanf("%d", &n);

    /*spausdiname funkcijos rezultatą, po jo - new line*/
    printf("%d\n", findSum(n)); 
    
    return 0;
}

     /*randame skaičių kvadratų sumą*/
int findSum(int n) {
    int sum = 0;
     /*c89*/
    int i = 1;
    for(i = 1; i <= n; i++)
    {
        sum += i*i;
    }
     /*grąžiname per vardą*/
    return sum;

}
