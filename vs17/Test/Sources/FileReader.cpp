#include "FileReader.h"
#include <regex>

FileReader::FileReader(const std::string& filename)
{
    istream_.open(filename, std::ios::in);

    if (!istream_.is_open()) {
        std::string message = "Сouldn't open a file: " + filename;
        throw std::runtime_error(message.c_str());
    }
}

bool FileReader::getUser(User& user)
{
    wchar_t buf[BUF_SIZE];
    return (getline(buf, BUF_SIZE) && parseUserFromString(buf, user));
}

bool FileReader::getline(wchar_t* buf, size_t len)
{
    if (!buf || !len) {
        throw std::logic_error("Passed buffer is NULL");
    }

    istream_.getline(buf, len);

    return !istream_.fail();
}

bool FileReader::parseUserFromString(const wchar_t* str, User& user)
{
                                  /*  |     Surname     | |       Name       |: |   ID    |  */
    static const std::wregex regex(L"([a-z|A-Z|а-я|А-Я]+) ([a-z|A-Z|а-я|А-Я]+): ([\\d]\\d+)");
    std::wcmatch match;

    if (std::regex_search(str, match, regex)) {
        user.surname = match.str(1);
        user.name = match.str(2);
        user.id = std::stoull(match.str(3));
        return true;
    }
    return false;
}

FileReader::operator bool() const
{
    return static_cast<bool>(istream_);
}

FileReader::~FileReader()
{
    istream_.close();
}