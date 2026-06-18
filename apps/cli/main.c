#include <stdio.h>

int main(void) {
    const char *lang = "C";
    printf("Hello and welcome to %s!\n", lang);

    for (int i = 1; i <= 5; i++) {
        printf("i = %d\n", i);
    }

    return 0;
}
