#include "bison-tree.h"

int main(void){

    DT* n1 = createTree("filhoa", 0);
    DT* n2 = createTree("filhob", 0);
    DT* n3 = createTree("filhoc", 0);

    DT* n00 = createTree("a", 0);
    DT* n01 = createTree("ab", 3, n1, n2, n3);
    DT* n02 = createTree("abc", 0);

    DT* n10 = createTree("abcd", 3, n00, n01, n02);

    DT* n03 = createTree("t", 0);
    DT* n04 = createTree("tf", 0);
    DT* n05 = createTree("tft", 0);

    DT* n11 = createTree("tfty", 3, n03, n04, n05);

    DT* n20 = createTree("King", 2, n10, n11);

    printTree(n20);

    return 0;
}