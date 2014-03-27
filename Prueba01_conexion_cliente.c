#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>

//Funcion del cliente
void Cliente(int puerto)
{
    int socket_C,conexion; 
    struct sockaddr_in Cliente; 
    char msg[256];  //Arreglo para el envio de msj
   

    if((socket_C=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)  //Creacion de socket
    
        printf("\nFallo creacion de socket");
   
    
 //Estructuras
	printf("INTRODUZCA EL PUERTO:\n");		//Permite que el usuario ingrese el puerto
    scanf("%d",&puerto);	
    Cliente.sin_family = AF_INET;		
    Cliente.sin_port=htons(puerto);
    Cliente.sin_addr.s_addr=INADDR_ANY;    //inet_addr ("192.168.153.134");

    conexion=connect(socket_C,(struct sockaddr*)&Cliente,sizeof(Cliente));  //Para conectar al servidor

    if(conexion==-1)  //Si la conexion falla
    {
        printf("\nError en conexion");
        
    }
	
   
#define VERDE  "\033[2K\r\033[01;32m" // DEFINE COLOR VERDE
#define BLANCO  "\033[00;37m" // DEFINE COLOR BLANCO


		printf("\n-----------------------Conectado-----------------------\n");
        fgets(msg,255,stdin);// Obtiene la info a enviar
		
		//int Compara_String=strncmp(msg,"adios",4);
        while(strncmp(msg,"adios",4)!=0) // mientras sea diferente de salir, 
        { 	 
            send(socket_C, msg, 256,0);		//ENVIA EL MSG DEL SERVIDOR
            fgets(msg,255,stdin);//Obtiene la informacion que se desea enviar
            printf(	VERDE "Mensaje enviado:"BLANCO" %s\n",msg);
           
        }
		
        send(socket_C,"Salir",256,0); //envia msj
     close(socket_C);  //cierra comunicaciones
	
}
//MENU 

 main(){
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Ejecutar cliente\n2---->Iniciar Conversacion\n\nOpcion:  ");
	scanf("%d",&opcion);
	if (opcion==1)
			printf("La opcion es la 1");
			Cliente(8888);
	if (opcion==2)
			printf("La opcion es la 2");

}


	
    close(socket_C);
    
   // return 0;
}

//MENU PRINCIPAL

 main(){
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Ejecutar cliente\n2---->Iniciar Conversacion\n\nOpcion:  ");
	scanf("%d",&opcion);
	if (opcion==1)
			printf("La opcion es la 1");
			Cliente(8888);
	if (opcion==2)
			printf("La opcion es la 2");

}

