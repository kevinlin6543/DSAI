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
    // Node creation for each member of the SimpleList
    class Node {
    public:
      Node* next;
      T data;
    };
    // Node pointers to the node before and after
    Node* head;
    Node* tail;
    string name;
    int numOfNodes = 0;
  public:
    virtual T pop() = 0;
    virtual void push(T newValue) = 0;
    string getName(){
      return name;}
    void setName(string newName){
        name = newName;}
    void setNull();
    bool getNumOfNodes(){
      return numOfNodes;}
};
//Used to set the initial Node in a SimpleList to point to NULL in front and behind
template<typename T>
void SimpleList<T>::setNull()
{
  head = NULL;
  tail = NULL;
}
template <typename T>
void SimpleList<T>::insertAtStart(T newValue)
  {
    numOfNodes++;
    Node *temp = new Node;
    temp->data = newValue;
    temp->next = head;
    head = temp;;
  }
template <typename T>
void SimpleList<T>::insertAtEnd(T newValue)
{
  numOfNodes++;
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
    numOfNodes--;
    Node* temp = new Node;
    temp = head;
    head = head->next;
    T waluigi = temp->data;
    delete temp;
    return waluigi;
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
      return (this->removeFromStart());}
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
      return (this->removeFromStart());}
    void push(T newValue) {
      this->insertAtEnd(newValue);
    }
};
template <typename T>
void pushF(string lName, T pushValue, ofstream *o, list<SimpleList<T> *> *cList)
{
  SimpleList<T> *tempList = findList(lName, cList);
  if (tempList == NULL)
    (*o) << "ERROR: This name does not exist!\n";
  else
    tempList->push(pushValue);
}
template <typename T>
void popF(string lName, ofstream *o, list<SimpleList<T> *> *cList)
{
  SimpleList<T> *tempList = findList(lName, cList);
  if (tempList == NULL)
    (*o) << "ERROR: This name does not exist!\n";
  else
  {
    if(tempList->getNumOfNodes() == 0)
      (*o) << "ERROR: This list is empty!\n";
    else
      (*o) << "Value popped: " << tempList->pop() << "\n";
  }
}
template <typename T>
SimpleList<T>* findList(string lName, list<SimpleList<T> *> *cList)
{
  for (typename list<SimpleList<T> *>::iterator t = cList->begin(); t != cList->end(); t++)
  {
    if((*t)->getName() == lName)
      return *t;
  }
    return NULL;
}
template <typename T>
void create(string lName, string lType, ofstream *o, list<SimpleList<T> *> *cList)
{
  if(findList(lName, cList) != NULL)
    (*o) << "ERROR: This name already exists!\n";
  else
  {
    if (lType == "queue")
    {
      SimpleList<T> *pSL = new Queue<T>(lName);
      cList->push_back(pSL);
    }
    else if (lType == "stack")
    {
      SimpleList<T> *pSL = new Stack<T>(lName);
      cList->push_back(pSL);
    }
  }
}

int main() {
  // Creation of Lists to store the SimpleList objects
  list<SimpleList<int> *> listSLi;
  list<SimpleList<double> *> listSLd;
  list<SimpleList<string> *> listSLs;
  // The strings to hold input and output file names
  string o;
  string i;
  // Prompts Users for the input and output file name
  cout << "Enter name of input file: ";
  getline(cin,i);
  cout << "Enter name of output file: ";
  getline(cin,o);
  // Using ofstream and ifstream to read and write to files
  ofstream output;
  output.open(o.c_str());
  ifstream input(i.c_str());
  string line;
  // Loop used to go through every line of input and handles the corresponding
  // command.
  while (input.good())
  {
    getline(input,line);
    if (line.empty())
      break;
    // Seperates each part of the line into strings to hold command, type, listName,
    // list type and the value to be pushed
    string command = line.substr(0,line.find(' '));
    string type = line.substr(line.find(' ')+1,1);
    string listName = line.substr(line.find(' ')+1,  line.find(' ',line.find(' ')+1)-line.find(' ')-1);
    string valuePush = line.substr(line.find(' ',line.find(' ')+1)+1,line.find("\n")-line.find(' ',line.find(' ')));
    string listType = line.substr(line.find(' ',line.find(' ')+1)+1,5);
    output << "PROCESSING COMMAND: " << line << "\n";
    // The
    if(command == "create")
    {
      if (type == "i")
        create(listName, listType, &output, &listSLi);
      else if (type == "s")
        create(listName, listType, &output, &listSLs);
      else if (type == "d")
        create(listName, listType, &output, &listSLd);
    }
    else if (command == "push")
    {
      if (type == "i")
      {
        stringstream si(valuePush);
        int intPush;
        si >> intPush;
        pushF(listName, intPush, &output, &listSLi);
      }
      else if (type == "s")
      {
        string stringPush = valuePush.c_str();
        pushF(listName, stringPush , &output, &listSLs);
      }
      else if (type == "d")
      {
        stringstream si(valuePush);
        double dPush;
        si >> dPush;
        pushF(listName, dPush, &output, &listSLd);
      }
    }
    else if (command == "pop" )
    {
      string listName = line.substr(line.find(' ')+1,  line.length()-2-line.find(' '));
      if (type == "i")
        popF(listName, &output, &listSLi);
      else if (type == "s")
        popF(listName, &output, &listSLs);
      else if (type == "d")
        popF(listName, &output, &listSLd);
    }
  }
  input.close();
  output.close();
  return 0;
}
