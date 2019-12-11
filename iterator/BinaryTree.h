#pragma once


template <typename T> struct Node;

template <typename T> struct BinaryTree
{
    Node<T> * root = nullptr;

    explicit BinaryTree(Node<T> * const root)
    : root{root}
    {
        root->set_tree(this);
    }

    

    template <typename U>
    struct InOrderIterator
    {
        Node<U> * current;

        explicit InOrderIterator(Node<U> * current)
        :current(current)
        {

        }
        // equal
        bool operator!= (const InOrderIterator & other)
        {
            return current != other.current;
        }

        // dereferencing
        Node<U> & operator*() {return *current;}

        //yield next
        InOrderIterator<U> & operator++()
        {
            if(current->right)
            {
                current = current->right;
                while(current->left)
                    current = current->left;
            }
            else
            {
                Node<T> * p = current->parent;
                while (p && current == p->right)
                {
                    current = p;
                    p = p->parent;
                }
                current = p;
            }
            return *this;
        }
    };

    typedef InOrderIterator<T> iterator;

    iterator begin()
    {
        Node<T> * n = root;
        if(n)
            while(n->left)
                n = n->left;
        return iterator{n};
    }

    iterator end()
    {
        return iterator{nullptr};
    }
};

