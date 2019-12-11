#include <iostream>
#include<vector>
using namespace std;


// We want to reuse the code for other class more than Person
// therefore

template<typename T>
struct  Observer
{
    virtual void field_changed(T & s, const string property_name) = 0; // pure virtual
};

// Observer subscribe/ unsubsribe
// Informing all observers when a change is actually made with method notify()
template <typename T> struct Observable
{
public:
    void notify(T& source, const string & name)
    {
        for(auto && obs : observers) obs->field_changed(source, name);
    }
    void subscribe(Observer<T>* f) {observers.push_back(f);}
    void unsubribe(Observer<T>* f)
    {
        auto it = observers.find(f);
        if(it == cend(observers))
        {
            return;
        }
        else
        {
            observers.erase(it);
        }
    }
private:
    // observers should not be access by users
    vector<Observer<T> *> observers;
};

struct Person : Observable<Person>
{
public:
    int get_age() const {return this->age;}
    void set_age(const int value)
    {
        if(value == this->age) return;
        this->age = value;
        notify(*this, "age");
    }
    Person(int age) : age(age) {}
private:
    int age;
};

// then inherent from the base Observer class

struct ConsolePersonObserver : Observer<Person>
{
    void field_changed(Person & s, const string property_name) override
    {
        cout << "Person's " << property_name << " has changed into" << s.get_age() << endl;
    };
};

// how to check a person entity is changed
// polling? not a good idea

// let us define a PersonListener CLass
/*
struct PersonListener
{
    virtual void person_changed(Person & p, const string property_name, const any_new_value) = 0; // pure virtual
};
*/



int main()
{
    Person p{20};
    ConsolePersonObserver cpo;
    p.subscribe(&cpo);
    p.set_age(20); // no output
    p.set_age(21); // make output
    return 0;
}
