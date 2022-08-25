#ifndef CODE_GENERATOR_HEADER_GUARD
#define CODE_GENERATOR_HEADER_GUARD

#include "Language.h"

class CodeGenerator
{
public:
    virtual ~CodeGenerator() {};
    virtual Language* getLanguage() const = 0;
    
    std::string generateCode()
    {
        someCodeRelatedThing();
        Language* language = getLanguage();
        std::string result = language->code();
        delete language;
        return result;
    }
    
    std::string someCodeRelatedThing()
    {
        Language* language = getLanguage();
        std::string result = language->codeRelatedThing();
        delete language;
        return result;
    }
};

#endif // CODE_GENERATOR_HEADER_GUARD