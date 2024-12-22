#include <string>
#include <vector>
#include <iostream>

// ---- Custom String Functions ------

// Split behaves exactly like python's 'split' function which divides a string into a list (in this case, a string vector) based on a specific separator (space by default)
// By design, this function fails some niche cases! (Separators at the start, concurrent separators, etc.)
// I left these niche cases so I can use them as examples of failed test cases in my upcoming unit testing repo.
std::vector<std::string> split(std::string str, char sep = ' ')
{
    int word_count = 0;

    // Iterates to find word count in order to appropriately reserve memory
    size_t pos = 0;
    while (pos < str.size())
    {
        if (str[pos++] == sep)
        {
            word_count++;
        };
    }

    std::vector<std::string> arr;

    // Now iterates to fill arr
    std::string token = "";
    pos = 0;

    while (pos < str.size())
    {
        char current_char = str[pos++];
        if (current_char == sep)
        {
            arr.push_back(token);
            token = "";
        }
        else
        {
            token += current_char;
        }
    }
    if (!token.size() == 0) // Handles last word; logic accounts for trailing separators
    {
        arr.push_back(token);
    }

    return arr;
};

// ----------------------------