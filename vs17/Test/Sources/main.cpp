#include "FileReader.h"
#include <algorithm>
#include <vector>
#include <iterator>


enum Commands
{
    SortByName    = User::SortOrder::byName,
    SortBySurname = User::SortOrder::bySurname,
    SortById      = User::SortOrder::byId,
    Cancel        = -1,
};

static void welcomeMessage()
{
    std::cout << "For sorting users by name press: " << Commands::SortByName
              << ", by surname press: "              << Commands::SortBySurname
              << ", by ID press: "                   << Commands::SortById
              << "\nTo cancel, press: "              << Commands::Cancel;
    std::cout << std::endl;
}

static std::istream& getCommandFromUser(std::string& str)
{
    std::cout << "> ";
    return std::getline(std::cin, str);
}

static void start(std::vector<User>& users)
{
    User::SortOrder order;
    std::string userInput;

    welcomeMessage();

    while (getCommandFromUser(userInput)) {

        try {
            switch (std::stoi(userInput)) {
            case SortByName:
                order = User::SortOrder::byName;
                break;
            case SortBySurname:
                order = User::SortOrder::bySurname;
                break;
            case SortById:
                order = User::SortOrder::byId;
                break;
            case Cancel:
                std::cout << "Cancel\n";
                return;
            default:
                throw std::exception();
            }
        }
        catch (std::exception&) {
            std::cout << "Wrong command!\n";
            continue;
        }

        std::sort(users.begin(), users.end(), User::Comparator(order));
        printUsers<std::vector>(users, order);
    }
}


int main(int argc, char * argv[])
{
    std::locale::global(std::locale("rus_rus.1251"));

    try {
        if (argc < 2) {
            throw std::logic_error("No input file!");
        }

        std::string filename = argv[1];

        FileReader reader(filename);
        std::vector<User> users;

        while (reader) {
            if (User user; reader.getUser(user)) {
                users.emplace_back(std::move(user));
            }
        }

        if (users.empty()) {
            throw std::runtime_error("Input file is empty or has an incorrect data format!");
        }

        start(users);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}