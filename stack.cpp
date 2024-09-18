#include <iostream>
#include <vector>

#include "utility.hpp"

#define APPEND_NEW_OBJECT 0
#define IO 1
#define AVERAGE_AMOUNT 1

class String 
{
    private:
        std::vector<char> _str;

    public:
        String() = default;

        String(const char* str)
        {
            size_t len = 0;
            while (str[len] != '\0') ++len;

            _str.reserve(len);
            for (size_t i = 0; i < len; ++i) 
            {
                _str.push_back(str[i]);
            }
        }

        String(const String& other) : _str(other._str) {}

        String& operator=(const String& other)
        {
            if (this == &other) return *this;

            _str = other._str;
            return *this;
        }

        ~String() = default;

        size_t length() const
        {
            return _str.size();
        }

        size_t size() const
        {
            return _str.size();
        }

        const char* c_str() const
        {
            return _str.data();
        }

        String append(const char* str)
        {
            size_t len = 0;
            while (str[len] != '\0') ++len;

            std::vector<char> new_str = _str;
            new_str.reserve(_str.size() + len);

            for (size_t i = 0; i < len; ++i) 
            {
                new_str.push_back(str[i]);
            }

            return String(new_str.data());
        }

        String append(const String& other)
        {
            return append(other.c_str());
        }

        String& append_override(const char* str)
        {
            size_t i = 0;
            while (str[i] != '\0') 
            {
                _str.push_back(str[i]);
                ++i;
            }

            return *this;
        }

        String& append_override(const String& other)
        {
            return append_override(other.c_str());
        }

        friend std::ostream& operator<<(std::ostream& os, const String& str)
        {
            for (const char& c : str._str)
            {
                os << c;
            }

            return os;
        }
};

#if APPEND_NEW_OBJECT == 1
void run() 
{
    // Append and create new object

    String one("Hello");
    String two(", World!");

#if IO == 1
    String three = one.append(two);

    std::cout << "Part A:" << std::endl
                << "\tString: '" << one << "'" << std::endl
                << "\tLength: " << one.length() << std::endl;
                
    std::cout << "Part B:" << std::endl
                << "\tString: '" << two << "'" << std::endl
                << "\tLength: " << two.length() << std::endl;

    std::cout << "Combined:" << std::endl
                << "\tString: '" << three << "'" << std::endl
                << "\tLength: " << three.length() << std::endl;
#endif
}
#else
void run() 
{
    // Append and override current object

    String one("Hello");
    String two(", World!");

    String three = one.append_override(two);

#if IO == 1
    std::cout << "Part A:" << std::endl
                << "\tString: '" << one << "'" << std::endl
                << "\tLength: " << one.length() << std::endl;
                
    std::cout << "Part B:" << std::endl
                << "\tString: '" << two << "'" << std::endl
                << "\tLength: " << two.length() << std::endl;

    // Place here for correct behaviour with this variant
    // String three = one.append_override(two);

    std::cout << "Combined:" << std::endl
                << "\tString: '" << three << "'" << std::endl
                << "\tLength: " << three.length() << std::endl;
#endif
}
#endif

int main() {
    double avg = 0;
    for (int i = 0; i < AVERAGE_AMOUNT; ++i)
        avg += funcTime(run);
    avg /= AVERAGE_AMOUNT;

    std::cout << "Time taken average (" << AVERAGE_AMOUNT << " runs): " << avg << "ns" << std::endl;
    return 0;
}