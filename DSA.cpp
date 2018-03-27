#include <iterator>
#include <iostream>

using namespace std;

template <typename Obj>
class SampleList
{
protected:

private:
  struct Node
  {
    Obj data;
    Node *prev;
    Node *next;

    Node(const Obj & d = Obj(), Node *p = NULL, Node *n = NULL)
      : data(d), prev(p), next(n){}
  }
  SimpleList()
  {
    prev = NULL;
    tail = NULL;
  }

public:
  class const_iterator
  {


  }
}
