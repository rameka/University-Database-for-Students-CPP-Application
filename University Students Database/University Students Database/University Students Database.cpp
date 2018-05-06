/*	University Students Database.cpp : This file consists of the entire program for the student database, which was designed 
*									   using Standard Template Library 
*	Author: Ramakrishna Sayee Meka, Syracuse University
*	Date: 24th March, 2018
*/


#include "stdafx.h"


#include <iostream>
#include <list>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	bool operator<(const course &c) { return (name < c.name); } //Required for sorting the courses using STL sort()
	bool operator==(const course &c) { return (name == c.name); } //Required of using the finding the courses using STL find()
};
// There are no memory leaks in any of the functionalities implemented
void add_student(map<int, map<int, list<course *> * > *> &DB, int id); //Registering a student to a database and creating a DB if it doesnt exist
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id); //Removing the student and his courses from the database
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); // Droping a course if of the student specified if exists
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);// Printing the courses based on semester
void print_student_all_courses(map<int, map<int, list<course *> * >  *> &DB, int id); //Printing the entire student courses
void print_DB(map<int, map<int, list<course *> * >  *> &DB); //Printing the Database

int main() {
	// The main function simulates the database, creation all its functionalites and deletion.
	map<int, map<int, list<course  *> *>   *> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id) {

	if (DB.size() == 0) {
		DB[id] = new map<int, list<course *> * >; return;
	}

	auto it1 = DB.find(id);//note the find syntax; different from find for list and vector
	if (it1 == DB.end()) {
		DB[id] = new map<int, list<course *> * >; return;
	}
}


void remove_student(map<int, map<int, list<course *> * > *> &DB, int id) {
	if (DB.find(id) == DB.end()) {
		return;
	}
	auto it1 = DB.find(id);
	map<int, list<course *> * > *student = it1->second;

	for (auto it = (*student).begin(); it != (*student).end(); it++)
	{
		list<course *> *courses = it->second;

		for (auto& cptr : *courses) {
			delete cptr;
		}
		(*courses).clear();
		delete it->second;
	}
	
	// Finally remove the element from DB
	DB.erase(id);
}


void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {

	if (DB.find(id) == DB.end()) return;

	if (DB[id]->size() == 0 || DB[id]->find(semester) == DB[id]->end()) {
		(*DB[id])[semester] = new list<course *>;

		(*DB[id])[semester]->push_back(new course(c));
		return;
	}

	else {
		int found = 0;
		list<course *>::iterator it1 = (*DB[id])[semester]->begin();
		while (it1 != (*DB[id])[semester]->end()) {
			if (**it1 == c) found = 1;
			it1++;
		}
		if (found == 1) return;
		(*DB[id])[semester]->push_front(new course(c));
		//DB[id][semester]->sort(); //If needed
	}

}

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;
	if (DB[id]->size() == 0) return;
	if (DB[id]->find(semester) == DB[id]->end()) return;
	auto it1 = DB.find(id);
	map<int, list<course *> * > *student = it1->second;

	auto it2 = (*student).find(semester);
	list<course *> *courses = it2->second;

	/*auto it = find((*courses).begin(), (*courses).end(), c);
	if (it != (*courses).end()) {
	(*courses).erase(it);
	}*/

	auto it = (*courses).begin();
	for (; it != (*courses).end(); it++) {
		if ((*it)->name == c.name) {
			//match found, delete the memory
			break;
		}
	}
	(*courses).erase(it);


}

void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id) {

	auto it1 = DB.find(id);
	map<int, list<course *> * > *student = it1->second;
	cout << "Student: " << id << "\nSemester: " << semester << endl;
	for (auto it = (*student)[semester]->begin(); it != (*student)[semester]->end(); it++)
	{
		course *c = *it;
		string name = c->name;
		int section = c->section;
		int credits = c->credits;

		cout << name << "\t" << section << "   " << credits << "\t";
	}
	cout << endl << endl;
	// Second Method

	/*auto it2 = (*student).find(semester);
	list<course *> *courses = it2->second;
	for (auto it = (*courses).begin(); it != (*courses).end(); it++) {
	std::cout << "\t" << (*it)->name << std::endl;
	}*/


}
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id) {
	auto it1 = DB.find(id);
	map<int, list<course *> * > *student = it1->second;
	cout << "Student Id: " << id << endl;
	for (auto topItr = (*student).begin(); topItr != (*student).end(); topItr++) {
		cout << "Semester: " << topItr->first << endl;
		for (auto it = (*student)[topItr->first]->begin(); it != (*student)[topItr->first]->end(); it++)
		{
			course *c = *it;
			string name = c->name;
			int section = c->section;
			int credits = c->credits;

			cout << name << "\t" << section << "   " << credits << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void print_DB(map<int, map<int, list<course *> * >  *> &DB) {
	for (auto dbPtr = DB.begin(); dbPtr != DB.end(); dbPtr++) {
		auto it1 = DB.find(dbPtr->first);
		map<int, list<course *> * > *student = it1->second;
		cout << "Student Id: " << dbPtr->first << endl;
		for (auto topItr = (*student).begin(); topItr != (*student).end(); topItr++) {
			cout << "Semester: " << topItr->first << endl;
			for (auto it = (*student)[topItr->first]->begin(); it != (*student)[topItr->first]->end(); it++)
			{
				course *c = *it;
				string name = c->name;
				int section = c->section;
				int credits = c->credits;

				cout << name << "\t" << section << "   " << credits << "\t";
			}
			cout << endl;
		}
	}
	cout << endl;
}
