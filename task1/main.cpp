class Foo
{
public:
    Foo(int j) 
    { 
        i = new int[j]; 
    }

    ~Foo() // problem: destructor of the base class should be virtual 
    { 
        delete i; // problem: should be delete[] i
    }

private:
    int* i;
};

class Bar: Foo // problem: should be public inheritance, private by default
{
public:
    Bar(int j) // problem: should have Foo constructor call here, cause we have non-default one for Foo
    { 
        i = new char[j]; 
    }
    ~Bar() 
    { 
        delete i; // problem: should be delete[] i 
    }

private:
    char* i;
};


void main() // problem: non-standard main function form, should return int
{
    Foo* f = new Foo(100);
    Foo* b = new Bar(200);
    *f = *b; 
    // problem: we will have double free error below, cause we have the same object pointed by two pointers.
    // this is general design error 
    delete f;
    delete b;

    // problem: main should return int
}