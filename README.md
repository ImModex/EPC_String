# Custom String Class - EPC

Assignment #1 Efficient Programming C++ - Create a custom string class

## Requirements
Write your own string class that offers at least the following functionalities:
- Strings can be initialized by const char*.
- Several strings can be appended together using an append() function.
- The internal string representation can be queried via a member function c_str().
- A length() or size() method allows the string length to be queried.
- Check your code on different compilers (Clang, GCC, MSVC)

**Optional:**
- A reserve() method that changes the container size.
- A capacity() method that allows the container size to be queried.

## Grading
- Constructor: 1 point
- Destructor: 1 point
- append: 2 points
- c_str: 1 points
- length & size: 1 points

**Deduction criteria**
- Memory problems (e.g. program crashes (sometimes), memory leak or could cause one, etc.)
- Performance (allocations on the heap that are not needed or additional avoidable copying of data)
- Portability to other platforms is not given
- Code is not const-correct

## Implementation
### Heap
First implementation is using heap assignments to dynamically handle a `char*` using the `new` and `delete` functionalities.

#### Usage
> make heap \
> ./heap \
> or \
> valgrind --leak-check=full --track-origins=yes ./heap

### Stack
Second implementation is using stack variables utilizing a `std::vector<char>` in the background.

#### Usage
> make stack \
> ./stack \
> or \
> valgrind --leak-check=full --track-origins=yes ./stack

## Info
`append(...)` vs `append_override(...)` \
- The first function copies the content of the given string to a _temporary buffer_ and returns a **new object** containing the appended string **leaving the original string the same**
- The second function copies the content of the given string _into_ the first string and returns the string that has been appened to

<br>
There are some define flags that change the program's behaviour

- `#define APPEND_NEW_OBJECT <1|0>` - this flag toggles between the `append(...)` and `append_override(...)` functions (1 = `append(...)`, 0 = `append_override(...)`)
- `#define IO <1|0>` - whether to print the output to the console or not
- `#define AVERAGE_AMOUNT 10000000` - how many times to run the program to average the runtime
    - (**WARNING!!! DO NOT HAVE IO ENABLED WITH THIS SET TO >1**) 

## Result
After playing around a bit, the test results on my machine are clear

Average runtimes were...
- Heap - `126.671ns`
- Stack - `396.178ns`

effectively making the heap variant much faster.