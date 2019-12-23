/*
*flyweight also called token
*it is a component that acts as a "smarter reference"
*to something.
*/

/*
image a mmo game.
*/

#include <iostream>
#include <stdint.h>
#include <string>
#include <boost/bimap.hpp>

using namespace std;


struct User
{
    User(const string & first_name, const string & last_name):
    first_name(add(first_name)), last_name(add(last_name)) {}
    const string& get_first_name() const
    {
        return names.left.find(first_name)->second;
    }
    const string& get_last_name() const
    {
        return names.left.find(last_name)->second;
    }
    friend ostream& operator<<(ostream& os, User &obj)
    {
        return os 
        << "first name: " << obj.get_first_name()
        << " last_name: " << obj.get_last_name();
    }

    static void info()
    {
        for (auto entry : names.left)
        {
        cout << "Key: " << entry.first << ", Value: " << entry.second << endl;
        }
    }
protected:
    unsigned int first_name, last_name;
    static boost::bimap<unsigned int, string> names;
    static unsigned int seed;
    static unsigned int add(const string & s);

};

unsigned int User::seed = 42;
boost::bimap<unsigned int, string> User::names{};

unsigned int User::add(const string & s)
{
    auto it = names.right.find(s);
    if(it == names.right.end())
    {
        // add it
        names.insert({++seed, s});
        return seed;
    }
    return it->second; 
}



int main()
{
    User a("alice", "Test");
    User b("bob", "Test2");

    cout << b << endl;

    User::info();
    return 0;
}