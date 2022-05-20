#include <aio.h>
#include <string.h>

#include "str_utils.h"

void replace_char(char* str, char char_to_replace, char replacement) {
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] == char_to_replace) {
            str[i] = replacement;
        }
    }
}
