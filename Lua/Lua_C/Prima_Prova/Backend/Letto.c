#include <stdio.h>

__declspec(dllexport) int somma(int a, int b) {
    return a + b;
}