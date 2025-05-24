#include <iostream>
#include <vector>
#include <locale>
#include <windows.h>
#include <random>

using namespace std;

// Заполняет матрицу рандомными числами от 0 до 9
void fill_matrix(vector<vector<double>> &matrix) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dist(0.0, 9.0);
    for (vector<double> &i : matrix) {
        for (double &j : i) {
            j = dist(gen);
        }
    }
}

// Заполняет стохастическую матрицу числами, суммирующимися в единицу
void fill_stochastic_matrix(vector<vector<double>> &matrix) {
    random_device rd;
    mt19937 gen(rd());

    if (matrix.size() != matrix[0].size()) {
        cout << "Матрица не является квадратной." << endl;
        return;
    }

    // Для стохастической матрицы сумма элементов по СТРОКАМ должна быть равна 1
    for (int i = 0; i < matrix.size(); ++i) { // перебираем строки
        double temp = 0.0;
        for (int j = 0; j < matrix[i].size() - 1; ++j) { // перебираем столбцы, кроме последнего
            uniform_real_distribution<double> dist(0.0, 1.0 - temp);
            const double generated_number = dist(gen);
            matrix[i][j] = generated_number;
            temp += matrix[i][j];
        }
        // Последний элемент строки заполняем так, чтобы сумма стала ровно 1
        matrix[i][matrix[i].size() - 1] = 1.0 - temp;
    }
}

// Перемножает две матрицы
vector<vector<double>> multiply_matrix(const vector<vector<double>> &matrix1, const vector<vector<double>> &matrix2) {
    // Проверка на возможность перемножения матриц
    if (matrix1[0].size() != matrix2.size()) {
        cout << "Матрицы не могут быть перемножены!" << endl;
        return {};
    }

    // Создание матрицы на вывод
    vector<vector<double>> result(matrix1.size(), vector<double>(matrix2[0].size()));

    // Перемножение
    for (int i = 0; i < matrix1.size(); ++i) {
        for (int j = 0; j < matrix2[0].size(); ++j) {
            for (int k = 0; k < matrix1[0].size(); ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Проверяет данные матрицы на соответствие условиям
void check_matrix_parameters(double &rows, double &columns) {
    if (rows < 1.0 || rows > 10.0 || columns < 1.0 || columns > 10.0) {
        constexpr double default_parameters[4] = {3.0, 4.0, 4.0, 6.0};
        cout << "Некорректные параметры, используются параметры по умолчанию: " << default_parameters[0] << " строк, "
        << default_parameters[1] << " столбцов" << endl;
        rows = default_parameters[0];
        columns = default_parameters[1];
    }
}

void display_matrix(const vector<vector<double>> &matrix) {
    for (const vector<double> &i : matrix) {
        for (const double &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Задание 1
void manipulating_matrix() {
    double row1 = 3.0;
    double column1 = 4.0;
    double row2 = 4.0;
    double column2 = 6.0;

    cout << "Введите количество строк и столбцов для первой матрицы (через пробел от 1 до 10): " << endl;
    cin >> row1 >> column1;
    check_matrix_parameters(row1, column1);

    cout << "Введите количество строк и столбцов для второй матрицы (через пробел от 1 до 10): " << endl;
    cin >> row2 >> column2;
    check_matrix_parameters(row2, column2);

    cout << "Введены значения:" << endl;
    cout << "Первая матрица: " << row1 << " строк, " << column1 << " столбцов" << endl;
    cout << "Вторая матрица: " << row2 << " строк, " << column2 << " столбцов" << endl;

    vector<vector<double>> matrix1(row1, vector<double>(column1));
    vector<vector<double>> matrix2(row2, vector<double>(column2));

    cout << "Заполняем матрицу рандомными значениями..." << endl;
    fill_matrix(matrix1);
    fill_matrix(matrix2);

    cout << "Перемножаем матрицы..." << endl;
    const vector<vector<double>> result = multiply_matrix(matrix1, matrix2);

    cout << "Новая (перемноженная) матрица:" << endl;
    display_matrix(result);
}

// Задание 2
void manipulating_stochastic_matrix() {
    int N = 2;

    cout << "Введите размерность матрицы (N x N): ";
    cin >> N;

    if (N < 2 || N > 10) {
        cout << "Введены неверные значения. Возвращаем размерность по умолчанию: 2" << endl;
        N = 2;
    }

    vector<vector<double>> matrix(N, vector<double>(N));
    fill_stochastic_matrix(matrix);

    cout << "Сгенерированная изначальная матрица:" << endl;
    display_matrix(matrix);

    cout << "Начинаем возведение матриц..." << endl;
    for (int i = 0; i < 20; ++i) {
        matrix = multiply_matrix(matrix, matrix);
        cout << "Шаг № " << i + 1 << ": Промежуточная матрица:" << endl;
        display_matrix(matrix);
    }

    // Вектор-строка начальных вероятностей (равномерное распределение)
    const vector<vector<double>> initial_probabilities(1, vector<double>(N, 1.0 / N));
    cout << "Матрица первоначальных вероятностей: " << endl;
    display_matrix(initial_probabilities);

    cout << "Перемножаем матрицы..." << endl;
    // Вектор-строка умножается на стохастическую матрицу (строки на столбцы)
    const vector<vector<double>> result = multiply_matrix(initial_probabilities, matrix);

    cout << "Итоговая матрица вероятностей:" << endl;
    display_matrix(result);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");

    char choice = '0';

    cout << "Выберите задание (0 — перемножение матриц (default), 1 — стохастическая матрица): ";
    cin >> choice;

    if (choice == '1') {
        manipulating_stochastic_matrix();
    } else {
        manipulating_matrix();
    }

    return 0;
}
