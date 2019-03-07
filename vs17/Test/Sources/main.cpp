#include "FileReader.h"
#include <algorithm>
#include <vector>
#include <iterator>

enum Commands
{
    SortByName        = User::SortOrder::byName,
    SortBySurname     = User::SortOrder::bySurname,
    SortByPhoneNumber = User::SortOrder::byPhoneNumber,
    Cancel            = -1,
};

static void welcomeMessage()
{
    std::wcout << L"Для сортировки по именам введите: " << Commands::SortByName
               << L", по фамилиям введите: "            << Commands::SortBySurname
               << L", по телефонам введите: "           << Commands::SortByPhoneNumber
               << L"\nДля отмены наберите: "            << Commands::Cancel;
    std::wcout << L'\n';
}

static void start(std::vector<User>& users)
{
    User::SortOrder tag;
    std::istream_iterator<int> itEOF;

    welcomeMessage();

    for (std::istream_iterator<int> it(std::cin); it != itEOF; ++it)
    {
        switch (*it) {
        case SortByName:
            tag = User::SortOrder::byName;
            break;
        case SortBySurname:
            tag = User::SortOrder::bySurname;
            break;
        case SortByPhoneNumber:
            tag = User::SortOrder::byPhoneNumber;
            break;
        case Cancel:
            return;
        default:
            std::wcout << L"Неправильная команда!\n";
            continue;
        }

        std::sort(users.begin(), users.end(), User::Comparator(tag));
        printUsers<std::vector>(users, tag);
    }
}

int main(int argc, char * argv[])
{
    std::locale::global(std::locale("rus_rus.1251"));

    try {
        if (argc < 2) throw std::logic_error("No input file!");

        std::string filename = argv[1];

        FileReader reader(filename);
        std::vector<User> users;

        while (reader) {
            if (User user; reader.getUser(user)) {
                users.emplace_back(std::move(user));
            }
        }

        start(users);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}