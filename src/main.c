#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

#include "views/cli.h"

int main() {
#ifdef _WIN32
    _setmode(1, _O_BINARY);
#endif
    cli();
    return 0;
}
