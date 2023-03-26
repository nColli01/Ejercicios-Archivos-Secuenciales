/* 
	ejer-1
	Crear un archivo llamado "Productos.dat" con el siguiente formato de registro:
		Codigo, int
		Descripcion, cadena 50 caracteres
		Stock, int
		Precio, float
	Los datos se ingresan por teclado, el fin de ingreso de datos es codigo igual a cero.
	
	ejer-2
	Leer el archivo "Productos.dat" y mostrar el contenido de los registros por pantalla (uno por cada linea de pantalla).
	
	ejer-3
	Generar un archivo llamado "Reposicion.dat" con los registros del archivo "Productos.dat" que tengan
	el stock igual a cero.
	
	ejer-4
	Dado un codigo de producto ingresado por teclado, modificar el precio del mismo en el archivo "Productos.dat".
	
	ejer-5
	Modificar el precio del archivo "Productos.dat" para varios productos. Para ello ingresar por teclado
	los codigos de productos cuyos precios se quieren modificar. El fin de ingreso de codigos de
	productos a modificar finaliza con el ingreso de un cero.
*/

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <cstring>
using namespace std;

typedef struct Producto {
	int codigo;
	char descripcion[50];
	int stock;
	float precio;
}Producto;

void crearArchivoProductos(void);
void mostrarArchivoProductos(void);
void crearArchivoReposicion(void);
void modificarPrecioArchivoProductos(void);
void modificarVariosPreciosArchivoProductos(void);

int main(void){
	int opcion;
	
	cout<<"--MENU--"<<endl;
	cout<<"0) EXIT"<<endl;
	cout<<"1) Crear archivo de productos"<<endl;
	cout<<"2) Leer archivo de productos"<<endl;
	cout<<"3) Crear archivo de reposicion"<<endl;
	cout<<"4) Modificar precio de producto"<<endl;
	cout<<"5) Modificar precio de varios productos"<<endl;
	
	cout<<"Opcion: ";
	cin>>opcion;
	cout<<endl;
	
	while(opcion != 0){
		switch(opcion){
			case 1:
				crearArchivoProductos();
				break;
			case 2:
				mostrarArchivoProductos();
				break;
			case 3:
				crearArchivoReposicion();
				break;
			case 4:
				modificarPrecioArchivoProductos();
				break;
			case 5:
				modificarVariosPreciosArchivoProductos();
				break;
		}
		cout<<endl<<"--MENU--"<<endl;
		cout<<"0) EXIT"<<endl;
		cout<<"1) Crear archivo de productos / anadir producto"<<endl;
		cout<<"2) Leer archivo de productos"<<endl;
		cout<<"3) Crear archivo de reposicion"<<endl;
		cout<<"4) Modificar precio de producto"<<endl;
		cout<<"5) Modificar precio de varios productos"<<endl;
		
		cout<<"Opcion: ";
		cin>>opcion;
		cout<<endl;
	}
	return 0;
}

void crearArchivoProductos(void){
	int codAux;
	string descripcion;
	
	FILE * ArchProductos = fopen("Productos.dat","ab");
	
	if(ArchProductos == NULL)
		cout<<"-- ERROR, NO se pudo abrir el archivo --"<<endl;
	else{
		Producto p;
		cout<<" -- producto --"<<endl;
		cout<<"Codigo (0=fin): ";
		cin>>codAux;
		while(codAux != 0){
			p.codigo = codAux;
			cout<<"Descripcion: ";
			getline(cin, descripcion);
			getline(cin, descripcion);
			strcpy(p.descripcion, descripcion.c_str());
			cout<<"Stock: ";
			cin>>p.stock;
			cout<<"Precio: ";
			cin>>p.precio;
			cout<<endl<<" -- producto --"<<endl;
			fwrite(&p,sizeof(Producto),1,ArchProductos);
			cout<<"Codigo (0=fin): ";
			cin>>codAux; 
		}
	}
	fclose(ArchProductos);
}

void mostrarArchivoProductos(void){
	FILE * ArchProductos = fopen("Productos.dat","rb");
	
	if(ArchProductos == NULL)
		cout<<"-- ERROR, NO se pudo abrir el archivo --"<<endl;
	else{
		Producto p;
		fread(&p,sizeof(Producto),1,ArchProductos);
		while(!feof(ArchProductos)){
			cout<<endl<<" -- producto --"<<endl;
			cout<<"Codigo: "<<p.codigo<<endl;
			cout<<"Descripcion: "<<p.descripcion<<endl;
			cout<<"Stock: "<<p.stock<<endl;
			cout<<"Precio: "<<p.precio<<endl;
			fread(&p,sizeof(Producto),1,ArchProductos);
		}
	}
	fclose(ArchProductos);
}

void crearArchivoReposicion(void){
	FILE * ArchReposicion = fopen("Reposicion.dat","ab");
	FILE * ArchProductos = fopen("Productos.dat","rb");
	
	if(ArchReposicion == NULL || ArchProductos == NULL)
		cout<<"-- ERROR, NO se pudo crear/abrir el archivo --"<<endl;
	else{
		Producto r;
		Producto p;
		fread(&p,sizeof(Producto),1,ArchProductos);
		while(!feof(ArchProductos)){
			if(p.stock == 0)
				fwrite(&p,sizeof(Producto),1,ArchReposicion);
			fread(&p,sizeof(Producto),1,ArchProductos);
		}
	}
}

void modificarPrecioArchivoProductos(void){
	int codProducto;
	float nuevoPrecio;
	
	FILE * ArchProductos = fopen("Productos.dat", "rb+");
	
	if(ArchProductos == NULL)
		cout<<"-- ERROR, NO se pudo abrir el archivo --"<<endl;
	else{
		Producto p;
		
		cout<<"Codigo de producto: ";
		cin>>codProducto;
		
		fread(&p,sizeof(Producto),1,ArchProductos);
		while(!feof(ArchProductos) && p.codigo!=codProducto)
			fread(&p,sizeof(Producto),1,ArchProductos);
			
		if(!feof(ArchProductos)){
			cout<<"Producto con codigo: "<<codProducto<<endl;
			cout<<"Nuevo precio: ";
			cin>>nuevoPrecio;
			p.precio=nuevoPrecio;
			fseek(ArchProductos,-(long)sizeof(Producto),SEEK_CUR);
			fwrite(&p,sizeof(Producto),1,ArchProductos);
			cout<<"Precio modificado con exito"<<endl;
		} else
			cout<<"Producto NO encontrado"<<endl;
		fclose(ArchProductos);
	}
}

void modificarVariosPreciosArchivoProductos(void){
	int i,j,codProductos[100];
	float nuevoPrecio;
	
	FILE * ArchProductos = fopen("Productos.dat", "rb+");
	
	if(ArchProductos == NULL)
		cout<<"-- ERROR, NO se pudo abrir el archivo --"<<endl;
	else{
		Producto p[100];
		i=0;
		
		do{
			cout<<"Codigo producto (0=fin): ";
			cin>>codProductos[i];
			i++;
		}while(i<100 && codProductos[i-1]!=0);
		
		j=0;
		while(j<i-1){
			fread(&p[j],sizeof(Producto),1,ArchProductos);
			while(!feof(ArchProductos) && p[j].codigo!=codProductos[j])
				fread(&p[j],sizeof(Producto),1,ArchProductos);
				
			if(!feof(ArchProductos)){
				cout<<"Producto con codigo: "<<codProductos[j]<<endl;
				cout<<"Nuevo precio: ";
				cin>>nuevoPrecio;
				p[j].precio=nuevoPrecio;
				fseek(ArchProductos,-(long)sizeof(Producto),SEEK_CUR);
				fwrite(&p[j],sizeof(Producto),1,ArchProductos);
				cout<<"Precio modificado con exito"<<endl;
			} else
			cout<<"Producto NO encontrado"<<endl;
			
			j++;
		}
		fclose(ArchProductos);
	}
	
	
}
