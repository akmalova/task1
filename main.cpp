#include <QCoreApplication>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ifstream f("..\\Task1\\matrix.txt");
    if (f.is_open()) {
        int n = 0;
        int num_of_elem = 0; // кол-во элементов
        char c;
        while(f.get(c)) {
            if (c == '\n') {
                num_of_elem++;
                n++;
            }
            else if (c == ' ')
                num_of_elem++;
        }
        int m = num_of_elem / n;

        f.clear();
        f.seekg(0, std::ios::beg); // переход в начало файла
        int matrix [n][m];
        for (int i = 0; i < n; i++)
             for (int j = 0; j < m; j++) {
                 f >> matrix[i][j];
             }
        f.close();

        cout << "Matrix: " << endl;
        for (int i = 0; i < n; i++) {
             for (int j = 0; j < m; j++) {
                 cout << matrix[i][j] << " ";
             }
             cout << endl;
        }

        // индексная сортировка
        int ind[m]; // массив индексов
        int sum[m]; // массив сумм элементов строк
        for (int i = 0; i < n; i++) {
            ind[i] = i;
            sum[i] = 0;
            for(int j = 0; j < m; j++)
                sum[i] += matrix[i][j];
        }

        bool flag = true;
        int j = n - 1;
        while (flag) {
            flag = false;
            for (int i = 0; i < j; i++) {
                if (sum[ind[i]] > sum[ind[i+1]]) {
                    int k = ind[i];
                    ind[i] = ind[i+1];
                    ind[i+1] = k;
                    flag = true;
                }
            }
            j--;
        }

        ofstream fout("..\\Task1\\sorted_matrix.txt");
        for (int i = 0; i < n; i++) {
             for (int j = 0; j < m; j++) {
                 fout << matrix[ind[i]][j] << " ";
             }
             fout << "\n";
        }
        cout << "Matrix is written to file" << endl;
        fout.close();
    }
    else
        cout << "Error" << endl;

    return a.exec();
}
