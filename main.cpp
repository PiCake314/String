#include <iostream>
#include "String.hpp"


void func(String str){
    std::cout << str << std::endl;
}


int main(){

    String s = "Hello, my name is %s, I am %d years old!";

    s.format("Ali", 21);

    std::cout << s << std::endl;


}