#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <cstring>

using namespace std;

/* Task structure , which consist name , description , category , status(done) and date
 * Date input format must be year-mm-dd hh-mm. Saving in system in yearmmddhhmm format for comparing with other date
 */
// Script author: Hovhannes Muradyan
// Phone number/Whats up/Viber: +374-43-10-60-82
struct task {
  string name;
  string description ;
  string category;
  int done;
  unsigned long long data;
  // Function for sorting this struct in list (set)
  bool operator < (const task &other) const
  {
    return name < other.name;
  }
};
// Making list , where can add and erase our tasks. Set's erase is O(log n) , it's the best solution for deleting/updating tasks.
set <task> tasks;
// Task example for looping
task myproduct;

// Function for adding new task in list. Usage format: add name description category date
void add(string name, string description, string category, string InputedData, string InputedTime , string DataTime)
{
  myproduct.name = name;
  myproduct.description = description;
  myproduct.category = category;
  myproduct.done = 0;
  // year-mm-dd hh-mm format converting to yearmmddhhmm
  for(int i = 0; i < InputedData.size(); i++){
    if(InputedData[i] != '-')
      DataTime+=InputedData[i];
  }
  for(int i = 0; i < InputedTime.size(); i++) {
    if(InputedTime[i] != ':')
      DataTime+=InputedTime[i];
  }
  myproduct.data = stoll(DataTime);
  DataTime = "";
  // Inserting task in set
  tasks.insert(myproduct);
}

// Function for changing task status in list via name. Usage format: done name
void done(string name)
{
  auto it = tasks.find({name});
  task newProduct = *it;
  tasks.erase(it);
  newProduct.done = 1;
  tasks.insert(newProduct);
}

// Function for updating exsisting task via name. Usage format: update name newdescription newcategory newdata
void update(string name, string description, string category, string InputedData, string InputedTime , string DataTime)
{
  auto it = tasks.find({name});
  task newProduct = *it;
  newProduct.description = description;
  newProduct.category = category;
  for(int i = 0; i < InputedData.size(); i++) {
    if(InputedData[i] != '-')
      DataTime+=InputedData[i];
  }
  for(int i = 0; i < InputedTime.size(); i++) {
    if(InputedTime[i] != ':')
      DataTime+=InputedTime[i];
  }
  newProduct.data = stoll(DataTime);
  tasks.erase(it);
  tasks.insert(newProduct);
}

// Function for deleting task via name. Usage format: delete name
void deleteTask(string name)
{
  auto it = tasks.find({name});
  tasks.erase(it);
}

// Function for showing all tasks in list
void select()
{
  for(auto  i:tasks) {
    cout << "Task name: " << i.name << endl;
    cout << "Task description: " << i.description << endl;
    cout << "Task category: " << i.category << endl;
    if(i.done == 1)
      cout << "Status: done"<<endl;
    else
      cout << "Status: in process"<<endl;
    cout << "Data: " << i.data << endl;
    cout << endl << endl;
  }
}

// Function for filtring and showing elements via users request
/*
 * Algorithm works with finding needed words and creating expected variables.
 * Date symbol is saving in char for saving memory , for <= and >= symbols is write special algorithm.
 */
void SelectSearch(string select1)
{
  string ExpectedCategory = "", ExpectedDescription="", foundeddata;
  int ExpectedStatus=-1;
  unsigned long long ExpectedDate;
  char DateSymbol = ' ';
  size_t fdescription = select1.find("description like");
  if(fdescription != string::npos) {
    for(int i = fdescription + 18; i < select1.size(); i++) {
      if(select1[i] == '"')
        break;
      ExpectedDescription += select1[i];
    }
  }
  size_t fdata = select1.find("date");
  if(fdata != string::npos) {
    DateSymbol = select1[fdata+5];
    for(int i = fdata + 8; i < select1.size(); i++) {
      if(select1[i] == '"' && i > fdata+10)
        break;
      if(select1[i] != '-' && select1[i] != ':' && select1[i] != ' ' && select1[i] != '"') {
        foundeddata += select1[i];
      }
    }
    ExpectedDate = stoll(foundeddata);
    if(DateSymbol == '<' && select1[fdata+6] == '=')
      ExpectedDate++;
    else if(DateSymbol == '>' && select1[fdata+6] == '=')
      ExpectedDate--;
  }
  size_t fcategory = select1.find("category=");
  if (fcategory != string::npos) {
    for(int i = fcategory + 10; i < select1.size(); i++) {
      if(select1[i] == '"')
        break;
      ExpectedCategory+=select1[i];
    }
  }
  size_t fstatus = select1.find("status=");
  if (fstatus != string::npos) {
    if(select1[fstatus+9] == 'n')
      ExpectedStatus = 1;
    else if(select1[fstatus+9] == 'f')
      ExpectedStatus = 0;
  }
  for(auto i:tasks){
    if(DateSymbol == ' '){
      size_t describator = i.description.find(ExpectedDescription);
      if((i.category == ExpectedCategory || ExpectedCategory == "") && describator != string::npos && (i.done == ExpectedStatus || ExpectedStatus == -1)) {
        cout << "Name: " << i.name << endl;
        cout << "Description: " << i.description << endl;
        cout << "Category: " << i.category << endl;
        cout << "Data: " << i.data  << endl;
      }
    }
    else if(DateSymbol == '<'){
      size_t describator = i.description.find(ExpectedDescription);
      if(i.data < ExpectedDate && (i.category == ExpectedCategory || ExpectedCategory == "") && describator != string::npos && (i.done == ExpectedStatus || ExpectedStatus == -1)) {
        cout << "Name: " << i.name << endl;
        cout << "Description: " << i.description << endl;
        cout << "Category: " << i.category << endl;
        cout << "Data: " << i.data  << endl;
      }
    }
    else if(DateSymbol == '>'){
      size_t describator = i.description.find(ExpectedDescription);
      if(i.data > ExpectedDate && (i.category == ExpectedCategory || ExpectedCategory == "") && describator != string::npos && (i.done == ExpectedStatus || ExpectedStatus == -1)) {
        cout << "Name: " << i.name << endl;
        cout << "Description: " << i.description << endl;
        cout << "Category: " << i.category << endl;
        cout << "Data: " << i.data  << endl;
      }
    }
  }
}


// Main function for getting request line and concentrating all functions.
int main() {
  string getedline;
  string name,  description,  category, InputedData,  InputedTime, DataTime ;
  string select1;
  while(true) {
    cout << "Input your correct command please. (-help for more information)" << endl;
    cin >> getedline;
    if(getedline == "add") {
      cin >> name >> description >> category >>  InputedData >> InputedTime;
      add(name, description, category, InputedData, InputedTime, "");
      cout << name << " successfully added!" << endl;
    }
    else if(getedline == "done") {
      cin >> name;
      done(name);
      cout << name << " is done! " << endl;
    }
    else if(getedline == "update") {
      cin >> name >> description >> category >>  InputedData >> InputedTime;
      update(name, description, category, InputedData, InputedTime, "");
      cout << name << " was successfully updated!" << endl;
    }
    else if(getedline == "delete") {
      cin >> name;
      deleteTask(name);
      cout << name << " deleted!";
    }
    else if(getedline == "select") {
      getline(cin, select1);
      if(select1.size() == 2)
        select();
      else if(select1.size() > 2)
        SelectSearch(select1);
    }
    else if(getedline == "-help") {
      cout << "Use add for adding new task" << endl << "Example: add hometask english lessons 2020-12-31 00:00" << endl;
      cout << "Use done for changing task status" << endl << "Example: done hometask" << endl;
      cout << "Use update for updating task information" << endl << "Example: update hometask armenian lessons 2020-12-31 00:15" << endl;
      cout << "Use delete for deleting task in list" << endl << "Example: delete hometask" << endl;
      cout << "Use select * where {predicate}" << endl << "Example: select * where category=\"lessons\"" << endl;
      cout << "Use select * to show all tasks" << endl << "Example: select *" << endl;
      cout << "Use stop to exit program" << endl;
      cout << endl;
    }
    else if(getedline == "stop") {
      cout << "Program is stopped successfully.";
      break;
    }
  }
}// SCRIPT BY HOVHANNES MURADYAN +37443106082
