#include <iostream>

#include "JavaLanguage.h"

std::string JavaLanguage::code() const
{
    std::string res("JavaLanguage::code");
    std::cout << res << std::endl;
    return res;
}

std::string JavaLanguage::codeRelatedThing() const
{
    std::string res("JavaLanguage::codeRelatedThing");
    std::cout << res << std::endl;
    return res;
}