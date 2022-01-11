#include "interface.h"
#include <stdexcept>

Hierarchy::Node* Hierarchy::copy(Node* root)
{
	if (root == nullptr)
	{
		return nullptr;
	}

	Node* copyNode = new Node(root->data, root->parent);
	size_t size = root->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		copyNode->children.push_back(copy(root->children[i]));
	}
	return copyNode;
}

void Hierarchy::erase(Node* root)
{
	if (root != nullptr)
	{
		size_t children_size = root->children.size();
		for (size_t i = 0; i < children_size; ++i)
		{
			erase(root->children[i]);
		}
		delete root;
	}
}

const std::vector<Hierarchy::Node*>& Hierarchy::sort(const std::vector<Node*> vector, std::vector<Node*>& newVector) const
{
	newVector = vector;

	size_t size = newVector.size();
	if (size < 2)
	{
		return newVector;
	}

	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (newVector[j]->data.compare(newVector[i]->data) < 0)
			{
				std::swap(newVector[i], newVector[j]);
			}
		}
	}

	return newVector;
}

Hierarchy::Node* Hierarchy::getNode(Node* root, const string& name) const
{
	if (root == nullptr)
	{
		return nullptr;
	}

	if (root->data == name)
	{
		return root;
	}

	size_t size = root->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		Node* current = getNode(root->children[i], name);
		if (current != nullptr)
		{
			return current;
		}
	}
	return nullptr;
}

int Hierarchy::getAllWorkers(Node* root) const
{
	if (root->children.size() == 0)
	{
		return 0;
	}

	size_t size = root->children.size();
	int children = size;
	for (size_t i = 0; i < size; ++i)
	{
		children += getAllWorkers(root->children[i]);
	}
	return children;
}

int Hierarchy::numOverloaded(Node* root, int workers) const
{
	if (root == nullptr || root->children.size() == 0)
	{
		return 0;
	}

	int count = 0;
	if (getAllWorkers(root) > workers)
	{
		++count;
	}

	size_t size = root->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		count += numOverloaded(root->children[i], workers);
	}
	return count;
}

int Hierarchy::longestChain(Node* root) const
{
	if (root == nullptr)
	{
		return 0;
	}

	int depth = 0;
	size_t size = root->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		depth = std::max(depth, longestChain(root->children[i]));
	}
	return depth + 1;
}

bool Hierarchy::insert(Node* node, const string& parent)
{
	Node* boss = getNode(root, parent);
	if (boss != nullptr)
	{
		node->parent = boss->data;
		boss->children.push_back(node);
		++employees;
		return true;
	}
	return false;
}

Hierarchy::Node* Hierarchy::removeWorker(Node* node, const string& name)
{
	size_t size = node->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (node->children[i]->data == name)
		{
			Node* removed = node->children[i];
			node->children.erase(node->children.begin() + i);
			employees -= removed->children.size() + 1;
			return removed;
		}
	}

}

void Hierarchy::load(const string& data)
{
	if (data.size() == 0)
	{
		return;
	}

	string parent, child;
	string no_spaces = data;
	no_spaces.erase(std::remove(no_spaces.begin(), no_spaces.end(), ' '), no_spaces.end());

	size_t save_symbol = 0;
	size_t str_size = no_spaces.size();
	for (size_t i = 0; i <= str_size; ++i)
	{
		if (no_spaces[i] == '-')
		{
			parent.insert(parent.begin(), no_spaces.begin() + save_symbol, no_spaces.begin() + i);
			save_symbol = i + 1;
		}
		else if (no_spaces[i] == '\n' || no_spaces[i] == '\0')
		{
			child.insert(child.begin(), no_spaces.begin() + save_symbol, no_spaces.begin() + i);
			save_symbol = i + 1;

			if (parent.empty() && !child.empty())
			{
				throw std::logic_error("There is no manager with that name!");
			}
			else if (!parent.empty() && !child.empty())
			{
				if (!hire(child, parent))
				{
					throw std::logic_error("There is no manager with that name!");
				}
			}
			parent.clear();
			child.clear();
		}
	}
}

Hierarchy::Node* Hierarchy::join(Hierarchy& newFirm, Node* other, Node* root) const
{
	if (other == nullptr)
	{
		return nullptr;
	}

	if (other->data != "Uspeshnia")
	{
		if (find(other->data))
		{
			Node* node = getNode(newFirm.root, other->data);
			if (node->parent != other->parent)
			{
				int new_firm_level = getLevel(newFirm.root, node->parent);
				int other_firm_level = getLevel(root, other->parent);

				if (new_firm_level > other_firm_level || (new_firm_level == other_firm_level && other->parent.compare(node->parent) < 0))
				{
					newFirm.hire(other->data, other->parent);
				}
			}
		}
		else
		{
			newFirm.insert(new Node(other->data,other->parent), other->parent);
		}
	}

	size_t size = other->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		join(newFirm, other->children[i], root);
	}

	return newFirm.root;
}

int Hierarchy::getLevel(Node* root, const std::string& name, int level) const
{
	if (root == nullptr)
	{
		return 0;
	}

	if (root->data == name)
	{
		return level;
	}

	int down_level = 0;
	size_t size = root->children.size();
	for (size_t i = 0; i < size; ++i)
	{
		down_level = getLevel(root->children[i], name, level + 1);
		if (down_level != 0)
		{
			return down_level;
		}
	}
	return down_level;
}

void Hierarchy::incorporate(Node* node)
{
	size_t size = node->children.size();
	if (node == nullptr || size == 0)
	{
		return;
	}

	for (size_t i = 0; i < size; ++i)
	{
		incorporate(node->children[i]);
	}

	if (size > 1)
	{
		Node* new_boss = getHighestSalaryWorker(node->children);
		for (size_t i = 0; i < size; ++i)
		{
			if (node->children[i]->data != new_boss->data)
			{
				insert(node->children[i], new_boss->data);
				--employees;
				node->children.erase(node->children.begin() + i);
				--size;
				--i;
			}
		}
	}
}

Hierarchy::Node* Hierarchy::getHighestSalaryWorker(const std::vector<Node*> workers) const
{
	Node* highest = workers[0];
	size_t size = workers.size();
	for (size_t i = 1; i < size; ++i)
	{
		if (getSalary(workers[i]->data) > getSalary(highest->data))
		{
			highest = workers[i];
		}
	}
	return highest;
}

bool Hierarchy::modernize(Node* node)
{
	size_t size = node->children.size();
	if (node == nullptr || size == 0)
	{
		return false;
	}

	for (size_t i = 0; i < size; ++i)
	{

		if (modernize(node->children[i]))
		{
			--i;
			--size;
		}
	}

	if (getLevel(root, node->data) % 2 != 0)
	{
		return fire(node->data);
	}
	return false;
}

Hierarchy::Hierarchy(Hierarchy&& r) noexcept
{
	root = nullptr;
	employees = 0;
	firmName.clear();
	std::swap(root, r.root);
	std::swap(employees, r.employees);
	std::swap(firmName, r.firmName);
}

Hierarchy::Hierarchy(const Hierarchy& r)
{
	root = copy(r.root);
	employees = r.employees;
	firmName = r.firmName;
}

Hierarchy::Hierarchy(const string& data)
{
	load(data);
}

Hierarchy::~Hierarchy() noexcept
{
	erase(root);
}

string Hierarchy::print() const
{
	if (root == nullptr)
	{
		return "";
	}

	string string;
	std::queue<Node*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		int queue_size = queue.size();
		while (queue_size > 0)
		{
			Node* front = queue.front();
			queue.pop();

			std::vector<Node*> sorted_vector;
			sort(front->children, sorted_vector);
			size_t size = sorted_vector.size();
			for (size_t i = 0; i < size; ++i)
			{
				string += front->data + "-" + sorted_vector[i]->data + "\n";
				queue.push(sorted_vector[i]);
			}
			--queue_size;
		}
	}
	return string;
}

int Hierarchy::longest_chain() const
{
	return longestChain(root);
}

bool Hierarchy::find(const string& name) const
{
	Node* node = getNode(root, name);
	if (node != nullptr)
	{
		return true;
	}
	return false;
}

int Hierarchy::num_employees() const
{
	return employees;
}

int Hierarchy::num_overloaded(int level) const
{
	return numOverloaded(root, level);
}

string Hierarchy::manager(const string& name) const
{
	Node* node = getNode(root, name);
	if (node != nullptr)
	{
		return node->parent;
	}
	return "";
}

int Hierarchy::num_subordinates(const string& name) const
{
	Node* node = getNode(root, name);
	if (node != nullptr)
	{
		return node->children.size();
	}
	return -1;
}

unsigned long Hierarchy::getSalary(const string& who) const
{
	Node* node = getNode(root, who);
	if (node != nullptr)
	{
		int children = num_subordinates(who);
		return 500 * children + 50 * (abs(getAllWorkers(node) - children));
	}
	return -1;
}

bool Hierarchy::fire(const string& name)
{
	Node* node = getNode(root, manager(name));
	if (node != nullptr)
	{
		Node* removed = removeWorker(node, name);
		size_t size = removed->children.size();
		for (size_t i = 0; i < size; ++i)
		{
			insert(removed->children[i], removed->parent);
		}
		return true;
	}
	return false;
}

bool Hierarchy::hire(const string& name, const string& boss)
{
	if (boss == "Uspeshnia" && employees == 0)
	{
		root = new Node(boss);
		employees = 1;
	}

	if (find(name))
	{
		Node* worker = getNode(root, name);
		if (boss != worker->parent)
		{
			removeWorker(getNode(root, worker->parent), name);
			return insert(worker, boss);
		}
	}
	return insert(new Node(name,boss), boss);
}

void Hierarchy::incorporate()
{
	incorporate(root);
}

void Hierarchy::modernize()
{
	modernize(root);
}

Hierarchy Hierarchy::join(const Hierarchy& right) const
{
	Hierarchy h(this->print());
	h.root = join(h, right.root, right.root);
	return h;
}

void Hierarchy::setName(const string& name)
{
	firmName = name;
}

const string& Hierarchy::getName() const
{
	return firmName;
}

void Hierarchy::setFileName(const string& name)
{
	fileName = name;
}

const string& Hierarchy::getFileName() const
{
	return fileName;
}