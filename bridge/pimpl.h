#pragma once
struct Person
{
    std::string name;
    void greet();
    Person();
    ~Person();
    class PersonImpl;
    PersonImpl * impl; //good place for gslowner<T>
};