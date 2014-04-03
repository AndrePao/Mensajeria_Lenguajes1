Archivos : Lectura_Escritura_Archivos.o Ultima_Union_2.o
	gcc Ultima_Union_2.c  Lectura_Escritura_Archivos.c -o Archivos

Lectura_Escritura_Archivos.o: Ultima_Union_2.o
	gcc Lectura_Escritura_Archivos.c -o Lectura_Escritura_Archivos.o

Ultima_Union_2.o:Ultima_Union_2.c
	gcc Ultima_Union_2.c -o Ultima_Union_2.o






