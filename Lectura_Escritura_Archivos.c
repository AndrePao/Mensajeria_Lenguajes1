#include <stdio.h>
//Mètodo imprime la informaciòn del archivo de texto en pantalla
#include <string.h>
#include <stdlib.h>
#include "Ultima_Union.c" //llamada al otro archivo
//Creacion de un struct para que almacene la informacion del txt
struct InformacionDEContacto{
	char IP[20];//variable almacena valores ingresados por usuario
	char Puerto[5];
	char Usuario[20];
	};

/////////////////////////////////////////////////////////////
//metodo que obtiene todos los usuarios del txt y los carga a un arreglo
void Leer_Contactos(struct InformacionDEContacto * ContactosLista){
	FILE*F; //se crea apuntador
	F= fopen("ArchivoDeAlmacenamiento", "r+"); //fopenf funciòn permite abrir archivo y r leerlo
	if (F==NULL) // si no encontro el archivo
		printf("\nError en archivo\n");

	else{
	
	int c; //contador que indicara la posicion en la que me encuentro dentro del arreglo de struct
	char cadena[30]; //variable que almacena las lineas del txt
	
		for (c=0;fgets(cadena, 100, F) != NULL;c++){
			if ((c>0) && (cadena[0]!=0)){
			
			int contador=0; //indica por cual caracter del arrego se evalua 
			int contador2=0; //sirve para asignar el espacio en los arreglos de struct
			while (cadena[contador]!='-'){ //ingresa el nombre de usuario en el arreglo
				(ContactosLista[c]).Usuario[contador2] = cadena[contador];
				contador++;
				contador2++;
				}
			(ContactosLista[c]).Usuario[contador] = '\0'; //agrega un caracter nulo, evito la basura
			contador2=0;
			contador++;
			while (cadena[contador]!='-'){ //ingresa el ip del usuario en el arreglo
				(ContactosLista[c]).IP[contador2] = cadena[contador];
				contador++;
				contador2++;
				}
			(ContactosLista[c]).IP[contador2] = '\0';
			contador2=0;
			contador++;
			while (cadena[contador]!='-'){ //ingreso el puerto del usuario en el arreglo
				(ContactosLista[c]).Puerto[contador2] = cadena[contador];
				contador++;
				contador2++;
				}
			(ContactosLista[c]).Puerto[contador2] = '\0';
			}
	}
	(ContactosLista[c]).Usuario[0] = '\0';//ultimo elmento del arreglo es nulo

}
fclose(F); 
}

////////////////////////////////////////////////////////////
//metodo q agrega un usuario al txt y carga en memoria la lista de usuarios nuevamente, con el nuevo usuario incorporado
void Agregar_Contacto(struct InformacionDEContacto * ContactosLista){
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
	fputs(Usuario,F); //almacena nombre en txt
	fputs("-",F); //separa los datos 
	
	printf("Ingrese el IP: ");
	scanf("%s",IP);
	fputs(IP,F);//ingreso de arreglo en el archivo de texto
	
	printf("Ingrese el puerto: ");
	scanf("%s",Puerto);
	fputs("-",F);
	fputs(Puerto,F);
	fputs("-",F); 
	fputs("\n",F); //cambia de linea el txt
	}
	Leer_Contactos(ContactosLista);
	printf("Contacto agregado correctamente\n");
	fclose(F); 
}

////////////////////////////////////////////////////////////
//metodo que busca el nombre del contacto solicitado por el usuario, si lo encuentra retorna el struct, sino lo encuentra retorna el struct vacio
struct InformacionDEContacto Buscar_Contacto(struct InformacionDEContacto * ContactosLista){
	char N [20];
			printf("Ingrese nombre usuario ");
			scanf("%s", N); //obtengo nombre de usuario a buscar
	int contador=1;
	int resultado;
	while ((ContactosLista[contador]).Usuario[0]!='\0'){
		resultado=strcmp(N,(ContactosLista[contador]).Usuario);
		if (resultado==0){
			printf("\nUsuario encontrado\n ");
			printf("\nNombre: %s\n ",ContactosLista[contador].Usuario);//imprimo la informacion del contacto
			printf("\nIP: %s\n ",ContactosLista[contador].IP);
			printf("\nPuerto: %s\n ",ContactosLista[contador].Puerto);
			return ContactosLista[contador];
		}
		contador++;
		
		}
	
	return (ContactosLista[contador]);	
	
	}
////////////////////////////////////////////////////////////
int main (){
	struct InformacionDEContacto ListaDeContactos[30]; //arreglo que contiene structs
	Leer_Contactos(&ListaDeContactos[0]); //metodo que lee el archivo de texto e ingresa al struct los contactos
	int opcion;
	printf("----------------------MENSAJERIA------------------\n");
	printf("-------------------------MENU---------------------\n\n\nDIGITE\n\n1---->Agregar Contacto\n2---->Iniciar Conversacion\n3---->Imprimir Lista de Contactos\n\nOpcion:  ");
	scanf("%d",&opcion);
	if (opcion==1) //si la opcion es agregar un contacto
		{Agregar_Contacto(&ListaDeContactos[0]);
		main();
	}
	
	else if (opcion==2){ //si la opcion es mensajeria
		struct InformacionDEContacto UsuarioAContactar=Buscar_Contacto(&ListaDeContactos[0]);//obtengo al contacto
		if (UsuarioAContactar.Usuario[0]=='\0'){ //verifico que exista el contacto
			printf("\nUsuario no encontrado, verifique que ingreso correctamente los datos\n ");
			main();}
		else{ //si contacto existe
			//obtengo el puerto, lo convierto a entero
			int puertoDecontacto=atoi(UsuarioAContactar.Puerto); //convierte el string a int
			//se realiza la parte de los socktes
			if (fork())
				Servidor();
			else
				Cliente(puertoDecontacto,UsuarioAContactar.IP);
			
			}
		}
	
	else if (opcion==3){ //imprime usuarios en consola
		int contador;
		printf("Lista de contactos\n");
		for (contador=1; ListaDeContactos[contador].Usuario[0]!='\0';contador++){
			printf("%s \n",ListaDeContactos[contador].Usuario);
			printf("\n");}
		main();
		}
	
	else
	main();
	

	return 1;
	}

