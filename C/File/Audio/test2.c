#include <windows.h>
#include <stdio.h>

int main() {
    char* filename = "test2.wav";
    printf ("Michele dopo molte lacrime riusci a fare questo, godetelo:");
    PlaySound (filename, NULL, SND_FILENAME | SND_SYNC);
    return 0;
}