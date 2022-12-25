#pragma once

#include <ostream>


class String{
    char *m_Buff = new char[1];
    uint16_t m_Size = 0;
    uint16_t m_Cap = 1;

public:
    String();
    // String(const char);
    String(const char*);
    String(const String&);

    ~String();

    [[nodiscard]] uint16_t length() const;

    [[nodiscard]] uint16_t capacity() const;

    String substr(uint16_t = 0, uint16_t = -1) const;

    char& operator[](uint16_t) const;

    char& at(uint16_t) const;

    friend String operator +(const String&, const String&);

    void operator += (const String&);

    friend String operator +(const String&, const char);

    void operator += (const char);

    void operator = (const char*);

    void operator = (const String&);

    friend std::ostream &operator <<(std::ostream&, const String&);



    void doubleStr();
};