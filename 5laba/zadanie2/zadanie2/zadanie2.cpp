#include <iostream>
#include <string>
#include <cmath>
#include <numeric> ///для нод
using namespace std;


class Fraction {

public:
	//обязательные поля числитель и знаменатель, целочисленные
	int chislitel;
	int znamenatel;

	Fraction() { //конструктор по умолчанию
		chislitel = 1;
		znamenatel = 1;
	}

	Fraction(double a) { //конструктор с одним параметром, передается десятичная дробь

		string c = to_string(a);

		int n = c.size();
		int k = 0;



		for (int i = n - 1; i > 0; i--) {
			if (c[i] == ',') {
				break;
			}

			else if (c[i] != '0' || k != 0) {
				k = k + 1;
			}

		}


		chislitel = a * pow(10, k);
		znamenatel = pow(10, k);

	}


	Fraction(int a, int b) { // конструктор с двумя параметрами

		chislitel = a;
		znamenatel = b;

		if (znamenatel == 0) { // знаменатель не равен нулю, если равен, то заменяем на 1
			cout << "Знаменатель не может быть равен нулю\n";
			znamenatel = 1;
		}



	}


	//сеттеры
	void set_chislitel(double x1) { //изменяют значения
		chislitel = x1;
	}

	void set_znamenatel(double y1) { //знаменатель не ноль
		znamenatel = y1;

		if (znamenatel == 0) {
			cout << "Знаменатель не может быть равен нулю\n";
			znamenatel = 1;
		}

	}

	//геттеры
	double get_chislitel() {  ///только считывают
		return chislitel;
	}

	double get_znamenatel() {
		return znamenatel;
	}



	void show() { //показ дроби на экран
		cout << chislitel << " / " << znamenatel << "\n\n\n";
	}

	//возврат значения типа double на основании значений числителя и знаменателя дроби,
	double vozvrat() {
		return double(chislitel) / double(znamenatel);

	}


	//сокращение дроби,
	void sokratit_drob() {
		int n = gcd(chislitel, znamenatel); //нод
		znamenatel = znamenatel / n;
		chislitel = chislitel / n;
	}






	//сравнение дробей,
	void sravnenie_drobey(Fraction ob2) {

		int znamenatel2 = ob2.znamenatel;

		int chislitel2 = ob2.chislitel;

		if (znamenatel == znamenatel2) {
			if (chislitel > chislitel2) {
				cout << chislitel << "/" << znamenatel << " > " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}
			else if (chislitel == chislitel2) {
				cout << chislitel << "/" << znamenatel << " = " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}
			else {
				cout << chislitel << "/" << znamenatel << " < " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}
		}
		else {

			if (chislitel * znamenatel2 > chislitel2 * znamenatel) {
				cout << chislitel << "/" << znamenatel << " > " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}
			else if (chislitel * znamenatel2 == chislitel2 * znamenatel) {
				cout << chislitel << "/" << znamenatel << " = " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}
			else {
				cout << chislitel << "/" << znamenatel << " < " << chislitel2 << "/" << znamenatel2 << "\n\n";
			}

		}

	}







	//сложение,
	void slozhenie_drobey(Fraction ob2) {

		int znamenatel2 = ob2.znamenatel;

		int chislitel2 = ob2.chislitel;

		if (znamenatel == znamenatel2) {
			int z = chislitel + chislitel2;
			cout << chislitel << "/" << znamenatel << " + " << chislitel2 << "/" << znamenatel2 << " = " << z << "/" << znamenatel << "\n\n";
		}
		else {
			int z = chislitel * znamenatel2 + chislitel2 * znamenatel;
			cout << chislitel << "/" << znamenatel << " + " << chislitel2 << "/" << znamenatel2 << " = " << z << "/" << znamenatel * znamenatel2 << "\n\n";

		}

	}





	//вычитание,
	void vichitanie_drobey(Fraction ob2) {

		int znamenatel2 = ob2.znamenatel;

		int chislitel2 = ob2.chislitel;

		if (znamenatel == znamenatel2) {
			int z = chislitel - chislitel2;
			cout << chislitel << "/" << znamenatel << " - " << chislitel2 << "/" << znamenatel2 << " = " << z << "/" << znamenatel << "\n\n";
		}
		else {
			int z = chislitel * znamenatel2 - chislitel2 * znamenatel;
			cout << chislitel << "/" << znamenatel << " - " << chislitel2 << "/" << znamenatel2 << " = " << z << "/" << znamenatel * znamenatel2 << "\n\n";

		}

	}




	//умножение,
	void umnozhenie_drobey(Fraction ob2) {

		int znamenatel2 = ob2.znamenatel;

		int chislitel2 = ob2.chislitel;



		cout << chislitel << "/" << znamenatel << " * " << chislitel2 << "/" << znamenatel2 << " = " << chislitel * chislitel2 << "/" << znamenatel * znamenatel2 << "\n\n";



	}





	//деление дробей

	void delenie_drobey(Fraction ob2) {

		int znamenatel2 = ob2.znamenatel;

		int chislitel2 = ob2.chislitel;



		cout << chislitel << "/" << znamenatel << " : " << chislitel2 << "/" << znamenatel2 << " = " << chislitel * znamenatel2 << "/" << znamenatel * chislitel2 << "\n\n";

	}

};
int main()
{
	setlocale(LC_ALL, "RUSSIAN");

	Fraction d1;
	Fraction d2(5.2457);
	Fraction d3(1, 4);

	d2.show();
	d2.sokratit_drob();
	d2.show();

	d1.sravnenie_drobey(d3);
	d1.slozhenie_drobey(d2);
	d1.vichitanie_drobey(d2);
	d1.umnozhenie_drobey(d3);
	d1.delenie_drobey(d3);
	cout << d3.vozvrat();


}
