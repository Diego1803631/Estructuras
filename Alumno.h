#pragma once
#include<fstream>
#include<iostream>
#include<time.h>
#include<string.h>
#include "resource.h"
#include"Materia.h"
class Alumno
{
private:
	int id{ 0 };
	int id_mat{ 0 };
	char matricula[100]{ 0 };
	char nombre[100]{ 0 };
	char apellido[100]{ 0 };
	Alumno* ant;
	Alumno* sig;
public:
	Alumno* lista = NULL;
	Alumno* tempant = NULL;
	int ctemp;
	Alumno();
	~Alumno();
	void Leer();
	void Escribir();
	void InsertarNodo(int,int, char[100], char[100], char[100]);
	void AgregaNodo(HWND Dlg);
	void EliminarNodo(Alumno* _temp);
	void Mostrar(HWND Dlg, int item);
	Alumno* BuscarNodo(char[100]);
	Alumno* BuscarID(char dato[100]);
	string GetMat(char[100]);
	void MostrarBuscado(HWND Dlg, Alumno*_temp);
	void EditarNodo(HWND Dlg, Alumno* _temp);
	void TransferirNodo(HWND Dlg, Alumno* _temp);
	void Inscribir(int, Alumno* aux);
	void eliminarnodos();
};
Alumno::Alumno() {
	/*fstream archivo("Alumnos.txt", ios::out | ios::app);
	archivo.close();
	archivo.open("Alumnos.txt", ios::in | ios::binary);
	if (archivo.is_open()) {
		Alumno* nuevo = new Alumno;
		archivo.read((char*)nuevo, sizeof(Alumno));
		while (!archivo.eof()) {
			nuevo->sig = NULL;
			Alumno* ultimo = lista;
			while (ultimo != NULL && ultimo->sig != NULL) {
				ultimo = ultimo->sig;
			}
			if (ultimo != NULL)
				ultimo->sig = nuevo;
			else
				lista = nuevo;
			nuevo = new Alumno;
			archivo.read((char*)nuevo, sizeof(Alumno));
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
	}*/
}
Alumno::~Alumno() {
	ofstream archivo;
	archivo.open("Alumnos.txt", ios::binary);
	if (archivo.is_open()) {
		Alumno* borrar = NULL;
		Alumno* aux = lista;
		while (aux != NULL) {
			archivo.write((char*)aux, sizeof(Alumno));
			borrar = aux;
			aux = (*aux).sig;
			delete borrar;
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
		eliminarnodos();
		PostQuitMessage(0);
	}
}
void Alumno::Leer() {
	fstream archivo("Alumnos.txt", ios::out | ios::app);
	archivo.close();
	archivo.open("Alumnos.txt", ios::in | ios::binary);
	if (archivo.is_open()) {
		Alumno* nuevo = new Alumno;
		archivo.read((char*)nuevo, sizeof(Alumno));
		while (!archivo.eof()) {
			nuevo->sig = NULL;
			Alumno* ultimo = lista;
			while (ultimo != NULL && ultimo->sig != NULL) {
				ultimo = ultimo->sig;
			}
			if (ultimo != NULL)
				ultimo->sig = nuevo;
			else
				lista = nuevo;
			nuevo = new Alumno;
			archivo.read((char*)nuevo, sizeof(Alumno));
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
	}
}
void Alumno::Escribir() {
	ofstream archivo;
	archivo.open("Alumnos.txt",ios::binary);
	if (archivo.is_open()) {
		Alumno* borrar = NULL;
		Alumno* aux = lista;
		while (aux != NULL) {
			archivo.write((char*)aux, sizeof(Alumno));
			borrar = aux;
			aux = (*aux).sig;
			delete borrar;
		}
		archivo.close();
	}
	else {
		MessageBox(0, "No es posible abrir el archivo.", "Aviso", MB_ICONINFORMATION);
		eliminarnodos();
		PostQuitMessage(0);
	}
}
void Alumno::InsertarNodo(int  _id, int _id_mat, char _matricula[100], char _nombre[100], char _apellido[100]) {
	Alumno* nuevo = new Alumno;
	nuevo->id = _id;
	nuevo->id_mat = _id_mat;
	strcpy_s(nuevo->matricula, _matricula);
	strcpy_s(nuevo->nombre, _nombre);
	strcpy_s(nuevo->apellido, _apellido);
	nuevo->ant = NULL;
	nuevo->sig = NULL;
	if (lista == NULL) {
		lista = nuevo;
	}
	else {
		Alumno* aux = lista;
		while (aux->sig != NULL) {
			aux = aux->sig;
		}
		aux->sig = nuevo;
		aux->sig->ant = aux;
		/*tempant = aux->ant;*/
	}
	
}
void Alumno::AgregaNodo(HWND Dlg) {
	SendDlgItemMessage(Dlg, IDC_NOMBRE, WM_GETTEXT, 100, (LPARAM)nombre);
	SendDlgItemMessage(Dlg, IDC_APELLIDO, WM_GETTEXT, 100, (LPARAM)apellido);
	id = id + 1;
	ctemp = atoi(matricula);
	srand(time(NULL));
	ctemp = 1800000 + rand() % 2000000;
	sprintf_s(matricula, "%d", ctemp);
	InsertarNodo(id,id_mat,matricula,nombre,apellido);
}
void Alumno::EliminarNodo(Alumno* _temp) {
	Alumno* aux = _temp;
	Alumno* ant = tempant;
	if (aux == lista) {
		lista = lista->sig;
	}
	else {
		ant->sig = aux->sig;
	}
	delete aux;
}
void Alumno::Mostrar(HWND Dlg,int item) {
	char tab[MAX_PATH] = { "" };
	Alumno* aux = lista;
	while(aux!=NULL) {
		strcat_s(tab, aux->matricula);
		strcat_s(tab, "\t\t\t");
		strcat_s(tab, aux->nombre);
		strcat_s(tab, " ");
		strcat_s(tab, aux->apellido);
		SendDlgItemMessage(Dlg, item, LB_ADDSTRING, 100, (LPARAM)tab);
		strcpy_s(tab, "");
		aux = aux->sig;
	}

}
Alumno* Alumno::BuscarNodo(char dato[100]) {
	Alumno* buscado = NULL;
	Alumno* aux = lista;
	while (aux != NULL) {
		if (strcmp(dato, aux->matricula) == 0) {
			buscado = aux;
			return buscado;
			break;
		}
		tempant = aux;
		aux = aux->sig;
	}
	tempant = aux->ant;
}
Alumno* Alumno::BuscarID(char dato[100]) {
	Alumno* buscado = NULL;
	Alumno* aux = lista;
	while (aux != NULL) {
		if (strcmp(dato, aux->nombre) == 0) {
			buscado = aux;
			return buscado;
			break;
		}
		tempant = aux;
		aux = aux->sig;
	}
	
}
string Alumno::GetMat(char dato[100]) {
	string aux = dato;
	string aux2 = aux.substr(0, 7);
	return aux2;
}
void Alumno::MostrarBuscado(HWND Dlg, Alumno* _temp) {
	char tab[MAX_PATH] = { "" };
	strcat_s(tab, _temp->matricula);
	strcat_s(tab, "\t\t\t");
	strcat_s(tab, _temp->nombre);
	strcat_s(tab, " ");
	strcat_s(tab, _temp->apellido);
	SendDlgItemMessage(Dlg, IDC_LIST2, LB_ADDSTRING, 100, (LPARAM)tab);
	strcpy_s(tab, "");
}
void Alumno::EditarNodo(HWND Dlg, Alumno* _temp) {
	Alumno* aux = _temp;
	SendDlgItemMessage(Dlg, IDC_NOMBRE, WM_GETTEXT, 100, (LPARAM)_temp->nombre);
	SendDlgItemMessage(Dlg, IDC_APELLIDO, WM_GETTEXT, 100, (LPARAM)_temp->apellido);
}
void Alumno::TransferirNodo(HWND Dlg, Alumno* _temp) {
	SendDlgItemMessage(Dlg, IDC_NOMBRE, WM_SETTEXT, 100, (LPARAM)_temp->nombre);
	SendDlgItemMessage(Dlg, IDC_APELLIDO, WM_SETTEXT, 100, (LPARAM)_temp->apellido);
}
void Alumno::Inscribir(int temp_id, Alumno* aux) {
	aux->id_mat = temp_id;
}
void Alumno::eliminarnodos() {
	if (lista == NULL) {
		delete lista;
	}
	else {
		Alumno* aux = lista;
		while (aux->sig != NULL) {
			lista = aux->sig;
			delete aux;
			aux = lista;
		}
		delete lista;
		lista = aux = NULL;
	}
}

