#include<iostream>
#include<sstream>
#include<vector>
#include<fstream>
using namespace std;

#pragma region tekrar
//read in
//write out
//void main() {
//	stringstream ss;
//	ss << "Mahmud 45 Leyla 41";
//	string name1,name2;
//	int age1,age2;
//
//	ss >> name1;
//	ss >> age1;
//
//	ss >> name2;
//	ss >> age2;
//	cout << "Name: " << name1 << endl;
//	cout << "age: " << age1 << endl;
//	cout << "Name: " << name2 << endl;
//	cout << "age: " << age2 << endl;
//}
#pragma endregion

#pragma region File with object
class Person {
public:
	string name;
	int age;
	Person() = default;
	Person(string name,int age) {
		this->name = name;
		this->age = age;
	}
	void Show() const {
		cout << "name: " << this->name << endl;
		cout << "age: " << this->age << endl;
	}
};

class Database {
public:
	vector<Person> people;
	void AddPerson(Person p) {
		people.push_back(p);	}

	void ShowPeople() {
		for (Person p:people)
		{
			cout << "--------------------------" << endl;
			p.Show();
		}
	}

	void DeleteLastPerson() {
		people.pop_back();
	}
};

void WriteToFile(const vector<Person>people, string path = "people.txt") {
	ofstream fs(path, ios::out);
	if (fs.is_open()) {
		for (Person p:people)
		{
			fs << p.name << "#" << p.age << "\n";
		}
	}
	else {
		throw string("File couldn't open...");
	}
	fs.close();
}

void ReadFromFile(vector<Person>&people, string path = "people.txt") {
	ifstream fs(path);
	if (fs.is_open()) {
		while(!fs.eof()) {
			string row;
			getline(fs, row);
			int counter = 0;
			Person p;
			string str_age;
			for (char character : row) {
				if (character != '#' && counter == 0) {
					p.name += character;
				}
				else if (character != '#' && counter == 1) {
					str_age += character;
				}
				else {
					counter++;
				}
			}
			if (str_age.size() != 0) {
				p.age = stoi(str_age); // string to int
				people.push_back(p);
			}
		}
	}
	else {
		throw string("File not found...");
	}
}

void main() {
	Database db;
	try
	{
		ReadFromFile(db.people);
	}
	catch (string ex)
	{
		cout << ex;
		WriteToFile(db.people);
	}

	int choice;
	do
	{
		cout << "1. ShowPeople\n2. AddPerson\n3. DeleteLastPerson\n0. Exit\nChoice: ";
		cin >> choice;
		system("cls");
		if (choice == 1) {
			db.ShowPeople();
		}
		else if (choice == 2) {
			Person newPerson;
			cin.ignore();
			cout << "Name: ";
			getline(cin, newPerson.name);
			cout << "Age: ";
			cin >> newPerson.age;
			db.AddPerson(newPerson);
			WriteToFile(db.people);
		}
		else if (choice == 3) {
			db.DeleteLastPerson();
			WriteToFile(db.people);
		}
		else if (choice != 0) {
			cout << "Invalid choice!" << endl;
		}
	} while (choice!=0);
}
#pragma endregion
