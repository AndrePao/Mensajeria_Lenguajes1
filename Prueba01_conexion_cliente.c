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

    if((socket_C=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)  //Crea socket
    {
        printf("\nFallo creacion de socket");
   //     return 0;
    }

   
    Cliente.sin_family = AF_INET;
    printf("INTRODUZCA EL PUERTO:\n");
    scanf("%d",&puerto);			
    Cliente.sin_port=htons(puerto);
    Cliente.sin_addr.s_addr=INADDR_ANY;    //inet_addr ("192.168.153.134");

    conexion=connect(socket_C,(struct sockaddr*)&Cliente,sizeof(Cliente));

    if(conexion==-1)
    {
        printf("\nError en conexion");
        //return 0;
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

