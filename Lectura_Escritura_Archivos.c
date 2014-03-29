#include <stdio.h>
//Mètodo imprime la informaciòn del archivo de texto en pantalla
#include <string.h>
#include <stdlib.h>
//Creacion de un struct para que almacene la informacion del txt
struct Info_Contacto{
	char *IP;//variable almacena valores ingresados por usuario
	char *Puerto;
	char *Usuario;
	};

struct Info_Contacto Lista[100]; // arreglo de struct, para que almacene la info del struct (da problemas)
int Es_Usuario(char * caracter, char * ptr){ //valida que el usuario que busca se encuentra en el txt
	if (*caracter!= *ptr)
	return 0;
	else{
	while (*caracter!='-'){
		if (*caracter== *ptr){
			caracter++;
			ptr++;}
		else
		return 0;
	}
	}
	return 1;

	}
/////////////////////////////////////////////////////////////////	
void Separar_info(char * caracter, int Contador){ // separa la linea de caracteres, y almacena la info en un arreglo de struct
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
	while (*caracter!='\0'){
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
	int puerto= atoi(Lista[Contador].Puerto); //convierte el string a int
	printf("%d", puerto);
	}
	
////////////////////////////////////////////////////////////////
void Imprime(FILE * F){ //imprime lista de usuarios
	char Nombre[30];
	char * Linea;
	int c=0;
	int p=0;
   char caracter[30];
	while (feof(F) == 0){ //mientras que no llegue al final del archivo
		//obtengo hilera
		fgets(caracter,100,F);
		//printf("%s",caracter);
		if ((c>0) && (caracter[0]!='\0')){
			Linea=&caracter[0];
			while (*Linea!='-'){
			Nombre[p]=*Linea;
			Linea++;
			p++;
			}
		Nombre[p]='\0';
		printf("\n%s",Nombre);
		bzero((char*)&Nombre,sizeof(Nombre)); //limpia el arreglo
				printf("\n%s",Nombre);

	}		
	

	p=0;	
	c++;
	}
		bzero((char*)&Nombre,sizeof(Nombre)); //limpia el arreglo
	 
	}
	
////////////////////////////////////////////////////////////////

int leer_Archivo(FILE * F){
		
	char N [20];
			printf("Ingrese nombre usuario ");
			scanf("%s", N); //obtengo nombre de usuario a buscar
	char * ptr = &N[0];
	int c=0;
   char caracter[30];
   if (feof(F)!=0) // si el archivo esta vacio
		return 0;
   else{
	while (feof(F) == 0){ //mientras que no llegue al final del archivo
		//obtengo hilera
		fgets(caracter,100,F); //obtengo arreglo
		//printf("%s",caracter);
		if ((c>0) && (caracter[0]!=0)){ //condicion del txt
			if(Es_Usuario(&caracter[0], ptr)){ //revisa que el usuario sea el que estoy buscando
			Separar_info(&caracter[0],c-1);  //metodo que separa informacion del arreglo y envia direccion e IP
			return 1;//retorna que encontro al usuario
	}
	}
	c++;
	bzero((char*)&caracter,sizeof(caracter));// se utiliza si uso un arreglo, limpia el arreglo*/	 
	}
	}
	printf("Usuario no encontrado");
	return 0; //sino encontro al usuario
	}
//////////////////////////////////////////////////////////////////////////
//Mètodo que escribe en el archivo de texto la informaciòn ingresada desde la consola
int escribir_Archivo(FILE * F){
	char IP[20];//variable almacena valores ingresados por usuario
	char Puerto[20];
	char Usuario[20];
	fseek(F,4-sizeof(int),SEEK_END);//funcion que coloca fichero al final del archivo
	
	printf("Ingrese el nombre de usuario: ");
	scanf("%s",Usuario);
	fputs(Usuario,F); //almacena nombre en txt
	fputs("-",F); //separa los datos 
	
	printf("Ingrese el IP: ");
	scanf("%s",IP);
	fputs(IP,F);//ingreso de arreglo en el archivo de texto
	
	printf("Ingrese el puerto: ");
	scanf("%s",Puerto);
	fputs("-",F);
	fputs(Puerto,F);
	
	
	fputs("\n",F); //cambia de linea el txt
	return 1;
}
////////////////////////////////////////////////////////////////
int Lectura_Escritura(int opc){ //metodo que abre el archivo
	FILE*F; //se crea apuntador
	F= fopen("ArchivoDeAlmacenamiento", "r+"); //fopenf funciòn permite abrir archivo y r leerlo
	if (F==NULL) // si no encontro el archivo
		printf("\nError en archivo\n");

	else{
		if (opc==1) //agrega usuario
		escribir_Archivo(F);
		else if (opc==2)
		leer_Archivo(F); //busca usuario
		else
		Imprime(F); //imprime usuarios
	}
	fclose(F);  //se cierra el archivo
	printf("\nListo\n");
	return 1;
	}
////////////////////////////////////////////////////////////
int main (){
	//mensaje de que usuario no existe
	Lectura_Escritura(3);
	
	return 1;}
