#include "test.h"
#include "decoder.h"
#include "encoder.h"
#include <iostream>
#include <string>
void test()
{
    int count;
    std::string text, encodetext;
    while(true)
    {
        std::cout << "Enter text." << std::endl;
        std::getline(std::cin,text);
        if(text == "break")
            break;
        std::cout << "Enter the encoding code." << std::endl;
        std::cin >> count;
        std::cin.clear();
        std::cin.ignore(32767,'\n');

        encodetext = encoder(text,count);
        encodetext = decoder(encodetext, count);
        if (encodetext == text)
            std::cout << "OK" << std::endl;
        else
            std::cout << "ERROR" << std::endl;
    }
}

