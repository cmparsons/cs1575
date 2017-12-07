#include <iostream>
#include <string>
#include "mystringmap.h"
using namespace std;

// --------------------------------------------------------------
void test0()
{
  MyStringMap<char> grades;

  cout << endl;
  cout << "--- Test 0 ----" << endl;
  cout << "Is Empty? " << boolalpha << grades.isEmpty() << endl;
  cout << "Size = " << grades.size() << "  Max = " << grades.max() << endl;


  grades.insert("Nate",'A');
  grades.insert("George",'C');
  grades.insert("Karl",'F');
  grades.insert("John",'B');
  grades.insert("Will",'B');

  cout << endl;
  cout << "Is Empty? " << boolalpha << grades.isEmpty() << endl;
  cout << "Size = " << grades.size() << "  Max = " << grades.max() << endl;

  grades.print();


  return;
}

// --------------------------------------------------------------
void test1()
{
  MyStringMap<string> thelist;

  cout << endl;
  cout << "--- Test 1 ----" << endl;
  cout << "Is Empty? " << boolalpha << thelist.isEmpty() << endl;
  cout << "Size = " << thelist.size() << "  Max = " << thelist.max() << endl;


  thelist.insert("Fry","Human");
  thelist.insert("Leela","Cyclops");
  thelist.insert("Hermes","Human");
  thelist.insert("Qubert","Clone");
  thelist.insert("Nibbler","Dog");
  thelist.insert("Bender","Robot");
  thelist.insert("Leela","Mutant");
  thelist.insert("Amy","Human");
  thelist.insert("Nibbler","Dog");
  thelist.insert("Kiff","Amphibiosan");
  thelist.insert("Nibbler","Nibblonian");

  cout << endl;
  cout << "Is Empty? " << boolalpha << thelist.isEmpty() << endl;
  cout << "Size = " << thelist.size() << "  Max = " << thelist.max() << endl;

  thelist.print();

  cout << endl;
  cout << "Testing remove" << endl;
  cout << "Removing Humans" << endl;

  thelist.remove("Fry");
  thelist.remove("Hermes");
  thelist.remove("Amy");

  thelist.remove("Nixon");

  thelist.print();


  cout << endl;
  cout << "Testing Lookup" << endl;

  try
  {
    cout << "Leela? " << thelist.valueOf("Leela") << endl;
    cout << "Bender? " << thelist.valueOf("Bender") << endl;
    cout << "Qubert? " << thelist.valueOf("Qubert") << endl;

    cout << "Nixon? ";
    cout << thelist.valueOf("Nixon") << endl;
  }
  catch (Oops e)
  {
    cout << "ERROR : " << e.getMsg() << endl;
  }

  cout << endl;
  //cout << "End of test #1" << endl;
  return;
}

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
int main ()
{
  cout << "MAP TESTER!!" << endl;

  test0();
  test1();

  return 0;
}
