# minic-parser-and-scanner

Scanner + parser bottom-up com verificação de tipos e contexto de identificadores + transformação de laços de repetição em desvios incondicionais (goto) para a Linguagem Mini-C (um subconjunto da linguagem C - sua gramática pode ser encontrada em https://github.com/TangoEnSkai/mini-c-compiler-c/blob/master/mini_c.gr e a gramática completa de C pode ser encontrada em https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm ) acrescida do tipo "char".

A implementação deve ser feita usando Flex + Bison e suas possíveis interfaces para outras linguagens.

Os entregáveis são:
- Código fonte
- Makefile e/ou intruções de compilação e execução
- Arquivos de exemplos
- Relatório descrevendo a atuação de cada membro, em caso de trabalho feito em dupla (não serão aceitas entregas feitas por mais do que dois componentes)


## Como utilizar:
### Env config

- Tenha o ```flex``` e o ```bison``` instalados em sua máquina.
    - Instalação no Linux:
        - ```sudo apt-get install flex```.
        - ```sudo apt-get install bison```.
    - Versão ```flex``` utilizada: ```flex 2.6.4```.
    - Versão ```bison``` utilizada: ```bison (GNU Bison) 3.8.2```.
- Necessário instalar ```GraphViz``` para geração da árvore de saída em arquivos PDF/PNG: https://graphviz.org/download/.
    - Versão utilizada: ```graphviz version 8.0.5 (20230430.1635)```.
    - Linux: ```sudo apt install graphviz```.

### Passos para compilar:

- Execute o script compile: ```./compile.sh```.

### Como executar

- Execute o script run.sh passando como argumento o caminho do arquivo minic que você deseja analizar: ```./run.sh data/example.mc```.
    - Há arquivos de exemplo de código no diretório ```data```.
- A saída deste programa é uma árvore em dois formatos: arquivo PDF e PNG.

## Distribuição das Tasks:

- [x] BNF
    - [x] Adicinar tipo char **(Daniel)**
    - [x] Permitir mais de uma Function no código **(Daniel)**
    - [x] Adicionar regra de criação do gotoStmt **(Valesca)**
- [x] Scanner: flex **(Ambos)**
- [x] Parser puro: bison **(Ambos)**
- [x] Análise semântica de tipo e contexto: bison **(Daniel)**
- [x] Conversão de loops para goto: bison **(Valesca)**
- [x] Visualização gráfica da árvore utilizando graphviz. **(Valesca)**
- [x] Montar shell script com instruções de compilação e documentação. **(Valesca)**
