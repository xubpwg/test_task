#ifndef LANGUAGE_HEADER_GUARD
#define LANGUAGE_HEADER_GUARD

#include <string>

class Language
{
public:
    virtual ~Language() {};

    virtual std::string code() const = 0;
    virtual std::string codeRelatedThing() const = 0;
};

#endif // LANGUAGE_HEADER_GUARD