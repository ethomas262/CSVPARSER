#ifndef BINARYTREE_CPP
#define BINARYTREE_CPP


#include <iostream>
#include <time.h>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//course struct used for encapsulating course data
struct Course {   
    string courseID;
    string courseName;
    vector<string> preReqs;
};

//Node structure for organizing binary Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course input_course) :
        Node() {
        course = input_course;
    }
};
//Binary Tree for organizing course data
class BinarySearchTree {

    private:
        Node* root;

        void addNode(Node* node, Course input_course);
        void inOrder(Node* node);
        void postOrder(Node* node);
        void preOrder(Node* node);
        Node* removeNode(Node* node, string input_courseID);

    public:
        BinarySearchTree();
        virtual ~BinarySearchTree();
        void InOrder();
        void PostOrder();
        void PreOrder();
        void Insert(string id, string name, vector<string> preReqs);
        void Remove(string courseId);
        Course* Search(string courseId);

};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}


BinarySearchTree::~BinarySearchTree() {
    delete root;
}




void BinarySearchTree::InOrder() {
    inOrder(root);
}


void BinarySearchTree::PostOrder() {
    postOrder(root);
}


void BinarySearchTree::PreOrder() {
    preOrder(root);
}



void BinarySearchTree::Insert(string id, string name, vector<string> preReqs) {
    // if root equarl to null ptr
    if (root == nullptr) {
        root = new Node( Course{id, name, preReqs});
        root->left = nullptr;
        root->right = nullptr;
    }
    // root is equal to new node bid
  // else
    else {
        Node* curr = root;
        while (curr != nullptr && curr->course.courseID != id) {
            if (id < curr->course.courseID) {  //if bid < curr bid find nullptr in left place
                if (curr->left == nullptr) {
                    curr->left = new Node(Course{ id, name, preReqs });
                    curr = curr->left;
                }
                else {
                    curr = curr->left;
                }

            }
            else {
                if (curr->right == nullptr) {     	//if bid > than curr bid find nullptr in right place
                    curr->right = new Node(Course{ id, name, preReqs });
                    curr = curr->right;
                }
                else {
                    curr = curr->right;
                }

            }
            
        }
        curr->left = nullptr;
        curr->right = nullptr;


    }
    // add Node root and bid
}



void BinarySearchTree::Remove(string courseId_input) {
    
    // remove node root bidID
    Node* curr = root;
    Node* par = nullptr;
    while (curr != nullptr) { // while curr is a valid pointer
        if (curr->course.courseID == courseId_input) {                                // if we find correct bid

            if (curr->left == nullptr && curr->right == nullptr) {                    //case one:  remove leaf node
                if (par == nullptr) { root = nullptr; }
                else if (par->left == curr) { par->left = nullptr; }
                else { par->right = nullptr; }
            }
            else if (curr->right == nullptr) {                                        //case two: remove node with only left child
                if (par == nullptr) { root = curr->left; }
                else if (par->left == curr) { par->left = curr->right; }
                else { par->right = curr->right; }

            }
            else if (curr->left == nullptr) {                                         //case three: remove node with only right child
                if (par == nullptr) { root = curr->right; }
                else if (par->left == curr) { par->left = curr->right; }
                else { par->right = curr->right; }
            }
            else {                                                                   //case four: Remove node with both children
                Node* suc = curr->right;
                while (suc->left != nullptr) {
                    suc = suc->left;
                }
                Course sucData = suc->course;
                Remove(suc->course.courseID);  		//find successor node replace node to delete
                curr->course = sucData;
                cout << "Node found and removed" << endl;
            }
        }
        else if (curr->course.courseID < courseId_input) {
            par = curr;
            curr = curr->right;
        }
        else {
            par = curr;
            curr = curr->left;
        }



    }
}



Course* BinarySearchTree::Search(string courseId_input) {
    Node* curr = root;

    // keep looping downwards until bottom reached or matching bidId found
    while (curr != nullptr) {
        // if match found, return current bid
        if (curr->course.courseID == courseId_input) {
            return &curr->course;
        }
        // if bid is smaller than current node then traverse left
        else if (courseId_input < curr->course.courseID) {
            curr = curr->left;
        }
        // else larger so traverse right
        else { curr = curr->right; }
    }
    Course* course = nullptr;
    return course;
}

void BinarySearchTree::addNode(Node* node, Course course_input) {
    // if node is larger then add to left
    if (course_input.courseID < node->course.courseID) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course_input);
            node = node->left;
            node->left = nullptr;
            node->right = nullptr;

        }
        else {
            //else recurse down left node
            addNode(node->left, course_input);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course_input);
            node = node->right;
            node->left = nullptr;
            node->right = nullptr;

        }
        //else
        else {
            //recurse down right node
            addNode(node->right, course_input);

        }
    }
}


void BinarySearchTree::inOrder(Node* node) {
    

    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder left
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->course.courseID << " " << node->course.courseName <<  endl;
        //InOder right
        inOrder(node->right);
    }
    
}
void BinarySearchTree::postOrder(Node* node) {
    
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->course.courseID << " " << node->course.courseName << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {

    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout <<"     "<< node->course.courseID << " " << node->course.courseName << endl;
        //postOrder left
        postOrder(node->left);
        //postOrder right
        postOrder(node->right);
    }
}

#endif #endif /*!BINARY_TREE_CPP*/