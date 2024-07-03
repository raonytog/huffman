# funcoes de execucao geral
all:
	run c
	run d


# funcoes para o compacta
# compila os arquivos necessários para codificar o arquivo.txt
compc:
	clear
	gcc compacta.c tree.c -o compacta
	echo Arquivo de compactacao compilado!

# executa a codificação do arquivo parametrizado
runc:
	make compc
	./compacta 

# compila e executa o valgrind do codificador
valgrindc:
	gcc compacta.c tree.c -o compacta
	valgrind --leak-check=full -s --track-origins=yes ./compacta


# compila os arquivos necessários para decodificar o arquivo.txt.comp
# funcoes para o descompacta
compd:
	clear
	gcc descompacta.c tree.c -o descompacta
	echo Arquivo de descompactacao compilado!

# executa a codificação do arquivo parametrizado
rund:
	make compd
	./descompacta 

valgrindd:
	gcc descompacta.c tree.c -o descompacta
	valgrind --leak-check=full -s --track-origins=yes ./descompacta