#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void resolver(int Nx, int Nt, string archivo);

int main() {
	
	int Nx = 100;
	int Nt = 1000;
	resolver(Nx, Nt, "onda1.dat");

	return 0;
}

void resolver(int Nx, int Nt, string archivo){
	float rho = 0.01;	// mass density of the string in kg/m
	float T = 40;		// Tension of the string in N
	float L = 1;		// Length of the string
	float c = sqrt(T/rho);
	float pi = 3.14159265359;
	float t_ini = 0.0;
	float t_fin = 0.1;
	float x_izq = 0.0;
	float x_der = L;
	float chi_izq = 0.0;
	float chi_der = 0.0;
	float delta_t = (t_fin-t_ini)/Nt;
	float delta_x = (x_der-x_izq)/Nx;
	float cp = delta_x/delta_t;
	float chi_n[Nx];
	float chi_n_plus_1[Nx];
	float chi_n_minus_1[Nx];
	float temporal[Nx];

	ofstream outfile;
	outfile.open(archivo);

	// Este for establece la condicion inicial
	for(int i=0; i < Nx; i++){
		if(i==0) {
			chi_n[i] = chi_izq;
			chi_n_plus_1[i] = chi_izq;
			chi_n_minus_1[i] = chi_izq;
		} else if(i==Nx-1) {
			chi_n[i] = chi_der;
			chi_n_plus_1[i] = chi_der;
			chi_n_minus_1[i] = chi_der;
		} else {
			chi_n[i] = 0.0001*sin(2*pi*i*delta_x/L);
		}
		outfile << chi_n[i] << " ";
	}
	outfile << endl;

	// Primera iteración
	outfile << chi_n_plus_1[0] << " ";
	for(int i = 1; i < Nx-1; i++) {
		chi_n_plus_1[i] = chi_n[i] + pow(c,2)/(2*pow(cp,2))*(chi_n[i+1]-2*chi_n[i]+chi_n[i-1]); 
		outfile << chi_n_plus_1[i] << " ";
	}
	outfile << chi_n_plus_1[Nx-1] << " ";
	outfile << endl;
	for(int i = 0; i < Nx; i++){
		chi_n_minus_1[i] = chi_n[i];
		chi_n[i] = chi_n_plus_1[i];
	}

	// Este while resuelve la ecuacion diferencial parcial
	while(t_ini+delta_t < t_fin) {
		outfile << chi_n_plus_1[0] << " ";
		for(int i = 1; i < Nx-1; i++){
			chi_n_plus_1[i] = 2*chi_n[i] - chi_n_minus_1[i] + pow(c,2)/pow(cp,2)*(chi_n[i+1]-2*chi_n[i]+chi_n[i-1]); 
			outfile << chi_n_plus_1[i] << " ";
		}
		outfile << chi_n_plus_1[Nx-1] << " ";
		outfile << endl;
		for(int i = 0; i < Nx; i++){
			chi_n_minus_1[i] = chi_n[i];
			chi_n[i] = chi_n_plus_1[i];
		}
		t_ini += delta_t;
	}
	outfile.close();
}