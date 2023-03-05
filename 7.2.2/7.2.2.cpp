#include <iostream>
#include <ctime>

int** CreateMatrix(int k, int n);
void ChangeMatrix(int** Matrix, int k, int n, int i);
void PrintMatrix(int** Matrix, int k, int n);

int FindMinElement(int** Matrix, int i, int j, int n, int min_element);
int FindMaxElement(int** Matrix, int i, int j, int n, int max_element);

int main()
{
    srand(time(NULL));

    int k, n;
    std::cout << "Enter k: "; //рядки
    std::cin >> k;
    std::cout << "Enter n: "; //стовпці
    std::cin >> n;

    int** Matrix = CreateMatrix(k, n);
    std::cout << "First Matrix:\n";
    PrintMatrix(Matrix, k, n);
    ChangeMatrix(Matrix, k, n, 1);
    std::cout << "Changed Matrix:\n";
    PrintMatrix(Matrix, k, n);

}

int** CreateMatrix(int k, int n)
{
    int** Matrix = new int* [k];
    for (int i = 0; i < k; i++)
    {
        Matrix[i] = new int[n];
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Matrix[i][j] = rand() % 10;
        }
    }
    return Matrix;
}

void ChangeMatrix(int** Matrix, int k, int n, int i) {
    if (i >= k) {
        return;
    }

    if (i % 2 == 1) {
        int min_element = FindMinElement(Matrix, i - 1, 0, n, Matrix[i - 1][0]);
        for (int j = 1; j < n; j++) {
            min_element = FindMinElement(Matrix, i - 1, j, n, min_element);
        }

        int max_element = FindMaxElement(Matrix, i, 0, n, Matrix[i][0]);
        for (int j = 1; j < n; j++) {
            max_element = FindMaxElement(Matrix, i, j, n, max_element);
        }

        for (int j = 0; j < n; j++) {
            if (Matrix[i - 1][j] == min_element) {
                Matrix[i - 1][j] = max_element;
            }
            else if (Matrix[i][j] == max_element) {
                Matrix[i][j] = min_element;
            }
        }
    }

    ChangeMatrix(Matrix, k, n, i + 1);
}

void PrintMatrix(int** Matrix, int k, int n)
{
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << Matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int FindMinElement(int** Matrix, int i, int j, int n, int min_element) {
    if (j == n) {
        return min_element;
    }

    if (Matrix[i][j] < min_element) {
        min_element = Matrix[i][j];
    }

    return FindMinElement(Matrix, i, j + 1, n, min_element);
}

int FindMaxElement(int** Matrix, int i, int j, int n, int max_element) {
    if (j == n) {
        return max_element;
    }

    if (Matrix[i][j] > max_element) {
        max_element = Matrix[i][j];
    }

    return FindMaxElement(Matrix, i, j + 1, n, max_element);
}