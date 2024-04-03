#include <iostream>
#include <fstream>
#include "locale.h"
#include <iomanip>
using namespace std;


void pokaz_macierz(double **x ,int count) {
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count + 1; j++) {
			cout<<setprecision(3) << setw(9) << x[i][j] << "  ";
			if (j == count - 1) cout << "| ";
		}
		cout << endl;
	}
	cout << endl;
}
bool licz_macierz_gauss_pivot(double **&x, int count, double m = 0) {
	for (int i = 0; i < count - 1; i++) {
		int max = i;
		for (int k = i + 1; k < count; k++) {
			if (abs(x[k][i]) > abs(x[max][i])) {
				max = k;
			}
		}
		if (i != max) {
			double* temp = x[i];
			x[i] = x[max];
			x[max] = temp;
		}
		for (int j = i + 1; j < count; j++) {
			m = (x[j][i]) / x[i][i];
			//pokaz_macierz(x, count);
			for (int k = i; k < count + 1; k++) {
				x[j][k] -= (m * x[i][k]);
			}
		}
	}
	return true;
}
bool licz_macierz_gauss_crout(double**& x, int count, int*& wektor, double m = 0) {
	for (int i = 0; i < count - 1; i++) {
		int max = i;
		for (int k = i + 1; k < count; k++) {
			if (abs(x[i][k]) > abs(x[i][max])) {
				max = k;
			}
		}
		if (i != max) {
			for (int j = 0; j < count; j++) {
				double temp = x[j][i];
				x[j][i] = x[j][max];
				x[j][max] = temp;
			}
			cout << endl << "NASTĄPIŁA ZMIANA KOLUMNY: " << i+1 << " z kolumną: " << max+1 << endl;
			wektor[i] = max;
		}
		for (int j = i + 1; j < count; j++) {
			m = (x[j][i]) / x[i][i];
			//pokaz_macierz(x, count);
			for (int k = i; k < count + 1; k++) {
				x[j][k] -= (m * x[i][k]);
			}
		}
	}
	return true;
}
void policz_to(double** x,double*& vals, int count) {
	vals[count - 1] = x[count - 1][count] / x[count - 1][count - 1];
	for (int i = count - 2; i >= 0; i--) {
		double temp = 0.0;

		for (int k = i + 1; k < count; k++) {
			temp += x[i][k] * vals[k];
		}
		vals[i] = (x[i][count] - temp) / x[i][i];
	}
}
void printuj_rozwiazania(double* vals, int count) {
	for (int i = 0; i < count; i++) {
		cout << "x" << i << " = " << vals[i];
		cout << endl;
	}

}
void odwroc_vals_crout(double*& vals, int* wektor, int count) {
	for (int i = count - 2; i >= 0; i--) {
		/*double pom = vals[i];
		vals[i] = vals[wektor[i]];
		vals[wektor[i]] = pom;*/
		if(wektor[i] != 0)
			swap(vals[i], vals[wektor[i]]);
	}
}
int main() {
	setlocale(LC_CTYPE, "Polish");
	ifstream h("data3.txt");

	int count;
	h >> count;

	double** x = new double* [count];
	double* vals = new double[count];
	int* wektor = new int[count];

	bool isCroute = false, isPivo = false;

	for (int i = 0; i < count+1; i++) {
		x[i] = new double[count];
		vals[i] = 0;
		wektor[i] = 0;
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count + 1; j++) {
			h >> x[i][j];
			if (i == j && x[i][j] == 0) {
				cout << "Zero na przekątnej." << endl;
				exit(-1);
			}
		}
	}
	h.close();

	cout << "Macierz rozszerzona przed obliczeniami" << endl;
	pokaz_macierz(x, count);

	//cout << "kazdy krok w zerowaniu macierzy: " << endl;
	//isCroute = licz_macierz_gauss_crout(x, count, wektor);
	isPivo = licz_macierz_gauss_pivot(x, count);

	
	cout << endl << "Macierz rozszerzona po postępowaniu prostym" << endl;
	pokaz_macierz(x, count);

	policz_to(x,vals,count);

	if (isPivo) {
		cout << "Rozwiązania: " << endl;
		printuj_rozwiazania(vals, count);
	}

	if (isCroute) {
		odwroc_vals_crout(vals, wektor, count);
		cout << "Rozwiązania: " << endl;
		printuj_rozwiazania(vals, count);
	}

	return 0;
}
