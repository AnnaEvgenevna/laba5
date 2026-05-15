#include <iostream>
using namespace std;
//Реализовать класс Point, описывающий точку в двумерном(или трёхмерном)
//пространстве.Предусмотреть поля, хранящие координаты по X и Y.Сделать
//конструктор по умолчанию, конструктор с параметрами, геттеры и сеттеры для
//всех полей, а также методы, позволяющие переместить точку(например -
  //  вверх, вниз, влево, вправо) на указанное количество единиц.



class Point {

public:

	double x;
	double y;

	Point() {
		x = 0;
		y = 0;
	}

	Point(double a, double b) {
		x = a;
		y = b;
	}

	double get_x() {  ///только считываю.т
		return x;
	}

	double get_y() {
		return y;
	}

	void set_x(double x1) { //изменяют значения
		x = x1;
	}

	void set_y(double y1) {
		y = y1;
	}




	void right(double x1) {
		x = x + x1;
	}

	void left(double x1) {
		x = x - x1;
	}

	void up(double y1) {
		y = y + y1;
	}

	void down(double y1) {
		y = y - y1;
	}




	void show() {
		cout << "x = " << x << " y = " << y << "\n\n\n";
	}




};





int main()
{
	setlocale(LC_ALL, "RUSSIAN");


	int a;
	int b;

	//Point p1;

	cout << "Введите координату x ";
	cin >> a;

	cout << "Введите координату y ";
	cin >> b;

	Point p1(a, b);



	cout << "На сколько единиц вы хотите переместить точку вверх? ";
	cin >> a;
	p1.up(a);

	cout << "На сколько единиц вы хотите переместить точку вниз? ";
	cin >> a;
	p1.down(a);

	cout << "На сколько единиц вы хотите переместить точку вправо? ";
	cin >> a;
	p1.right(a);

	cout << "На сколько единиц вы хотите переместить точку влево? ";
	cin >> a;
	p1.left(a);

	p1.show();

	cout << "Введите координату x ";
	cin >> a;
	p1.set_x(a);

	cout << "Введите координату y ";
	cin >> a;
	p1.set_y(a);


	p1.show();


}