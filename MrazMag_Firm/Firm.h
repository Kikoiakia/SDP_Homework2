#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "interface.h"

using std::string;

class Firm {
private:
	std::vector<Hierarchy> firms;
	bool running = true;
	void Help() const;
	void Load(string& object_name, string& file_path);
	void Save(string& object_name);
	void Save(string& object_name, string& file_path);
	void Find(string& object_name, string& employee_name);
	void NumSubordinates(string& object_name, string& employee_name);
	void Manager(string& object_name, string& employee_name);
	void NumEmployees(string& object_name);
	void Overloaded(string& object_name);
	void Join(string& object_name1, string& object_name2, string& object_name_new);
	void Fire(string& object_name, string& employee_name);
	void Hire(string& object_name, string& employee_name, string& employer_name);
	void Salary(string& object_name, string& employee_name);
	void Incorporate(string& object_name);
	void Modernize(string& object_name);
	void ReadInput(const string& command, string& input1, string& input2, string& input3, string& input4) const;
	void Exit();

public:
	void Open();	
};