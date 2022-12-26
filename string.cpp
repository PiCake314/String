#include "string.hpp"


String::String() : m_Size(0), m_Cap(1){ m_Buff[0] = char(NULL); }


// String::String(const char c) : m_Size(0) {}


String::String(const char *other) : m_Cap(1){
    // printf("Constructing!\n");

    for(m_Size = 0; other[m_Size] != '\0'; m_Size++){
        if(m_Size >= m_Cap) doubleStr();

        m_Buff[m_Size] = other[m_Size];
    }
    m_Buff[m_Size] = '\0';

    // printf("Constructed!\n");
}


String::String(const String &other) : m_Cap(1){

    for(m_Size = 0; other[m_Size] != '\0'; m_Size++){
        if(m_Size >= m_Cap) doubleStr();

        m_Buff[m_Size] = other[m_Size];
    }
    m_Buff[m_Size] = '\0';
}


String::~String(){
    // printf("Distructed!\nm_Buff: %s\nSize: %d\nCap: %d\n", m_Buff, m_Size, m_Cap);
    delete[] m_Buff;
}


uint16_t String::length() const{
    return m_Size;
}


uint16_t String::capacity() const{
    return m_Cap;
}


String String::substr(uint16_t index, int16_t len) const{
    len = len == -1 ? m_Size : len;

    char *ret = new char[len+1];

    for(int i = 0; i < len; i++)
        ret[i] = m_Buff[index+i];
    ret[len] = '\0';

    String r = ret;
    delete[] ret;
    return r;
}


bool String::search(const String &toFind) const{
    int limit = m_Size - toFind.m_Size - 1;

    for(int i = 0; i < limit; i++)
        if(substr(i, toFind.m_Size) == toFind) return true;

    return false;
}


int String::find(const String& toFind) const{
    int limit = m_Size - toFind.m_Size - 1;

    for(int i = 0; i < limit; i++)
        if(substr(i, toFind.m_Size) == toFind) return i;

    return -1;
}


void String::insert(const String &toIns, int16_t pos){
    pos = pos == -1 ? m_Size : pos;
    
    String end = substr(pos);

    uint16_t limit = pos + toIns.m_Size+ end.m_Size;

    for(m_Size = pos < m_Size ? pos : m_Size; m_Size < limit; m_Size++){
        if(m_Size >= m_Cap) doubleStr();

        if(m_Size < pos) m_Buff[m_Size] = ' ';
        else m_Buff[m_Size] = m_Size - pos < toIns.m_Size ? toIns[m_Size - pos] : end[m_Size - pos - toIns.m_Size];
    }

    m_Buff[m_Size] = '\0';
}



template <typename T, typename... Tpack>
String String::format(T first, Tpack... rest) const{

}


char& String::operator[](uint16_t index) const{
    return m_Buff[index];
}


char& String::at(uint16_t index) const{
    return m_Buff[index];
}


String operator+(const String &us, const String &other){
    int size = us.m_Size + other.m_Size;

    char *buffer = new char[size+1];

    for(int i = 0; i < size; i++)
        buffer[i] = i < us.m_Size ? us.m_Buff[i] : other.m_Buff[i - us.m_Size];

    buffer[size] = '\0';

    String ret = buffer;
    delete[] buffer;
    return ret;
}


void String::operator+=(const String &other){
    int size = m_Size + other.m_Size;

    for(int s = 0; s < other.m_Size; s++){
        if(m_Size >= m_Cap) doubleStr();

        m_Buff[m_Size++] = other.m_Buff[s];
    }

    m_Buff[size] = '\0';
}


String operator+(const String &us, const char c){
    String ret = us;
    if(ret.m_Size+1 >= ret.m_Cap) ret.doubleStr();
    ret[ret.m_Size] = c;

    return ret;
}


void String::operator+=(const char c){
    if(m_Size >= m_Cap) doubleStr();
    m_Buff[m_Size++] = c;
    m_Buff[m_Size] = '\0';
}


void String::operator=(const char *other){
    // printf("Reconsing!\nS: %d\nC: %d\n", m_Size, m_Cap);

    for(m_Size = 0; other[m_Size] != '\0'; m_Size++){
        if(m_Size >= m_Cap) doubleStr();

        m_Buff[m_Size] = other[m_Size];;
    }
    m_Buff[m_Size] = '\0';

    // printf("Recons!\n");
}


void String::operator=(const String &other){

    for(m_Size = 0; other[m_Size] != '\0'; m_Size++){
        if(m_Size >= m_Cap) doubleStr();

        m_Buff[m_Size] = other[m_Size];
    }
    m_Buff[m_Size] = '\0';

    // printf("Recons!\n");
}


bool String::operator==(const String &other) const{
    if(m_Size == other.m_Size){
        for(int i = 0; i < m_Size; i++)
            if(m_Buff[i] != other[i]) return false;

        return true;
    }

    return false;
}



std::ostream &operator <<(std::ostream &os, const String &s){
    return os << s.m_Buff;
}

std::istream &operator >>(std::istream &is, const String &s){
    return is >> s.m_Buff;
}


void String::doubleStr(){
    m_Cap *= 2;
    char *newBuff = new char[m_Cap];

    for(int i = 0; i < m_Size; i++) newBuff[i] = m_Buff[i];

    delete[] m_Buff;
    m_Buff = newBuff;
}