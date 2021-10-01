#include <bits/stdc++.h>
using namespace std;

class B_Node
{
    public:

        int data;
        int count;  // repeatition of value, duplicate values
        B_Node* left_child;
        B_Node* right_child;
        B_Node* parent;
        B_Node()
        {
            data = - 99999;    // considering as empty or default value
            count = 0;
            left_child = nullptr;
            right_child = nullptr;
            parent = nullptr;
        }

        B_Node(int data)
        {
            this->data = data;
            count = 1;
            left_child = nullptr;
            right_child = nullptr;
            parent = nullptr;
        }

        B_Node(int data, B_Node* parent)
        {
            this->data = data;
            this->count = 1;
            this->left_child = nullptr;
            this->right_child = nullptr;
            this->parent = parent;
    }
};

class Binary_Search_Tree
{
    public:

        B_Node* root;
        int number_of_elements;
        Binary_Search_Tree()
        {
            root = nullptr;
            number_of_elements = 0;
        }
        // check if empty
        bool is_empty()
        {
            return number_of_elements == 0;
        }

        // size function
        int size()
        {
            return number_of_elements;
        }
        
        // insert function
        void insert(B_Node* b)
        {
            if(is_empty())
            {
                root = new B_Node(b->data, nullptr);
                number_of_elements++;
            }
            else
            {
                int key = b->data;
                B_Node* temp;
                temp = root;
                bool inserted = false;
                while(!inserted)
                {
                    if(key > temp->data)
                    {
                        if(temp->right_child == nullptr)
                        {
                            temp->right_child = new B_Node(key, temp);
                            inserted = true;
                            number_of_elements++;
                        }
                        else
                        {
                            temp = temp->right_child;
                        }
                    }
                    else if(key < temp->data)
                    {
                        if(temp->left_child == nullptr)
                        {
                            temp->left_child = new B_Node(key,temp);
                            inserted = true;
                            number_of_elements++;
                        }
                        else
                        {
                            temp = temp->left_child;
                        }
                    }
                    else        // handle duplicate values
                    {
                        temp->count++;
                    }
                }
            }
        }
        // find root
        B_Node* get_root()
        {
            return root;
        }

        // find parent
        B_Node* get_parent(B_Node* bnode)
        {
            return bnode->parent;
        }

        // check if root node
        bool is_leaf(B_Node* bnode)
        {
            return (bnode->left_child == nullptr && bnode->right_child == nullptr);
        }

        // check if internal node
        bool is_internal_node(B_Node* bnode)
        {
            return !is_leaf(bnode);
        }
        // preorder traversal
        void preorder(B_Node* bnode)
        {
            if(bnode == nullptr)
            {
                return;
            }
            else
            {
                cout<<bnode->data<<" ";
                preorder(bnode->left_child);
                preorder(bnode->right_child);
            }
        }
        //inorder traversal
        void inorder(B_Node* bnode)
        {
            if(bnode == nullptr)
            {
                return;
            }
            else
            {
                inorder(bnode->left_child);
                cout<<bnode->data<<" ";
                inorder(bnode->right_child);
            }
        }

        // postorder traversal
        void postorder(B_Node* bnode)
        {
            if(bnode == nullptr)
            {
                return;
            }
            else
            {
                postorder(bnode->left_child);
                postorder(bnode->right_child);
                cout<<bnode->data<<" ";
            }
        }

        // search function
        B_Node* search(int key)
        {
            B_Node* temp = root;
            do
            {
                if(key > temp->data)
                {
                    if(temp-> right_child == nullptr)
                    {
                        return new B_Node();
                    }
                    else
                    {
                        temp = temp->right_child;
                    }
                }
                else if(key < temp->data)
                {
                    if(temp-> left_child == nullptr)
                    {
                        return new B_Node();
                    }
                    else
                    {
                        temp = temp->left_child;
                    }
                }
                // found case
                if(key ==temp->data)
                {
                    return temp;
                }
            }while(!is_leaf(temp));
            return new B_Node();
        }

        // find successor of a node
        B_Node* get_successor(int element)
        {

            B_Node* temp = search(element);
            temp = temp->right_child;
            while(temp->left_child)
            {
                temp = temp->left_child;
            }
            return temp;
        }

        // delete node function
        B_Node* delete_node(int element)
        {
            B_Node* temp = search(element);
            if(!temp->left_child && !temp->right_child) // leaf node deletion 
            {
                cout<<"\nleaf node case\n";
                if(temp == root)    // single node in the tree i.e. tree having only one node whcih is root
                {
                    delete root;
                    root == nullptr;
                    return root;
                }
                else    // usual leaf nodes which are not root
                {
                    if(temp->parent->left_child == temp)    // if leaf to be deleted is left child
                    {
                        cout<<"\nis left child\n";
                        temp->parent->left_child = nullptr;             // use this working with connections
                        delete temp;        // deletes only the data of temp node not the temp pointer
                        //return temp->parent;// trace back to parent using temp pointer as pointer does not get deleted only its data get deleted
                    }
                    else    // leaf to be deleted is the right child
                    {
                        cout<<"\nis right child\n";
                        temp->parent->right_child = nullptr;    // use this working with connections
                        delete temp;    // deletes only the data of temp node not the temp pointer
                        //return temp->parent;// trace back to parent using temp pointer as pointer does not get deleted only its data get deleted
                    }
                    B_Node* temp_parent = temp->parent;
                    temp->left_child = temp->right_child = temp->parent = nullptr;
                    return temp_parent;
                }
            }
            else if(temp->left_child && temp->right_child)  // deletion of nodes with both the child 
            {
                B_Node* successor_node = get_successor(element);
                // removing successor from its original position
                if(successor_node->parent->left_child == successor_node) // successor node is left child
                {
                    successor_node->parent->left_child = nullptr;
                }
                else    // successor node is right child
                {
                    successor_node->parent->right_child = nullptr;                    
                }
                successor_node->parent = nullptr;
                //successor node has been cut off from the tree
                //NOTE: REMOVAL OF SUCCESSOR WILL CAUSE SOME NODE TO HAVE ONLY ONE CHILD WHICH PREVIOUSLY HAD TWO CHILDREN
                if(temp == root)    // root with two children is to be deleted
                {
                    successor_node->left_child = temp->left_child;
                    temp->left_child->parent = successor_node;
                    successor_node->right_child = temp->right_child;
                    temp->right_child->parent = successor_node;
                    root = successor_node;
                    delete temp;
                    temp->left_child = temp->left_child = temp->parent = nullptr;
                    return root;
                }
                else    // node to be deleted is neither root nor leaf and has 2 children
                {
                    successor_node->left_child = temp->left_child;
                    if(temp->left_child)    //if left child exists after removing successor
                        temp->left_child->parent = successor_node;
                    successor_node->right_child = temp->right_child;
                    if(temp->right_child)   //left child exists after removing successor
                        temp->right_child->parent = successor_node;
                    if(temp->parent->left_child == temp)    // node to be deleted is a left child
                    {
                        temp->parent->left_child = successor_node;

                    }
                    else
                    {
                        temp->parent->right_child = successor_node;
                    }
                    successor_node->parent = temp->parent;
                    delete temp;    // deletes the contents of temp, nothing to do with connections established by pointers
                    temp = temp->left_child = temp->right_child = temp->parent = nullptr;
                    return successor_node; 
                       
                }
                // B_Node* successor_node = get_successor(element);
                // cout<<"\nSuccessor "<<successor_node->data;
                // temp->data = successor_node->data;
                // delete successor_node;
                // if(successor_node->parent->left_child == successor_node)    // if successor is aleft child
                // {
                //     cout<<"\nLeft child ";
                //     cout<<successor_node->parent->data<<" "<<successor_node->parent->parent->data;
                //     delete successor_node->parent->left_child;
                //     successor_node->parent->left_child == NULL;
                    
                //     cout<<"testing "<<search(58)->left_child->data;
                
                    
                // }
                // else
                // {
                //     delete successor_node->parent->right_child;
                //     successor_node->parent->right_child == nullptr;

                // }
                // return successor_node->parent;
            }
            else    // deletion of node with single child case
            {
                if(temp->parent->left_child = temp)   // if temp is a left child
                {
                    if(temp->left_child)    //temp is a left child and has a left child
                    {
                        temp->parent->left_child = temp->left_child;
                        temp->left_child->parent = temp->parent;
                    }
                    else    //temp is left child and has a right child
                    {
                        temp->parent->left_child = temp->right_child;
                        temp->right_child->parent = temp->parent;
                    } 
                }
                else    // temp is a right child
                {
                    if(temp->left_child)    // temp is a right child and has a left child and
                    {
                        temp->parent->right_child = temp->left_child;
                        temp->left_child->parent = temp->parent;
                    }
                    else    //temp is a right child and has a right child
                    {
                        temp->parent->right_child = temp->right_child;
                        temp->right_child->parent = temp->parent;
                    }
                    
                }
                delete temp;
                B_Node* temp_parent = temp->parent;
                temp = temp->left_child = temp->right_child = temp->parent = nullptr;
                return temp_parent;
            }
        }
        // data type checking
        B_Node* datatype1()
        {
            if(NULL == nullptr)
                cout<<"\nYes";
            return NULL;
        }

};

int main()
{
    Binary_Search_Tree bst;
    int no_of_inputs = 15;
    int insert_data[] = { 100, 50, 150, 25, 75, 125, 175, 12, 37, 60, 85, 112, 132, 158, 200};                             
    for(int i=0; i<15; i++)
    {
        cout<<" "<<insert_data[i];
        bst.insert(new B_Node(insert_data[i]));
    }
   
       
    
    // cout<<"\nPreorder: ";
    // bst.preorder(bst.root);
    // cout<<"\nInorder: ";
    // bst.inorder(bst.root);
    // cout<<"\nPostorder: ";
    // bst.postorder(bst.root);
    // cout<<"\nSuccessor: "<<bst.get_successor(41)->data;
    // cout<<"\nDatatype: "<<bst.datatype1();
    int d;
    cout<<"\nEnter number of element to delete ";
    cin>>d;
    B_Node* deleted_node;
    while(d--)
    {
        int e;
        cout<<"\nBefore deletion :";
        cout<<"\nPreorder: ";
        bst.preorder(bst.root);
        // cout<<"\nInorder: ";
        // bst.inorder(bst.root);
        // cout<<"\nPostorder: ";
        // bst.postorder(bst.root);
        cout<<"\nEnter which element to delete ";
        cin>>e;
        
        deleted_node = bst.delete_node(e);
        cout<<"\nAfter deletion";
        cout<<"\nPreorder: ";
        bst.preorder(bst.root);
        // cout<<"\nInorder: ";
        // bst.inorder(bst.root);
        // cout<<"\nPostorder: ";
        // bst.postorder(bst.root);

    }
}