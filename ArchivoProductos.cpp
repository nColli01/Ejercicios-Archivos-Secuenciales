/* 
	ejer-1
	Crear un archivo llamado "Productos.dat" con el siguiente formato de registro:
		Codigo, int
		Descripcion, cadena 50 caracteres
		Stock, int
		Precio, float
	Los datos se ingresan por teclado, el fin de ingreso de datos es codigo igual a cero.
*/

#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

typedef struct Producto {
	int codigo;
	char descripcion[50];
	int stock;
	float precio;
}Producto;

void crearArchivoProductos(void);

int main(void){
	int opcion;
	
	cout<<"--MENU--"<<endl;
	cout<<"0) EXIT"<<endl;
	cout<<"1) Crear archivo"<<endl;
	
	cout<<"Opcion: ";
	cin>>opcion;
	cout<<endl;
	
	switch(opcion){
		case 0:
			break;
		case 1:
			crearArchivoProductos();
			break;
		
	}
		
	return 0;
}

void crearArchivoProductos(void){
	int codAux;
	
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
			cout<<"Descripcion: "<<endl;
			cin>>p.descripcion;
			cout<<"Stock: ";
			cin>>p.stock;
			cout<<"Precio: ";
			cin>>p.precio;
			cout<<endl<<" -- producto --"<<endl;
			cout<<"Codigo (0=fin): ";
			cin>>codAux; 
		}
		fwrite(&p,sizeof(p),1,ArchProductos);
	}
}