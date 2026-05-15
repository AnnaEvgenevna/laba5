//3. Реализовать класс MyVector, представляющий собой одномерный безразмерный динамический массив для удобной работы с целыми числами типа int.
//В классе должно быть три поля : указатель на инкапсулированный массив типа int(можно назвать его data, или ar); 
//текущее количество существующих элементов в массиве(int size, изначально - 0); резерв памяти(int capacity, по умолчанию 10).

#include <iostream>
#include <ctime> //для time()
#include <algorithm> //для swap
using namespace std;

class MyVector {

private:

    int* data; //указатель на массив
    int size; //текущее кол-во существующих эл-тов в массиве
    int capacity; //резерв памяти


    /* EnsureCapacity(приватный метод!проверяет, достаточно ли резерва
         памяти для хранения указанного в параметре количества элементов.
         Если значение параметра меньше текущего capacity, то ничего не
         происходит.Если значение параметра больше текущего capacity, то
         массив пересоздаётся, памяти выделяется в 1.5 раза + 1 элемент
         больше, а существующие элементы не должны быть потеряны)*/

    void EnsureCapacity(int n) {

        if (n >= capacity) {

            int c = capacity * 1.5 + 1;
            int* d = new int[c];

            for (int i = 0; i < size; i++) {
                d[i] = data[i];
            }

            data = d;
            capacity = c;
        }
    }




public:

    //конструктор по умолчанию 
    MyVector() {
        size = 0;
        capacity = 10;
        data = new int[capacity];

        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }
    }

    // Параметризированный конструктор 
    MyVector(int n) {
        size = 0;
        capacity = n;

        if (capacity <= 0) { //вектор не может быть отрицательной длины
            capacity = 10;
        }

        data = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            data[i] = 0;
        }

    }


    int get_size() {
        return size;
    }
    int get_capacity() {
        return capacity;
    }

    void set_capacity(int n) {
        if (n <= 0) { //вектор не может быть отрицательной длины
            capacity = 10;
        }
        else {
            capacity = n;
        }
    }


    //Print(показ на экран консоли всех элементов массива)

    void Print() {

        for (int i = 0; i < size; i++) {
            cout << data[i] << "  ";

        }
    }


    //•PushBack(добавление элемента в конец массива.Должна быть проверка,
       // достаточно ли памяти!)
    void PushBack(int element) {
        EnsureCapacity(size + 1); //проверка 
        data[size] = element; //добавляем элемент в конец 
        size++; //кол-во элементов на 1 больше стало
    }

    //•PushFront(добавление одного элемента в начало массива)
    void PushFront(int element) {

        EnsureCapacity(size + 1);//проверка на память

        //cдвигаем все эл-нты вправо
        for (int i = size; i > 0; i--) {
            data[i] = data[i - 1];
        }
        data[0] = element;
        size++;
    }

    //Insert(вставка одного элемента в массив по указанному индексу, с
       // проверкой на выход за пределы массива)
    void Insert(int index, int element) {

        if (index < 0 || index > size) {
            cout << "Выход за пределы массива\n";
            return;
        }

        EnsureCapacity(size + 1);//проверка на память


        for (int i = size; i > index; i--) { //идем с конца до нужного индекса
            data[i] = data[i - 1]; //сдвигаем элементы вправо
        }
        data[index] = element;
        size++;
    }

    //•RemoveAt(удаление одного элемента по указанному индексу.Должна
        //быть проверка на допустимость индекса)
    void RemoveAt(int index) {

        if (index < 0 || index >= size) {
            cout << "Недопустимый индекс\n";
            return;
        }

        // Сдвигаем элементы влево
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    //•Remove(удаление элементов, значение которых
       // совпадает со значением переданного параметра)
    void Remove(int element) {
        int new_size = 0;
        for (int i = 0; i < size; ++i) {
            if (data[i] != element) {
                data[new_size++] = data[i];
            }
        }
        size = new_size;
    }

    //•PopFront(удаление первого элемента из массива)
    void PopFront() {
        RemoveAt(0);
    }

    //•PopBack(удаление последнего элемента из массива)
    void PopBack() {
        RemoveAt(size - 1);
    }

    //•Clear(обнуление массива - всем элементам массива по индексам от 0
        //до size - 1 присвоить значение 0, полю size присвоить значение 0)
    void Clear() {
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
        size = 0;
    }

    //•IsEmpty(метод возвращает true, если size = 0, и false в обратном случае)
    bool IsEmpty() {
        if (size == 0) {
            return true;
        }
        else {
            return false;
        }
    }

    //•TrimToSize(метод подгоняет значение capacity под size, естественно
        //с перевыделением памяти)
    void TrimToSize() {
        if (size == capacity) {
            return;
        }

        int* d = new int[size]; //выделяем динамическую память для массива 
        for (int i = 0; i < size; i++) {
            d[i] = data[i];
        }

        data = d;
        capacity = size;
    }

    //•IndexOf(линейный поиск слева направо первого вхождения в массив
       // указанного значения.В результате работы вернуть индекс найденного
       // элемента, а eсли ничего не найдено, вернуть - 1)
    int IndexOf(int element) {
        for (int i = 0; i < size; i++) {
            if (data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    //•LastIndexOf(линейный поиск справа налево вхождения в массив
       // указанного значения.В результате работы вернуть индекс найденного
       // элемента, а eсли ничего не найдено, вернуть - 1)
    int LastIndexOf(int element) {
        for (int i = size - 1; i >= 0; i--) {
            if (data[i] == element) {
                return i;
            }
        }
        return -1;
    }

    //•Reverse (изменение порядка следования элементов в массиве на противоположный)
    void Reverse() {
        for (int i = 0; i < size / 2; i++) {
            int n = data[i];
            data[i] = data[size - 1 - i];
            data[size - 1 - i] = n;
        }
    }

    //•SortAsc (быстрая сортировка значений элементов массива по возрастанию)
    void SortAsc() {
        sort(data, data + size);
    }

    //•SortDesc (быстрая сортировка значений элементов массива по убыванию)
    void SortDesc() {
        sort(data, data + size, greater<int>());
    }

    //•Shuffle (случайное перемешивание элементов массива)
    void Shuffle() {
        for (int i = size - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }

    //•RandomFill (заполнение массива случайными значениями)
    void RandomFill() {
        for (int i = 0; i < size; i++) {
            data[i] = rand() % 101;   // случайное число от 0 до 100
        }
    }


    //•Equals(в качестве параметра передаётся указатель на другой вектор.
       // Метод сравнивает массивы не только по количеству элементов, но и по их содержимому)
    bool Equals(MyVector* d) {

        if (size != d->size) {
            return false;
        }

        for (int i = 0; i < size; i++) {
            if (data[i] != d->data[i]) {
                return false;
            }
        }
        return true;
    }

    //•GetElementAt (возврат копии элемента массива по указанному индексу,
    //с проверкой на выход за пределы массива)
    int GetElementAt(int index) {
        if (index < 0 || index >= size) {
            cout << "Выход за пределы массива\n";
            return 0;
        }
        return data[index];
    }

    //•Clone (метод создаёт точную копию вектора).
    MyVector Clone() const {
        return MyVector(*this); // используем конструктор копирования
    }


    //конструктор копирования
    MyVector(const MyVector& d) {
        size = d.size;
        capacity = d.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = d.data[i];
        }
    }




    // Оператор присваивания
    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this; // защита от самоприсваивания
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new int[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }


    //перегрузка операции [ ]
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            cout << "Выход за границы массива\n";
            return data[0];
        }
        return data[index];
    }



    //перегрузка операции ==
    bool operator==(MyVector& other) {
        return Equals(&other);
    }

    //перегрузка << (вывод)
    friend ostream& operator<<(ostream& os, MyVector& vec) { //friend - функция имеет доступ к приватным полям

        for (int i = 0; i < vec.size; i++) {
            os << vec.data[i] << " ";
        }

        return os;
    }
};


int main() {

    setlocale(LC_ALL, "Russian");

    cout << "   КОНСТРУКТОРЫ   " << "\n";
    MyVector v1; // capacity=10, size=0
    cout << "v1 создан через конструктор без параметров " << v1 << "\n";
    cout << "size v1 = " << v1.get_size() << ", capacity v1 = " << v1.get_capacity() << "\n\n";

    MyVector v2(5); // параметризованный, capacity=5

    cout << "v2 создан через конструтор с параметром (5)" << v2 << "\n";
    cout << "size v2 = " << v2.get_size() << ", capacity v2 = " << v2.get_capacity() << "\n\n";


    cout << "   ДОБАВЛЕНИЕ ЭЛЕМЕНТОВ   " << "\n";
    //добавление элемента в конец 
    v1.PushBack(10);
    v1.PushBack(20);
    v1.PushBack(30);

    //вывод v1 через перегруженный <<
    cout << "После добавления в конец массива 10, 20, 30: " << v1 << "\n";
    v1.PushFront(5); //добавление в начало, со сдвигом
    cout << "После добавления в начало массива элемента 5: " << v1 << "\n";

    v1.Insert(2, 15); // вставка элемента 15 по индексу 2
    cout << "После добавления элемента по индексу: " << v1 << "\n";
    v1.Insert(10, 99);   // неверный индекс
    cout << "Текущий v3: " << v1 << "\n\n";


    cout << "   УДАЛЕНИЕ ЭЛЕМЕНТОВ   " << "\n";
    MyVector v4 = v1; //конструктор копирования
    v4.RemoveAt(3); //удаление элемента по индексу

    cout << "v4 после удаления элемента с индексом 3: " << v4 << "\n";
    cout << "v1 после удаления элемента с индексом 3 из v4: " << v1 << "\n";

    v4.Remove(20); //удалить элемннты == 20
    cout << "v4 после удаления элементов == 20: " << v4 << "\n";
    v4.PopFront();
    cout << "v4 после удаления первого элемента: " << v4 << "\n";
    v4.PopBack();
    cout << "после удаления последнего элемента: " << v4 << "\n\n";


    cout << "   НЕКОТОРЫЕ ФУНКЦИИ   " << "\n";
    MyVector v5;
    v5.PushBack(1);
    v5.PushBack(2);
    v5.PushBack(3);
    cout << "v5: " << v5 << ", size=" << v5.get_size() << ", capacity=" << v5.get_capacity() << "\n";

    if (v5.IsEmpty()) {
        cout << "Массив пустой? Да!\n";
    }
    else {
        cout << "Массив пустой? Нет!\n";
    }

    v5.Clear();
    cout << "После Clear (очистка) : " << v5 << "\n";

    if (v5.IsEmpty()) {
        cout << "Массив пустой? Да!\n";
    }
    else {
        cout << "Массив пустой? Нет!\n";
    }

    v5.PushBack(100);
    v5.PushBack(200);
    cout << "v5 после добавления элементов: " << v5 << ", size=" << v5.get_size() << ", capacity=" << v5.get_capacity() << "\n";
    v5.TrimToSize();
    cout << "После TrimToSize (подгоняем capacity под size): size=" << v5.get_size() << ", capacity=" << v5.get_capacity() << "\n\n";


    cout << "   ПОИСК   " << "\n";
    MyVector v6;
    int arr[] = { 5, 3, 8, 3, 9, 3, 8, 11, 0, 23, 45, 3, 5 };
    for (int x : arr) v6.PushBack(x);
    cout << "v6: " << v6 << "\n";
    cout << "Какой индекс у первого вхождения элемента 3? -  " << v6.IndexOf(3) << "\n";
    cout << "Какой последний индекс вхождения элемента 5? -  " << v6.LastIndexOf(5) << "\n";
    cout << "Какой индекс у первого вхождения элемента 100? - " << v6.IndexOf(99) << "\n\n"; //-1 значит что этого элемента нет


    cout << "   РАЗНОЕ ПЕРЕМЕШИВАНИЕ   " << "\n";

    cout << "Исходный: " << v6 << "\n";
    v6.Reverse();
    cout << "Reverse: " << v6 << "\n";//в обратном порялке
    v6.SortAsc();
    cout << "Сортировка по возрастанию : " << v6 << "\n";
    v6.SortDesc();
    cout << "Сортировка по убыванию : " << v6 << "\n";
    v6.Shuffle();
    cout << "Перемешивание : " << v6 << "\n\n";


    cout << "   ЗАПОЛНЕНИЕ МАССИВА СЛУЧАЙНЫМИ ЧИСЛАМИ ОТ 0 ДО 100 " << "\n";
    v6.RandomFill();
    v6.Print(); ///вывод через принт, а не через <<
    cout << "\n\n";


    cout << "   Сравнение массивов" << "\n";
    MyVector v7, v8;
    int arr1[] = { 5, 3, 8, 3, 9, 3, 8, 11, 0, 23, 45, 3, 5 };
    for (int x : arr1) v7.PushBack(x);
    MyVector v9 = v7; //конструктор копирования

    int arr2[] = { 5, 3, 8, 3, 9, 3, 0, 11, 0, 23, 45, 3, 5 };
    for (int x : arr2) v8.PushBack(x);

    cout << "v7 = " << v7 << "\n";
    cout << "v8 = " << v8 << "\n";
    cout << "v9 = " << v9 << "\n";

    if (v7.Equals(&v8)) {
        cout << "Массивы v7 и v8 равны\n";
    }
    else {
        cout << "Массивы v7 и v8 не равны\n";
    }

    if (v7.Equals(&v9)) {
        cout << "Массивы v7 и v9 равны\n\n";
    }
    else {
        cout << "Массивы v7 и v9 не равны\n\n";
    }

    cout << "   ВОЗВРАТ ЭЛЕМЕНТА ПО УКАЗАННОМУ ИНДЕКСУ" << "\n";
    cout << "v7 = " << v7 << "\n";
    cout << "GetElementAt(1): " << v7.GetElementAt(1) << "\n";
    cout << "GetElementAt(55): " << v7.GetElementAt(55) << "\n\n";  // неверный индекс



    cout << "   КЛОНИРОВАНИЕ И КОПИРОВАНИЕ" << "\n";
    MyVector v10;
    v10.PushBack(10); v10.PushBack(20); v10.PushBack(30);
    MyVector v11 = v10.Clone();  // клонирование
    MyVector v12(v10);    // конструктор копирования
    cout << "Оригинал v10: " << v10 << "\n";
    cout << "Копия v11 (Clone): " << v11 << "\n";
    cout << "Копия v12 (конструктор копирования): " << v12 << "\n";
    v10.PushBack(40);
    cout << "После изменения оригинала: v10 = " << v10 << ", v11 = " << v11 << ", v12 = " << v12 << "\n\n";


    cout << "   ПРИСВАИВАНИЕ" << "\n";
    MyVector v13;
    v13 = v10;
    cout << "v13 = v10: " << v13 << "\n\n";


    cout << "   ОПЕРАТОР []" << "\n";

    cout << "v10[1] = " << v10[1] << "\n";
    v10[1] = 77;
    cout << "После v10[1]=77: " << v10 << "\n";
    cout << "Попытка доступа v10[100]: " << v10[100] << "\n\n";  // выход за границы, то выводим первый элемент


    return 0;
}


