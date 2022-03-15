#pragma once
#include <iostream>
using namespace std;

//templated node class 
template <class T>
class node
{
private:
    T data;
    node* next;
    node* prev;

public:
    //default constructor for our node
    node()
    {
        data = T();
        next = nullptr;
        prev = nullptr;
    }

    //getter and setter functions for the data in each node
    void setData(T data)
    {
        this->data = data;
    }
    T getData()
    {
        return data;
    }

    //getter and setter functions for the next node pointer
    void setNext(node* next)
    {
        this->next = next;
    }
    node* getNext()
    {
        return this->next;
    }

    //getter and setter functions for the previous node pointer
    void setPrev(node* prev)
    {
        this->prev = prev;
    }
    node* getPrev()
    {
        return this->prev;
    }
};

//templated linked list class
template <class T>
class LinkedList
{
protected:
    node<T>* head;
    node<T>* tail;
    int count;

public:
    //default constructor for the linked list
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    //destructor that deletes our entire linked list
    ~LinkedList()
    {
        node<T>* temp = head;
        
        while (temp != 0)
        {
            node<T>* nextTemp = temp->getNext();
            delete temp;
            temp = nextTemp;
        }
        head = 0;
    }

    //function to return the count of our list
    int getCount()
    {
        return count;
    }

    //function that allows us to add nodes to the front of our linked list
    void addFront(T data)
    {
        node<T>* nTemp = new node<T>();
        nTemp->setData(data);

        if (head == 0)
        {

            head = nTemp;
            tail = nTemp;
            count++;
        }

        else
        {
            nTemp->setNext(head);
            head->setPrev(nTemp);
            head = nTemp;
            count++;
        }
    }

    //function that allows us to remove nodes from the front of our linked list
    void removeFront()
    {
        if (head == 0)
        {
            return;
        }

        else
        {    
            node<T>* nTemp = head;
            head = head->getNext();

            if (head != 0)
            {
                head->setPrev(0);
            }
            
            delete nTemp;
            count--;
           
        }
    }

    //function that adds nodes to the back of our list
    void addRear(T data)
    {
        node<T>* nTemp = new node<T>();
        nTemp->setData(data);

        if (head == 0)
        {
            head = nTemp;
            tail = nTemp;
            count++;
        }

        else
        {
            nTemp->setPrev(tail);
            tail->setNext(nTemp);
            tail = tail->getNext();
            count++;
        }
    }

    //function that removes a node from the end of our list
    void removeRear()
    {
        if (head == 0)
        {
            return;
        }

        else
        {
            node<T>* temp = tail;
            tail = tail->getPrev();

            if (head != 0)
            {
                tail->setNext(0);
            }
           
            delete temp;
            count--;
        }
    }

    //function that allows us to insert a node a specific location within our linked list
    void insertAt(T data, int index)
    {
        if (head == 0)
        {
            head = new node<T>();
            head->setData(data);
            count++;
        }

        else
        {
            if (index < 1)
            {
                addFront(data);
            }

            else if (index >= count)
            {
                addRear(data);
            }

            else
            {
                node<T>* temp = head;
                node<T>* nNode = new node<T>();
                nNode->setData(data);

                for (int i = 0; i < index - 1; i++)
                {
                    temp = temp->getNext();
                }

                nNode->setNext(temp->getNext());
                nNode->setPrev(temp);
                temp->setNext(nNode);
                nNode->getNext()->setPrev(nNode);
                count++;
            }
        }
    }

    //function that removes a node from a user defined location in the list
    void removeAt(int index)
    {
        //this subtracts one from the user input in order to change the user input into the correct spot in the list
        //;index--;

        if (head == 0)
        {
            return;
        }

        else
        {
            if (index < 1)
            {
                removeFront();
            }

            else if ((index+1) >= count)
            {
                removeRear();
            }

            else
            {
                node<T>* temp = head;

                for (int i = 0; i < index; i++)
                {
                    temp = temp->getNext();
                }

                node<T>* nTemp = temp->getNext();
                nTemp->setPrev(temp->getPrev());
                temp->getPrev()->setNext(nTemp);
                delete temp;
                count--;
            }
        }
    }

    //function that returns the data from a specific location in our list
    T getAt(int index)
    {
        if (head == 0)
        {
            //we solved this issue by just returnin itself
            return T();
        }
        node<T>* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }

        return temp->getData();
    }

    //operator overload, not needed
    T& getRefAt(int index)
    {
        if (head == 0)
        {
            return T();
        }
        node<T>* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }
        return temp->getData();
    }

    //additional function we put in to our transaction list library for our own pritoty queue
    void setDataAt(int index, T val)
    {
        if (head == 0)
        {
           // return T();
            return;
        }
        node<T>* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }
        temp->setData(val);
    }

    //function that prints the data found in each node of our list
    void print()
    {
        node<T>* temp = head;

        while (temp != 0)
        {
            temp->getData().print();
            temp = temp->getNext();
        }
    }
};
