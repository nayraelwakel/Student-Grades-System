#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class student
{
public:
	string name;
	int id=0;
	double grade=0.0;
	void print()
	{
		cout << id << " | " << name << " | " << grade << endl;
	}
};

//bubble sort by grade -> O(n^2)
void sortGrade(student students[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (students[j].grade < students[j + 1].grade)
			{
				swap(students[j], students[j + 1]);
			}
		}
	}
}

//linear search -> O(n)
int linearSearchName(const student students[], int n, const string& targetName, int& cmparisons)
{
	cmparisons = 0;
	for (int i = 0; i < n; i++)
	{
		cmparisons++;
		if (students[i].name == targetName)
		{
			return i;
		}
	}
	return -1;
}

//bubble sort by id -> O(n^2)
void sortId(student students[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (students[j].id < students[j + 1].id)
			{
				swap(students[j], students[j + 1]);
			}
		}
	}
}

//binary search -> O(log n)
int binarySearchId(const student students[], int n, int targetId, int& cmparisons)
{
	cmparisons = 0;
	int s = 0, e = n - 1, m;
	while (s <= e)
	{
		cmparisons++;
		m = (s + e) / 2;
		if (targetId == students[m].id)
		{
			return m;
		}
		else if (targetId > students[m].id)
		{
			s = m + 1;
		}
		else
		{
			e = m - 1;
		}
	}
	return -1;
}

//recursive total -> O(n)
double totalGrades(student g[], int n)
{
	if (n == 0)
	{
		return 0;
	}
	return g[n - 1].grade + totalGrades(g, n - 1);
}

int main()
{
	const int maxStudents = 100;
	student students[maxStudents];
	int studentCount = 0;
	int choice;

	do
	{
		cout << "\t----- Student Grades System -----" << endl;
		cout << "1. Add Student." << endl;
		cout << "2. Display Students." << endl;
		cout << "3. Sort by Grade (Descending) & Show Ranks." << endl;
		cout << "4. Linear Search by Name." << endl;
		cout << "5. Binary Search by ID." << endl;
		cout << "6. Statistics (Highest, Lowest, Average)." << endl;
		cout << "7. Exit." << endl;

		cout << "Enter your Choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			if (studentCount > maxStudents)
			{
				cout << "Database is full!";
			}
			else
			{
				cout << "Enter name: ";
				cin.ignore();
				getline(cin, students[studentCount].name);
				cout << "Enter ID: ";
				cin >> students[studentCount].id;
				cout << "Enter grade: ";
				cin >> students[studentCount].grade;
				studentCount++;
				cout << "Student added successfully!" << endl;
			}
			break;
		}
		case 2:
		{
			if (studentCount == 0)
			{
				cout << "No students found!" << endl;
			}
			else
			{
				cout << "ID | Name | Grade" << endl;
				cout << "------------------" << endl;
				for (int i = 0; i < studentCount; i++)
				{
					students[i].print();
				}
			}
			break;
		}
		case 3:
		{
			if (studentCount == 0)
			{
				cout << "No students to sort!" << endl;
			}
			else
			{
				student tempStudents[maxStudents];
				for (int i = 0; i < studentCount; i++)
				{
					tempStudents[i] = students[i];
				}
				sortGrade(tempStudents, studentCount);
				cout << "Students ranked by grade (Descending):" << endl;
				for (int i = 0; i < studentCount; i++)
				{
					cout << (i + 1) << " Rank: ";
					tempStudents[i].print();
				}
			}
			break;
		}
		case 4:
		{
			if (studentCount == 0)
			{
				cout << "No students to search!" << endl;
			}
			else
			{
				string targetName;
				cout << "Enter name to search: ";
				cin.ignore();
				getline(cin, targetName);
				int comparisons = 0;
				int index = linearSearchName(students, studentCount, targetName, comparisons);
				if (index != -1)
				{
					cout << "Student found at index "<< index << endl;
					students[index].print();
				}
				else
				{
					cout << "Student not found." << endl;
				}
				cout << "Comparisons made: "
					<< comparisons << endl;
			}
			break;
		}
		case 5:
		{
			if (studentCount == 0)
			{
				cout << "No students to search!" << endl;
			}
			else
			{
				student tempStudents[maxStudents];
				for (int i = 0; i < studentCount; i++)
				{
					tempStudents[i] = students[i];
				}
				sortId(tempStudents, studentCount);
				int targetId;
				cout << "Enter ID to search: ";
				cin >> targetId;
				int comparisons = 0;
				int index = binarySearchId(tempStudents, studentCount, targetId, comparisons);
				if (index != -1)
				{
					cout << "Student found!" << endl;
					tempStudents[index].print();
				}
				else
				{
					cout << "Student not found." << endl;
				}
				cout << "Comparisons made: "<< comparisons << endl;
			}
			break;
		}
		case 6:
		{
			if (studentCount == 0)
			{
				cout << "No students available for statistics!" << endl;
			}
			else
			{
				double highest = students[0].grade;
				double lowest = students[0].grade;
				string highestName = students[0].name;
				string lowestName = students[0].name;
				for (int i = 1; i < studentCount; i++)
				{
					if (students[i].grade > highest)
					{
						highest = students[i].grade;
						highestName = students[i].name;
					}

					if (students[i].grade < lowest)
					{
						lowest = students[i].grade;
						lowestName = students[i].name;
					}
				}
				double total = totalGrades(students, studentCount);
				double avg = total / studentCount;
				cout << "Highest Grade: "<< highest<< " (Student: "<< highestName<< ")" << endl;
				cout << "Lowest Grade: "<< lowest<< " (Student: "<< lowestName<< ")" << endl;
				cout << "Class Average: "<< avg << endl;
			}
			break;
		}
		case 7:
		{
			cout << "Thank you." << endl;
			break;
		}

		default:
		{
			cout << "Invalid choice! Please try again." << endl;
		}
		}

	} while(choice != 7);
	return 0;
}

