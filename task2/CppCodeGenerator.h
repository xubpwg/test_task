#ifndef CPP_CODE_GENERATOR_HEADER_GUARD
#define CPP_CODE_GENERATOR_HEADER_GUARD

#include "CodeGenerator.h"
#include "CppLanguage.h"

class CppCodeGenerator : public CodeGenerator
{
public:
    virtual Language* getLanguage() const override
    {
        return new CppLanguage();
    }
};

#endif // CPP_CODE_GENERATOR_HEADER_GUARD