//
// Created by toi on 27/03/2020.
//
#include <cstring>
//for: strlen(), strcpy(), strcmp()
#include "MyFunctions.hpp"

bool array_find_str(char const* arr[], char const* str) {
    if(str == nullptr){
        return false;
    }
    unsigned index = 0;
    while(arr[index] != nullptr && std::strcmp(arr[index], str) != 0){
        index++;
    }
    return arr[index] != nullptr;
}

void mem_copy(char *& to, char const* from, bool canDeleteTo) {
    if (canDeleteTo && to != nullptr) {
        delete[] to;
        to = nullptr;
    }
    if (from == nullptr || (!canDeleteTo && to != nullptr)) {
        return;
    }
    to = new char[std::strlen(from) + 1];
    std::strcpy(to, from);
}