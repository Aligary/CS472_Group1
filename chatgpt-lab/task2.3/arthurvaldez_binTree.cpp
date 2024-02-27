/****************************
 *    CS 302 Assignment 4   *
 *                          *
 *  Arthur Ethan Valdez III *
 * **************************/

/*
 *         Name: Arthur Ethan Valdez, 2001802124
 *  Description: This program creates a binary tree based on user input, and finds the longest
 *               zigzag path.
 *        Input: The program requires user inputs.
 *       Output: The program is expected the path with the longest zigzag.
 */

#include <vector>
#include <string>
#include <iostream>

struct binTreeNode
{
	std::string location;
	binTreeNode * left;
	binTreeNode * right;
};

class binTree
{	
public:
	binTree();
	~binTree();
	void buildTree(std::vector<std::string>);
	std::vector<std::string> zigzag();
    //binTreeNode * getRoot();
    //void printPreorder( binTreeNode * node);
    
    
private:
	binTreeNode* buildTree(binTreeNode *, std::vector<std::string>, int);
	std::vector<std::string> zigzag(binTreeNode *, bool, std::vector<std::string>);
	void deallocateTree(binTreeNode*);
	binTreeNode* root;
};

binTree::binTree()
{
	root = nullptr;
}

binTree::~binTree(){
    deallocateTree(root);
}

/*
 *  deallocateTree(): Deallocates the binary tree.
 *  parameters: binTreeNode * r - node to be passed in
 *  return value: Void.
 *  Algorithm: Recursively calls itself to delete both sides of the tree until finally
 *             deleting the root node.
 */
void binTree::deallocateTree(binTreeNode * r)
{
	if(r == NULL)
        return;
    
    deallocateTree(r->left);
    deallocateTree(r->right);

    delete r;
}

/*
 *  buildTree(): Constructs the binary tree.
 *  parameters: std::vector<std::string> locations - vector to create the binary tree
 *  return value: Void.
 *  Algorithm: If locations is empty, it returns. Otherwise, calls an overloaded function of
 *             itself.
 */
void binTree::buildTree(std::vector<std::string> locations)
{
	if(locations.size() == 0)
		return;
	root = buildTree(new binTreeNode(), locations, 0);
}

/*
 *  buildTree(): Constructs the binary tree.
 *  parameters: binTreeNode * r - node to be passed in
 *              std::vector<std::string> locations - vector to create the binary tree
 *              int index - the current position in the vector
 *  return value: Returns a binTreeNode.
 *  Algorithm: Returns nullptr and deletes the node if out of bounds or if the string in the vector is equal to "=.
 *             Otherwise, it recursively calls itself and assigns nodes locations based on these algorithms:
 *             index * 2 + 1 and (index + 1) * 2.
 */
binTreeNode* binTree::buildTree(binTreeNode * r, std::vector<std::string> locations, int index)
{
    //Base cases
    if(index < locations.size() && index > -1)
    {
        r->location = locations[index];
        if(r->location == "_")
        {
            delete r;
            return nullptr;
        }
        r->left = buildTree(new binTreeNode(), locations, index * 2 + 1);
        r->right = buildTree(new binTreeNode(), locations, (index + 1) * 2);
    }
    else
    {
        delete r;
        return nullptr;
    }
    return r;
}

/*
 *  zigzag(): Returns the vector with the longest path.
 *  parameters: None.
 *  return value: Returns a string vector.
 *  Algorithm: Calls each side recursively, and compares the two longest paths.
 */
std::vector<std::string> binTree::zigzag()
{
    std::vector<std::string> vector1; 
    std::vector<std::string> leftZag;
    std::vector<std::string> rightZag;

    leftZag = zigzag(root,true,leftZag);
    rightZag = zigzag(root,false,rightZag);

    if(leftZag.size() + rightZag.size() == 0)
        return vector1;
    if(leftZag.size() > rightZag.size())
        return leftZag;
    return rightZag;
}

/*
 *  zigzag(): Returns the vector with the longest path.
 *  parameters: binTreeNode * r - node to be passed in
 *              bool childType - determines which side the node is on
 *              std::vector<std::string> path - the current zigzag path
 *  return value: Returns a string vector.
 *  Algorithm: Calls each side recursively, and compares the two longest paths. If the node is on the left side, it checks the child's right
 *             side and see if it's nullptr. If it's not nullptr, then the current node is added to path and recursively calls itself on both
 *             sides of the child. However, depending on what side, the vector that is passed in is either path or an empty vector. This entire
 *             process happens on the left side as well.
 */
std::vector<std::string> binTree::zigzag(binTreeNode * r, bool childType, std::vector<std::string> path)
{
    std::vector<std::string> vector1;               // empty vector
    std::vector<std::string> leftPath;              // left path
    std::vector<std::string> rightPath;             // right path

    if(r == nullptr)
        return vector1;
    if(childType == true)
    {
        path.push_back(r->location);
        vector1.push_back(r->location);
        leftPath = zigzag(r->left,true,vector1);
        rightPath = zigzag(r->right,false,path);
    }
    else
    {
        path.push_back(r->location);
        vector1.push_back(r->location);
        leftPath = zigzag(r->left,true,path);
        rightPath = zigzag(r->right,false,vector1);
    }
    if(path.size() > rightPath.size() && path.size() > leftPath.size())
        return path;
    if(leftPath.size() > rightPath.size())
        return leftPath;
    return rightPath;
}

/*

binTreeNode * binTree::getRoot()
{
    return root;
}

// Given a binary tree, print its nodes in inorder
void binTree::printPreorder(binTreeNode * node)
{
    if (node == NULL)
        return;
 
    //first print data of node
    std::cout << node->location << " ";
 
    //then recur on left subtree
    printPreorder(node->left);
 
    // now recur on right subtree
    printPreorder(node->right);
}*/


//binTreeNode* binTree::getRoot()
//{
//    return root;
//}