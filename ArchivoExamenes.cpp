/*
	ejer-6
	Se tiene un archivo secuencial, llamado “Examenes.dat”, con los exámenes rendidos por los
	alumnos que cursan la carrera de Ingeniería en Informática. De cada alumno se tiene número de
	matrícula, nombre, código de materia y nota obtenida. Se pide hacer un programa que ingrese por
	teclado un número de matrícula y un código de materia y que informe si el alumno rindió esa
	materia y la nota que obtuvo
*/

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <cstring>
using namespace std;

typedef struct Examen{
	int matricula;
	char nombre[20];
	int codigo;
	float nota;
}Examen;

void crearArchivoExamenes(void);
void buscarPorMatriculaCodigo(void);
void mostrarArchivoExamenes(void);

int main(void){
	int opcion;
	
	do{
		cout<<"0) EXIT"<<endl;
		cout<<"1) Crear Archivo / Agregar datos a Examenes.dat"<<endl;
		cout<<"2) Buscar si el alumno rindio y su nota por matricula y codigo de materia"<<endl;
		cout<<"3) Mostrar datos examenes"<<endl;
		
		cout<<"Opcion: ";
		cin>>opcion;
		switch(opcion){
			case 1:
				crearArchivoExamenes();
				break;
			case 2:
				buscarPorMatriculaCodigo();
				break;
			case 3:
				mostrarArchivoExamenes();
				break;
		}
	}while(opcion!=0);
	
	return 0;
}

void crearArchivoExamenes(void){
	int matricula;
	string nombre;
		
	FILE * ArchExamenes = fopen("Examenes.dat","ab");
	
	if(ArchExamenes == NULL)
		cout<<"--ERROR, Archivo examenes NO se pudo crear / abrir --"<<endl;
	else{
		Examen exa;
		
		cout<<"-- INGRESO DATOS EXAMEN --"<<endl;
		cout<<"Matricula (0=fin): ";
		cin>>matricula;
		
		while(matricula != 0){
			exa.matricula=matricula;
			cout<<"Nombre: ";
			getline(cin, nombre);
			getline(cin, nombre);
			strcpy(exa.nombre, nombre.c_str());
			cout<<"Codigo: ";
			cin>>exa.codigo;
			cout<<"Nota: ";
			cin>>exa.nota;
			fwrite(&exa,sizeof(Examen),1,ArchExamenes);
			
			cout<<"-- INGRESO DATOS EXAMEN --"<<endl;
			cout<<"Matricula (0=fin): ";
			cin>>matricula;
		}	
	}
	fclose(ArchExamenes);
}

void buscarPorMatriculaCodigo(void){
	FILE * ArchExamenes = fopen("Examenes.dat","rb");
	
	if(ArchExamenes == NULL)
		cout<<"--ERROR, Archivo examenes NO se pudo abrir --"<<endl;
	else{
		Examen exa;
		int matricula,codigo;
		cout<<"Matricula del alumno: ";
		cin>>matricula;
		cout<<"Codigo de materia: ";
		cin>>codigo;
		
		fread(&exa,sizeof(Examen),1,ArchExamenes);
		while(matricula!=exa.matricula || codigo!=exa.codigo && !feof(ArchExamenes))
			fread(&exa,sizeof(Examen),1,ArchExamenes);
		
		if(!feof(ArchExamenes)){
			fseek(ArchExamenes,long(-sizeof(Examen)),SEEK_CUR);
			cout<<"Alumno con matricula: "<<matricula<<endl;
			cout<<"Materia con codigo: "<<codigo<<endl;
			if(exa.nota>=4.0)
				cout<<"--APROBADO--"<<endl;
			else
				cout<<"--DESAPROBADO--"<<endl;
			cout<<"Con nota: "<<exa.nota<<endl;
		} else
			cout<<"DATO NO ENCONTRADO"<<endl;
		
		fclose(ArchExamenes);
	}
}

void mostrarArchivoExamenes(void){
	FILE * ArchExamenes = fopen("Examenes.dat","rb");
	
	if(ArchExamenes == NULL)
		cout<<"--ERROR, Archivo examenes NO se pudo abrir --"<<endl;
	else{
		Examen exa;
		fread(&exa,sizeof(Examen),1,ArchExamenes);
		while(!feof(ArchExamenes)){
			cout<<"---------------------"<<endl;
			cout<<"Matricula: "<<exa.matricula<<endl;
			cout<<"Nombre: "<<exa.nombre<<endl;
			cout<<"Codigo: "<<exa.codigo<<endl;
			cout<<"Nota: "<<exa.nota<<endl;
			fread(&exa,sizeof(Examen),1,ArchExamenes);

		}
	}
	fclose(ArchExamenes);
}