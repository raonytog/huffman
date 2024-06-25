all:
	make enc
	make dec

## Funcões de codificação: ##
# compila os arquivos necessarios para codificar o arquivo.txt
comp enc:
	clear
	gcc compacta.c bitmap.c -o encode

# executa a codificacao do arquivo parametrizado
enc:
	make encode
	./encode 

# compila e executa o valgrind do codificador
val enc:
	make enc
	.valgrind --leak-check=full -s --track-origins=yes  ./encode


## Funcões de decodificação: ##
# compila os arquivos necessarios para decodificar o arquivo.txt
comp dec:
	clear
	gcc descompacta.c bitmap.c -o decode

# executa a decodificação do arquivo parametrizado
dec:
	make dec
	./decode 

# compila e executa o valgrind do decodificador
val dec:
	make dec
	.valgrind --leak-check=full -s --track-origins=yes  ./decode
