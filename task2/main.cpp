#include <vector>

#include "CppCodeGenerator.h"
#include "JavaCodeGenerator.h"

void fillGenerators(std::vector<CodeGenerator*>& generators)
{
    generators.push_back(new CppCodeGenerator());
    generators.push_back(new JavaCodeGenerator());
}

int main(int argc, char *argv[])
{
    std::vector<CodeGenerator*> generators;
    fillGenerators(generators);

    for (const auto& generator : generators)
    {
        generator->generateCode();
        delete generator;
    }

    return 0;
}