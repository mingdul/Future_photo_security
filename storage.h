// Storage.h
#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <iostream>

// 제네릭 클래스
template <typename T>
class Storage {
private:
    std::vector<T> items; // T 타입의 아이템을 저장할 벡터

public:
    void add(const T& item) {
        items.push_back(item); // 아이템 추가
    }

    T get(int index) const {
        if (index < 0 || index >= items.size()) {
            throw std::out_of_range("Index out of range"); // 인덱스 범위 검사
        }
        return items[index]; // 아이템 반환
    }

    void printAll() const { // 모든 아이템 출력
        for (const auto& item : items) {
            std::cout << item << std::endl;
        }
    }
};

#endif
