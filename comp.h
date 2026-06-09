#pragma once
#include <iostream>
#include<initializer_list>
#include<string>
#include<stdio.h>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <fstream>

struct Comp{
    std::string name;
    std::string section;
    size_t price;

    Comp(){name =""; section =""; price = 0; }
    Comp(std::string a , std::string b , size_t c){
        name = a; section = b; price = c;
    }
    Comp(Comp& other){
        name = other.name; section = other.section; price = other.price;
    }
    Comp(const Comp& other){
        name = other.name; section = other.section; price = other.price;
    }

    bool operator==(const Comp& other) const{
        return name == other.name && section == other.section && price == other.price;
    }

    bool operator==(const Comp& other){
        return name == other.name && section == other.section && price == other.price;
    }

    bool operator<(const Comp& other){
        return name[0] < other.name[0];
    }

    bool operator>(const Comp& other){
        return name[0] > other.name[0];
    }
};

inline std::ostream& operator<<(std::ostream& os , const Comp& other){
    os << other.name << " " << other.section << " "  << other.price << ".";
    return os;
}

inline std::ifstream& operator>>(std::ifstream& is , Comp& other){
    is >> other.name >> other.section >> other.price;
    return is;
}

struct Bag{
    std::string name;
    size_t count;
    std::string section;

    Bag(){name =""; count = 0; section = ""; }
    Bag(std::string a , size_t b , std::string c){
        name = a; count = b; section = c;
    }
    Bag(Bag& other){
        name = other.name; count = other.count; section = other.section;
    }
    Bag(const Bag& other){
        name = other.name; count = other.count; section = other.section;
    }

    bool operator==(const Bag& other) const{
        return name == other.name && count == other.count && section == other.section;
    }

    bool operator==(const Bag& other){
        return name == other.name && count == other.count && section == other.section;
    }

    bool operator<(const Bag& other){
        return name[0] < other.name[0];
    }

    bool operator>(const Bag& other){
        return name[0] > other.name[0];
    }
};

inline std::ostream& operator<<(std::ostream& os , const Bag& other){
    os << other.name << " " << other.count << " "  << other.section << ".";
    return os;
}

inline std::ifstream& operator>>(std::ifstream& is , Bag& other){
    is >> other.name >> other.count >> other.section;
    return is;
}


template <typename T>
class COMP{
private:
    T* data;
    size_t amount;
public:
    COMP() : data(nullptr) , amount(0) {};

    COMP(size_t a ){
        amount = a;
        data = new T[a];
    };

    COMP(std::initializer_list<T> other){
        amount = other.size();
        data = new T[amount];
        size_t i{};
        for(const auto& x : other){
            data[i] = x;
            ++i;
        }
    }

    COMP(const COMP<T>& other){
        amount = other.amount;
        data = new T[amount];
        for(size_t i{}; i < amount; ++i){
            data[i] = other.data[i];
        }
    }

    size_t get_size(){
        return amount;
    }

    size_t get_size() const{
        return amount;
    }

    void push_back(const T& arg){
        T* temp = new T[amount + 1];
        for(size_t i{}; i < amount; ++i){
            temp[i] = data[i];
        }
        temp[amount] = arg;
        delete[] data;
        data = new T[amount + 1];
        for(size_t i{}; i < amount+1; ++i){
            data[i] = temp[i];
        }
        ++amount;
        delete[] temp;
    }

    void pop_index(size_t index) {
        if (index >= amount) {
            throw std::out_of_range("Индекс за пределами массива!");
        }

        for (size_t i = index; i < amount - 1; ++i) {
            data[i] = data[i + 1];
        }

        --amount;
    }

    friend std::ostream& operator<<(std::ostream& os, const COMP<T>& other){
        for(size_t i{}; i < other.amount; ++i){
            os << other.data[i] << std::endl;
        }
        return os;

    }

    friend std::istream& operator>>(std::istream& is, COMP<T>& other){
        size_t n;
        std::cout << "How many elements do u want to fill in: "; std::cin >> n;
        other.data = new T[n];
        other.amount = n;
        for(size_t i{}; i < other.amount; ++i){
            std::cout << "Input element: "; is >> other.data[i]; std::cout << std::endl;
        }
        return is;
    }

    void WriteTextData(std::ofstream& out){
        if(!out.is_open()){
            std::cout << "Cannot write into this file.\n";
        }
        size_t i{};
        while(i < amount){
            out << data[i] << std::endl;
            ++i;
        }

        out.close();
    }

    void ReadTextData(std::ifstream& fin){
        if(!fin.is_open()){
            std::cout << " Cannot read from this file.\n";
        }
        T* temp =  new T[100];
        size_t i{};
        while(fin >> temp[i]){
            ++i;
        }

        amount = i;
        delete[] data;
        data = new T[amount];
        for(size_t j{}; j < amount; ++j){
            data[j] = temp[j];
        }
        delete[] temp;
        fin.close();

    }

    ~COMP(){
        if((*this).get_size() != 0)
            delete[] data;
    }

    COMP operator=(const COMP& other){
        amount = other.amount;
        data = new T[amount];
        for(size_t i{}; i < amount; ++i){
            data[i] = other.data[i];
        }
        return *this;
    }

    T& operator[](size_t i){
        return data[i];
    }

    T& operator[](size_t i) const {
        return data[i];
    }

    void ReadData(const char* fin){
        std::ifstream is(fin , std::ios::binary | std::ios::ate );
        if (!is.is_open()) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }

        long long int a = is.tellg();
        is.seekg(0 , std::ios::beg);

        size_t count = a / sizeof(T);
        if( count == 0){
            std::__throw_range_error("Array has 0 elements. ");
            return;
        }

        delete[] data;
        data = nullptr;
        amount = count;
        data = new T[count];

        is.read(reinterpret_cast<char*>(data), a);

        is.close();

    }

    void WriteData(const char* fout){
        std::ofstream of(fout , std::ios::binary );
        if (!of.is_open()) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }
        if(amount == 0){
            std::__throw_range_error("Array has 0 elements. ");
            return;
        }
        long long int a = amount * sizeof(T);

        of.write(reinterpret_cast<char*>(data), a);
        of.close();

    }

    void Sort(){
        for(size_t i{}; i < (*this).amount - 1;++i){
            size_t min_index = i;
            for(size_t j = i + 1; j < (*this).amount; ++j){
                if((*this).data[j] < (*this).data[min_index]){
                    min_index = j;
                }
            }
            std::swap((*this).data[i], (*this).data[min_index]);
        }
    }

    void ReverseSort(){
        for(size_t i{}; i < (*this).amount - 1;++i){
            size_t min_index = i;
            for(size_t j = i + 1; j < (*this).amount; ++j){
                if((*this).data[j] > (*this).data[min_index]){
                    min_index = j;
                }
            }
            std::swap((*this).data[i], (*this).data[min_index]);
        }
    }

};

template <typename U>
COMP<U> operator+(const COMP<U>& first, const COMP<U>& second) {
    COMP<U> temp;

    for (size_t i = 0; i < first.get_size(); ++i) {
        temp.push_back(first[i]);
    }

    for (size_t i = 0; i < second.get_size(); ++i) {
        temp.push_back(second[i]);
    }

    U exmpl{};
    size_t temp_size = temp.get_size();

    for (size_t i = 0; i < temp_size; ++i) {
        for (size_t j = i + 1; j < temp_size; ++j) {
            if (temp[i] == temp[j]) {
                temp[j] = exmpl;
            }
        }
    }

    for (size_t i = temp.get_size(); i > 0; --i) {
        if (temp[i - 1] == exmpl) {
            temp.pop_index(i - 1);
        }
    }

    return temp;
}


