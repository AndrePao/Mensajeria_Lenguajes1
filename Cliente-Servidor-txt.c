#include <stdio.h>
//Mètodo imprime la informaciòn del archivo de texto en pantalla
#include <string.h>
#include <stdlib.h>
//#include "Ultima_Union.c"

#include<stdio.h>		//Estandar input output
#include<string.h>      //Libreria de bzero
#include<sys/socket.h>  //Libreria de sockets
#include<netinet/in.h> 	//Utilizado para encabezados
#include<sys/types.h>	//Para error
#include<stdlib.h>      //Para error
#include<netdb.h>		//Para base de datos
#include<signal.h>

//#include "Agregar_Buscar_Usuario.c"

//Definicion de colores para el envio de mensaje
#define VERDE  "\033[2K\r\033[01;32m" // DEFINE COLOR VERDE
#define BLANCO  "\033[00;37m" // DEFINE COLOR BLANCO
#define AZUL  "\x1B[34m" // DEFINE COLOR AZUL

//Funcion "config" para tomar el puerto del servidor
int Obtener_Puerto(){ FILE*F; //se crea apuntador
 F= fopen("Archivo_Config", "r+"); //fopenf funciòn permite abrir archivo y r leerlo 
 if (F==NULL) // si no encontro el archivo 
 printf("\nError en archivo\n");
  else{ char numero[5];
   int contador=0;
    while (feof(F) == 0){ //mientras que no llegue al final del archivo 
    fgets(numero,100,F); 
    if (contador==0){ 
		contador++; 
		int Puerto= atoi(numero); 
		//printf("%s", numero);
		 bzero((char*)&numero,sizeof(numero)); 
		 return Puerto; }
		  } 
		 } 
		 fclose(F); //se cierra el archivo 
		 return 0; }

//Funcion del servidor que recibe mensajes
void Servidor()
{
//Estructuras del cliente y servidor
struct sockaddr_in dir_ser , dir_cli;
int SKT, SKT_2; 							//para socket del servidor "SKT" y cliente "SKT_2"
char msg [256]; 									// Para el mensaje que se envia y recibe


//Creación del socket
SKT= socket(AF_INET , SOCK_STREAM , 0 );
if(SKT == -1) 										//validacion de socket
													//si es igual a -1 quiere decir que fallo
    printf("Fallo en la creacion del socket " );


//printf("Socket creado\n"); 					//Si no hay fallo, la comunicacion ya se realizo


//definicion de estructuras  "STRUCT" Protocolos			//TODO BIEN
dir_ser.sin_family = AF_INET;   						 //Listo
dir_ser.sin_addr.s_addr = INADDR_ANY; //inet_addr ("192.168.153.134"); //Listo
int Puerto=Obtener_Puerto();
dir_ser.sin_port = htons(Puerto); 					 //Listo 8989
																		//BIEN
//Declaracion del BIND= Sirve para poder recibir conexiones, una direccion IP y puerto a traves del que se enviaran los datos
int Conexion;
Conexion= bind(SKT,(struct sockaddr *)&dir_ser, sizeof(dir_ser)); // devuelve -1 o 0

//Creacion del bind  
if( Conexion <0)

	perror("Error\n");							//TERMINA BIND    

//Creacion del listen para la escucha
listen(SKT , 5);

//Utilizacion de sizeof 
socklen_t largo;
largo= sizeof(struct sockaddr_in);

//Creacion funcion accept para aceptar comunicacion del cliente
SKT_2 = accept(SKT , (struct sockaddr *) &dir_cli, &largo); //Permanece en espera hasta que el cliente se conecte



if (SKT_2 == -1)

    printf("Error de conexion: ");



//Funcion para recibir los mensajes del cliente
	
while(1)
    { 	
        recv(SKT_2,msg,256,0);
     
   if (strncmp(msg,"1",1)==0) // mientras sea diferente de salir, 
		{
		printf("\nAdios\n");
		
		kill(getpid()-1, SIGKILL);
		break;
		}
else
	printf(	AZUL "Mensaje recibido:"BLANCO"%s\n",msg); //Imprime informacion en pantalla utilizando los define de colore
}
		close(SKT);  //cierra comunicaciones
		close(SKT_2);  //Ciera comunicacion
 
   
}



//Funcion del cliente
void Cliente(int pi, char *IP)
{
    int socket_C,conexion; 
    struct sockaddr_in Cliente; 
    char msg[256];  //Arreglo para el envio de msj
   

    if((socket_C=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)  //Creacion de socket
    
        printf("\nFallo creacion de socket");
   
    int M;
    

	printf("\n-----------------------Conectado-----------------------\n");
	printf("\nIngrese mensaje . . .\n");
    scanf("%d",&M);
    
//Estructuras   Protocolos
    Cliente.sin_family = AF_INET;		
    Cliente.sin_port=htons(pi);
    Cliente.sin_addr.s_addr=INADDR_ANY;	 			//inet_addr (*IP); 						//inet_addr (*IP);  //INADDR_ANY

    conexion=connect(socket_C,(struct sockaddr*)&Cliente,sizeof(Cliente));  //Para conectar al servidor

    if(conexion==-1)  //Si la conexion falla
    {
        printf("\nError en conexion");
        
    }
	
//Ciclo
while(1){
		
		
        fgets(msg,255,stdin);		 // Obtiene la info a enviar
           
        if (strncmp(msg,"1",1)==0)	 // mientras sea diferente de salir, 
		{
		//printf("\nAdios\n");
		kill(getpid()-1, SIGKILL);	 //Mata los procesos
		
		break;
		}
		else{
		send(socket_C, msg, 256,0);		//ENVIA EL MSG DEL SERVIDOR
		printf(	VERDE "Mensaje enviado:"BLANCO" %s\n",msg);
	}
		
} 
     close(socket_C);  //cierra comunicaciones
	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Creacion de un struct para que almacene la informacion del txt0
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
	printf("\nNombre de usuario: %s", Lista[Contador].Usuario);
	printf("\nDireccion IP: %s", Lista[Contador].IP);
	printf("\nPuerto: %s",Lista[Contador].Puerto);
	int puerto= atoi(Lista[Contador].Puerto); //convierte el string a int
	if (fork())
		Servidor();
	else
		{Cliente(puerto,Lista[Contador].IP);
		main();}
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
		if ((c>0) && (caracter[0]!=0)){
			Linea=&caracter[0];
			while (*Linea!='-'){
			Nombre[p]=*Linea;
			Linea++;
			p++;
			}
		Nombre[p]='\0';
		printf("\n%s",Nombre);
	}		
	bzero((char*)&Nombre,sizeof(Nombre)); //limpia el arreglo

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
	printf("\n\n---------------------Accion Finalizada------------------------\n");
	//main();
	return 1;
	}
////////////////////////////////////////////////////////////
void main (){
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Agregar Contacto\n2---->Iniciar Conversacion\n3---->Imprimir Lista de Contactos\n\nOpcion:  ");
	scanf("%d",&opcion);
	Lectura_Escritura(opcion);
	
	}
