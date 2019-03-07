#pragma once
#include <string>
#include <iostream>

struct User
{
    std::wstring surname     = L"";
    std::wstring name        = L"";
    uint64_t     phoneNumber = 0;

    enum class SortOrder
    {
        byName        = 1,
        bySurname     = 2,
        byPhoneNumber = 3,
    };

    template<template<class> class RelationalOp = std::less>
    struct Comparator
    {
        bool operator() (const User& lhs, const User& rhs) const
        {
            RelationalOp op;

            switch (order_) {
            case User::SortOrder::byName:        return op(lhs.name, rhs.name);
            case User::SortOrder::bySurname:     return op(lhs.surname, rhs.surname);
            case User::SortOrder::byPhoneNumber: return op(lhs.phoneNumber, rhs.phoneNumber);
            }
        }
        User::SortOrder order_ = User::SortOrder::byName;

        explicit Comparator(User::SortOrder order) : order_(order) {}
    };

    template<template<class> class TContainer>
    friend void printUsers(const TContainer<User>& users, User::SortOrder order);

    friend class FileReader;
};

template<template<class> class TContainer>
inline void printUsers(const TContainer<User>& users, User::SortOrder order)
{
    for (const auto& user : users)
    {
        switch (order) {
        case User::SortOrder::byName:
            std::wcout << user.name << L' ' << user.surname << ": " << user.phoneNumber << L'\n';
            break;
        case User::SortOrder::bySurname:
            std::wcout << user.surname << L' ' << user.name << ": " << user.phoneNumber << L'\n';
            break;
        case User::SortOrder::byPhoneNumber:
            std::wcout << user.phoneNumber << ": " << user.surname << L' ' << user.name << L'\n';
            break;
        }
    }
}