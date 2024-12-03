#include <stdio.h>
int w=3;
int *ciao = &w;
int main () {
    printf ("%d %p", *ciao, ciao);
}
