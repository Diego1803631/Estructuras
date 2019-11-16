#pragma region Directivas
#include<iostream>
#include <Windows.h>
#include <string>
#include<fstream>
#include <commdlg.h>
#include "resource.h"
#include"Coordinador.h"
#include"Materia.h"
#include"Semestre.h"
#include"Alumno.h"
#include"Calificaciones.h"
#include "Semestre.h"
#include "Materia.h"
#include "Alumno.h"
#include "Calificaciones.h"
#pragma endregion
using namespace std;
int gShow = 0;
HWND ghDlg = 0;
HINSTANCE ghInst;
struct Temporal {
	char UsuarioTemp[100];
	char NombreTemp[100] = {"Diego Flores"};
	char ContraseñaTemp[100] = { "12345" };
}user;
char contraseña[100];
char folder[MAX_PATH] = "";
char logo[MAX_PATH] = { "C:/Users/Diego Alberto Flores/Documents/5to/Estructura de datos/Avance/Avance/FCFM3.bmp" };
int index;
int temp_id;
bool coor_gen = false;
bool coor_car = false;
bool buscado = false;
bool editar = false;
char btemp[100] = { " " };
char mtemp[100];
Coordinador coordinador;
Semestre semestre;
Materia materia;
Alumno alumno;
Calificaciones calificaciones;
#pragma region Declaraciones
BOOL CALLBACK vUsuario(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vCoordinadorGeneral(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vCoordinadorCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vPeriodo(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vMateria(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vAlumno(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vInscribir(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vCalificaciones(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vKardex(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
BOOL CALLBACK vBusqueda(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam);
int  WINAPI  WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmd, int show)
{
	alumno.Leer();
	semestre.Leer();
	materia.Leer();
	calificaciones.Leer();
	ghInst = hInst;
	gShow = show;
	ghDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), 0, vUsuario);
	ShowWindow(ghDlg, show);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (GetMessage(&msg, 0, 0, 0))
	{
		if (ghDlg == 0 || !IsDialogMessage(ghDlg, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}
BOOL CALLBACK vUsuario(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	switch (Mensaje) {
	case WM_INITDIALOG: {
		SendMessage(Dlg, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK)));
		SendMessage(Dlg, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, MAKEINTRESOURCE(IDI_ASTERISK)));
		SendDlgItemMessage(Dlg, IDC_USUARIO, CB_ADDSTRING, 100, (LPARAM)"Coordinador General");
		SendDlgItemMessage(Dlg, IDC_USUARIO, CB_ADDSTRING, 100, (LPARAM)"Coordinador de Carrera");
		return true;
	}
	case WM_COMMAND:{
		switch (LOWORD(wParam)){
		case IDOK:
			SendDlgItemMessage(Dlg, IDC_CONTRA, WM_GETTEXT, 100, (LPARAM)contraseña);
			if (strcmp(contraseña, user.ContraseñaTemp) == 0) {
				index = SendDlgItemMessage(Dlg, IDC_USUARIO, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(Dlg, IDC_USUARIO, CB_GETLBTEXT, (WPARAM)index, (LPARAM)user.UsuarioTemp);
				if (strcmp(user.UsuarioTemp, "Coordinador General") == 0) {
					coor_gen = true;
					EndDialog(Dlg, 0);
					ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
					ShowWindow(ghDlg, gShow);
				}
				else {
					coor_car = true;
					EndDialog(Dlg, 0);
					ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
					ShowWindow(ghDlg, gShow);
				}
			}
			return true;
		case IDCANCEL:
			PostQuitMessage(0);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
void Inscribir(HWND Dlg);
#pragma endregion
#pragma region CoordinadorGeneral
BOOL CALLBACK vCoordinadorGeneral(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam)
{
	static HBITMAP bmp1, bmp2;
	bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_IMAGE, STM_GETIMAGE, IMAGE_BITMAP, 0);
	bmp2 = (HBITMAP)LoadImage(NULL, logo, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	switch (Mensaje) {
	case WM_INITDIALOG: {
		SendDlgItemMessage(Dlg, IDC_IMAGE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_ARCHIVO_SALIR:
			PostQuitMessage(0);
			return true;
		case ID_VER_KARDEX:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG10), 0, vKardex);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_NUEVO_COORDINADOR:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG4), 0, vCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_NUEVO_SEMESTRE:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG5), 0, vPeriodo);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_NUEVO_MATERIA:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG6), 0, vMateria);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_BUSQUEDA:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG11), 0, vBusqueda);
			ShowWindow(ghDlg, gShow);
			/*coordinador.PreOrden(coordinador.raiz);*/
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	static HBITMAP bmp1, bmp2;
	bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_IMAGE, STM_GETIMAGE, IMAGE_BITMAP, 0);
	bmp2 = (HBITMAP)LoadImage(NULL, coordinador.foto, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	switch (Mensaje) {
	case WM_INITDIALOG: {
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_FOTO:
			coordinador.openfilename();
			if (GetOpenFileName(&ofn) == TRUE) {
				SetWindowText(GetDlgItem(Dlg, IDC_INFO), ofn.lpstrFile);
			}
			SendDlgItemMessage(Dlg, IDC_IMAGE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			return true;
		case ID_NUEVA:
			EnableWindow(GetDlgItem(Dlg, IDC_CN), true);
			EnableWindow(GetDlgItem(Dlg, IDC_CC), true);
			EnableWindow(GetDlgItem(Dlg, IDC_CS), true);
			EnableWindow(GetDlgItem(Dlg, IDC_CD), true);
			return true;
		case IDOK:
			coordinador.AgregarCarrera(Dlg);
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vPeriodo(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		SendDlgItemMessage(Dlg, IDC_RADIO1, BM_SETCHECK, BST_CHECKED, 0);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
			semestre.AgregaNodo(Dlg);
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vMateria(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
			materia.AgregaNodo(Dlg);
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
#pragma endregion
#pragma region CoordinadorCarrera
BOOL CALLBACK vCoordinadorCarrera(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	static HBITMAP bmp1, bmp2;
	bmp1 = (HBITMAP)SendDlgItemMessage(Dlg, IDC_IMAGE, STM_GETIMAGE, IMAGE_BITMAP, 0);
	bmp2 = (HBITMAP)LoadImage(NULL, logo, IMAGE_BITMAP, 100, 100, LR_LOADFROMFILE);
	switch (Mensaje) {
	case WM_INITDIALOG: {
		editar = false;
		SendDlgItemMessage(Dlg, IDC_IMAGE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_ARCHIVO_SALIR:
			/*alumno.Escribir();*/
			PostQuitMessage(0);
			return true;
		case ID_VER_KARDEX:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG10), 0, vKardex);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_NUEVO_ALUMNO:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG7), 0, vAlumno);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_ALUMNO_INSCRIBIR:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG8), 0, vInscribir);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_ALUMNO_CALIFICACIONES:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG9), 0, vCalificaciones);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_BUSQUEDA:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG11), 0, vBusqueda);
			ShowWindow(ghDlg, gShow);
			return true;

		}
		return true;
	}
	case WM_CLOSE: {
		/*alumno.eliminarnodos();*/
		PostQuitMessage(0);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vAlumno(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		if (editar) 
			alumno.TransferirNodo(Dlg, alumno.BuscarNodo(mtemp));
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
			if (editar)
				alumno.EditarNodo(Dlg, alumno.BuscarNodo(mtemp));
			else
				alumno.AgregaNodo(Dlg);
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vInscribir(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		alumno.Mostrar(Dlg,IDC_LIST1);
		materia.Mostrar(Dlg,IDC_LIST2);
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_INS:
			Inscribir(Dlg);
			MessageBox(0, "Inscripción completada.", "Aviso", MB_ICONINFORMATION);
			return true;
		case IDCANCEL:
			EndDialog(Dlg, 0);
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vCalificaciones(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
#pragma endregion
BOOL CALLBACK vKardex(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		return true;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if(coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
BOOL CALLBACK vBusqueda(HWND Dlg, UINT Mensaje, WPARAM wParam, LPARAM lparam) {
	switch (Mensaje) {
	case WM_INITDIALOG: {
		strcpy_s(btemp, " ");
		if (coor_gen) {
			SendDlgItemMessage(Dlg, IDC_TIPO, CB_ADDSTRING, 100, (LPARAM)"Coordinador");
			SendDlgItemMessage(Dlg, IDC_TIPO, CB_ADDSTRING, 100, (LPARAM)"Semestre");
			SendDlgItemMessage(Dlg, IDC_TIPO, CB_ADDSTRING, 100, (LPARAM)"Materia");
		}
		SendDlgItemMessage(Dlg, IDC_TIPO, CB_ADDSTRING, 100, (LPARAM)"Alumno");
		SendDlgItemMessage(Dlg, IDC_TIPO, CB_ADDSTRING, 100, (LPARAM)"Calificaciones");
		return true;
	}
	case WM_COMMAND:
	{

		switch (LOWORD(wParam)) {
		case ID_CANCEL:
			EndDialog(Dlg, 0);
			if (coor_gen)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
			if (coor_car)
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
			ShowWindow(ghDlg, gShow);
			return true;
		case ID_BUSC:
			SendDlgItemMessage(Dlg, IDC_LIST2, LB_RESETCONTENT, 0,0);
			EnableWindow(GetDlgItem(Dlg, IDC_BA), false);
			EnableWindow(GetDlgItem(Dlg, ID_BUSC2), false);
			index = SendDlgItemMessage(Dlg, IDC_TIPO, CB_GETCURSEL, 0, 0);
			SendDlgItemMessage(Dlg, IDC_TIPO, CB_GETLBTEXT, (WPARAM)index, (LPARAM)btemp);
			if (strcmp(btemp, "Coordinador") == 0) {
				coordinador.PreOrden(coordinador.raiz, Dlg);
			}
			if (strcmp(btemp, "Alumno") == 0) {
				EnableWindow(GetDlgItem(Dlg, IDC_BA), true);
				EnableWindow(GetDlgItem(Dlg, ID_BUSC2), true);
				alumno.Mostrar(Dlg,IDC_LIST2);
			}
			if (strcmp(btemp, "Materia") == 0) {
				materia.Mostrar(Dlg, IDC_LIST2);
			}
			return true;
		case ID_BUSC2:
			SendDlgItemMessage(Dlg, IDC_LIST2, LB_RESETCONTENT, 0, 0);
			SendDlgItemMessage(Dlg, IDC_BA, WM_GETTEXT, 100, (LPARAM)mtemp);
			alumno.MostrarBuscado(Dlg, alumno.BuscarNodo(mtemp));
			return true;
		case ID_EDITAR:
			index = SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETCURSEL, 0, 0);
			SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETTEXT, (WPARAM)index, (LPARAM)mtemp);
			strcpy_s(mtemp, alumno.GetMat(mtemp).c_str());
			editar = true;
			if (strcmp(btemp, "Coordinador") == 0) {
				EndDialog(Dlg, 0);
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG4), 0, vCarrera);
				ShowWindow(ghDlg, gShow);
			}
			if (strcmp(btemp, "Semestre") == 0) {
				EndDialog(Dlg, 0);
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG5), 0, vPeriodo);
				ShowWindow(ghDlg, gShow);
			}

			if (strcmp(btemp, "Materia") == 0) {
				EndDialog(Dlg, 0);
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG6), 0, vMateria);
				ShowWindow(ghDlg, gShow);
			}

			if (strcmp(btemp, "Alumno") == 0) {
				EndDialog(Dlg, 0);
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG7), 0, vAlumno);
				ShowWindow(ghDlg, gShow);
			}

			if (strcmp(btemp, "Calificaciones") == 0) {
				EndDialog(Dlg, 0);
				ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG9), 0, vCalificaciones);
				ShowWindow(ghDlg, gShow);
			}
			return true;
		case ID_ELIMINAR:
			index = SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETCURSEL, 0, 0);
			SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETTEXT, (WPARAM)index, (LPARAM)mtemp);
			strcpy_s(mtemp, alumno.GetMat(mtemp).c_str());
			alumno.EliminarNodo(alumno.BuscarNodo(mtemp));
			MessageBox(0, "Elemento eliminado.", "Aviso", MB_ICONINFORMATION);
			SendDlgItemMessage(Dlg, IDC_LIST2, LB_RESETCONTENT, 0, 0);
			return true;
		}
		return true;
	}
	case WM_CLOSE: {
		EndDialog(Dlg, 0);
		if (coor_gen)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG2), 0, vCoordinadorGeneral);
		if (coor_car)
			ghDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DIALOG3), 0, vCoordinadorCarrera);
		ShowWindow(ghDlg, gShow);
		return true;
	}
	case WM_DESTROY: {
		return true;
	}
	} return false;
}
void Inscribir(HWND Dlg) {
	index = SendDlgItemMessage(Dlg, IDC_LIST1, LB_GETCURSEL, 0, 0);
	SendDlgItemMessage(Dlg, IDC_LIST1, LB_GETTEXT, (WPARAM)index, (LPARAM)mtemp);
	index = SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETCURSEL, 0, 0);
	SendDlgItemMessage(Dlg, IDC_LIST2, LB_GETTEXT, (WPARAM)index, (LPARAM)btemp);
	temp_id = materia.BuscarID(btemp);
	alumno.Inscribir(temp_id, alumno.BuscarNodo(mtemp));
}
//USAR BOOLS-Agregar tiempos para inscripciones, calificaciones, etc.

