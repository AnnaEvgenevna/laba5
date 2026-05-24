//Описать класс, реализующий тип данных "вещественная матрица" и работу с ними.

//Лабораторная работа 6
// Дьяковой Анны 4.301-1

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <stdexcept> //для исключений (ошибок)

using namespace std;
class Matrix {
private:
    vector<vector<double>> data; //двумерный вещественный массив
    int rows, cols;


    // единичная матрица //мне понадобилась для возведения в степень
    static Matrix edinitsa(int n) {
        Matrix resultat(n, n);
        for (int i = 0; i < n; ++i)
            resultat.data[i][i] = 1.0;
        return resultat;
    }

public:
    // Конструктор без параметров
    Matrix() {
        rows = 0;
        cols = 0;
    }

    //Конструктор с параметрами
    explicit Matrix(int r, int c) {
        rows = r;
        cols = c;
        data.assign(rows, vector<double>(cols, 0.0)); //создает rows штук векторов и запоняет нулями, это инициализация матрицы нулями
    }


    int get_Rows() const { 
        return rows; 
    }

    int get_Cols() const { 
        return cols; 
    }


    Matrix(const Matrix& other) = default;

    // Оператор присваивания
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }
   
   
    // сложение
    Matrix operator+(const Matrix& other) const {

        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Для сложения матриц их размеры должны совпадать!");

        Matrix resultat(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                resultat.data[i][j] = data[i][j] + other.data[i][j];

        return resultat;
    }

    //вычитание
    Matrix operator-(const Matrix& other) const {

        if (rows != other.rows || cols != other.cols)
            throw invalid_argument("Для вычитания матриц их размеры должны совпадать!");

        Matrix resultat(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                resultat.data[i][j] = data[i][j] - other.data[i][j];

        return resultat;
    }

    //умножение на матрицу
    Matrix operator*(const Matrix& other) const {

        if (cols != other.rows)
            throw invalid_argument("Умножение невозможно, так как число столбцов матрицы А != числу чтрок матрицы В!");

        Matrix result(rows, other.cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j)
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];

        return result;
    }

    Matrix operator/(const Matrix& other) const {

        if (rows != cols || other.rows != other.cols)
            throw invalid_argument("Деление матриц определено только для квадратных матриц");

        if (rows != other.rows)
            throw invalid_argument("Для деления матрицы должны быть одного размера");

        return *this * other.inverse(); //деление это умножение на обратную
    }



    //умножение на скаляр
    Matrix operator*(double c) const {

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] * c; //поэлеметное умножение на число

        return result;
    }

    //деление на скаляр
    Matrix operator/(double c) const {

        if (c == 0) 
            throw invalid_argument("Нельзя делить на ноль!");

        Matrix result(rows, cols);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] / c; //поэлементное деление на скаляр

        return result;
    }

    //Комбинированные операции присваивания(+=, -=, *=, /=)
    Matrix& operator+=(const Matrix& other) {
        *this = *this + other; return *this; 
    }

    Matrix& operator-=(const Matrix& other) { 
        *this = *this - other; return *this; 
    }

    Matrix& operator*=(const Matrix& other) { 
        *this = *this * other; return *this; 
    }

    Matrix& operator/=(const Matrix& other) {
        *this = *this / other; return *this;
    }

    Matrix& operator*=(double scalar) { 
        *this = *this * scalar; return *this; 
    }

    Matrix& operator/=(double scalar) { 
        *this = *this / scalar; return *this; 
    }


    //Операции сравнения на равенство / неравенство
    bool operator==(const Matrix& other) const {

        if (rows != other.rows || cols != other.cols) 
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] != other.data[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix& other) const {

        if (rows != other.rows || cols != other.cols)
            return true; //если размеры различаются, матрицы не равны

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] != other.data[i][j])
                    return true; //если хотя бы один элемент отличается, то не равны
        return false;              
    }


    // Транспонирование матрицы
    Matrix transponirovanie() const {

        Matrix resultat(cols, rows);

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                resultat.data[j][i] = data[i][j];

        return resultat;
    }

    //Метод вычисления определителя
    double det() const {

        if (rows != cols) 
            throw invalid_argument("Определитель существует только для квадратных матриц");

        Matrix t = *this; //копия, чтобы не испортить оригинальную матрицу.
        double det = 1.0; //начальное значение

        for (int i = 0; i < rows; ++i) {
            int l = i; 
            for (int j = i + 1; j < rows; ++j)
                if (abs(t.data[j][i]) > abs(t.data[l][i]))
                    l= j;
            if (t.data[l][i] == 0.0) //Проверка вырожденности. Если ведущий элемент 0 то определитель 0.
                return 0.0;
            if (l != i) {
                swap(t.data[i], t.data[l]); //перестановка строк
                det = -det; //из-за перестановки меняется знак определителя
            }
            det *= t.data[i][i]; //умножение диагонали. После метода Гаусса determinant равен произведению диагональных элементов.
            for (int j = i + 1; j < rows; ++j) {
                double factor = t.data[j][i] / t.data[i][i]; //обнуление под диагональю(глав шаг), factor-на сколько нужно вычесть текущую строку.
                for (int k = i + 1; k < cols; ++k)
                    t.data[j][k] -= factor * t.data[i][k];
            }
        }
        return det;
    }


    //обратная матрица

    // Получение минорной матрицы (удаление строки row и столбца col)
    Matrix getMinor(int row, int col) const {

        if (rows != cols)
            throw invalid_argument("Минор только для квадратной матрицы");

        int n = rows;
        if (n < 2)
            throw invalid_argument("Минор не определён для матрицы 1x1");

        Matrix minor(n - 1, n - 1); //сама минорная матрица

        int mi = 0;
        for (int i = 0; i < n; ++i) {
            if (i == row) continue; //пропускаем строку вычеркивания
            int mj = 0;
            for (int j = 0; j < n; ++j) {
                if (j == col) continue;
                minor.data[mi][mj] = data[i][j];
                mj++;
            }
            mi++;
        }
        return minor;
    }

    // Алгебраическое дополнение элемента (i, j)
    double cofactor(int i, int j) const {

        Matrix minor = getMinor(i, j);

        double detMinor = minor.det(); // определитель этого минора

        if ((i + j) % 2 == 0) { //знакочередование
            return detMinor;
        }
        else {
            return -detMinor;
        }
    }

    // транспонированная матрица алгебраических дополнений
    Matrix a() const {

        if (rows != cols)
            throw invalid_argument("Присоединённая матрица только для квадратной");

        int n = rows;
        Matrix ad(n, n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ad.data[i][j] = cofactor(i, j);// матрица алгебраических дополнений

        return ad.transponirovanie(); //транспонированная матрица алг доп                  
    }

    // Обратная матрица 
    Matrix inverse() const {

        double detA = det();

        if (detA == 0)
            throw invalid_argument("Матрица вырождена, обратной не существует");

        Matrix ad = a(); //транспонированная матрица алгебраических дополнений
        int n = rows;
        Matrix resultat(n, n);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                resultat.data[i][j] = ad.data[i][j] / detA; //каждый элемент делим на значение определителя
        return resultat; //это обратная матрица
    }



    // Возведение в целую степень
    Matrix vozvedenie_v_stepen(int stepen) const {

        if (rows != cols)
            throw invalid_argument("Возводить в степень можно только квадратные матрицы!");

        if (stepen == 0) 
            return edinitsa(rows); //в нулевой степени просто единица

        if (stepen < 0) 
            return inverse().vozvedenie_v_stepen(-stepen);

        Matrix resultat = edinitsa(rows);

        for (int i = 1; i <= stepen; i++) {
            resultat = resultat * *this;
        }
        return resultat;
    }


    //Столбцовая норма (максимум суммы модулей по столбцам)
    double norma() const {

        double max_Sum = 0.0;
        for (int j = 0; j < cols; j++) {
            double colSum = 0.0;

            for (int i = 0; i < rows; i++)
                colSum += abs(data[i][j]);

            if (colSum > max_Sum) 
                max_Sum = colSum;
        }
        return max_Sum;
    }

    //Методы, реализующие проверку типа матрицы(квадратная, диагональная, нулевая, единичная, симметрическая, верхняя\нижняя треугольная)

    bool isSquare() const { //проверка на квадратность

        if (rows == cols) {
            return true;
        }
        else {
            return false;
        }
    }

    bool isDiagonal() const { //проверка на диагональность

        if (!isSquare()) //если не квадратная то сразу не диагольная
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (i != j && data[i][j] != 0.0) 
                    return false;

        return true;
    }

    bool isZero() const { //провеерка на ноль 

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] != 0.0) 
                    return false;

        return true;
    }

    bool isEdinichnaya() const { // проверка на единичную матрицу

        if (!isSquare()) 
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                if (i == j && data[i][j] != 1.0) return false;
                if (i != j && data[i][j] != 0.0) return false;
            }
        return true;
    }

    bool isSymmetric() const { //проверка на симметричность

        if (!isSquare()) 
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = i + 1; j < cols; ++j)
                if (data[i][j] != data[j][i]) return false;
        return true;
    }

    bool isUpperTriangular() const { //верхнедиаг

        if (!isSquare()) 
            return false;

        for (int i = 1; i < rows; ++i)
            for (int j = 0; j < i; ++j)
                if (data[i][j] != 0.0) return false;
        return true;
    }

    bool isLowerTriangular() const { //нижнедиаг

        if (!isSquare()) 
            return false;

        for (int i = 0; i < rows; ++i)
            for (int j = i + 1; j < cols; ++j)
                if (data[i][j] != 0.0) return false;
        return true;
    }



    //Операции ввода\вывода в стандартные потоки
   
    void input() {
        cout << " Введите элементы матрицы размера " << rows << " на " << cols << "\n";
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                cout << " [" << i<< "][" << j << "]    =  ";
                cin >> data[i][j];   
            }      
    }

    void print() const {

        for (int i = 0; i < rows; ++i) {
            cout << "  ";

            for (int j = 0; j < cols; ++j)
                cout << setw(8) << setprecision(2) << data[i][j] << " ";
            cout << "\n";
        }
        //setw(8) – ширина поля для вывода каждого числа = 8 символов
        //setprecision(2) - 2 знака после запятой
    }
     

    //перегрузка ввода и вывода
    friend ostream& operator<<(ostream& os, const Matrix& m) {
        m.print();
        return os;
    }
    friend istream& operator>>(istream& is, Matrix& m) {
        for (int i = 0; i < m.rows; ++i)
            for (int j = 0; j < m.cols; ++j)
                is >> m.data[i][j];
        return is;
    }

};


void printMenu() {
    cout << "\n     ГЛАВНОЕ МЕНЮ   \n"
        "   1. Создать матрицу A\n"
        "   2. Создать матрицу B\n"
        "   3. A + B\n"
        "   4. A - B\n"
        "   5. B - A\n"
        "   6. A * B\n"
        "   7. B * A\n"
        "   8. A / B\n"
        "   9. B / A\n"
        "   10. A * скаляр\n"
        "   11. A / скаляр\n"
        "   12. A += B\n"
        "   13. A -= B\n"
        "   14. A *= B\n"
        "   15. A *= скаляр\n"
        "   16. A /= скаляр\n"
        "   17. A == B\n"
        "   18. A != B\n"
        "   19. Транспонирование \n"
        "   20. Определитель \n"
        "   21. Обратная матрица \n"
        "   22. возведение в степень\n"
        "   23. Норма матрицы \n"
        "   24. Проверка типов матрицы\n"
        "   25. Вывести A\n"
        "   26. Вывести B\n"
        "   27. Ввести A заново\n"
        "   28. Ввести B заново\n"
        "   0. Выход\n"
        "   Ваш выбор: ";
}



void printTypeCheck(const Matrix& m, const string& name) {
    cout << "\n  Проверка типов матрицы " << name << "\n";

    cout << " Квадратная: ";
    if (m.isSquare()) {
        cout << "Да\n";
    }
    else {
        cout << "Нет\n";
    }

    if (m.isSquare()) {
        cout << " Диагональная: ";
        if (m.isDiagonal()) {
            cout << "Да\n";
        }
        else {
            cout << "Нет\n";
        }

        cout << " Единичная: ";
        if (m.isEdinichnaya()) {
            cout << "Да\n";
        }
        else {
            cout << "Нет\n";
        }

        cout << " Симметричная: ";
        if (m.isSymmetric()) {
            cout << "Да\n";
        }
        else {
            cout << "Нет\n";
        }

        cout << " Верхнетреугольная: ";
        if (m.isUpperTriangular()) {
            cout << "Да\n";
        }
        else {
            cout << "Нет\n";
        }

        cout << " Нижнетреугольная: ";
        if (m.isLowerTriangular()) {
            cout << "Да\n";
        }
        else {
            cout << "Нет\n";
        }
    }

    cout << " Нулевая: ";
    if (m.isZero()) {
        cout << "Да\n";
    }
    else {
        cout << "Нет\n";
    }
}





int main() {
    setlocale(LC_ALL, "Russian");

    Matrix A, B;
    bool hasA = false, hasB = false;
    int choice, stepen;
    double scalar;


    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int r, c;
            cout << " Введите количество строк матрицы А: ";
            cin >> r;
            cout << " Введите количество столбцов матрицы А: ";
            cin >> c;
            A = Matrix(r, c);
            cout << " Ввод матрицы A:\n";
            A.input();
            hasA = true;
            cout << "Матрица A:\n" << A;
        } break;

        case 2: {
            int r, c;
            cout << " Введите количество строк матрицы B: ";
            cin >> r;
            cout << " Введите количество столбцов матрицы B: ";
            cin >> c;
            B = Matrix(r, c);
            cout << " Ввод матрицы B:\n";
            B.input();
            hasB = true;
            cout << "Матрица B:\n" << B;
        } break;

        case 3: // A + B
            if (hasA && hasB) {
                cout << "A + B =\n" << (A + B) << "\n";
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 4: // A - B
            if (hasA && hasB) {
                cout << "A - B =\n" << (A - B) << "\n";
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 5: // B - A
            if (hasA && hasB) {
                cout << "B - A =\n" << (B - A) << "\n";
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 6: // A * B
            if (hasA && hasB) {
                try { cout << "A * B =\n" << (A * B) << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 7: // B * A
            if (hasA && hasB) {
                try { cout << "B * A =\n" << (B * A) << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 8: // A / B
            if (hasA && hasB) {
                try { cout << "A / B =\n" << (A / B) << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 9: // B / A
            if (hasA && hasB) {
                try { cout << "B / A =\n" << (B / A) << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 10: // A * скаляр
            if (hasA) {
                cout << "Введите скаляр: ";
                cin >> scalar;
                cout << "A * " << scalar << " =\n" << (A * scalar) << "\n";
            }
            else cout << "Сначала создайте матрицу A!\n";
            break;

        case 11: // A / скаляр
            if (hasA) {
                cout << "Введите скаляр: ";
                cin >> scalar;
                try { cout << "A / " << scalar << " =\n" << (A / scalar) << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте матрицу A!\n";
            break;

        case 12: // A += B
            if (hasA && hasB) {
                try { A += B; cout << "A += B -> A =\n" << A << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 13: // A -= B
            if (hasA && hasB) {
                try { A -= B; cout << "A -= B -> A =\n" << A << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 14: // A *= B
            if (hasA && hasB) {
                try { A *= B; cout << "A *= B -> A =\n" << A << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 15: // A *= скаляр
            if (hasA) {
                cout << "Введите скаляр: ";
                cin >> scalar;
                A *= scalar;
                cout << "A *= " << scalar << " -> A =\n" << A << "\n";
            }
            else cout << "Сначала создайте матрицу A!\n";
            break;

        case 16: // A /= скаляр
            if (hasA) {
                cout << "Введите скаляр: ";
                cin >> scalar;
                try { A /= scalar; cout << "A /= " << scalar << " -> A =\n" << A << "\n"; }
                catch (const exception& e) { cout << "Ошибка: " << e.what() << "\n"; }
            }
            else cout << "Сначала создайте матрицу A!\n";
            break;

        case 17: // A == B
            if (hasA && hasB) {
                cout << (A == B ? "A == B (матрицы равны)" : "A != B (матрицы не равны)") << "\n";
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

        case 18: // A != B
            if (hasA && hasB) {
                cout << (A != B ? "A != B (матрицы не равны)" : "A == B (матрицы равны)") << "\n";
            }
            else cout << "Сначала создайте обе матрицы!\n";
            break;

            
        case 19: { // Транспонирование
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            if (matChoice == 1 && hasA) {
                cout << "Транспонирование A:\n" << A.transponirovanie() << "\n";
            }
            else if (matChoice == 2 && hasB) {
                cout << "Транспонирование B:\n" << B.transponirovanie() << "\n";
            }
            else {
                cout << "Матрица не создана или неверный выбор.\n";
            }
        } break;

        case 20: { // Определитель
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            try {
                if (matChoice == 1 && hasA) {
                    cout << "det(A) = " << setprecision(6) << A.det() << "\n";
                }
                else if (matChoice == 2 && hasB) {
                    cout << "det(B) = " << setprecision(6) << B.det() << "\n";
                }
                else {
                    cout << "Матрица не создана или неверный выбор.\n";
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        } break;

        case 21: { // Обратная матрица
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            try {
                if (matChoice == 1 && hasA) {
                    cout << "Обратная A:\n" << A.inverse() << "\n";
                }
                else if (matChoice == 2 && hasB) {
                    cout << "Обратная B:\n" << B.inverse() << "\n";
                }
                else {
                    cout << "Матрица не создана или неверный выбор.\n";
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        } break;

        case 22: { // Возведение в степень
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            cout << "Введите степень: ";
            cin >> stepen;
            try {
                if (matChoice == 1 && hasA) {
                    cout << "A^" << stepen << " =\n" << A.vozvedenie_v_stepen(stepen) << "\n";
                }
                else if (matChoice == 2 && hasB) {
                    cout << "B^" << stepen << " =\n" << B.vozvedenie_v_stepen(stepen) << "\n";
                }
                else {
                    cout << "Матрица не создана или неверный выбор.\n";
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
        } break;

        case 23: { // Норма матрицы
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            if (matChoice == 1 && hasA) {
                cout << "Норма A = " << setprecision(6) << A.norma() << "\n";
            }
            else if (matChoice == 2 && hasB) {
                cout << "Норма B = " << setprecision(6) << B.norma() << "\n";
            }
            else {
                cout << "Матрица не создана или неверный выбор.\n";
            }
        } break;

        case 24: { // Проверка типов
            if (!hasA && !hasB) { cout << "Нет ни одной матрицы!\n"; break; }
            int matChoice;
            cout << "Выберите матрицу (1 - A, 2 - B): ";
            cin >> matChoice;
            if (matChoice == 1 && hasA) {
                printTypeCheck(A, "A");
            }
            else if (matChoice == 2 && hasB) {
                printTypeCheck(B, "B");
            }
            else {
                cout << "Матрица не создана или неверный выбор.\n";
            }
        } break;

        case 25: // Вывести A
            if (hasA) cout << "Матрица A:\n" << A;
            else cout << "Матрица A не создана!\n";
            break;

        case 26: // Вывести B
            if (hasB) cout << "Матрица B:\n" << B;
            else cout << "Матрица B не создана!\n";
            break;

        case 27: // Ввести A заново
        {
            int r, c;
            cout << " Введите количество строк матрицы А: ";
            cin >> r;
            cout << " Введите количество столбцов матрицы А: ";
            cin >> c;
            A = Matrix(r, c);
            cout << " Ввод матрицы A:\n";
            A.input();
            hasA = true;
            cout << "Матрица A обновлена:\n" << A;
        }
        break;

        case 28: // Ввести B заново
        {
            int r, c;
            cout << " Введите количество строк матрицы B: ";
            cin >> r;
            cout << " Введите количество столбцов матрицы B: ";
            cin >> c;
            B = Matrix(r, c);
            cout << " Ввод матрицы B:\n";
            B.input();
            hasB = true;
            cout << "Матрица B обновлена:\n" << B;
        }
        break;

        case 0:
            break;

        default:
            cout << " Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}