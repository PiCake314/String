#include "string.hpp"


String::String() : m_Size(0), m_Cap(1){
    m_Buff[0] = char(NULL); 
    // printf("Default!\n");
}


String::String(const char c) : m_Size(1), m_Cap(2){
    delete[] m_Buff;
    m_Buff = new char[2];
    m_Buff[0] = c;
    m_Buff[1] = '\0';

    // printf("Char'd!\n");
}


String::String(const char *other) : m_Cap(1){

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

    // printf("Copied!\n");
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
    int limit = m_Size - toFind.m_Size;

    char *sub = new char[toFind.m_Size+1];

    for(int i = 0; i <= limit; i++){
        for(int j = 0; j < toFind.m_Size; j++)
            sub[j] = m_Buff[i+j];
        sub[toFind.m_Size] = '\0';

        if(toFind == sub){
            delete[] sub;
            return i;
        }
    }

    delete[] sub;
    return -1;
}


int String::rfind(const String& toFind) const{
    int limit = m_Size - toFind.m_Size;

    char *sub = new char[toFind.m_Size+1];

    int last = -1;
    for(int i = 0; i <= limit; i++){
        for(int j = 0; j < toFind.m_Size; j++)
            sub[j] = m_Buff[i+j];
        sub[toFind.m_Size] = '\0';

        if(toFind == sub) last = i;
    }

    delete[] sub;
    return last;
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


uint16_t String::count(String c){
    int limit = m_Size - c.m_Size - 1;

    int total = 0;
    for(int i = 0; i < limit; i++)
        if(substr(i, c.m_Size) == c) total++;

    return total;
}


void String::cut(uint16_t index, int16_t len){
    if(len == -1){
        m_Size = index;
        m_Buff[index] = '\0';
        return;
    }

    int limit = m_Size - len;

    for(m_Size = index; m_Size < limit; m_Size++)
        m_Buff[m_Size] = m_Buff[m_Size+len];

    m_Buff[m_Size] = '\0';
}


String* String::split(String delimiter){
    if(delimiter.m_Size >= m_Size) return {};

    bool flag = substr(0, delimiter.m_Size) != delimiter;
    uint16_t size = 0;
    for(int i = 0; i <= m_Size - delimiter.m_Size; i++)
        if(substr(i, delimiter.m_Size) == delimiter) flag = true;
        else if(flag){
            size++;
            flag = false;
        }


    String *array = new String[size];
    int i = 0;
    while(i <= m_Size - delimiter.m_Size && substr(i, delimiter.m_Size) == delimiter) i += delimiter.m_Size;

    for(int prev = i, ind = 0; i <= m_Size; i++){
        if(substr(i, delimiter.m_Size) == delimiter || i == m_Size){
            array[ind] = substr(prev, i - prev);
            ind++;

            while(i <= m_Size - delimiter.m_Size && substr(i, delimiter.m_Size) == delimiter) i += delimiter.m_Size;
            prev = i;
        }
    }
    return array;
}


void String::toUpper(){
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] >= 'a' && m_Buff[i] <= 'z')
            m_Buff[i] -= 32;
}


String String::upper() const{
    String ret(m_Buff);
    ret.toUpper();
    return ret;
}


bool String::isUpper() const{
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] >= 'a' && m_Buff[i] <= 'z') return false;

    return true;
}


void String::toLower(){
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] >= 'A' && m_Buff[i] <= 'Z')
            m_Buff[i] += 32;
}


String String::lower() const{
    String ret(m_Buff);
    ret.toLower();
    return ret;
}


bool String::isLower() const{
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] >= 'A' && m_Buff[i] <= 'Z') return false;

    return true;
}


void String::title(){
    if(*m_Buff >= 'a' && *m_Buff <= 'z') *m_Buff -= 32;

    for(int i = 1; i < m_Size; i++)
        if(m_Buff[i] >= 'a' && m_Buff[i] <= 'z' && m_Buff[i-1] == ' ')
            m_Buff[i] -= 32;
}


String String::titled() const{
    String ret(m_Buff);
    ret.title();
    return ret;
}


bool String::isTitle() const{
    if(*m_Buff >= 'a' && *m_Buff <= 'z') return false;

    for(int i = 1; i < m_Size; i++)
        if(m_Buff[i] >= 'a' && m_Buff[i] <= 'z' && m_Buff[i-1] == ' ')
            return false;

    return true;
}


void String::capitalize(){
    if(*m_Buff >= 'a' && *m_Buff <= 'z') (*m_Buff) -= 32;

    for(int i = 1; i < m_Size; i++)
        if(m_Buff[i] >= 'A' && m_Buff[i] <= 'Z') m_Buff[i] += 32;
}


String String::capitalized() const{
    String ret(m_Buff);
    ret.capitalize();
    return ret;
}


bool String::isCapitalize() const{
    if(*m_Buff >= 'a' && *m_Buff <= 'z') return false;

    for(int i = 1; i < m_Size; i++)
        if(m_Buff[i] >= 'A' && m_Buff[i] <= 'Z') return false;

    return true;
}


void String::strip(){
    for(; m_Size-1 >= 0 &&  m_Buff[m_Size-1] == ' '; m_Size--);

    int start = 0;
    for(; m_Buff[start] == ' '; start++, m_Size--);

    for(int i = 0; i < m_Size; i++)
        m_Buff[i] = m_Buff[i+start];

    m_Buff[m_Size] = '\0';
}


// void String::stripVer2EXPERIMENTAL(){
//     for(; *m_Buff == ' '; m_Buff++, m_Cap--, m_Size--, d++);
//     for(; m_Size-1 >= 0 && m_Buff[m_Size-1] == ' '; m_Size--);
//     m_Buff[m_Size] = '\0';
// }


String String::stripped(){
    String ret(m_Buff);
    ret.strip();
    return ret;
}


void String::lstrip(){
    int start = 0;
    for(; m_Buff[start] == ' '; start++);

    m_Size -= start;
    for(int i = 0; i < m_Size; i++)
        m_Buff[i] = m_Buff[i+start];

    m_Buff[m_Size] = '\0';
}


String String::lstripped(){
    String ret(m_Buff);
    ret.lstrip();
    return ret;
}


void String::rstrip(){
    int end = 0;
    for(int i = m_Size-1; m_Buff[i] == ' '; i--, end++);

    m_Size -= end;
    m_Buff[m_Size] = '\0';
}


String String::rstripped(){
    String ret(m_Buff);
    ret.rstrip();
    return ret;
}


bool String::startswith(const String &s) const{
    return m_Size >= s.m_Size && substr(0, s.m_Size) == s;
}


bool String::endsWith(const String &s) const{
    return m_Size >= s.m_Size && substr(m_Size-s.m_Size) == s;
}


bool String::isAlpha() const{
    for(int i = 0; i < m_Size; i++)
        if((m_Buff[i] < 'A' || m_Buff[i] > 'Z')
        && (m_Buff[i] <'a' || m_Buff[i] > 'z'))
            return false;

    return true;
}


bool String::isDecimal() const{
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] < '0' || m_Buff[i] > '9')
            return false;

    return true;
}


bool String::isAlNum() const{
    return isDecimal() || isAlpha();
}


bool String::isSpace() const{
    for(int i = 0; i < m_Size; i++)
        if(m_Buff[i] != ' ' && m_Buff[i] != '\t' && m_Buff[i] != '\n')
            return false;

    return true;
}


void String::setEncryptionFunc(String(*func)(String)) { enc = func; }

void String::setDecryptionFunc(String(*func)(String)) { dec = func; }


void String::encrypt(){
    String temp = enc(m_Buff);

    m_Size = temp.m_Size;
    m_Cap = temp.m_Cap;

    delete[] m_Buff;
    m_Buff = new char[m_Size+1];

    for(int i = 0; i < m_Size; i++)
        m_Buff[i] = temp.m_Buff[i];
    m_Buff[m_Size] = '\0';
}


void String::decrypt(){
    String temp = dec(m_Buff);

    m_Size = temp.m_Size;
    m_Cap = temp.m_Cap;

    delete[] m_Buff;
    m_Buff = new char[m_Size+1];

    for(int i = 0; i < m_Size; i++)
        m_Buff[i] = temp.m_Buff[i];
    m_Buff[m_Size] = '\0';
}


char& String::operator[](uint16_t index) const{
    return m_Buff[index];
}


char& String::at(uint16_t index) const{
    return m_Buff[index];
}


void String::forEach(void(*func)(char&)){
    for(uint16_t i = 0; i < m_Size; i++)
        func(m_Buff[i]);
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
    ret[ret.m_Size++] = c;
    ret[ret.m_Size] = '\0';

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


bool String::operator==(const char* other) const{
    for(int i = 0; i < m_Size && other[i] != '\0'; i++)
        if(m_Buff[i] != other[i]) return false;

    return true;
}

bool String::operator==(const String &other) const{
    if(m_Size == other.m_Size){
        for(int i = 0; i < m_Size; i++)
            if(m_Buff[i] != other[i]) return false;

        return true;
    }

    return false;
}


bool String::operator!=(const char* other) const{
    for(int i = 0; i < m_Size && other[i] != '\0'; i++)
        if(m_Buff[i] != other[i]) return true;

    return false;
}

bool String::operator!=(const String &other) const{
    if(m_Size == other.m_Size){
        for(int i = 0; i < m_Size; i++)
            if(m_Buff[i] != other[i]) return true;

        return false;
    }

    return true;
}


std::ostream &operator <<(std::ostream &os, const String &s){
    return os << s.m_Buff;
}

std::istream &operator >>(std::istream &is, const String &s){
    return is >> s.m_Buff;
}


char* String::begin() const{ return m_Buff; }
char* String::end() const{ return m_Buff + m_Size; }



String String::toString(int num){
    if(num == 0) return "";
    return toString(num/10) + char((num%10)+48);
}


void String::doubleStr(){
    m_Cap *= 2;
    char *newBuff = new char[m_Cap];

    for(int i = 0; i < m_Size; i++) newBuff[i] = m_Buff[i];

    delete[] m_Buff;
    m_Buff = newBuff;
}