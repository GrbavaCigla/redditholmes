#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int find(char *text, char *to_find) {
    int index = 0;
    int result = -1;
    int temp_res = -1;
    int text_len = strlen(text);
    int find_len = strlen(to_find);

    for (int i = 0; i < text_len; i++) {
        if (tolower(to_find[index]) == tolower(text[i])) {
            index++;
            if (temp_res == -1) {
                temp_res = i;
            }
            if (index == find_len) {
                result = temp_res;
            }
        } else if (temp_res != -1) {
            temp_res = -1;
            index = 0;
        }
    }
    return result;
}

int main() {
    int bla = find(":flag-gb: United Kingdom", "United Kingdom");
    printf("%d", bla);

    return 0;
}