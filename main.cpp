#include <iostream>
#include <vector>
#include <locale>
#include <windows.h>
#include <random>

using namespace std;

// Заполняет матрицу рандомными числами от 0 до 9
void fill_matrix(vector<vector<int>> &matrix) {
    for (vector<int> &i : matrix) {
        for (int &j : i) {
            j = rand() % 10; // NOLINT(*-msc50-cpp)
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

    for (int i = 0; i < matrix[0].size(); ++i) {
        double temp = 0.0;
        for (vector<double> &j : matrix) {
            uniform_real_distribution<double> dist(0.0, 1.0 - temp);
            const double generated_number = dist(gen);
            j[i] = generated_number;
            temp = generated_number;
        }
    }
}

// Перемножает две матрицы
vector<vector<auto>> multiply_matrix(const vector<vector<auto>> &matrix1, const vector<vector<auto>> &matrix2) {
    // Проверка на возможность перемножения матриц
    if (matrix1[0].size() != matrix2.size()) {
        cout << "Матрицы не могут быть перемножены!" << endl;
        return {};
    }

    // Создание матрицы на вывод
    vector<vector<auto>> result(matrix1.size(), vector<auto>(matrix2[0].size()));

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
void check_matrix_parameters(int &rows, int &columns) {
    if (rows < 1 || rows > 10 || columns < 1 || columns > 10) {
        constexpr int default_parameters[4] = {3, 4, 4, 6};
        cout << "Некорректные параметры, используются параметры по умолчанию: " << default_parameters[0] << " строк, "
        << default_parameters[1] << " столбцов" << endl;
        rows = default_parameters[0];
        columns = default_parameters[1];
    }
}

void display_matrix(auto &matrix) {
    for (const auto &i : matrix) {
        for (const auto &j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}

// Задание 1
void manipulating_matrix() {
    int row1 = 3;
    int column1 = 4;
    int row2 = 4;
    int column2 = 6;

    cout << "Введите количество строк и столбцов для первой матрицы (через пробел от 1 до 10): " << endl;
    cin >> row1 >> column1;
    check_matrix_parameters(row1, column1);

    cout << "Введите количество строк и столбцов для второй матрицы (через пробел от 1 до 10): " << endl;
    cin >> row2 >> column2;
    check_matrix_parameters(row2, column2);

    cout << "Введены значения:" << endl;
    cout << "Первая матрица: " << row1 << " строк, " << column1 << " столбцов" << endl;
    cout << "Вторая матрица: " << row2 << " строк, " << column2 << " столбцов" << endl;

    vector<vector<int>> matrix1(row1, vector<int>(column1));
    vector<vector<int>> matrix2(row2, vector<int>(column2));

    cout << "Заполняем матрицу рандомными значениями..." << endl;
    fill_matrix(matrix1);
    fill_matrix(matrix2);

    cout << "Перемножаем матрицы..." << endl;
    const vector<vector<int>> result = multiply_matrix(matrix1, matrix2);

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

    vector<double> initial_probabilities(N, 1.0 / N);


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
