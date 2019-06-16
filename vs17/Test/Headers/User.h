#pragma once
#include <string>
#include <iostream>

struct User
{
    std::wstring name    = L"";
    std::wstring surname = L"";
    uint64_t     id      = 0;

    enum class SortOrder
    {
        byName    = 1,
        bySurname = 2,
        byId      = 3,
    };

    template<template<class> class RelationalOp = std::less>
    struct Comparator
    {
        User::SortOrder order_ = User::SortOrder::byName;

        bool operator() (const User& lhs, const User& rhs) const
        {
            RelationalOp op;

            switch (order_) {
            case User::SortOrder::byName:     return op(lhs.name, rhs.name);
            case User::SortOrder::bySurname:  return op(lhs.surname, rhs.surname);
            case User::SortOrder::byId:       return op(lhs.id, rhs.id);
            default:                          return false;
            }
        }

        explicit Comparator(User::SortOrder order) : order_(order) {
            /* Empty */
        }
    };
};


template<template<class> class TContainer>
inline void printUsers(const TContainer<User>& users, User::SortOrder order)
{
    std::wcout << L"-------------------------------------------------------\n";
    for (const auto& user : users)
    {
        switch (order) {
        case User::SortOrder::byName:
            std::wcout << user.name << L' ' << user.surname << ": " << user.id << L'\n';
            break;
        case User::SortOrder::bySurname:
            std::wcout << user.surname << L' ' << user.name << ": " << user.id << L'\n';
            break;
        case User::SortOrder::byId:
            std::wcout << user.id << ": " << user.name << L' ' << user.surname << L'\n';
            break;
        }
    }
    std::wcout << L"-------------------------------------------------------\n";
}