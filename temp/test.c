#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// gotoStmt: 'label' '{' 'if' '(' optExpr ')' stmt optExpr 'goto label ' ';' {$$ = }

char* mergeStr(char* s, int n) {
    int originalLen = strlen(s);
    int numLen = snprintf(NULL, 0, "%d", n);
    int newLen = originalLen + numLen + 1;
    char* newString = (char*) malloc(newLen * sizeof(char));
    sprintf(newString, "%s %d", s, n);
    return newString;
}

int main() {
    char* original = "algo";
    int num = 0;

    char* ptr = mergeStr(original, num);
    printf("%s\n", original);
    printf("%s\n", ptr);

    return 0;
}
