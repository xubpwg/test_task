#ifndef CPP_LANGUAGE_HEADER_GUARD
#define CPP_LANGUAGE_HEADER_GUARD

#include "Language.h"

class CppLanguage : public Language
{
public:
    CppLanguage() = default;

    virtual std::string code() const override;
    virtual std::string codeRelatedThing() const override;
}; 

#endif // CPP_LANGUAGE_HEADER_GUARD