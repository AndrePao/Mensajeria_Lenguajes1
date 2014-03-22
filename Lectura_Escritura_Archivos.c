#include <stdio.h>
//Mètodo imprime la informaciòn del archivo de texto en pantalla
#include <string.h>
//Mètodo que escribe en el archivo de texto la informaciòn ingresada desde la consola
int escribir_Archivo(FILE*F){
	char IP[20];//variable almacena valores ingresados por usuario
	char Puerto[20];
	char Usuario[20];
	fseek(F,4-sizeof(int),SEEK_END);//funcion que coloca fichero al final del archivo
	
	printf("Ingrese el IP: ");
	scanf("%s",IP);
	fputs(IP,F);//ingreso de arreglo en el archivo de texto
	
	printf("Ingrese el puerto: ");
	scanf("%s",Puerto);
	fputs(";",F);
	fputs(Puerto,F);
	
	printf("Ingrese el nombre de usuario: ");
	fputs(";",F);
	scanf("%s",Usuario);
	fputs(Usuario,F);
	fputs("\n",F);

	
	return 1;
	}


int Lectura_Escritura(int opc){ 
	FILE*F; //se crea apuntador
	F= fopen("ArchivoDeAlmacenamiento", "r+"); //fopenf funciòn permite abrir archivo y r leerlo
	if (F==NULL) // si no encontro el archivo
		printf("\nError en archivo\n");

	else{
		if (opc==1)
		//leer_Archivo(F); todavìa no lo he implementado...
		//else
		escribir_Archivo(F);
}
	fclose(F);  //se cierra el archivo
	printf("\nListo\n");
	return 0;
}

int main (){
	Lectura_Escritura(1);
	return 1;}
