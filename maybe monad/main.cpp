#include <iostream>
#include <string>
#include <memory>

using namespace std;

/*
how to express the presence or absence of a value
1. nullptr encoding 
2. smart pointer ...
3. std::optional<T>
*/
template <typename T> 
struct Maybe;
template <typename T> 
Maybe<T> maybe(T* context);

/* nullptr approach */
struct Address
{
    string * house_name = nullptr;
    Address(string * s) : house_name(s) {}
};

struct Person
{
    Address * add = nullptr;
};

/* conventional method 
void print_house_name(Person * p)
{
    if(p && p->add && p->add->house_name)
        cout << *p->add->house_name << endl;
}
*/

/* maybe */
template <typename T> 
struct Maybe
{
    T * context;
    Maybe(T * context) : context(context) {}


    /* 
    Drills deeper into the object if context != nullptr
    Does nothing if the context is, in fact, nullptr
    */
    template <typename Func>
    auto With(Func evaluator)
    {
        return context != nullptr ? maybe(evaluator(context)) : nullptr;
    }

    template <typename TFunc>
    auto Do(TFunc action)
    {
        if(context != nullptr) action(context);
        /* for nullptr context, return *this without side effect */
        return *this;
    }

};

template <typename T> 
Maybe<T> maybe(T* context)
{
    return Maybe<T>(context);
}

/* a fluent interface */
void print_house_name(Person * p)
{
    auto z = maybe(p)
            .With([](auto x) {return x->add;})
            .With([](auto x) {return x->house_name;})
            .Do([](auto x) {cout << *x << endl;});
}


int main()
{
    Person * p = new Person;
    p->add = new Address(new string("test"));

    print_house_name(p);
    return 0;

}


