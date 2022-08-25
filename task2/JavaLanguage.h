#ifndef JAVA_LANGUAGE_HEADER_GUARD
#define JAVA_LANGUAGE_HEADER_GUARD

#include "Language.h"

class JavaLanguage : public Language
{
public:
    JavaLanguage() = default;

    virtual std::string code() const override;
    virtual std::string codeRelatedThing() const override;
}; 

#endif // CPP_LANGUAGE_HEADER_GUARD