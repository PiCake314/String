#pragma once

#include <ostream>
#include <istream>
#include <unordered_map>
#include <vector>

class String{
    char *m_Buff = new char[1];
    uint16_t m_Size;
    uint16_t m_Cap;

    String toString(int);
    const String& toString(const String& s) { return s; }
    void doubleStr();


    String (*enc)(String);
    String (*dec)(String);

public:
    String();
    String(const char);
    String(const char*);
    String(const String&);

    ~String();



    /**
     * @return The length of the string.
     */
    uint16_t length() const;



    /**
     * @return The capacity of the buffer.
     */
    uint16_t capacity() const;



    /**
     * @param ind
     * @param len
     * @return A substring of the original string. 
     */
    [[nodiscard]] String substr(uint16_t = 0, int16_t = -1) const;



    /**
     * @brief Searches for the given string.
     * 
     * @return true if it wase found. False otherwize.
     */
    bool search(const String&) const;



    /**
     * @brief Finds the first instance of the given string.
     */
    int find(const String&) const;



    /**
     * @brief Finds from the end of the string.
     */
    [[nodiscard]] int rfind(const String&) const;



    /**
     * @brief Inserts the given string at the given index.
     * 
     * @param str
     * @param ind
     */
    void insert(const String&, int16_t = -1);



    /**
     * @brief Counts how many times the given string appears in the string.
     * 
     * @param str
     */
    [[nodiscard]] uint16_t count(String);



    /**
     * @brief Removes the part specified from the string.
     * 
     * @param ind
     * @param len
     */
    void cut(uint16_t = 0, int16_t = -1);



    /**
     * @brief Creates an array of strings using the given delimiter.
     * 
     * @param delimiter
     * @return A dynamically allocated String array.
     */
    String* split(String);


    /**
     * @brief Joins an array of Strings using the string itself as a delimiter.
     */
    void join(String[], uint16_t);
    void join(std::vector<String>);

    /**
     * @brief 
     * 
     */
    void forEach(void(*)(char&), int = -1);


    /**
     * @brief Converts the string to upper case.
     */
    void toUpper();

    /**
     * @return An upper case copy of the original string. 
     */
    [[nodiscard]] String upper() const;

    /**
     * @brief Checks if the string is upper case.
     */
    bool isUpper() const;


    /**
     * @brief Converts the string to lower case.
     */
    void toLower();

    /**
     * @return A lower case copy of the original string. 
     */
    [[nodiscard]] String lower() const;

    /**
     * @brief Checks if the string is lower case.
     */
    bool isLower() const;


    /**
     * @brief Converts the string to title case.
     */
    void title();

    /**
     * @return A title case copy of the original string. 
     */
    [[nodiscard]] String titled() const;

    /**
     * @brief Checks if the string is title case.
     */
    bool isTitle() const;


    /**
     * @brief Capitalizes the first letter and makes the rest lower case.
     */
    void capitalize();

    /**
     * @return A copy of the String with the first letter capitalized and the rest are lower.
     */
    [[nodiscard]] String capitalized() const;


    /**
     * @brief Checks if first letter of the string is capitalized and the rest lower.
     */
    bool isCapitalize() const;


    /**
     * @brief Strips the string from excess spaces.
     */
    void strip();

    /**
     * @return A stripped copy of the string.
     */
    [[nodiscard]] String stripped();
    // void stripVer2EXPERIMENTAL();


    /**
     * @brief Strips the string from the left.
     */
    void lstrip();

    /**
     * @return An lstripped copy of the string.
     */
    [[nodiscard]] String lstripped();

    /**
     * @brief Strips the string from the right.
     */
    void rstrip();

    /**
     * @return An rstripped copy of the string.
     */
    [[nodiscard]] String rstripped();


    /**
     * @brief Checks if the strings starts with the given string.
     */
    bool startswith(const String&) const;

    /**
     * @brief Checks if the strings ends with the given string.
     */
    bool endsWith(const String&) const;

    /**
     * @brief Checks if the string has only alphabetical characters. 
     */
    bool isAlpha() const;

    /**
     * @brief Checks if the string has only decimal numbers. 
     */
    bool isDecimal() const;

    /**
     * @brief Checks if the string has only decimal numbers. 
     */
    bool isAlNum() const;

    /**
     * @brief Checks if the string has only space characters. 
     */
    bool isSpace() const;


    /**
     * @brief Set the Encryption Func object.
     */
    void setEncryptionFunc(String(*)(String));


    /**
     * @brief Set the Decryption Func object.
     */
    void setDecryptionFunc(String(*)(String));

    /**
     * @brief Encrypts the string using the given function.
     */
    void encrypt();

    /**
     * @brief Decrypts the string using the given function.
     */
    void decrypt();

    char& operator[](uint16_t) const;

    char& at(uint16_t) const;

    friend String operator +(const String&, const String&);

    void operator += (const String&);

    friend String operator +(const String&, const char);

    void operator += (const char);

    void operator = (const char*);

    void operator = (const String&);

    bool operator == (const char*) const;
    bool operator == (const String&) const;

    bool operator != (const char*) const;
    bool operator != (const String&) const;


    friend std::ostream &operator <<(std::ostream&, const String&);

    friend std::istream &operator >>(std::istream&, const String&);


    char* begin() const;
    char* end() const;


    /**
     * @brief Formats the string that contain '%' followed by ['d', 'c'...etc]
     * 
     * @tparam The pack that's used to replace the '%'.
     */
    void format() const{}
    template <typename T, typename... Tpack>
    void format(T first, Tpack... rest){
        int ind = find('%');

        if(ind == -1) return;

        switch (m_Buff[ind+1]){
            case 'c':
                cut(ind, 2);
                insert((first), ind);
                break;

            case 'C':
                break;

            case 'd':
                cut(ind, 2);
                insert(toString((first)), ind);
                break;

            case 'i':
                cut(ind, 2);
                insert(toString((first)), ind);
                break;

            case 'o':

                break;

            case 'u':
                cut(ind, 2);
                insert(toString((first)), ind);
                break;

            case 'x':

                break;

            case 'e':
            case 'E':
            case 'f':
            case 'F':
                cut(ind, 2);
                insert(toString((first)), ind);
                break;

            case 'g':
            case 'G':
                cut(ind, 2);
                insert(toString((first)), ind);
                break;

            case 'a':
            case 'A':
                break;

            case 'n':
                break;

            case 'p':
                break;

            case 's':
                cut(ind, 2);
                insert(first, ind);
                break;

            case 'S':
                cut(ind, 2);
                insert(first, ind);
                break;

            case 'z':
                break;
        }

        format(rest...);
    }


    // template <typename T>
    // String format_map(std::unordered_map<String, T>){

    // }


};

