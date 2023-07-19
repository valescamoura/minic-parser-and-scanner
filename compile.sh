echo '===> Compiling...'
flex -o lexer.c src/scanner.l
bison -d src/parser.y
gcc -Wno-implicit -o parser.out parser.tab.c lexer.c src/utils/bison-tree.c
echo '===> Done.'