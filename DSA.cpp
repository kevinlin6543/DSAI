#include <iterator>
#include <iostream>

using namespace std;

template <typename T>
class SampleList
{
  protected:
    void insertAtEnd(T newValue);
    void insertAtStart(T newValue);
    T removeFromStart();
  private:
    class node
    {
      T data;
      node *prev;
      node *next;
    }
    node *head, *tail;
    String name;
  public:
  SimpleList()
  {
    prev = NULL;
    tail = NULL;
  }
  virtual T pop() = 0;
  virtual void push(T newValue) = 0;
  String getName()
    return name};
};

template <typename T>
  void insertAtStart(T newValue)
  {
    node *temp = new node;
    temp->data = newValue;
    temp->next = head;
    head = temp;
  }
  void insertAtEnd(T newValue)
  {
    node *temp = new node;
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
    node *temp = new node;
    temp = head;
    head = head->next;
    return temp->data
    delete temp;
  }
