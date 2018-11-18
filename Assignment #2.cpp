// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " "
	   << (*ipD)->val2 << " "
	   << (*ipD)->val3 << " "
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }

  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

unsigned int getMax(vector<Data *> &v, int field)
{
  unsigned int currentMax;
  if (field == 2)
    currentMax = v[0]->val2;
  else if (field == 3)
    currentMax = v[0]->val3;
  for (int i = 0; i < v.size(); i++)
  {
    if (v[i]->val2 > currentMax && field == 2)
      currentMax = v[i]->val2;
    else if (v[i]->val3 > currentMax && field == 3)
      currentMax = v[i]->val3;
  }
  return currentMax;
}

string getMaxStr(vector<Data *> &v)
{
  string currentMax = v[0]->val4;
  for (int q = 1; q < v.size() ; q++)
  {
    if (v[q]->val4 > currentMax)
      currentMax = v[q]->val4;
  }
  return currentMax;
}

list<Data *>::iterator i, notsorted, prevsort;
void insertionSort(list<Data *> &l)
{
  i = l.begin();
  for (i++; i != l.end(); i++)
  {
    notsorted = i;
    prevsort = i; prevsort--;
    while ((*notsorted)->val1 < (*prevsort) ->val1  && notsorted != l.begin())
      iter_swap(notsorted--, prevsort--);
  }
}

void insertionSortStr(vector<Data *> &vec)
{
  Data* temp;
  for (int i = 1; i < vec.size(); i++)
  {
    int j = i;
    temp = vec[i];
    while (j > 0 && temp->val4 < vec[j-1]->val4)
    {
      vec[j] = vec[j-1];
      j--;
    }
    vec[j] = temp;
  }
}

void countSort(vector<Data *> &vec, unsigned long deg, int b, int field)
{
  vector<Data *> tempVec(vec.size());
  int count[b] = {0};
  for (int i = 0; i < vec.size(); i++)
  {
    if (field == 2)
      count[ (vec[i]->val2 / deg) % b ]++;
    else if (field == 3)
      count[ (vec[i]->val3 / deg) % b ]++;
    else if (field == 4)
    {
      int strNum = vec[i]->val4[0]*1000000 + vec[i]->val4[1]*1000 + vec[i]->val4[2]*1;
      count[(strNum / deg) % b]++;
    }
  }
  for (int i = 1; i < b; i++)
    count[i] += count[i - 1];
  int i = vec.size();
  while (true)
  {
    i--;
    if (field == 2)
    {
      tempVec[count[(vec[i]->val2 / deg) % b] - 1] = vec[i];
      count[ (vec[i]->val2 / deg ) % b ]--;
    }
    else if (field == 3)
    {
      tempVec[count[(vec[i]->val3 / deg) % b] - 1] = vec[i];
      count[ (vec[i]->val3 / deg) % b ]--;
    }
    else if (field == 4)
    {
      int strNum = vec[i]->val4[0]*1000000 + vec[i]->val4[1]*1000 + vec[i]->val4[2]*1;
      tempVec[count[(strNum / deg) % b] - 1] = vec[i];
      count[ (strNum / deg) % b ]--;
    }
    if(i == 0)
      break;
  }
  vec.swap(tempVec);
}

void radixSort(list<Data *> &l, int field)
{
  int base = 10;
  unsigned int max = 0;
  vector<Data *> v{ make_move_iterator(begin(l)),
                      make_move_iterator(end(l)) };
  string maxString = getMaxStr(v);
  if (field == 2)
    base = 500000;
  else if (field == 3)
    base = 92;
  else if (field == 4)
    base = 1000;
  else {}
  if (field == 2 || field == 3)
    max  = getMax(v, field);
  else if (field == 4)
    max = maxString[0]*1000000 + maxString[1]*1000 + maxString[2]*1;
  for (unsigned long deg = 1; max / deg > 0; deg *= base)
    countSort(v, deg, base, field);
  if (field == 4)
    insertionSortStr(v);
  list<Data *> newList(v.begin(), v.end());
  l.swap(newList);
}

void sortDataList(list<Data *> &l, int field) {
  if(field == 1)
    insertionSort(l);
  else
    radixSort(l, field);
}
