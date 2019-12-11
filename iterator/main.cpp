#include <iostream>
#include <string>
#include "Node.h"
#include "BinaryTree.h"

using namespace std;


int main()
{

    //         me
    //        /  \
    //   mother   father
    //      / \
    //   m'm   m'f
    BinaryTree<string> family{
        new Node<string>{"me", 
        new Node<string>{"mother",
            new Node<string>{"mother's mother"},
            new Node<string>{"mother's father"}
        },
        new Node<string>{"father"}
        }
    };
    //int count = 0;
    //traverse in-order
    for(auto it = family.begin(); it != family.end(); ++it)
    {
        cout << (*it).value << endl;
        //count++;
    }
    //cout << count << endl;
    return 0;
}