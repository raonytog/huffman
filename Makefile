# Funções de execução geral
all: runc rund 				# executa o codigo inteiro
vall: valgrindc valgrind 	# valgrind geral

# Funções para o compacta
# Compila os arquivos necessários para codificar o arquivo.txt
compc:
	clear
	gcc compacta.c tree.c bitmap.c -o compacta -lm

# Executa a codificação do arquivo parametrizado
runc: compc
	./compacta 

# Compila e executa o valgrind do codificador
valgrindc: compc
	valgrind --leak-check=full -s --track-origins=yes ./compacta


# Funções para o descompacta
# Compila os arquivos necessários para decodificar o arquivo.txt.comp
compd:
	clear
	gcc descompacta.c tree.c bitmap.c -o descompacta -lm

# Executa a decodificação do arquivo parametrizado
rund: compd
	./descompacta 

valgrindd: compd
	valgrind --leak-check=full -s --track-origins=yes ./descompacta
