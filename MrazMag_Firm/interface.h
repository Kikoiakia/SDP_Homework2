#pragma once
#include <string>
#include <vector>
#include <queue>

using std::string;

class Hierarchy
{
private:
    /// <summary>
    /// Node structure
    /// </summary>
    struct Node {
        /// <summary>
        /// The name of the employee
        /// </summary>
        string data = "";
        /// <summary>
        /// Subordinates of the employee
        /// </summary>
        std::vector<Node*> children{};
        /// <summary>
        /// Name of his manager
        /// </summary>
        string parent = "";

        /// <summary>
        /// Constructor for a node 
        /// </summary>
        /// <param name="_data">The name of the employee</param>
        /// <param name="_parent">The name of the parent</param>
        Node(const string& _data, const string& _parent = "") {
            data = _data;
            parent = _parent;
        }
    };
    /// <summary>
    /// Root of the Tree Hierarchy
    /// </summary>
    Node* root;

    /// <summary>
    /// How many employees are currently working
    /// </summary>
    size_t employees;

    /// <summary>
    /// The name of the Hierarchy
    /// </summary>
    string firmName;

    /// <summary>
    /// Name of the file assossiated with the Hierarchy
    /// </summary>
    string fileName;

    /// <summary>
    /// Erases a node
    /// </summary>
    /// <param name="node"></param>
    void erase(Node* node);

    /// <summary>
    /// Copies a Node
    /// </summary>
    /// <param name="node"></param>
    /// <returns>Node pointer</returns>
    Node* copy(Node* node);

    /// <summary>
    /// Sorts a vector by employee name
    /// </summary>
    /// <param name="vector"> - Initial vector to sort</param>
    /// <param name="newVector"> - Vector which will keep the sorted vector</param>
    /// <returns>A new sorted vector</returns>
    const std::vector<Node*>& sort(const std::vector<Node*> vector, std::vector<Node*>& newVector) const;
 
    /// <summary>
    /// Finds and returns a node from a tree with given name
    /// </summary>
    /// <param name="root"></param>
    /// <param name="name"></param>
    /// <returns></returns>
    Node* getNode(Node* root, const string& name) const;

    /// <summary>
    /// Returns all workers in a tree
    /// </summary>
    /// <param name="root"></param>
    /// <returns></returns>
    int getAllWorkers(Node* root) const;

    /// <summary>
    /// Returns the number of overloaded workers
    /// </summary>
    /// <param name="root"></param>
    /// <param name="workers"></param>
    /// <returns></returns>
    int numOverloaded(Node* root, int workers) const;

    /// <summary>
    /// Returns the longest chain in a tree
    /// </summary>
    /// <param name="root"></param>
    /// <returns></returns>
    int longestChain(Node* root) const;

    /// <summary>
    /// Inserts a node in the tree with given parent
    /// </summary>
    /// <param name="node"></param>
    /// <param name="parent"></param>
    /// <returns>True if the insertion is successful otherwise False</returns>
    bool insert(Node* node, const string& parent);

    /// <summary>
    /// Removes the worker and his employees with a given name
    /// </summary>
    /// <param name="node"></param>
    /// <param name="name"></param>
    /// <returns>The removed node</returns>
    Node* removeWorker(Node* node, const string& name);

    /// <summary>
    /// Loads data from a given string
    /// </summary>
    /// <param name="data"></param>
    void load(const string& data);

    /// <summary>
    /// Joins 2 Hierarchies into one
    /// </summary>
    /// <param name="newFirm"></param>
    /// <param name="root1"></param>
    /// <param name="root2"></param>
    /// <returns>Returns the new Hierarchy</returns>
    Node* join(Hierarchy& newFirm, Node* root1, Node* root2) const;

    /// <summary>
    /// Gets the current level/depth of the tree for a node with given name
    /// </summary>
    /// <param name="root"></param>
    /// <param name="name"></param>
    /// <param name="level"></param>
    /// <returns></returns>
    int getLevel(Node* root, const std::string& name, int level = 0) const;

    /// <summary>
    /// Incorporates the Hierarchy
    /// </summary>
    /// <param name="root"></param>
    void incorporate(Node* root);

    /// <summary>
    /// Gets the highest salary worker
    /// </summary>
    /// <param name="workers"></param>
    /// <returns></returns>
    Node* getHighestSalaryWorker(const std::vector<Node*> workers) const;

    /// <summary>
    /// Modernizes the Hierarchy
    /// </summary>
    /// <param name="root"></param>
    /// <returns></returns>
    bool modernize(Node* root);

public:
    Hierarchy(Hierarchy&& r) noexcept;
    Hierarchy(const Hierarchy& r);
    Hierarchy(const string& data);
    ~Hierarchy() noexcept;
    void operator=(const Hierarchy&) = delete;

    /// <summary>
    /// Returns a string representing the Hierarchy
    /// </summary>
    /// <returns></returns>
    string print()const;

    /// <summary>
    /// Returns the number of nodes in the longest chain
    /// </summary>
    /// <returns></returns>
    int longest_chain() const;

    /// <summary>
    /// Checks if a employee with given name is in the Hierarchy
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool find(const string& name) const;

    /// <summary>
    /// Returns the number of employees in the Hierrachy
    /// </summary>
    /// <returns></returns>
    int num_employees() const;

    /// <summary>
    /// Returns the number of overloaded employees
    /// </summary>
    /// <param name="level"></param>
    /// <returns></returns>
    int num_overloaded(int level = 20) const;

    /// <summary>
    /// Returns the name of the manager of an employee with a given name
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    string manager(const string& name) const;

    /// <summary>
    /// Returns the number of subordinates of an employee with a given name
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    int num_subordinates(const string& name) const;

    /// <summary>
    /// Gets the salary of an employee with a given name
    /// </summary>
    /// <param name="who"></param>
    /// <returns></returns>
    unsigned long getSalary(const string& who) const;

    /// <summary>
    /// Removes an employee with a given name
    /// </summary>
    /// <param name="who"></param>
    /// <returns></returns>
    bool fire(const string& name);

    /// <summary>
    /// Adds an employee with a given name and manager
    /// </summary>
    /// <param name="name"></param>
    /// <param name="boss"></param>
    /// <returns></returns>
    bool hire(const string& name, const string& boss);

    /// <summary>
    /// Incorporates the Hierarachy
    /// </summary>
    void incorporate();

    /// <summary>
    /// Modernizes the Hierarachy
    /// </summary>
    void modernize();

    /// <summary>
    /// Returns a new Hierarchy which is a combination of current and given
    /// </summary>
    /// <param name="right"></param>
    /// <returns></returns>
    Hierarchy join(const Hierarchy& right) const;

    /// <summary>
    /// Sets the name of the Hierarchy
    /// </summary>
    /// <param name="name"></param>
    void setName(const string& name);

    /// <summary>
    /// Gets the name of the Hierarchy
    /// </summary>
    /// <returns></returns>
    const string& getName() const;

    /// <summary>
    /// Sets the name of the file corresponded with the Hierarchy
    /// </summary>
    /// <param name="name"></param>
    void setFileName(const string& name);

    /// <summary>
    /// Gets the name of the file corresponded with the Hierarchy
    /// </summary>
    /// <returns></returns>
    const string& getFileName() const;
}; 


