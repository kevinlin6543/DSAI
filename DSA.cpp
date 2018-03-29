#include <iterator>
#include <iostream>
#include <string>

using namespace std;


template <typename T>
class SampleList
{
  class Node {
  public:
    Node(Node* next = NULL, T data = T{});
  private:
    Node* next;
    int data;
  };
  protected:
    void insertAtEnd(T newValue);
    void insertAtStart(T newValue);
    T removeFromStart();
    Node *head;
    Node *tail;
  private:
    string name;
  public:
    SimpleList()
    {
      prev = NULL;
      tail = NULL;
    }
    virtual T pop() = 0;
    virtual void push(T newValue) = 0;
    string getName(){
      return name;}
};

template <typename T>
  void insertAtStart(T newValue)
  {
    Node *temp = new Node;
    temp->data = newValue;
    temp->next = head;
    head = temp;
  }
template <typename T>
  void insertAtEnd(T newValue)
  {
    Node *temp = new Node;
    temp->data = newValue;
    temp->next = NULL;
    if(head == NULL)
    {
      head = temp;
      tail = temp;
      temp = NULL;
    }
    else
    {
      tail->next = temp;
      tail = temp;
    }
  }
  T removeFromStart()
  {
    Node *temp = new Node;
    temp = head;
    head = head->next;
    return temp->data
    delete temp;
  }

template <typename T>
class Stack : public SimpleList
{
  public:
    T Stack::pop(){
      this->};
    void push(T newValue);
}

template <typename T>
class Queue : public SimpleList
{
  public:
    T Queue::pop(){
      this->insertAtEnd()};
    void Queue::push(T newValue){
      this->removeFromStart()};
}
