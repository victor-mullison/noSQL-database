#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Dependencies/stringmethods.cpp"

/*
---- Structure ----
- Database is structured similarly to firestore but without "collections."
- The only collection (folder) is the database folder, which contains named files that resemble firestore documents. (Document name, dictionary entries.)
- Dictionary entries have a string key that maps to string data. Program can be expanded to support many data types in the future.
- Rather than using a document class, the database works via .txt files in the "database" folder.
*/

// Returns value if found, returns an empty string otherwise.
std::string get(std::string document, std::string key)
{
    std::ifstream doc("database/" + document + ".txt");
    if (!doc.is_open())
    {
        std::cout << "No document \"" << document << ".txt\" found in the database." << std::endl;
        return "";
    }

    // Find and return entry in file, if it exists
    std::string line;
    while (std::getline(doc, line))
    {
        std::vector<std::string> split_line;
        split_line = split(line);

        if (split_line[0] == key)
        {
            return split_line[1];
        }
    }

    return ""; // Empty string if not found.
};

void set(std::string document, std::string key, std::string value)
{
    std::ifstream old_doc("database/" + document + ".txt"); // No need to error handle here; its handled by the ofstream

    std::ofstream new_doc("database/" + document + ".txt");
    if (!new_doc.is_open())
    {
        // Shouldn't reach here, ofstream will open the doc if it exists and make one if it doesn't.
        std::cout << "Error: Could not open or create document \"" << document << ".txt\" " << std::endl;
        return;
    }

    // Iterates through the old file until it finds an entry to overwrite; if it doesn't; adds it to the end.
    std::string line;
    bool overwritten = false;
    while (std::getline(old_doc, line))
    {
        std::vector<std::string> split_line;
        split_line = split(line);

        if (split_line[0] == key)
        {
            new_doc << split_line[0] << " " << value << std::endl;
            overwritten = true;
        }
        else
        {
            new_doc << split_line[0] << " " << split_line[1] << std::endl;
        }
    }

    if (!overwritten)
    { // Key wasn't found; adds new entry.
        new_doc << key << " " << value << std::endl;
    }

    old_doc.close();
    new_doc.close();
};

void display(std::string document)
{
    std::ifstream doc("database/" + document + ".txt");
    if (!doc.is_open())
    {
        std::cout << "No document \"" << document << ".txt\" found in the database." << std::endl;
        return;
    }

    std::cout << " ------- " << document << " ------- " << std::endl;
    std::string line;
    while (std::getline(doc, line))
    {
        std::vector<std::string> split_line;
        split_line = split(line);
        std::cout << std::setw(20) << split_line[0] << " : " << split_line[1] << std::endl;
    }
    doc.close();
};

// Used to split command + args and call appropriate functions.
void parseCommand(std::string input)
{
    std::vector<std::string> parsed_command = split(input);

    if (parsed_command.size() == 0) // For empty input
    {
        return;
    }

    std::string command = parsed_command[0];
    if (command == "get")
    {
        if (parsed_command.size() != 3)
        {
            std::cout << "Incorrect args, call to \"get\" expects: get <document_name> <key>" << std::endl;
        }
        else
        {
            std::string value;
            value = get(parsed_command[1], parsed_command[2]);

            if (value != "")
            {
                std::cout << parsed_command[1] << "[" << parsed_command[2] << "] holds: " << value << std::endl;
            }
            else
            {
                std::cout << "No value found for " << parsed_command[1] << "[" << parsed_command[2] << "]" << std::endl;
            }
        }
    }
    else if (command == "set")
    {
        if (parsed_command.size() != 4)
        {
            std::cout << "Incorrect args, call to \"set\" expects: set <document_name> <key> <value>" << std::endl;
        }
        else
        {
            set(parsed_command[1], parsed_command[2], parsed_command[3]);
        }
    }
    else if (command == "display")
    {
        if (parsed_command.size() != 2)
        {
            std::cout << "Incorrect args, call to \"display\" expects: display <document_name>" << std::endl;
        }
        else
        {
            display(parsed_command[1]);
        }
    }
    else
    {
        std::cout << "Unrecognized command." << std::endl;
    }
};

int main()
{
    std::cout << "Thanks for taking a look at my database program! This program is meant to show some understanding of C++ and common database setups, but its main purpose is to be used to demonstrate proficiency in unit testing, coming in a future repo." << std::endl
              << std::endl;

    std::cout << "To use the database, use commands \"get\", \"set\", and \"display\". Type \"quit\" to quit the program. Type \"help\" to repeat this message at any point." << std::endl
              << std::endl;

    while (true)
    {

        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);

        // quit is handled here to easily terminate the program.
        if (command == "quit")
        {
            return 0;
        }

        if (command == "help")
        {
            std::cout << "To use the database, use commands \"get\", \"set\", and \"display\". Type \"quit\" to quit the program. Type \"help\" to repeat this message at any point." << std::endl
                      << std::endl;
            continue;
        }

        parseCommand(command);
        std::cout << std::endl;
    };
};