#include <stdio.h>

int main() {

    int n = 0, i = 0;
    scanf("%d", &n);

    for(i = 1; i*i <= n; i++) printf("%d ", i*i);
    printf("\n");

    return 0;
}