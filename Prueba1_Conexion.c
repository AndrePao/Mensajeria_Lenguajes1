#include<stdio.h>		//Estandar input output
#include<string.h>      //Biblioteca de bzero
#include<sys/socket.h>  //biblioteca de sockets
#include<netinet/in.h> 	//Utilizado para encabezados
#include<sys/types.h>	//Para error
#include<stdlib.h>      //Para error

void Servidor(int p)
{
//Estructuras del cliente y servidor
struct sockaddr_in dir_ser , dir_cli;
int SKT, SKT_2, recibido; 							//para socket del servidor "SKT" y cliente "SKT_2"
//char msg [256]; 									// Para el mensaje que se envia y recibe
int puerto;
	printf("\nIntroduzca puerto:\n");
    scanf("%d",&puerto);

//Creación del socket
SKT= socket(AF_INET , SOCK_STREAM , 0 );
if(SKT == -1) 										//validacion de socket
{													//si es igual a -1 quiere decir que fallo
    printf("Fallo en la creacion del socket " );
}

printf("Socket creado\n"); 					//Si no hay fallo, la comunicacion ya se realizo


//definicion de estructuras  "STRUCT" Protocolos			//TODO BIEN
dir_ser.sin_family = AF_INET;   						 //Listo
dir_ser.sin_addr.s_addr = INADDR_ANY; //inet_addr ("192.168.153.134"); //Listo
dir_ser.sin_port = htons( puerto ); 					 //Listo
																		//BIEN
//Declaracion del BIND= Sirve para poder recibir conexiones, una direccion IP y puerto a traves del que se enviaran los datos
int Conexion;
Conexion= bind(SKT,(struct sockaddr *)&dir_ser, sizeof(dir_ser)); // devuelve -1 o 0

//Creacion del bind  
if( Conexion <0)

{
	perror("Error\n");
    //puts("bind failed");
    return 1;
}
puts("bind creado correctamente");					//TERMINA BIND    

//Creacion del listen para la escucha
listen(SKT , 5);

//Utilizacion de sizeof 
socklen_t largo;
largo= sizeof(struct sockaddr_in);

//Creacion funcion accept para aceptar comunicacion del cliente
SKT_2 = accept(SKT , (struct sockaddr *) &dir_cli, &largo); //Permanece en espera hasta que el cliente se conecte


printf("CONECTANDO...");


if (SKT_2 == -1)
{
    printf("Error de conexion: ");
}

puts("Conexion Aceptada");								//TODO BIEN !!! HAY QUE AGREGAR FORK()



    close(SKT);  //cierra comunicaciones
   // close(SKT_2);  //Ciera comunicacion
   //return 0;
}
//MENU PRINCIPAL


main(){
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Correr servidor\n2---->Iniciar Conversacion\n\nOpcion:  ");
	scanf("%d",&opcion);
	if (opcion==1)
			printf("La opcion es la 1");
			Servidor(8888);
	if (opcion==2)
			printf("La opcion es la 2");
		
}

