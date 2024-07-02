#include <string>
#include <vector>

class StringUtils
{
public:
    StringUtils() = delete;
    static std::vector<std::string> split(const std::string& input, const std::string& delim)
    {
        char* str = (char*)input.c_str();
        char* del = (char*)delim.c_str();

        std::vector<std::string> output;

        // This method is not thread safe since strtok isn't thread safe.
        char* token = strtok(str, del);
        while (token != nullptr)
        {
            output.emplace_back(token);
            token = strtok(nullptr, del);
        }

        return output;
    }
    static std::string strip(const std::string& str)
    {
        std::string out;
        std::size_t start = str.find_first_not_of(" \t\r\n");
        std::size_t end = str.find_last_not_of(" \t\r\n");

        if (start == std::string::npos || end == std::string::npos)
        {
            printf("Either start or end was std::string::npos. Returning original string.\n");
            return str;
        }
        out = str.substr(start, (end - start) + 1);
        return out;
    }
    static std::string stripEnd(const std::string& str, std::string post)
    {
        std::string out;
        std::size_t start = 0;
        std::size_t end = str.find_last_not_of(post);

        if (end == std::string::npos)
        {
            printf("Either start or end was std::string::npos. Returning original string.\n");
            return str;
        }
        out = str.substr(start, (end - start) + 1);
        return out;
    }
};