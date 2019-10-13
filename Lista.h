#include<iostream>
using namespace std;
#pragma region TEMPLATE
class Lista {
public:
	Lista(char* _archivo) {}
	~Lista(){}
	void AgregarNodo() {

	}
	void MostrarNodo() {

	}
	void BuscarNodo() {

	}
	void EliminarNodo() {

	}
};
#pragma endregion
class Alumno {
private:
	int id = { 0 };
	long matricula = { 0 };
	char nombre[100] = { "" };
	char apellidoPaterno[100] = { "" };
	char apellidoMaterno[100] = { "" };
	char carrera[100] = { "" };
	Alumno* ant;
	Alumno* sig;
public:
	Alumno* lista = NULL;
	Alumno* tempant = NULL;
	/*Alumno(char* _archivo) {}
	~Alumno() {}*/
	void AgregarNodo(int _id, int _matricula, char _nombre[100], char _Paterno[100], char _Materno[100], char _carrera[100]) {
		Alumno* nuevo = new Alumno;
#pragma region DATOS
		nuevo->id = _id;
		nuevo->matricula = _matricula;
		strcpy_s(nuevo->nombre, _nombre);
		strcpy_s(nuevo->apellidoPaterno, _Paterno);
		strcpy_s(nuevo->apellidoMaterno, _Materno);
		strcpy_s(nuevo->carrera, _carrera);
#pragma endregion
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
		}
	}
	void MostrarNodo() {
		Alumno* aux = lista;
		while (aux != NULL) {
			imprimir(aux);
			aux = aux->sig;
		}
	}
	Alumno* BuscarNodo(int dato) {
		Alumno* aux = lista;
		Alumno* ant = NULL;
		while (aux != NULL) {
			if (aux->matricula == dato) {
				return aux;
				break;
			}
			ant = aux;
			tempant = ant;
			aux = aux->sig;
		}
		
	}
	void EliminarNodo(Alumno*_temp) {
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
	void imprimir(Alumno* _aux) {
		cout << _aux->id << endl;
		cout << _aux->matricula << endl;
		cout << _aux->nombre << endl;
		cout << _aux->apellidoPaterno << endl;
		cout << _aux->apellidoMaterno << endl;
		cout << _aux->carrera << endl;
		cout << endl;
	}
};

