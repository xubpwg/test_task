#include <iostream>

#include "CppLanguage.h"

std::string CppLanguage::code() const
{
    std::string res("CppLanguage::code");
    std::cout << res << std::endl;
    return res;
}

std::string CppLanguage::codeRelatedThing() const
{
    std::string res("CppLanguage::codeRelatedThing");
    std::cout << res << std::endl;
    return res;
}