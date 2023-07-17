# minic-parser-and-scanner

Scanner + parser bottom-up com verificação de tipos e contexto de identificadores + transformação de laços de repetição em desvios incondicionais (goto) para a Linguagem Mini-C (um subconjunto da linguagem C - sua gramática pode ser encontrada em https://github.com/TangoEnSkai/mini-c-compiler-c/blob/master/mini_c.gr e a gramática completa de C pode ser encontrada em https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm ) acrescida do tipo "char".

A implementação deve ser feita usando Flex + Bison e suas possíveis interfaces para outras linguagens.

Os entregáveis são:
- Código fonte
- Makefile e/ou intruções de compilação e execução
- Arquivos de exemplos
- Relatório descrevendo a atuação de cada membro, em caso de trabalho feito em dupla (não serão aceitas entregas feitas por mais do que dois componentes)


## Passos para compilar:

```./compile.sh```

ou:

- flex -o lexer.c src/scanner.l
- bison -d src/parser.y
- gcc -o parser.out parser.tab.c lexer.c src/utils/bison-tree.c

## Como executar

```./run.sh data/example.mc```

## Tasks:

- [x] BNF
    - [x] Adicinar tipo char
    - [x] Permitir mais de uma Function no código
- [x] Scanner: flex **(Daniel)**
- [x] Parser puro: bison **(Daniel)**
- [ ] Análise semântica de tipo e contexto: bison **(Daniel)**
- [ ] Conversão de for para goto: bison **(Valesca)**
- [x] Fazer a função de visualização da árvore utilizando graphviz. **(Valesca)**
- [x] Montar shell script e instruções de compilação. **(Valesca)**
