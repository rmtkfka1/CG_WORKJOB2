#include <iostream>
#include "pch.h"

using namespace std;

int main() {
    const int size = 10;
    char matrix[size * size]; // 10x10 행렬을 일차원 배열로 표현

    // 일차원 배열 초기화
    for (int i = 0; i < size * size; ++i) {
        matrix[i] = '-';
    }

    // "x"자 모양 추가
    for (int i = 0; i < size; ++i) {
        matrix[i * size + i] = 'x';              // 대각선 위쪽
        matrix[i * size + (size - 1 - i)] = 'x'; // 대각선 아래쪽
    }

    // 결과 출력 (일차원 배열을 10x10 행렬로 출력)
    for (int i = 0; i < size * size; ++i) {
        cout << matrix[i] << " ";
        if ((i + 1) % size == 0) {
            cout << endl;
        }
    }

    return 0;
}