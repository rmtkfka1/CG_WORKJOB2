#include <iostream>
#include "pch.h"

using namespace std;

int main() {
    const int size = 10;
    char matrix[size * size]; // 10x10 ����� ������ �迭�� ǥ��

    // ������ �迭 �ʱ�ȭ
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = '-';
    }

    // "x"�� ��� �߰�
    for (int i = 0; i < size; ++i) {
        matrix[i * size + i] = 'x';              // �밢�� ����
        matrix[i * size + (size - 1 - i)] = 'x'; // �밢�� �Ʒ���
    }

    // ��� ��� (������ �迭�� 10x10 ��ķ� ���)
    for (int i = 0; i < size * size; ++i) {
        cout << matrix[i] << " ";
        if ((i + 1) % size == 0) {
            cout << endl;
        }
    }

    return 0;
}