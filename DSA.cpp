#include <iterator>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class SimpleList
{
  protected:
    void insertAtEnd(T newValue);
    void insertAtStart(T newValue);
    T removeFromStart();
  private:
    class Node {
    public:
      Node* next;
      T data;
    };
    Node* head;
    Node* tail;
    string name;
  public:
    SimpleList();
    virtual T pop() = 0;
    virtual void push(T newValue) = 0;
    string getName(){
      return name;}
};

template <typename T>
void SimpleList<T>::insertAtStart(T newValue)
  {
    Node *temp = new Node;
    temp->data = newValue;
    temp->next = head;
    head = temp;
  }
template <typename T>
void SimpleList<T>::insertAtEnd(T newValue)
  {
    Node* temp = new Node();
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
template <typename T>
T SimpleList<T>::removeFromStart()
  {
    Node* temp = new Node;
    temp = head;
    head = head->next;
    return temp->data;
    delete temp;
  }

template <typename T>
class Stack : public SimpleList<T>
{
  public:
    Stack()
    {
      SimpleList<T>();
    }
    T pop(){
      this->removeFromStart();}
    void push(T newValue);
};

template <typename T>
class Queue : public SimpleList<T>
{
  public:
    Queue() {
      head = NULL;
      tail = NULL;
    }
    T pop(){
      this->removeFromStart();}
    void push(T newValue) {
      this->insertAtEnd(newValue);
    }
};



int main() {
  Queue<int> test;
  test.push(15);
  //test.push(1);
  //cout<<test.pop();
  cout<<"Hello programming!\n";
  //ofstream tester;
  //tester.open("ex.txt");
  //tester <<test.pop();
  //tester << "Hello programming!\n";
  //tester.close();

  //char *token = std::strtok(input, "\n");
   //while (token != NULL) {
     //char *command =
  return 0;
}
