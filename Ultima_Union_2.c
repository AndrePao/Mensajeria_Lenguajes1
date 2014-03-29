#include<stdio.h>		//Estandar input output
#include<string.h>      //Biblioteca de bzero
#include<sys/socket.h>  //biblioteca de sockets
#include<netinet/in.h> 	//Utilizado para encabezados
#include<sys/types.h>	//Para error
#include<stdlib.h>      //Para error
// Biblioteca para el uso de base de datos en red
#include <netdb.h>
#include <signal.h>
void Servidor()
{
//Estructuras del cliente y servidor
struct sockaddr_in dir_ser , dir_cli;
int SKT, SKT_2, recibido; 							//para socket del servidor "SKT" y cliente "SKT_2"
char msg [256]; 									// Para el mensaje que se envia y recibe
//int puerto;
	
	
//Creación del socket
SKT= socket(AF_INET , SOCK_STREAM , 0 );
if(SKT == -1) 										//validacion de socket
													//si es igual a -1 quiere decir que fallo
    printf("Fallo en la creacion del socket " );


//printf("Socket creado\n"); 					//Si no hay fallo, la comunicacion ya se realizo


//definicion de estructuras  "STRUCT" Protocolos			//TODO BIEN
dir_ser.sin_family = AF_INET;   						 //Listo
dir_ser.sin_addr.s_addr = INADDR_ANY; //inet_addr ("192.168.153.134"); //Listo
dir_ser.sin_port = htons( 8989 ); 					 //Listo
																		//BIEN
//Declaracion del BIND= Sirve para poder recibir conexiones, una direccion IP y puerto a traves del que se enviaran los datos
int Conexion;
Conexion= bind(SKT,(struct sockaddr *)&dir_ser, sizeof(dir_ser)); // devuelve -1 o 0

//Creacion del bind  
if( Conexion <0)

{
	perror("Error\n");
    //puts("bind failed");
   // return 1;
}
//puts("bind creado correctamente");					//TERMINA BIND    

//Creacion del listen para la escucha
listen(SKT , 5);

//Utilizacion de sizeof 
socklen_t largo;
largo= sizeof(struct sockaddr_in);

//Creacion funcion accept para aceptar comunicacion del cliente
SKT_2 = accept(SKT , (struct sockaddr *) &dir_cli, &largo); //Permanece en espera hasta que el cliente se conecte


//printf("CONECTANDO...");


if (SKT_2 == -1)

    printf("Error de conexion: ");


//puts("Conexion Aceptada");								//TODO BIEN !!! HAY QUE AGREGAR FORK()




#define VERDE  "\033[2K\r\033[01;32m" // DEFINE COLOR VERDE
#define BLANCO  "\033[00;37m" // DEFINE COLOR BLANCO
#define AZUL  "\x1B[34m" // DEFINE COLOR AZUL


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

   // printf("\nAdios\n");
   // send(SKT_2,"Desconectado",256,0);
    close(SKT);  //cierra comunicaciones
    close(SKT_2);  //Ciera comunicacion
	//return 0;
}



//Funcion del cliente
void Cliente(int pi)
{
    int socket_C,conexion; 
    struct sockaddr_in Cliente; 
    char msg[256];  //Arreglo para el envio de msj
   

    if((socket_C=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)  //Creacion de socket
    
        printf("\nFallo creacion de socket");
   
    int puerto;
 //Estructuras
    printf("\n-----------------------Conectado-----------------------\n");
	printf("\nIngrese mensaje . . .\n");
	//printf("INTRODUZCA EL PUERTO:\n");		//Permite que el usuario ingrese el puerto
    scanf("%d",&puerto);
    	
	//printf("\nVerificando Puerto. . .\n");
    Cliente.sin_family = AF_INET;		
    Cliente.sin_port=htons(pi);
    Cliente.sin_addr.s_addr=INADDR_ANY;    //inet_addr ("192.168.153.134");

    conexion=connect(socket_C,(struct sockaddr*)&Cliente,sizeof(Cliente));  //Para conectar al servidor

    if(conexion==-1)  //Si la conexion falla
    {
        printf("\nError en conexion");
        
    }
	
   
#define VERDE  "\033[2K\r\033[01;32m" // DEFINE COLOR VERDE
#define BLANCO  "\033[00;37m" // DEFINE COLOR BLANCO
//printf("\n-----------------------Conectado-----------------------\n");
while(1){
		
		
        fgets(msg,255,stdin);// Obtiene la info a enviar
         //   fgets(msg,255,stdin);//Obtiene la informacion que se desea enviar
       
           
       if (strncmp(msg,"1",1)==0) // mientras sea diferente de salir, 
		{
		printf("\nAdios\n");
		kill(getpid()-1, SIGKILL);
		break;
		}
		else{
		send(socket_C, msg, 256,0);		//ENVIA EL MSG DEL SERVIDOR
		printf(	VERDE "Mensaje enviado:"BLANCO" %s\n",msg);
	}
	}
     send(socket_C,"Salir",256,0); //envia msj
     close(socket_C);  //cierra comunicaciones
	
}

//MENU PRINCIPAL


int main(){
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Correr servidor\n2---->Iniciar Conversacion\n\nOpcion:  ");
	scanf("%d",&opcion);
	if (fork()){
	//if (opcion==1)
			//printf("Llamada a servidor");
			Servidor();
			}
	//if (opcion==2)
	else{
			//printf("Llamada al cliente");
			Cliente(8888);
		}
}

