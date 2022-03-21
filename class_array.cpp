#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void Sift (int *a, int m, int i) // Функция для создания пирамиды в пирамидальной сортировке
{
    int j, c, f, t;
    j = 2*i + 1; //Левый потомок
    c = a[i];
    f = 1;
    for (j, f; ((j < m) && f); )
    {
        if ((j + 1) < m) // если правый потомок больше левого - делаем замену с ним
        {
            if (a[j + 1] > a[j])
            {
                j++;
            }
        }
        if (a[j] > c)
        {
            a[i] = a[j];
            i = j;
            j = 2*i + 1;
        }
        else
        {
            f = 0;
        }
    }
    a[i] = c;
    return;
} 

class Array
{
    int *a, n;
    public:
    // конструктор 1
    // len – число элементов в массиве
    // t = 1 – неупорядоченный массив
    // t = 2 – массив, упорядоченный по неубыванию
    // t = 3 – массив, упорядоченный по невозрастанию
    // d – диапазон псевдослучайных чисел для неупорядоченного массива (при t = 1)
    Array (int len = 1, int t = 1, int d = 10);
    Array (int *arr, int len); // конструктор 2: по массиву
    Array (Array &arr);
    ~ Array ()
    {
        if (a)
        {
            delete []a; 
            a = NULL; 
        }
    }

    int Getn() // Для сортировки Хоар_2
    {
        return n;
    }

    Array & operator = (Array &arr);
    int & operator [] (int i);

    bool Test (); // проверка на упорядоченность по неубыванию
    bool operator == (Array arr); // равенство элементов массивов (но не порядка)

    void Shell_sort ();
    void Heapsort ();
    void Hoar_sort (int l, int r);
    void Bit_sort ();
    
    friend istream & operator >> (istream &, Array &);
    friend ostream & operator << (ostream &, Array &);
};

Array :: Array (int len, int t, int d)
{
    if (t == 1)
    {
        n = len;
        a = new int [n];
        srand (time (NULL));
        for (int i = 0; i < n; i ++)
        {
            a[i] = rand() % d;
        }   
    }
    else if (t == 2) // >= 
    {
        n = len;
        a = new int [n];
        srand (time (NULL));
        a[0] = rand() % d;
        for (int i = 1; i < n; i ++)
        {
            a[i] = a[i-1] + rand() % d;
        }
        
    }
    else
    {
        n = len;
        a = new int [n];
        srand (time (NULL));
        a[n-1] = rand() % d;
        for (int i = n-2; i >= 0; i --)
        {
            a[i] = a[i+1] + rand() % d;
        }
    }
}

Array :: Array (int *arr, int len)
{
    n = len;
    a = new int [n];
    for (int i = 0; i < n; i ++)
    {
        this -> a[i] = arr[i];
    }
}

Array :: Array (Array &arr)
{
    a = new int [arr.n];
    for (n = 0; n < arr.n; n ++)
    {
        a[n] = arr.a[n];
    }
}

Array & Array :: operator = (Array &arr)
{
    if (this != &arr) //s = s
    {
        delete []a;
        a = new int [n = arr.n];
        for (int i = 0; i < n; i ++)
        {
            a[i] = arr. a[i];
        }
    }
    return *this;
}

int & Array :: operator [] (int i)
{
    if ((i < 0) || (i >= n))
    {
        cout << "Index outside" << endl;
        exit (1);
    }
    return a[i];
}

bool Array :: Test () //по неубыванию
{
    int k = 1;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i+1])
        {
            return false;
        }
    }

    return true;
}

bool Array :: operator == (Array arr) //!!!!
{
    if (n == arr.n) 
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < arr.n; j++)
            {
                if (a[i] == arr[j])
                {
                    arr[j] = arr[(arr.n-1)];
                    arr.n --; 
                    //cout << "++" << endl;
                    break;
                }
            }
        }
        if (arr.n == 0)
        {
            return true;
        }
    }
    return false; // Если длина не совпадает - ложь
}

// Sorting
void Array :: Shell_sort ()
{
    // Подсчёт числа шагов
    int number_h = 0;
    int m = n / 2;
    while (m > 0)
    {
        number_h ++;
        m = m / 2;
    }
    
    //Заполнение массива из шагов, h1 > h2 > ... > last_h = 1
    int *h; 
    h = new int [number_h];
    m = n / 2;
    for (int i = 0; i < number_h; i++)
    {
        h[i] = m;
        m = m / 2;
    }

    int i, step, b, el_2, el_1, x;
    for (i = 0; i < number_h; i++) //Цикл для смены шага
    {
        step = h[i]; // Берём текущий шаг
        for (b = 0; b < step; b++) // b пробегает индексы всех элементов в подпоследовательности
        {
            el_2 = b + step; //Номер элемента для сравнения в одной подпоследовательности 
            for (el_2; el_2 < n; el_2 += step)
            {
                x = a[el_2];
                el_1 = el_2 - step; //Номер элемента для сравнения  в другой подпоследовательности
                for (el_1; ((el_1 >= 0) && (a[el_1] > x)); el_1 = el_1 - step) //Сортировка вставкой для подмассивов
                {
                    a[el_1 + step] = a[el_1];
                }
                a[el_1 + step] = x;   
            }
            
        }
    }
    delete [] h;
    return;
}

void Array :: Heapsort () //Stop
{
    int i, x; // Строим пирамиду
    for (i = n/2 - 1; i >= 0; i--)
    {
        Sift (a, n, i);
    }

    i = n - 1;
    for (i; i > 0; i--) 
    {
        x = a[0];
        a[0] = a[i];
        a[i] = x;
        Sift (a, i-1, 0); //Меняем текущий элемент с корнем, упорядочиваем пирамиду, убирая последний элемент
    }
    return;
}

void Array :: Hoar_sort (int l, int r) //Хоар_2
{
        int i, j, x, t;
        if (l >= r)
        {
            return;
        }
        i = l + 1;
        j = r;
        x = a[l]; //Первый элемент в подпоследовательности
        while (i <= j)
        {
            for (i; ((i <= j) && (a[i] <= x)); i++);
            for (j; ((j >= i) && (a[j] > x)); j--);
            if (i < j) // Если левый элемент больше правого
            {
                t = a[i];
                a[i] = a[j];
                a[j] = t;
                i++;
                j--;
            }
        }
        t = a[l];
        a[l] = a[j];
        a[j] = t;
        j--;
        //cout << "x: " << x << endl;
        //cout << "j, i: " << j << "  " << i << endl;
        //cout << *this << endl;
        Hoar_sort (l, j);
        Hoar_sort (i, r);
    return;
}   

istream & operator >> (istream &enter, Array &arr)
{
    cin >> arr.n;
    delete [] arr.a;

    arr.a = new int[arr.n];

    for (int i = 0; i < arr.n; i++)
    {
        cin >> arr.a[i];
    }    
    return enter;
}

ostream & operator << (ostream &res, Array &arr)
{
    for (int i = 0; i < arr.n; i ++)
    {
        res << arr[i] << " ";
    }
    return res;
}

int main ()
{
    ////Конструктор №2
    ////int *m, len_m;
    ////cin >> len_m;
    ////m = new int [len_m];
    ////for (int i = 0; i < len_m; i++)
    ////{
    ////    cin >> m[i];
    ////}
////
    ////Array arr1 (m, len_m);
    ////cout << "arr1: " << arr1 << endl;
    //
    ////Конструктор №1 для t = 1; 2; 3.
    //Array arr2 (10), arr3 (10, 2, 5), arr4 (10, 3, 5), arr6;
    //cout << "arr2: " << arr2 << endl;
    //cout << "arr3: " << arr3 << endl;
    ////cout << "arr4: " << arr4 << endl;
    //
    //cout << "-------------" << endl;
//
    ////Array arr5 = arr2; //Конструктор копирования
    ////cout << "arr5: " << arr5 << endl;
    //arr6 = arr3; //Оператор присваивания
    //cout << "arr6: "<< arr6 << endl;
////
    //cout << "-----------" << endl;
    //////Перегруженная операция ввода
    //Array arr7;
    //cin >> arr7;
    //cout << "arr7: " << arr7 << endl;
    //cout << "Test: " << arr7.Test() << endl; //Проверка на упорядоченность по неубыванию
    //cout << "Operator == : " << (arr6 == arr3) << endl; //Проверка на равенство элементов массивов
    
    //cout << "-----------" << endl;
    
    //cout << arr5 [4] << endl;
    //arr6[0] = -50;
    //cout << arr6 << endl;
    
    //SHELL-SORT
    //arr2. Shell_sort();
    //cout << arr2;


    //HEAPSORT
    //arr7. Heapsort();
    //cout << arr7 << endl;

    //HOAR-SORT
    //int l = 0, r = arr2.Getn() - 1;
    //arr2. Hoar_sort(l, r);
    //cout << arr2 << endl;

    //delete []m;

    Array arr (100000, 2, 100000);
    Array m = arr;
    
    cout << "Hoar_sort" << endl;
    int start_1 = clock();
    int l = 0, r = arr.Getn() - 1;
    arr.Hoar_sort(l, r);
    int end_1 = clock();
    double duration_1 = (double)(end_1 - start_1) / (double) CLOCKS_PER_SEC;

    if (arr.Test())
    {
        cout << "Okey: Test()" << endl;
    }

    if (m == arr)
    {
        cout << "Okey: ==" << endl;
    }

    cout << "The time: " << duration_1 << " seconds" << endl;
    
    arr = m;
    cout << "Shell_sort"<< endl;
    int start_2 = clock();
    arr.Shell_sort();
    int end_2 = clock();
    double duration_2 = (double)(end_2 - start_2) / (double) CLOCKS_PER_SEC;

    if (arr.Test())
    {
        cout << "Okey: Test()" << endl;
    }

    if (arr == m) 
    {
        cout << "Okey: ==" << endl;
    }

    cout << "The time: " << duration_2 << " seconds" << endl;
    
    arr = m;
    cout << "Heapsort" << endl;
    int start_3 = clock();
    arr.Heapsort();
    int end_3 = clock();
    double duration_3 = (double)(end_3 - start_3) / (double) CLOCKS_PER_SEC;

    if (arr.Test())
    {
        cout << "Okey: Test()" << endl;
    }

    if (arr == m)
    {
        cout << "Okey: ==" << endl;
    }
    
    cout << "The time: " << duration_3 << " seconds" << endl;

    return 0;
}