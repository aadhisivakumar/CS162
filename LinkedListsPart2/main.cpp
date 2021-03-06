/*
Name: Aadhi Sivakumar
Date: 1/30/22
Description: //Second part of Linked Lists, using code for node.h and node.o from Nihal Parthasarathy
*/

#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"
using namespace std;

//Function Prototypes
void addStudent(Node* head, Student* newStudent);
void printStudents(Node* next);
void deleteStudent(Node* head, int studID);
void average(Node* next, int count, float sum);
void displayMenu();

int main() 
{
  cout << "Welcome to my linked list" << endl;
  //user input for option
  char option[10];
  //declaring first head as NULL
  Node* head = NULL;
  
  do
	{
    //display menu
    displayMenu();

    //geting user input
    cin.getline(option, 10);
    
    // convert the input to upper case	
		for (int i=0; i < strlen(option); i++)
		{		
   			option[i] = toupper(option[i]);
		}	

		// options based on users input for option

    //gets data and add directly if there is an empty list, otherwise calls function add.
		if (strcmp(option, "ADD") == 0)
		{
      char firstName[20];
      char lastName[20];
      int studID;
      float studGPA;
      cout << "First Name: ";
      cin >> firstName;
      cout << "Last Name: ";
      cin >> lastName;
      cout << "ID: ";
      cin >> studID;
      cout << "GPA: ";
      cin >> studGPA;
      Student* newStudent = new Student(firstName, lastName, studID, studGPA);
      //checks if head is null 
      if (head == NULL) 
      {
	      head = new Node(newStudent);
      }
      //places it where the ID is greater than studID
      else if (head->getStudent()->getStudID() > studID) 
      {
	      Node* temp = head;
	      head = new Node(newStudent);
      	head->setNext(temp);
      }
      else 
      {
	      addStudent(head, newStudent);
      }
    }

    //print
		else if (strcmp(option, "PRINT") == 0)
		{
			printStudents(head);
		}

    //delete
		else if (strcmp(option, "DELETE") == 0)
		{
      if (head == NULL) 
      {
	      cout << "There are no students to delete" << endl;
      } 
      else 
      {
	      int studID;
      	cout << "ID: ";
	      cin >> studID;
	      if (head->getStudent()->getStudID() == studID) 
        {
	        Node* temp = head;
	        head = head->getNext();
	        delete(temp);
	      } 
        else 
        {
	        deleteStudent(head, studID);
		    }
      }
    }

    //average
		else if (strcmp(option, "AVERAGE") == 0) 
    {
      int averageCount = 0;
      int sum = 0;
      average(head, averageCount, sum);
		}
    cin.ignore();
	}		 
  while(strcmp(option, "QUIT") != 0);

  
  cout << "You have exited the program. Goodbye." <<endl;
  
  return 0;		
}

// displays options user can do
void displayMenu()
{
	cout << endl << "Select an option:" << endl << endl; 
	cout << "ADD--->Type 'ADD' to add a new student record: " << endl;
  cout << "PRINT--->Type 'PRINT' to print out all the students currently stored: " << endl;
	cout << "DELETE--->Type 'DELETE' to delete a student ID number from the record: " << endl;
	cout << "QUIT--->Type 'QUIT' to exit the program: " << endl;
  cout << "AVERAGE--->Type 'AVERAGE' to print the GPA average of all students:" << endl << endl;
  cout << "Press enter after the average, print, and quit function executes to see the display menu again" << endl;
}

//add a new node (holding a new student) to the linked list
void addStudent(Node* head, Student* newStudent) 
{
  Node* curr = head;
  //placinf node where it belongs
  if (curr->getNext() == NULL || curr->getNext()->getStudent()->getStudID() > newStudent->getStudID())
  {
    Node* newNode = new Node(newStudent);
    newNode->setNext(curr->getNext());
    curr->setNext(newNode);
  } 
  else 
  { 
    addStudent(head->getNext(), newStudent);
  }
}

//print out the student data of every node in the linked list
void printStudents(Node* next) 
{
//if it isnt at the last, print these
  if (next != NULL) 
  { 
    cout << next->getStudent()->getFirstName();
    cout << " " << next->getStudent()->getLastName();
    cout << ", ID: " << next->getStudent()->getStudID();
    cout << ", GPA: " << fixed << setprecision(2) << next->getStudent()->getGPA() << endl;
    printStudents(next->getNext());
  }
}

//delete the node of the student with the given id
void deleteStudent(Node* current, int studID) 
{
  //searches the next node's data if it isn't NULL
  if (current->getNext() != NULL) 
  { 
    if (current->getNext()->getStudent()->getStudID() == studID) 
    {
      Node* temp = current->getNext();
      current->setNext(temp->getNext());
      delete(temp);
    } 
    else 
    { 
      deleteStudent(current->getNext(), studID);
    }
  } 
  //code that executes if no match is found
  else 
  { 
    cout << "There is no student with that ID" << endl;
  }
}

//averages
void average(Node* next, int count, float sum) 
{
  if (next != NULL) 
  {
    count++;
    //adds student's GPA's
    sum += next->getStudent()->studGPA;
    //recalls functions
    average(next->getNext(), count, sum);
  }
  else 
  {
//divides aum by ct
    sum = sum/count;
    //prints the average and setts precision to 2 decimals
    cout << "Average of the GPA's is: " << fixed << showpoint << setprecision(2) << sum << endl;
  }
}
