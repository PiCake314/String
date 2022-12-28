#pragma once

#include <ostream>
#include <istream>
#include <type_traits>

class String{
    char *m_Buff = new char[1];
    uint16_t m_Size;
    uint16_t m_Cap;

    String toString(int);
    const String& toString(const String& s) { return s; }
    void doubleStr();

public:
    String();
    String(const char);
    String(const char*);
    String(const String&);

    ~String();


    [[nodiscard]] uint16_t length() const;

    [[nodiscard]] uint16_t capacity() const;

    [[nodiscard]] String substr(uint16_t = 0, int16_t = -1) const;

    [[nodiscard]] bool search(const String&) const;

    [[nodiscard]] int find(const String&) const;

    void insert(const String&, int16_t = -1);

    [[nodiscard]] uint16_t count(String c);

    void cut(uint16_t = 0, int16_t = -1);



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



    void toUpper();

    String upper();

    void toLower();

    String lower();

    void toTitle();

    String title();

    char& operator[](uint16_t) const;

    char& at(uint16_t) const;

    friend String operator +(const String&, const String&);

    void operator += (const String&);

    friend String operator +(const String&, const char);

    void operator += (const char);

    void operator = (const char*);

    void operator = (const String&);

    [[nodiscard]] bool operator == (const char*) const;
    [[nodiscard]] bool operator == (const String&) const;

    friend std::ostream &operator <<(std::ostream&, const String&);

    friend std::istream &operator >>(std::istream&, const String&);

};

