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



    String format() const{ return m_Buff; }

    template <typename T, typename... Tpack>
    String format(T first, Tpack... rest){

        String ret = m_Buff;
        int ind = ret.find('%');

        if(ind == -1) return ret;

        switch (ret[ind+1]){
            case 'c':
                ret.cut(ind, 2);
                ret.insert((first), ind);
                break;

            case 'C':
                break;

            case 'd':
                ret.cut(ind, 2);
                ret.insert(toString((first)), ind);
                break;

            case 'i':
                ret.cut(ind, 2);
                ret.insert(toString((first)), ind);
                break;

            case 'o':

                break;

            case 'u':
                ret.cut(ind, 2);
                ret.insert(toString((first)), ind);
                break;

            case 'x':

                break;

            case 'e':
            case 'E':
            case 'f':
            case 'F':
                ret.cut(ind, 2);
                ret.insert(toString((first)), ind);
                break;

            case 'g':
            case 'G':
                ret.cut(ind, 2);
                ret.insert(toString((first)), ind);
                break;

            case 'a':
            case 'A':
                break;

            case 'n':
                break;

            case 'p':
                break;

            case 's':
                ret.cut(ind, 2);
                ret.insert(first, ind);
                break;

            case 'S':
                ret.cut(ind, 2);
                ret.insert(first, ind);
                break;

            case 'z':
                break;
        }

        return ret.format(rest...);
    }


    char& operator[](uint16_t) const;

    char& at(uint16_t) const;

    friend String operator +(const String&, const String&);

    void operator += (const String&);

    friend String operator +(const String&, const char);

    void operator += (const char);

    void operator = (const char*);

    void operator = (const String&);

    [[nodiscard]] bool operator == (const String&) const;

    friend std::ostream &operator <<(std::ostream&, const String&);

    friend std::istream &operator >>(std::istream&, const String&);

};

