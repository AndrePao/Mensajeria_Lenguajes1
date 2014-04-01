#include<stdio.h>		//Estandar input output
#include<string.h>      //Biblioteca de bzero
#include<sys/socket.h>  //biblioteca de sockets
#include<netinet/in.h> 	//Utilizado para encabezados
#include<sys/types.h>	//Para error
#include<stdlib.h>      //Para error
#include<netdb.h>		// Libreria permite  uso de base de datos 
#include<signal.h>
//Definicion de colores para los mensajes recibidos

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


void Servidor()
{
//Estructuras del cliente y servidor
struct sockaddr_in dir_ser , dir_cli;
int SKT, SKT_2; 									//para socket del servidor "SKT" y cliente "SKT_2"
char msg [256]; 									// Para el mensaje que se envia y recibe


//Creación del socket
SKT= socket(AF_INET , SOCK_STREAM , 0 );
if(SKT == -1) 										//validacion de socket
													//si es igual a -1 quiere decir que fallo
    printf("Fallo en la creacion del socket " );

													//Si no hay fallo, la comunicacion ya se realizo


//definicion de estructuras  "STRUCT" Protocolos	//TODO BIEN
dir_ser.sin_family = AF_INET;   					//Listo
dir_ser.sin_addr.s_addr = INADDR_ANY; 				//inet_addr ("192.168.153.134"); //Listo
dir_ser.sin_port = htons( 8888 ); 					//Listo
																		//BIEN
//Declaracion del BIND= Sirve para poder recibir conexiones, una direccion IP y puerto a traves del que se enviaran los datos
int Conexion;
Conexion= bind(SKT,(struct sockaddr *)&dir_ser, sizeof(dir_ser)); // devuelve -1 o 0

//Creacion del bind  
if( Conexion <0)
	perror("Error\n");
  
									//TERMINA BIND    

//Creacion del listen para la escucha
listen(SKT , 5);

//Utilizacion de sizeof 
socklen_t largo;
largo= sizeof(struct sockaddr_in);

//Creacion funcion accept para aceptar comunicacion del cliente
SKT_2 = accept(SKT , (struct sockaddr *) &dir_cli, &largo); //Permanece en espera hasta que el cliente se conecte



if (SKT_2 == -1)

    printf("Error de conexion: ");					//TODO BIEN 



//Funcion para recibir los mensajes del cliente
	
while(1)
    { 	
        recv(SKT_2,msg,256,0);
     
   if (strncmp(msg,"1",1)==0) // si es igual a 1 se cierra el proceso,   
		{
		printf("\nAdios\n");			
		kill(getpid()-1, SIGKILL);				//Funcion para matar los procesos 
		break;									//Hace un break del ciclo
		}
else
	printf(	AZUL "Mensaje recibido:"BLANCO"%s\n",msg); //Imprime informacion en pantalla utilizando los define de colores
}

    close(SKT);  		//cierra comunicaciones
    close(SKT_2);  		//Ciera comunicacion
  
}



//Funcion del cliente
void Cliente(int Puerto, char * IP)
{
    int socket_C,conexion;  //Socket
    struct sockaddr_in Cliente; 
    char msg[256];  //Arreglo para el envio de msj
   

    if((socket_C=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)  //Creacion de socket
    
        printf("\nFallo creacion de socket");
   
    int M;

	printf("\n-----------------------Conectado-----------------------\n");
	printf("\nIngrese mensaje . . .\n");						//Permite que el usuario ingrese el puerto
    scanf("%d",&M);
    
	//Estructuras
    Cliente.sin_family = AF_INET;		
    Cliente.sin_port=htons(Puerto);
    Cliente.sin_addr.s_addr= inet_addr (*IP); 					//INADDR_ANY;    //inet_addr ("192.168.153.134");

    conexion=connect(socket_C,(struct sockaddr*)&Cliente,sizeof(Cliente));  //Para conectar al servidor

    if(conexion==-1)  //Si la conexion falla
    {
        printf("\nError en conexion");
        
    }


while(1){
	
        fgets(msg,255,stdin);				// Obtiene la info a enviar
        
        if (strncmp(msg,"1",1)==0) 			//Si es igual 1 mata los procesos
		{
		printf("\nAdios\n");				//Imprime Adios cuando se desconecta
		kill(getpid()-1, SIGKILL);			//Encargado de cerrar los procesos
		break;								//Cierra el while
		}
		
		else{
		send(socket_C, msg, 256,0);			//ENVIA EL MSG DEL SERVIDOR
		printf(	VERDE "Mensaje enviado:"BLANCO" %s\n",msg);		
	}
		
}
     close(socket_C);  //cierra comunicaciones
	
}

