#include "Firm.h"
#include <iostream>

void Firm::Help() const{
	std::cout << "help												– shows this help text.\n";
	std::cout << "load object_name file_path/file_name				- loads Hierarchy data from file.\n";
	std::cout << "save object_name file_path/file_name				- saves Hierarchy data to file\n";
	std::cout << "find object_name worker_name						- checks if there is a worker in given Hierarchy\n";
	std::cout << "num_subordinate object_name worker_name			- returns the number of subordinates of worker in a Hierarchy\n";
	std::cout << "manager object_name worker_name 					- returns the name of the manager of worker in a Hierarchy\n";
	std::cout << "num_employees object_name							- returns the number of workers in a Hierarchy\n";
	std::cout << "overloaded object_name							- returns the number of managers that have more than 20 subordinates in a Hierarchy\n";
	std::cout << "join object_name1 object_name2 object_name3		- returns the merged firm of object_name1 and object_name2 and loads it to object_name3\n";
	std::cout << "fire object_name worker_name 						- removes worker from a Hierarchy\n";
	std::cout << "hire object_name worker_name manager_name			- add worker as subordinate to manager in a Hierarchy\n";
	std::cout << "salary object_name worker_name 					- returns the salary of worker in firm a Hierarchy\n";
	std::cout << "incorporate object_name							- incorporates a Hierarchy\n";
	std::cout << "modernize object_name								- modernizes a Hierarchy\n";
	std::cout << "exit												- stops the program" << std::endl;
}



void Firm::Load(string& object_name, string& file_path) {
	string data = "", text;	
	
	if (file_path == "") {
		while (std::getline(std::cin, text)) {
			text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
			if (text == "^Z" || text == "^D") break;
			data += text;
			data += '\n';
		}
		if (data.empty()) {
			string message = "Couldn't load " + object_name + ".\n";
			throw message;
		}
	}
	else {
		std::ifstream ReadFile(file_path);
		if(ReadFile.is_open())
			while (std::getline(ReadFile, text)) {
				text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
				data += text;
				data += '\n';
			}
		else {
			string message = "File didn't open!\n";
			throw message;
		}

		ReadFile.close();
	}

	if (data.empty()) {
		string message = "Couldn't load " + object_name + ".\n";
		throw message;
	}

	Hierarchy hierarchy = Hierarchy(data);
	hierarchy.setName(object_name);
	if (!file_path.empty())
		hierarchy.setFileName(file_path);
	firms.push_back(hierarchy);
	std::cout << object_name << " loaded successfully!\n";	
}

void Firm::Save(string& object_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0) {
			found = true;
			std::cout << a.print();
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to save.\n";
		throw message;
	}
}

void Firm::Save(string& object_name, string& file_path) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0) {
			found = true;
			a.setFileName(file_path);
			std::ofstream newFile(file_path);
			newFile << a.print();
			newFile.close();
			std::cout << object_name << " saved.\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to save.\n";
		throw message;
	}
}

void Firm::Find(string& object_name, string& employee_name) {
	bool found = false;
	for (auto a : firms)
		if (a.getName().compare(object_name) == 0) {
			found = true;
			if (a.find(employee_name))
				std::cout << employee_name << " is employed in " << object_name << ".\n";
			else {
				string message = "Couldn't find employee with that name.\n";
				throw message;
			}
			break;
		}
	if (!found) {
		string message = "No such object exists to find employee.\n"; 
		throw message;
	}
	
}

void Firm::NumSubordinates(string& object_name, string& employee_name) {
	bool found = false;
	for (auto a : firms)
		if (a.getName().compare(object_name) == 0) {
			found = true;
			if (a.find(employee_name)) {
				int employees = a.num_subordinates(employee_name);
				if (employees > 0)
					std::cout << employee_name << " has " << employees << " subordinates.\n";
				else
					std::cout << employee_name << " has no subordinates.\n";
			}
			else {
				string message = "Couldn't find employee with that name.\n";
				throw message;
			}
			break;
		}
	if (!found) {
		string message = "No such object exists to find number of subordiantes of an employee.\n";;
		throw message;
	}
}

void Firm::Manager(string& object_name, string& employee_name) {
	bool found = false;
	for (auto a : firms)
		if (a.getName().compare(object_name) == 0) {
			found = true;
			if (a.find(employee_name)) {
				std::cout << "The manager of " << employee_name << " is " << a.manager(employee_name) << ".\n";
			}
			else {
				string message = "There is no " + employee_name + " in " + object_name + ".\n";
				throw message;
			}
			break;
		}
	if (!found) {
		string message = "No such object exists to find employee.\n";
		throw message;
	}

}

void Firm::NumEmployees(string& object_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0) 
		{
			found = true;
			std::cout << "There are " << a.num_employees() << " employees in " << a.getName() << ".\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to get employees.\n";
		throw message;
	}
}

void Firm::Overloaded(string& object_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			int overloaded_workers = a.num_overloaded();
			if (overloaded_workers > 0)
			{
				std::cout << "There are " << overloaded_workers << " in " << object_name << std::endl;
			}
			else
			{
				std::cout << "No overloaded employees in " << object_name << std::endl;
			}
		}
	}
	if (!found) {
		string message = "No such object exists to get overloaded employees.\n";
		throw message;
	}
}

void Firm::Join(string& object_name1, string& object_name2, string& object_name_new) {
	int first = -1, second = -1;
	for (size_t i = 0; i < firms.size(); ++i) {
		if (firms[i].getName().compare(object_name1) == 0)
			first = i;
		if (firms[i].getName().compare(object_name2) == 0)
			second = i;
		if (first > 0 && second > 0)
			break;
	}
	if (first == -1) {
		string message = "First Hierrachy doesn't exists.\n";
		throw message;
	}
	if (second == -1) {
		string message = "Second Hierrachy doesn't exists.\n";
		throw message;
	}

	Hierarchy firm = firms[first].join(firms[second]);
	firm.setName(object_name_new);
	firms.push_back(firm);
	std::cout << object_name_new << " created.\n";
}

void Firm::Fire(string& object_name, string& employee_name) {
	if (employee_name == "Uspeshnia") {
		string message = "You can't fire " + employee_name + ".\n";
		throw message;
	}
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			if (a.fire(employee_name)) {
				std::cout << employee_name << " was fired.\n";
				break;
			}
			std::cout << "There isn't " << employee_name << " in " << object_name << ".\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to fire employees.\n";
		throw message;
	}
}

void Firm::Hire(string& object_name, string& employee_name, string& employer_name) {
	if (employee_name == "Uspeshnia") {
		string message = "You can't hire " + employee_name + ".\n";
		throw message;
	}
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			if (a.hire(employee_name, employer_name)) {
				std::cout << employee_name << " was hired.\n";
				break;
			}
			std::cout << "There isn't a manger " << employer_name << " in " << object_name << ".\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to hire employees.\n";
		throw message;
	}
}

void Firm::Salary(string& object_name, string& employee_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			long salary = a.getSalary(employee_name);
			if(salary == -1)
				std::cout << "There isn't an employee " << employee_name << " in " << object_name << ".\n";
			else
				std::cout << "The salary of " << employee_name << " is " << salary << ".\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to get salary of employees.\n";
		throw message;
	}
}

void Firm::Incorporate(string& object_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			a.incorporate();
			std::cout << object_name << " incorporated.\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to incorporate.\n";
		throw message;
	}
}

void Firm::Modernize(string& object_name) {
	bool found = false;
	for (auto a : firms) {
		if (a.getName().compare(object_name) == 0)
		{
			found = true;
			a.modernize();
			std::cout << object_name << " modernized.\n";
			break;
		}
	}
	if (!found) {
		string message = "No such object exists to modernize.\n";
		throw message;
	}
}

void Firm::Exit() {
	running = false;
}

void Firm::ReadInput(const string& command, string& input1, string& input2, string& input3, string& input4) const {
	size_t save_symbol = 0;
	size_t size = command.size();
	for (size_t i = 0; i <= size; ++i)
	{
		if (command[i] == ' ' && command[i + 1] == ' ')
		{
			continue;
		}
		else if (command[i] == ' ' || command[i] == '\0')
		{
			if (input1.empty())
			{
				input1.insert(input1.begin(), command.begin() + save_symbol, command.begin() + i);
			}
			else if (input2.empty())
			{
				input2.insert(input2.begin(), command.begin() + save_symbol, command.begin() + i);
			}
			else if (input3.empty())
			{
				input3.insert(input3.begin(), command.begin() + save_symbol, command.begin() + i);
			}
			else
			{
				input4.insert(input4.begin(), command.begin() + save_symbol, command.begin() + i);
			}
			save_symbol = i + 1;
		}
	}
}

void Firm::Open() {
	string input1, input2, input3, input4;
	while (running) {
		string command;
		std::cout << "> ";
		std::getline(std::cin, command);
		ReadInput(command, input1, input2, input3, input4);
		if (input1 == "help")
		{
			Help();
		}
		else if (input1 == "load")
		{
			try {
				Load(input2, input3);
			}
			catch (const char* e) {
				std::cout << e;
			}
		}
		else if (input1 == "save")
		{
			try {
				if (input3 == "")
					Save(input2);
				else
					Save(input2, input3);
			}
			catch(const char* e){
				std::cout << e;
			}
		}
		else if (input1 == "find")
		{
			try {
				Find(input2, input3);
			}
			catch (const char* e) {
				std::cout << e;
			}
		}
		else if (input1 == "num_subordinates")
		{
			try {
				NumSubordinates(input2, input3);
			}
			catch (const string e) {
				std::cout << e;
			}
		}
		else if (input1 == "manager")
		{
			try {
				Manager(input2, input3);
			}
			catch (const string e) {
				std::cout << e;
			}
		}
		else if (input1 == "num_employees")
		{
			try {
				NumEmployees(input2);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "overloaded")
		{
			try {
				Overloaded(input2);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "join")
		{
			try {
				Join(input2, input3, input4);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "fire")
		{
			try {
				Fire(input2, input3);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "hire")
		{
			try {
				Hire(input2, input3, input4);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "salary")
		{
			try {
				Salary(input2, input3);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "incorporate")
		{
			try {
				Incorporate(input2);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "modernize")
		{
			try {
				Modernize(input2);
			}
			catch (const string e) {
				std::cout << e;

			}
		}
		else if (input1 == "exit")
		{
			Exit();
		}
		else
		{
			std::cout << "Please enter correct command!" << std::endl;
		}
		std::cout << std::endl;
		input1.clear();
		input2.clear();
		input3.clear();
		input4.clear();
	}
}
