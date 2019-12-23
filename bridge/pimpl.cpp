#include <stdio.h>
#include <string>
#include "pimpl.h"
/*
*definition is here, not in the header
*/
struct Person::PersonImpl
{
    void greet(Person* p);
};

Person::Person()
    : impl(new PersonImpl), name("John"){}

Person::~Person() {delete impl;}

void Person::greet()
{
    impl->greet(this);
}

void Person::PersonImpl::greet(Person* p)
{
    printf("hello %s \n", p->name.c_str());
}

int main()
{
    Person a;
    a.greet();
    return 0;
}