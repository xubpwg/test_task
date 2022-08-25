#ifndef JAVA_CODE_GENERATOR_HEADER_GUARD
#define JAVA_CODE_GENERATOR_HEADER_GUARD

#include "CodeGenerator.h"
#include "JavaLanguage.h"

class JavaCodeGenerator : public CodeGenerator
{
public:
    virtual Language* getLanguage() const override
    {
        return new JavaLanguage();
    }
};

#endif // JAVA_CODE_GENERATOR_HEADER_GUARD