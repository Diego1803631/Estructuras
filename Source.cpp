#include<iostream>
#include<time.h>
#include "Lista.h"
using namespace std;
#pragma region DECLARACIONES
Alumno alumno;
void CapturarNodo();
void CapturaBusqueda();
#pragma endregion
void main() {
	while (1) {
#pragma region MENU
		system("cls");
		cout << "MENU" << endl;
		cout << "1.Registro de Coordinadores" << endl;//carrera
		cout << "2.Creacion de Semestre" << endl;
		cout << "3.Registro de Materias" << endl;
		cout << "4.Registro de Alumnos" << endl;
		cout << "5.Proceso de Inscripciones" << endl;
		cout << "6.Captura de Calificaciones" << endl;
		cout << "7.Mostrar" << endl;
		cout << "8.BuscarAlumno" << endl;
		cout << "9.Salir" << endl;
#pragma endregion
		int op;
		cout << "Escoja una opcion: "; cin >> op;
		switch (op)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			system("cls");
			cout << "Registro de Alumnos" << endl;
			CapturarNodo();
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			system("cls");
			cout << "Mostrar" << endl;
			alumno.MostrarNodo();
			system("PAUSE");
			break;
		case 8:
			system("cls");
			cout << "Buscar" << endl;
			CapturaBusqueda();
			system("PAUSE");
			break;
		default:
			delete alumno.lista;
			exit(0);
			break;
		}
	}


	system("PAUSE");
}
void CapturarNodo() {
	int id;
	long matricula;
	char nombre[100];
	char apellidoPaterno[100];
	char apellidoMaterno[100];
	char carrera[100];
	srand(time(NULL));
	id = 1 + rand() % (100);
	matricula = 1800000 + rand() % 2000000;
	try {
		cout << "Nombre/s: ";
		cin >> nombre;
		cout << "Apellido Paterno: ";
		cin >> apellidoPaterno;
		cout << "Apellido Materno: ";
		cin >> apellidoMaterno;
		cout << "Carrera: ";
		cin >> carrera;
		if (strlen(nombre) > 100 || strlen(apellidoPaterno) > 100 || strlen(apellidoMaterno) > 100 || strlen(carrera) > 100)
			throw 1;
	}
	catch (int n) {
		cout << "Error" << endl;
	}
	alumno.AgregarNodo(id, matricula, nombre, apellidoPaterno, apellidoMaterno, carrera);
}
void CapturaBusqueda() {
	long mat;
	int op = 0;
	Alumno* temp = NULL;
	cout << "Ingrese la matricula: ";
	cin >> mat;
	temp = alumno.BuscarNodo(mat);
	alumno.imprimir(temp);
	cout << "Desea eliminarlo? 1)si/2)no: ";
	cin >> op;
	if (op == 1) {
		alumno.EliminarNodo(temp);
	}
}
