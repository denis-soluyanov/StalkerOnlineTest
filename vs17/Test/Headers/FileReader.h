#pragma once
#include "User.h"
#include <fstream>

class FileReader
{
private:
    std::wifstream      istream_;
    static const size_t BUF_SIZE = 1024;

public:
    explicit FileReader(const std::string& filename);
    bool getline(wchar_t* buf, size_t len);
    bool getUser(User& user);
    operator bool() const;
    ~FileReader();

private:
    bool parseUserFromString(const wchar_t* str, User& user);

    /* Disabled */
    FileReader(const FileReader&)            = delete;
    FileReader& operator=(const FileReader&) = delete;
};