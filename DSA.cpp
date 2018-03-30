#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
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
    virtual T pop() = 0;
    virtual void push(T newValue) = 0;
    string getName(){
      return name;}
    void setName(string newName){
        name = newName;}
    void setNull();
};
template<typename T>
void SimpleList<T>::setNull()
{
  head = NULL;
  tail = NULL;
}
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
    //delete temp;
  }
template <typename T>
class Stack : public SimpleList<T>
{
  public:
    Stack(string s)
    {
      this->setName(s);
      this->setNull();
    }
    T pop(){
      this->removeFromStart();}
    void push(T newValue){
      this->insertAtStart(newValue);}
};
template <typename T>
class Queue : public SimpleList<T>
{
  public:
    Queue(string s)
    {
      this->setName(s);
      this->setNull();
    }
    T pop(){
      this->removeFromStart();}
    void push(T newValue) {
      this->insertAtStart(newValue);
      cout<<"works";
    }
};

int main() {
  list<SimpleList<int> *> listSLi;
  list<SimpleList<double> *> listSLd;
  list<SimpleList<string> *> listSLs;

  Queue<int> test("blank");
  test.push(15);
  cout<<test.pop()<<endl;
  cout<<"Hello programming!\n";
  ofstream tester;
  tester.open("ex.txt");
  tester << "Hello programming!\n";
  string line;
  ifstream myfile ("example.txt");
  while ( myfile.good() )
  {
    //cout << "step" << endl;
    getline (myfile,line);
    string command = line.substr(0,line.find(' '));
    string type = line.substr(line.find(' ')+1,1);
    string listName = line.substr(line.find(' ')+1,line.find(' ',line.find(' '))-line.find(' ')+2);
    string valuePush = line.substr(line.find(' ',line.find(' ')+1)+1,line.find("\n")-line.find(' ',line.find(' ')));
    string listType = line.substr(line.find(' ',line.find(' ')+1)+1,5);
    tester << command << "\n";
    cout << type << endl;
    tester << listType<< "\n";
    if(command == "create")
    {
      //cout << "created"<<endl;
      if (listType == "queue")
      {
        cout << "created i" <<endl;
        if (type == "i")
        {
          SimpleList<int> *pSLi;
          pSLi = new Queue<int>(listName);
          listSLi.push_front(pSLi);

        }
        else if (type == "s")
        {
          SimpleList<string> *pSLs;
          pSLs = new Queue<string>(listName);
          listSLs.push_front(pSLs);
        }
        else if (type == "d")
        {
          SimpleList<double> *pSLd;
          pSLd = new Queue<double>(listName);
          listSLd.push_front(pSLd);
        }
      }
      else if (listType == "stack")
      {
        if (type == "i")
        {
          SimpleList<int> *pSLi;
          pSLi = new Stack<int>(listName);
          listSLi.push_front(pSLi);
        }
        else if (type == "s")
        {
          SimpleList<string> *pSLs;
          pSLs = new Stack<string>(listName);
          listSLs.push_front(pSLs);
        }
        else if (type == "d")
        {
          SimpleList<double> *pSLd;
          pSLd = new Stack<double>(listName);
          listSLd.push_front(pSLd);
        }
      }
      else
        cout<<"shit"<<endl;
    }
    else if (command == "push")
    {
      //cout << valuePush << endl;
      //cout << "pushed"<<endl;
      if (type == "i")
      {
        stringstream si(valuePush);
        int intPush;
        si >> intPush;
        for(list<SimpleList<int> *>::iterator it = listSLi.begin(); it != listSLi.end(); ++it)
        {
          if ((*it)->getName() == listName)
            (*it)->push(intPush);
            else {}
        }
      }
      else if (type == "s")
      {
        for(list<SimpleList<string> *>::iterator st = listSLs.begin(); st != listSLs.end(); ++st)
        {
          if ((*st)->getName() == listName)
            (*st)->push(valuePush);
            else {}
        }
      }
      else if (type == "d")
      {
        stringstream sd(valuePush);
        double dPush;
        sd >> dPush;
        for(list<SimpleList<double> *>::iterator dt = listSLd.begin(); dt != listSLd.end(); ++dt)
        {
          if ((*dt)->getName() == listName)
            (*dt)->push(dPush);
          else {}
        }
      }
    }
    else if (command == "pop")
    {
      //cout << "popped"<<endl;
      if (type == "i")
      {
        for(list<SimpleList<int> *>::iterator it = listSLi.begin(); it != listSLi.end(); ++it)
        {
          if ((*it)->getName() == listName)
            cout<<"Pop:"<<(*it)->pop()<<endl;
          else {}
        }
      }
      else if (type == "s")
      {
        for(list<SimpleList<string> *>::iterator st = listSLs.begin(); st != listSLs.end(); ++st)
        {
          if ((*st)->getName() == listName)
            cout<<"Pop:"<<(*st)->pop()<<endl;
          else {}
        }
      }
      else if (type == "d")
      {
        for(list<SimpleList<double> *>::iterator dt = listSLd.begin(); dt != listSLd.end(); ++dt)
        {
          if ((*dt)->getName() == listName)
            cout<<"Pop:"<<(*dt)->pop()<<endl;
          else {}
        }
      }
    }
  }
  myfile.close();
  tester.close();
  return 0;
}
