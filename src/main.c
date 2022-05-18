#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

// Alterar ficheiros incluídos
#include <stdio.h>

int main() {
#ifdef _WIN32
    _setmode(1, _O_BINARY);
#endif
    // Alterar a partir desta linha.
    printf("Template para projeto de Programação e Algoritmos.\n");
    return 0;
}
