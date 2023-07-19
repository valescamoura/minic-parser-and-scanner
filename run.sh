if [ -z $1 ]; then
    echo 'Informe o caminho do arquivo que contém o código-fonte a ser analisado.'
    exit 1
fi
# if [ -z $1 ]; then
#     echo 
#     exit(1)
# fi

echo '===> Running...'
./parser.out < $1  # data/example.mc

echo '===> Done.'
echo '===> Output in tree.pdf and tree.png.'
