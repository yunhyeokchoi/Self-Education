#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
static void GetInput(T* pData, string msg)
{
  cout << msg << endl;
  cin >> *pData;
  if(cin.fail())
  {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max());
    GetInput(pData, msg);
  }

}

/*
  Create three classes Person, Professor and Student.
  The class Person should have data members name and age. 
  The classes Professor and Student should inherit from the class Person.
*/
class Person
{
  public:
    Person(){};
    virtual ~Person(){};
    
    //Mark these virtual functions pure virtual.
    /*There are two types of output depending on the object.*/
    virtual void getdata() = 0;
    virtual void putdata() = 0;
    
    int m_cur_id;
  
  protected:
    string m_name;
    unsigned int m_age; 
};

/*
  The class Professor should have two integer members: publications and cur_id. 
  There will be two member functions: getdata and putdata. 
*/
class Professor : public Person
{
  public:
    Professor(){};
    ~Professor(){};
    /*
      The function getdata should get the input from the user: 
      the name, age and publications of the professor. 
    */
    virtual void getdata()
    {
      GetInput(&m_name, "Enter name. 1 <= length <= 100");
      
      cout << "Enter age. 1 <= age <= 80" << endl;
      cin >> m_age;
      cout << "Enter publications. 1 <= publications <= 1000" << endl;
      cin >> m_publications;
    }
    /*
      The function putdata should print the name, age, publications and the cur_id of the professor.
      If the object is of type Professor, print the space separated name, age, publications and id on a new line.
    */
    virtual void putdata()
    {
      cout << m_name << " " << m_age << " " << m_publications << " " << m_cur_id << endl;
    }
    
  private:
    int m_publications;
};

/*
  The class Student should have two data members: 
  marks, which is an array of size 6 and cur_id. 
  It has two member functions: getdata and putdata. 
  The function getdata should get the input from the user: 
  the name, age, and the marks of the student in 6 subjects. 
  The function putdata should print the name, age, sum of the marks and the cur_id of the student.
*/
class Student : public Person
{
  public:
    Student(){};
    ~Student(){};

    virtual void getdata()
    {
      cout << "Enter name. 1 <= length <= 100" << endl;
      cin >> m_name;
      cout << "Enter age. 1 <= age <= 80" << endl;
      cin >> m_age;
      for(unsigned int i = 0; i < 6; ++i)
      {
        cout << "Enter marks. 0 <= publications <= 100" << endl;
        cin >> m_marks[i];
      }
    }
    /*
      If the object is of the Student class, 
      print the space separated name, age, the sum of the marks in 6 subjects and id on a new line.
    */
    virtual void putdata()
    {
      int markSum = 0;
      for(unsigned int i = 0; i < 6; ++i)
        markSum += m_marks[i];
      
      cout << m_name << " " << m_age << " " << markSum << " " << m_cur_id << endl;
    }
  
  private:
    int m_marks[6];
};

/*
  For each object being created of the Professor or the Student class, 
  sequential id's should be assigned to them starting from 1.
  Solve this problem using virtual functions, constructors and static variables. 
  You can create more data members if you want.
*/
/*
  There are two types of input. 
  If the object being created is of the Professor class, you will have to input the name, age and publications of the professor.
  If the object is of the Student class, you will have to input the name, age and the marks of the student in 6 subjects.
*/
/*
  For each object being created of the Professor or the Student class, 
  sequential id's should be assigned to them starting from 1.
*/
int main(void)
{
  vector<Person*> person;
  
  //Store the number of people to create,
  //and the value itself will be retrieved from the user.
  unsigned int nop = 0;
  cout << "Type in the number of persons to create." << endl;;
  cin >> nop; 
  unsigned int id = 0;
  for(unsigned int i = 0; i < nop; ++i)
  {
    GetInput(&id, "Type in 1 to create a professor, and 2 to create a student.");
    if((id == 1) || 
       (id == 2))
    {
      Person* newOne;
      
      if(id == 1)
        newOne = new Professor();
      else if(id == 2)
        newOne = new Student();
      
      newOne->getdata();
      newOne->m_cur_id = id;
      person.push_back(newOne);
    }
    else
      ++nop;
  }
  
  for(unsigned int i = 0; i < nop; ++i)
  {
    person[i]->putdata();
    delete person[i];
  }
  return 0;
}