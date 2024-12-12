#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

#define EPS 1e-5 // �������
#define PI 3.14159265358979323846

// ������� ��� ������������
double func(double x) {
    return 1.0 / (sin(2 * x) * sin(2 * x));
}

// ����� ��������
double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (func(a) + func(b));
    for (int i = 1; i < n; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}

// ����� ��������
double simpson_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = func(a) + func(b);
    for (int i = 1; i < n; ++i) {
        if (i % 2 == 0) {
            sum += 2 * func(a + i * h);
        }
        else {
            sum += 4 * func(a + i * h);
        }
    }
    return sum * h / 3.0;
}

// ˳��� �����������
double left_rectangle_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}

// ������ �����������
double right_rectangle_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += func(a + i * h);
    }
    return sum * h;
}

// ����������� �����������
double central_rectangle_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += func(a + (i + 0.5) * h);
    }
    return sum * h;
}

int main() {
    setlocale(LC_ALL, "RU");
    double a = PI / 9;
    double b = PI / 8;
    int n = 1;
    double integral_trapezoidal, integral_simpson, integral_left, integral_right, integral_central;

    // ���������� ��������� � ���������� ���������� n
    do {
        integral_trapezoidal = trapezoidal_rule(a, b, n);
        integral_simpson = simpson_rule(a, b, n);
        integral_left = left_rectangle_rule(a, b, n);
        integral_right = right_rectangle_rule(a, b, n);
        integral_central = central_rectangle_rule(a, b, n);
        n *= 2; // ��������� ������� ����������
    } while (fabs(integral_trapezoidal - integral_simpson) > EPS);

    // ������ ���������� ����'���� (����� ��������� ������)
    double exact_solution = 0.5 * (cos(2 * a) - cos(2 * b)); // ������� �� �������

    // ��������� ����������
    printf("�������� ������� ��������: %f\n", integral_trapezoidal);
    printf("�������� ������� ��������: %f\n", integral_simpson);
    printf("�������� ������ ����������������: %f\n", integral_left);
    printf("�������� ������� ����������������: %f\n", integral_right);
    printf("�������� ������������ ����������������: %f\n", integral_central);
    printf("������ ����������� �������: %f\n", exact_solution);

    return 0;
}