#pragma once

#include <ostream>
#include <istream>
#include <unordered_map>

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


    uint16_t length() const;

    uint16_t capacity() const;

    [[nodiscard]] String substr(uint16_t = 0, int16_t = -1) const;

    bool search(const String&) const;

    int find(const String&) const;

    [[nodiscard]] int rfind(const String&) const;

    void insert(const String&, int16_t = -1);

    [[nodiscard]] uint16_t count(String c);

    void cut(uint16_t = 0, int16_t = -1);


    /**
     * @brief Creates an array of strings using the given delimiter
     * 
     * @param delimiter
     * @return A dynamically allocated String array
     */
    String* split(String);

    void join(String[]);


    void toUpper();
    [[nodiscard]] String upper() const;
    bool isUpper() const;


    void toLower();
    [[nodiscard]] String lower() const;
    bool isLower() const;


    void title();
    [[nodiscard]] String titled() const;
    bool isTitle() const;


    void capitalize();
    [[nodiscard]] String capitalized() const;
    bool isCapitalize() const;


    void strip();
    [[nodiscard]] String stripped();
    // void stripVer2EXPERIMENTAL();

    void lstrip();
    [[nodiscard]] String lstripped();

    void rstrip();
    [[nodiscard]] String rstripped();


    bool startswith(const String&) const;
    bool endsWith(const String&) const;


    bool isAlpha() const;

    bool isDecimal() const;

    bool isAlNum() const;

    bool isSpace() const;

    void setEncryptionFunc(String(*_)(String));

    void setDecryptionFunc(String(*_)(String));

    void encrypt();

    void decrypt();

    char& operator[](uint16_t) const;

    char& at(uint16_t) const;

    void forEach(void(*)(char&));

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

