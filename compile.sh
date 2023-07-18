echo '===> Compiling...'
flex -o lexer.c src/scanner.l
bison -d src/parser.y
gcc -Wno-implicit -o parser_program.out parser.tab.c lexer.c src/utils/bison-tree.c src/utils/symbol-table.c
echo '===> Done.'