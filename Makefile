all:
	make comp
#	make descomp

## Funcões de codificação: ##
# compila os arquivos necessarios para codificar o arquivo.txt
comp:
	clear
	gcc compacta.c tree.c -o comp

# executa a codificacao do arquivo parametrizado
comp run:
	make comp
	./comp 

# compila e executa o valgrind do codificador
val comp:
	make comp
	valgrind --leak-check=full -s --track-origins=yes  ./comp


# ## Funcões de decodificação: ##
# # compila os arquivos necessarios para decodificar o arquivo.txt
# comp dec:
# 	clear
# 	gcc descompacta.c bitmap.c -o decode

# # executa a decodificação do arquivo parametrizado
# dec:
# 	make dec
# 	./decode 

# # compila e executa o valgrind do decodificador
# val dec:
# 	make dec
# 	.valgrind --leak-check=full -s --track-origins=yes  ./decode
