#include <iostream>

#include "utility.hpp"

#define APPEND_NEW_OBJECT 0
#define IO 1
#define AVERAGE_AMOUNT 1

class String
{
    private:
        char* _str;     // Base string pointer
        size_t _len;    // Length of the string


        // Who needs std::string anyway?
        size_t _strlen(const char* str)
        {
            size_t len = 0;
            while (str[len] != '\0') ++len;
            return len;
        }

        void _strcpy(char* dest, const char* src)
        {
            size_t i = 0;
            while ((dest[i] = src[i]) != '\0') ++i;
        }

        void _strcat(char* dest, const char* src)
        {
            size_t i = 0;
            while (dest[i] != '\0') ++i;
            _strcpy(dest + i, src);
        }

    public:
        // Constructors
        String() : _str(nullptr), _len(0) {}

        String(const char* str) : _str(nullptr), _len(0)
        {
            _len = _strlen(str);
            _str = new char[_len + 1];
            _strcpy(_str, str);
        }

        // Copy constructor
        String(const String& other) : _str(nullptr), _len(other._len) 
        {
            _len = other._len;
            _str = new char[_len + 1];
            _strcpy(_str, other._str);
        }

        // Move operator
        String& operator=(const String& other) 
        {
            if (this == &other) return *this;

            delete[] _str;
            _len = other._len;
            _str = new char[_len + 1];
            _strcpy(_str, other._str);
            
            return *this;
        }

        // Move assignment constructor
        String(String&& other) : _str(other._str), _len(other._len)
        {
            other._str = nullptr;
            other._len = 0;
        }

        // Move assignment operator
        String& operator=(String&& other)
        {
            if (this == &other) return *this;

            delete[] _str;
            _str = other._str;
            _len = other._len;
            other._str = nullptr;
            other._len = 0;

            return *this;
        }

        // Destructor
        ~String() 
        {
            delete[] _str;
        }

        size_t length() const
        {
            return _len;
        }

        size_t size() const
        {
            return _len;
        }

        const char* c_str() const
        {
            return _str;
        }

        // Append and create new object
        String append(const char* str)
        {
            size_t new_len = _len + _strlen(str);
            char* new_str = new char[new_len + 1];

            _strcpy(new_str, _str);
            _strcat(new_str, str);

            String new_str_obj = String(new_str);
            delete[] new_str;

            return new_str_obj;
        }

        String append(const String& other)
        {
            return append(other.c_str());
        }

        // Append and override current object
        String& append_override(const char* str)
        {
            size_t new_len = _len + _strlen(str);
            char* new_str = new char[new_len + 1];
         
            _strcpy(new_str, _str);
            _strcat(new_str, str);

            delete[] _str;
            _str = new_str;
            _len = new_len;

            return *this;
        }        

        String& append_override(const String& other)
        {
            return append_override(other.c_str());
        }

        bool reserve(const size_t& new_capacity)
        {
            if (new_capacity <= _len)
                return false;

            char* new_str = new char[new_capacity + 1];
            _strcpy(new_str, _str);

            delete[] _str;
            _str = new_str;

            return true;
        }

        friend std::ostream& operator<<(std::ostream& os, const String& str)
        {
            return os << str._str;
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