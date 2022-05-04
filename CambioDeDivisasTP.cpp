#include "pch.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <vector>
#include <functional>
using namespace System;
using namespace std;
void Menu(float dineroActual);
void LecturaMonedas();
void LecturaUsuario();
void EscrituraUsuario(string nombre, int edad, int dni, float dinero);
void CrearUsuario();
void MostrarDineroActual(float dineroActual, string usuario);
float ModificarDineroActual(float dineroActual);
void CambioDivisas(float dineroActual);
vector<string> usuarioActual;
float cambioPorMonedas[7];
int i = 0;
float dineroActual = 0;

//-----------------------------------------------------------------------------------------------------------------------------------------------

template <class Generico>
class Nodo {
public:
	Generico valor;
	Nodo <Generico>* sig;
	Nodo(Generico val) {
		valor = val;
		sig = nullptr;
	}
};

template <class Generico>
class Lista {
	Nodo<Generico>* ini;
	Nodo<Generico>* fin;
	size_t cant;
public:
	Lista() {
		ini = fin = nullptr;
		cant = 0;
	}

	void push_front(Generico val) { //Al frente
		Nodo<Generico>* n = new Nodo<Generico>(val);
		if (cant == 0)
			ini = n;
		else {
			n->sig = ini;
			ini = n;
		}
		++cant;
	}

	void push_back(Generico val) { //Al ultimo
		Nodo<Generico>* nuevo = new Nodo<Generico>(val);
		if (ini == nullptr)
			ini = fin = nuevo;
		else {
			fin->sig = nuevo;
			fin = nuevo;
		}
		cant++;
	}

	void print(function<void(Generico)> print) { //Imprimir
		Nodo<Generico>* aux = ini;
		while (aux->sig != nullptr) {
			print(aux->valor);
			aux = aux->sig;
		}
	}
};

class SaldoTotal {
public:
	string MONEDA;
	float CANTIDAD;
	SaldoTotal(float CANTIDAD = 0) :CANTIDAD(CANTIDAD) {}
	string toString() {
		return MONEDA + " " + to_string(CANTIDAD);
	}
};

//-----------------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
	string nombre;
	int edad;
	int dni;
	float dinero;
}Usuario;

void CrearUsuario() {
	Usuario Usuario;
	cout << endl << "----------------------------------------------------------" << endl;
	cout << "Ingrese nombre de usuario: "; cin >> Usuario.nombre;
	usuarioActual.push_back(Usuario.nombre);
	cout << "Ingrese edad: "; cin >> Usuario.edad;
	cout << "Ingrese dni: "; cin >> Usuario.dni;
	cout << "Ingrese dinero: S/."; cin >> Usuario.dinero;
	dineroActual = Usuario.dinero;
	EscrituraUsuario(Usuario.nombre, Usuario.edad, Usuario.dni, Usuario.dinero);
	i++;
}

void LecturaUsuario() {
	ifstream archivo;
	string texto;
	archivo.open("USUARIOS.txt", ios::in);
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo.";
		system("pause");
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		cout << texto << endl;
	}
	archivo.close();
	char tecla = getch();
}
void EscrituraUsuario(string nombre, int edad, int dni, float dinero) {
	ofstream archivo;
	archivo.open("USUARIOS.txt", ios::out);
	if (archivo.is_open())
	{
		archivo << "-----------------------------------------------" << endl;
		archivo << "Nombre de usuario: " << nombre << endl;
		archivo << "Edad: " << edad << endl;
		archivo << "Dni: " << dni << endl;
		archivo << "Dinero acumulado: S/." << dinero << endl;
	}
	archivo.close();
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void CambioDivisas(float dineroActual)
{
	string TipoMoneda;
	int k;
	cout << "(Tipos de moneda valida : USD, EUR, RUB, MXN, JPY, AUD, CAD)" << endl;

	do {
		cout << "Escoga la moneda de cambio: "; cin >> TipoMoneda;
	} while (TipoMoneda != "USD" && TipoMoneda != "EUR" && TipoMoneda != "RUB" &&
		TipoMoneda != "MXN" && TipoMoneda != "JPY" && TipoMoneda != "AUD" && TipoMoneda != "CAD");

	auto cambioMoneda = [](float monto, float cambio) {return monto * cambio; };

	if (TipoMoneda == "USD") { cambioPorMonedas[0] = cambioMoneda(dineroActual, 0.27); k = 0; }
	if (TipoMoneda == "EUR") { cambioPorMonedas[1] = cambioMoneda(dineroActual, 0.25); k = 1; }
	if (TipoMoneda == "RUB") { cambioPorMonedas[2] = cambioMoneda(dineroActual, 18.58); k = 2; }
	if (TipoMoneda == "MXN") { cambioPorMonedas[3] = cambioMoneda(dineroActual, 5.31); k = 3; }
	if (TipoMoneda == "JPY") { cambioPorMonedas[4] = cambioMoneda(dineroActual, 33.79); k = 4; }
	if (TipoMoneda == "AUD") { cambioPorMonedas[5] = cambioMoneda(dineroActual, 0.37); k = 5; }
	if (TipoMoneda == "CAD") { cambioPorMonedas[6] = cambioMoneda(dineroActual, 0.33); k = 6; }

	cout << "Conversion de S/. " << dineroActual << " a " << TipoMoneda << " es de: " << cambioPorMonedas[k] << " " << TipoMoneda << endl;
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void LecturaMonedas() {
	ifstream archivo;
	string texto;
	archivo.open("MONEDAS.txt", ios::in);
	if (archivo.fail()) {
		cout << "\nNo se pudo abrir el archivo.";
		system("pause");
	}
	while (!archivo.eof()) {
		getline(archivo, texto);
		cout << texto << endl;
	}
	archivo.close();
	char tecla = getch();
}

float ModificarDineroActual (float dineroActual) {
	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << " Escriba el nuevo valor del dinero en la cuenta actual: S/."; cin >> dineroActual;
	cout << endl << " La operacion se ha realizado con exito" << endl;
	system("pause");
	return (dineroActual);
}

void MostrarDineroActual(float dineroActual, string usuario)
{
	cout << endl << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << " El dinero actual en la cuenta de " << usuario << " es de S/." << dineroActual << endl;
	system("pause");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

void nuevacuenta(string Moneda) {
	ofstream cuenta;
	float deposito;
	cuenta.open("CUENTAS.txt", ios::in);

	if (cuenta.fail()) {
		cout << "Hubo un error al abrir el archivo, presione cualquier tecla para regresar al menu...";
		char tecla = getch();
		return;
	}
	if (cuenta.is_open()) {
		cout << "Cuanto desea depositar?"; cin >> deposito;
		cuenta << Moneda << deposito;
	}
	cuenta.close();
}

void eliminarCuentas() {

	ofstream cuentas;
	cuentas.open("CUENTAS.txt", ios::out | ios::trunc);
	cuentas.close();
}

int main()
{
	Usuario Usuario;
	float dineroInicial = 0;
	string TipoMoneda;
	cout << endl << "-------------------------------------------------------------------------------" << endl << endl;
	cout << " Desarrollado por:\n";
	cout << "	Sebastian Pacheco Astiguetta\n";
	cout << "	Ivan Jeanpierre La Madrid Lozano\n";
	cout << endl << "-------------------------------------------------------------------------------" << endl << endl;
	cout << "Ingrese la cantidad de dinero con la que desea operar" << endl;
	cout << "Ingrese nombre de usuario: "; cin >> Usuario.nombre;
	usuarioActual.push_back(Usuario.nombre);
	cout << "Ingrese edad: "; cin >> Usuario.edad;
	cout << "Ingrese dni: "; cin >> Usuario.dni;
	cout << "Ingrese dinero: S/."; cin >> Usuario.dinero;
	dineroActual = Usuario.dinero;
	EscrituraUsuario(Usuario.nombre, Usuario.edad, Usuario.dni, Usuario.dinero);
	system("cls");

	Menu(Usuario.dinero);
}
void Menu(float dineroact)
{
	Lista<SaldoTotal> dinero;

	int opcion;
	cout << endl << "-------------------------------Cambio de divisas-------------------------------" << endl;
	cout << endl << " Usuario actual: " << usuarioActual[i] << endl;
	cout << endl << " 1.- Realizar un cambio de divisa inmediato" << endl;
	cout << " 2.- Mostrar la lista de monedas disponibles" << endl;
	cout << " 3.- Modificar el dinero en la cuenta actual." << endl;
	cout << " 4.- Crear un nuevo usuario." << endl;
	cout << " 5.- Mostrar los usuarios creados." << endl;
	cout << " 6.- Mostrar el dinero guardado en la cuenta actual." << endl;
	cout << " 7.- Eliminar las cuentas de ahorros." << endl;
	cout << endl << "-------------------------------------------------------------------------------" << endl;
	cout << endl << " Escoja una opcion: ";

	do {
		cin >> opcion;
		if (opcion < 1 || opcion > 8) cout << "Opcion " << opcion << " invalida. Ingrese nueva opcion: ";
	} while (opcion < 1 || opcion > 8);

	switch (opcion)
	{
	case 1:
		system("CLS");
		CambioDivisas(dineroActual);
		break;
	case 2:
		system("CLS");
		LecturaMonedas();
		break;
	case 3:
		system("CLS");
		dineroActual = ModificarDineroActual(dineroActual);

		break;
	case 4:
		system("CLS");
		CrearUsuario();
		break;
	case 5:
		system("CLS");
		LecturaUsuario();
		break;
	case 6:
		system("CLS");
		MostrarDineroActual(dineroActual, usuarioActual[i]);
		break;
	case 7:
		system("CLS");
		eliminarCuentas();
		break;
	default:
		break;
	}
	system("cls");
	Menu(dineroActual);
	system("pause");
}