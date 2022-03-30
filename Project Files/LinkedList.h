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
        
        //while loop that walks through our list and deletes each node
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

        //default action that sets the new node as the head and tail if the list is empty
        if (head == 0)
        {
            head = nTemp;
            tail = nTemp;
            count++;
        }

        //else statement that adds the node to the beginning of the list, if it is not empty
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
        //if statement that returns nothing if the list is empty
        if (head == 0)
        {
            return;
        }

        //else statement that handles the removal of the head of our list, if it has one that is not null
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

        //default action that sets the new node as the head and tail if the list is empty
        if (head == 0)
        {
            head = nTemp;
            tail = nTemp;
            count++;
        }

        //else statment that will add a node to the end of our non-empty list
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
        //if statement that returns nothing if the list is empty
        if (head == 0)
        {
            return;
        }

        //else statement that removes the tail of our list
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
        //statement that simply inserts the node as the head of our list, if it is empty
        if (head == 0)
        {
            head = new node<T>();
            head->setData(data);
            count++;
        }

        //else statement that handles each specific node insertion scenario
        else
        {
            //statement that will call the addFront function if the index is zero
            if (index < 1)
            {
                addFront(data);
            }

            //statement that adds the node to the end of the list if the index is beyond or equal to the current size of the list
            else if (index >= count)
            {
                addRear(data);
            }

            //else statement that handles the insertion of the node when it is between two other nodes
            else
            {
                //creating our temp and new node node objects
                node<T>* temp = head;
                node<T>* nNode = new node<T>();
                nNode->setData(data);

                //loop that uses our temp node to walk through the list to the desired location
                for (int i = 0; i < index - 1; i++)
                {
                    temp = temp->getNext();
                }

                //properly inserting the new node into the list 
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
        //statement that does nothing if the list is empty
        if (head == 0)
        {
            return;
        }

        //else block that handles the removal of the node at the specified index 
        else
        {
            //if the index is zero, this statement removes the head node
            if (index < 1)
            {
                removeFront();
            }

            //statement that removes the tail node if the index is equal or greater than the list size
            else if ((index+1) >= count)
            {
                removeRear();
            }

            //else statement that handles the deletion of a node that is within the list
            else
            {
                //creating our temporary node pointer
                node<T>* temp = head;

                //for loop that allows to walk to the specified index in the list
                for (int i = 0; i < index; i++)
                {
                    temp = temp->getNext();
                }

                //removing the node and repairing the links in the list
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
        //returning a default form of the object if the list is empty
        if (head == 0)
        {
            return T();
        }

        //creating our temporary node
        node<T>* temp = head;

        //traversing through the list
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }

        //returning the desired element
        return temp->getData();
    }

    //function that will return a reference of the node from our list
    T& getRefAt(int index)
    {
        //returning a default form of the object if the list is empty
        if (head == 0)
        {
            return T();
        }
        
        //creating the temporary node
        node<T>* temp = head;

        //traversing through our linked list
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }

        //returning the data of the node
        return temp->getData();
    }

    //additional function we put into our transaction list library for our own priority queue
    void setDataAt(int index, T val)
    {
        //returning nothing if the list is empty
        if (head == 0)
        {
            return;
        }

        //creating the temporary node
        node<T>* temp = head;

        //traversing to the location marked by the index passed to the function
        for (int i = 0; i < index; i++)
        {
            temp = temp->getNext();
        }
        
        //setting the node's data
        temp->setData(val);
    }

    //function that prints the data found in each node of our list
    void print()
    {
        //creating our temporary node
        node<T>* temp = head;

        //while loop that allows us to traverse through the list and print each node's data
        while (temp != 0)
        {
            temp->getData().print();
            temp = temp->getNext();
        }
    }
};
