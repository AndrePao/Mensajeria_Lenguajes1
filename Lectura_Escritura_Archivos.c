#include <stdio.h>
//Mètodo imprime la informaciòn del archivo de texto en pantalla
#include <string.h>
//Creacion de un struct 
struct Info_Contacto{
	char *IP;//variable almacena valores ingresados por usuario
	char *Puerto;
	char *Usuario;
	};

struct Info_Contacto Lista[100]; // definicion del struct

/////////////////////////////////////////////////////////////////	
void Separar_info(char * caracter, int Contador){
	printf("hoalalamdwoncowe");
	char NOM[20];
	char I[20];
	char P[20];
	int c=0;
	while (*caracter!='-'){
			NOM[c]=*caracter;
			caracter++;
			c++;
			}
	NOM[c]='\0';
	caracter++;
	c=0;
	while (*caracter!='-'){
			I[c]=*caracter;
			caracter++;
			c++;
			}
	caracter++;
	I[c]='\0';
	c=0;
	while (*caracter!=0){
			P[c]=*caracter;
			caracter++;
			c++;}
	P[c]='\0';
	Lista[Contador].Usuario=&NOM[0];
	Lista[Contador].IP=&I[0];
	Lista[Contador].Puerto=&P[0];
	printf("\nEstoy en el struct U: %s", Lista[Contador].Usuario);
	printf("\nEstoy en el struct I: %s", Lista[Contador].IP);
	printf("\nEstoy en el struct  P: %s",Lista[Contador].Puerto);
	printf("\n%d", Contador);
	
	}
////////////////////////////////////////////////////////////////
//hacer validaciòn...	 / 
int leer_Archivo(){
	FILE*F; //se crea apuntador
	F= fopen("ArchivoDeAlmacenamiento", "r+"); //fopenf funciòn permite abrir archivo y r leerlo
	if (F==NULL) // si no encontro el archivo
		printf("\nError en archivo\n");
	else{
	int c=0;
   char caracter[30];
	while (feof(F) == 0){ //mientras que no llegue al final del archivo
		//obtengo hilera
		fgets(caracter,100,F);
		printf("%s",caracter);
		if ((c>0) && (caracter[0]!=0)){
		Separar_info(&caracter[0],c-1);
	}
	c++;
		bzero((char*)&caracter,sizeof(caracter));// se utiliza si uso un arreglo, limpia el arreglo*/
}	 
}
	fclose(F);  //se cierra el archivo
	printf("\nListo\n");
		 
		 return 1;
	}
//////////////////////////////////////////////////////////////////////////
//Mètodo que escribe en el archivo de texto la informaciòn ingresada desde la consola
int escribir_Archivo(){
	FILE*F; //se crea apuntador
	F= fopen("ArchivoDeAlmacenamiento", "r+"); //fopenf funciòn permite abrir archivo y r leerlo
	if (F==NULL) // si no encontro el archivo
		printf("\nError en archivo\n");

	else{
	char IP[20];//variable almacena valores ingresados por usuario
	char Puerto[20];
	char Usuario[20];
	fseek(F,4-sizeof(int),SEEK_END);//funcion que coloca fichero al final del archivo
	
	printf("Ingrese el nombre de usuario: ");
	scanf("%s",Usuario);
	fputs(Usuario,F);
	fputs("-",F);
	
	printf("Ingrese el IP: ");
	scanf("%s",IP);
	fputs(IP,F);//ingreso de arreglo en el archivo de texto
	
	printf("Ingrese el puerto: ");
	scanf("%s",Puerto);
	fputs("-",F);
	fputs(Puerto,F);
	
	
	fputs("\n",F);
}
	fclose(F);  //se cierra el archivo
	printf("\nListo\n");
	return 1;
	}

////////////////////////////////////////////////////////////
int main (){
	
	escribir_Archivo();
	leer_Archivo();
	return 1;}
