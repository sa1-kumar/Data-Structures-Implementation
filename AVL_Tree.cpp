#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;

class B_Node
{
    public:

        int data;
        int count;  // repeatition of value, duplicate values
        B_Node* left_child;
        B_Node* right_child;
        B_Node* parent;
        int height;
        B_Node()
        {
            data = - 99999;    // considering as empty or default value
            count = 0;
            left_child = nullptr;
            right_child = nullptr;
            parent = nullptr;
            height = 0;        
        }

        B_Node(int data)
        {
            this->data = data;
            count = 1;
            left_child = nullptr;
            right_child = nullptr;
            parent = nullptr;
            height = 0;
        }

        B_Node(int data, B_Node* parent)
        {
            this->data = data;
            this->count = 1;
            this->left_child = nullptr;
            this->right_child = nullptr;
            this->parent = parent;
            height = 0;
    }
};

// creating a class to store x, y, z nodes used during rotation


class AVL_Tree
{
    public:

        B_Node* root;
        int number_of_elements;

        // instance variable for operational purposes
        B_Node* x;
        B_Node* y;
        B_Node* z;
        B_Node* cascade_point;
        
        AVL_Tree()
        {
            root = nullptr;
            number_of_elements = 0;

            x=nullptr;
            y=nullptr;
            z=nullptr;
            cascade_point = nullptr;

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
        B_Node* insert(B_Node* b)
        {
            if(is_empty())
            {
                root = new B_Node(b->data, nullptr);
                number_of_elements++;
                return root;
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
                            return temp->right_child;
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
                            return temp->left_child;
                        }
                        else
                        {
                            temp = temp->left_child;
                        }
                    }
                    else        // handle duplicate values
                    {
                        temp->count++;
                        inserted = true;
                        number_of_elements++;   //duplicate nodes will also be counted
                        return temp;
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
            if(temp->right_child)
                temp = temp->right_child;
            else
                return nullptr;
            while(temp->left_child)
            {
                temp = temp->left_child;
            }
            return temp;
        }
        B_Node* remove_successor_of(int element)    //element whose successor needs to be removed
        {
            B_Node* successor_node = get_successor(element);
            cascade_point = successor_node->parent;
                // removing successor from its original position
                if(is_leaf(successor_node))
                {
                    if(successor_node->parent->left_child == successor_node) // successor node is left child
                    {
                        successor_node->parent->left_child = nullptr;
                    }
                    else    // successor node is right child
                    {
                        successor_node->parent->right_child = nullptr;                    
                    }
                    successor_node->parent = nullptr;
                    return successor_node;
                }
                else    // case when successor node has one child
                {       // POINT TO NOTE: IF SUCCESSOR NODE HAS A CHILD THEN IT WILL ALWAYS HAVE A RIGHT CHILD
                    B_Node* successor_child = successor_node->right_child;
                    successor_child->parent = nullptr;
                    successor_node->right_child = nullptr;
                    // child of successor cut off from the parent
                    if(successor_node->parent->left_child == successor_node) // successor node is left child
                    {
                        //successor_node->parent->left_child = nullptr;

                        successor_node->parent->left_child = successor_child;
                        successor_child->parent = successor_node->parent;
                    }
                    else    // successor node is right child
                    {
                        //successor_node->parent->right_child = nullptr;  

                        successor_node->parent->right_child = successor_child;
                        successor_child->parent = successor_node->parent;                  
                    }
                    successor_node->parent = nullptr;
                    return successor_node;


                }
                
        }

        // delete node function
        B_Node* delete_node(int element)
        {
            B_Node* temp = search(element);
            if(!temp->left_child && !temp->right_child) // leaf node deletion 
            {
                //cout<<"\nleaf node case\n";
                if(temp == root)    // single node in the tree i.e. tree having only one node whcih is root
                {
                    delete root;
                    root = nullptr;
                    root->parent = root->left_child = root->right_child = nullptr;
                    cascade_point = root;
                    return root;
                }
                else    // usual leaf nodes which are not root
                {
                    if(temp->parent->left_child == temp)    // if leaf to be deleted is left child
                    {
                        //cout<<"\nis left child\n";
                        temp->parent->left_child = nullptr;             // use this working with connections
                        delete temp;        // deletes only the data of temp node not the temp pointer
                        //return temp->parent;// trace back to parent using temp pointer as pointer does not get deleted only its data get deleted
                    }
                    else    // leaf to be deleted is the right child
                    {
                        //cout<<"\nis right child\n";
                        temp->parent->right_child = nullptr;    // use this working with connections
                        delete temp;    // deletes only the data of temp node not the temp pointer
                        //return temp->parent;// trace back to parent using temp pointer as pointer does not get deleted only its data get deleted
                    }
                    B_Node* temp_parent = temp->parent;
                    temp->left_child = temp->right_child = temp->parent = nullptr;
                    cascade_point = temp_parent;
                    return temp_parent;
                }
            }
            else if(temp->left_child && temp->right_child)  // deletion of nodes with both the child 
            {
                number_of_elements--;
                B_Node* successor_node = remove_successor_of(element);  // return successor node and cuts it off from the tree
                successor_node->left_child = temp->left_child;
                if(temp->left_child)    //if left child exists after removing successor
                    temp->left_child->parent = successor_node;
                successor_node->right_child = temp->right_child;
                if(temp->right_child)   //left child exists after removing successor
                    temp->right_child->parent = successor_node;
                //cout<<"\nDeleting Root\n";
                if(temp != root)
                {
                    if(temp->parent->left_child == temp)    // node to be deleted is a left child , WILL NOT WORK FOR THE ROOT CASE
                        temp->parent->left_child = successor_node;
                    else
                        temp->parent->right_child = successor_node;
                }
                else
                    root = successor_node;
                
                successor_node->parent = temp->parent;
                delete temp;    // deletes the contents of temp, nothing to do with connections established by pointers6
                temp = temp->left_child = temp->right_child = temp->parent = nullptr;
                return successor_node; 
                       
                
            }
            else    // deletion of node with single child case
            {
                if(temp->parent->left_child == temp)   // if temp is a left child
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
                cascade_point = temp_parent;
                return temp_parent;
            }
        }

        //function to assign height to the nodes
        void assign_height(B_Node* top_node)
        {   
            if(is_leaf(top_node))
            {   
                top_node->height = 1;
                return;
            }
            else
            {   
                if(top_node->right_child)
                    assign_height(top_node->right_child);
                if(top_node->left_child)
                    assign_height(top_node->left_child);
                int left_height, right_height;


                if(top_node->right_child)
                    right_height = top_node->right_child->height;
                else
                    right_height = 0;

                if(top_node->left_child)
                    left_height = top_node->left_child->height;
                else
                    left_height = 0;

                top_node->height = max(left_height, right_height) + 1;
            }
        }

        // recursive function to display height of each node
        void display_height(B_Node* bnode)
        { 
            if(is_leaf(bnode))
            {
                cout<<"\nLeaf Node: "<<bnode->data<<" | height: "<<bnode->height;
                if(bnode->parent)
                    cout<<" | parent: "<<bnode->parent->data;
                return;
            }
            else
            {
                cout<<"\nNode: "<<bnode->data<<" | height: "<<bnode->height;
                if(bnode->left_child)
                    cout<<" | Left child: "<<bnode->left_child->data;
                if(bnode->right_child)
                    cout<<" | Right child: "<<bnode->right_child->data;
                if(bnode->parent) 
                    cout<<" | parent: "<<bnode->parent->data;
                if(bnode->left_child)
                {             
                    display_height(bnode->left_child);
                }
                if(bnode->right_child)
                {     
                    display_height(bnode->right_child);
                }
            }
        }
        
        //function to check if a node is balanced or not
        bool is_balanced(B_Node* node)
        {
            
            int left_height, right_height;
            if(node->left_child)
                left_height = node->left_child->height;
            else
                left_height = 0;
            if(node->right_child)
                right_height = node->right_child->height;
            else
                right_height = 0;
            if(abs(left_height - right_height) > 1)
                return false;
            else
                return true; 
        }

        //function to find the first imbalanced node from any leaf towards root
        B_Node* find_imbalanced_node(B_Node* node)
        {
            do
            {
                if(!is_balanced(node))
                    return node;
                else
                    node = node->parent;
            }while(node!= root->parent);  // will also check the root as parent of root is nullptr
            return nullptr;
        }

        // function to locate x, y and z nodes for insertion in the AVL Tree
        void locate_xyz_for_insertion(B_Node* insertion_point)
        {
            x=y=z=nullptr;
            x=insertion_point;

            if(x->parent)   // ensuring parent of x exists
            {
                y=x->parent;
                if(y->parent)   // parent of y exists
                    z=y->parent;
            }
            while(z != root->parent)    // ensuring z does not move up beyond root , also if z exits then y and x will also exist
            {
                if(!is_balanced(z))
                    break;
                else
                {
                    x=y;
                    y=z;
                    z=z->parent;
                }
            }
            if(!z)  // z is nullptr , means all nodes were balanced or z did not exit which also implies the nodes were balanced
            {
                x=y=z = nullptr;    // clearing the variable data because data are not required 
            }
            else
            {
                // cout<<"\nx at :"<<x->data<<"\n";
                // cout<<"\ny at :"<<y->data<<"\n";
                // cout<<"\nz at :"<<z->data<<"\n";

            }
        }
        
        // function  to locate x, y, z node for deletion
        void locate_xyz_for_deletion(B_Node* deletion_point)//checks each node for imabalance starting from deletion_point and moving towards root
        {
            x=y=z=nullptr;
            cascade_point=deletion_point;
            do
            {
                if(!is_balanced(cascade_point))
                {
                    z = cascade_point;
                    // if z is unbalanced then y and x will definitely exist
                    // assigning y node
                    int left_height, right_height;
                    if(z->left_child)
                        left_height = z->left_child->height;
                    else
                        left_height = 0;
                    if(z->right_child)
                        right_height = z->right_child->height;
                    else
                        right_height = 0;
                    if(left_height > right_height)
                        y = z->left_child;
                    else
                        y = z->right_child;

                    // assigning x node
                    left_height = right_height = 0;
                    if(y->left_child)
                        left_height = y->left_child->height;
                    else
                        left_height = 0;
                    if(y->right_child)
                        right_height = y->right_child->height;
                    else
                        right_height = 0;
                    if(left_height > right_height)
                        x = y->left_child;
                    else
                        x = y->right_child;

                    return;      
                }
                else 
                    cascade_point = cascade_point->parent;

            }while(cascade_point != root->parent);  // parent of rool is nullptr, root also needs to be checked for evaluation

            
        }

        //function to find the imbalance case for rotation 
        char find_rotation_case(B_Node* x, B_Node* y, B_Node* z)
        {
            if(z)   // ensuring x, y and z exists | if z exists it means x and y also exists
            {
                if(z->left_child)
                {
                    if(z->left_child->left_child)   // ensuring the path exists
                    {
                        if(z->left_child == y && z->left_child->left_child == x)
                            return '/'; // Left-Left case
                    }
                    if(z->left_child->right_child)    
                    {
                        if(z->left_child == y && z->left_child->right_child == x )
                            return '<'; // Left-Right case
                    }  
                }
                if(z->right_child)    // if left child does not exists then right hild has to exist 
                {
                    if(z->right_child->right_child)     //ensuring path exists
                    {
                        if(z->right_child == y && z->right_child->right_child == x)
                            return '\\'; //Right-Right case || To represent a single backslash, it's necessary to place double backslashes (\\) 
                    }
                    if(z->right_child->left_child)
                    {
                        if(z->right_child == y && z->right_child->left_child == x)
                            return '>';     // Right-Left case
                    }          
                }
            }
            return 'X';
        }

        //function to perform right rotation on any node and return point of rotation in the tree
        B_Node* right_rotation(B_Node* rotating_node)
        {
            B_Node* cut = rotating_node->parent;
            char child_type;    // parent of z node
            if(rotating_node->parent)   // when rotation is not at the root
            {
                if(rotating_node->parent->left_child == rotating_node) // if node to be rotated is a left child
                    {
                        rotating_node->parent->left_child = nullptr;
                        child_type = 'L';
                    }
                if(rotating_node->parent->right_child == rotating_node)   // if node to be rotated is a right child
                    {
                        rotating_node->parent->right_child = nullptr;
                        child_type = 'R';
                        //cout<<"\ny case\n";
                    }
                rotating_node->parent = nullptr;
                // node to be rotated cut off from the tree
            }
            B_Node* rotating_left_node = rotating_node->left_child; // y node
            B_Node* donating_child = rotating_left_node->right_child;   // T3 

            // separating z and y
            rotating_node->left_child = nullptr;
            rotating_left_node->parent = nullptr;

            //separating y and T3
            rotating_left_node->right_child = nullptr;
            if(donating_child)  // ensuring child to be donated exists
                donating_child->parent = nullptr;

            // reconnecting T3 as left child to z
            rotating_node->left_child = donating_child;  
            if(donating_child)  // ensuring if donating child exists
                donating_child->parent = rotating_node;

            // reconnecting y and z by making z the right child of y
            rotating_left_node->right_child = rotating_node;
            rotating_node->parent = rotating_left_node;

            //now reconnecting the rotated subtree to the original tree
            rotating_left_node->parent = cut;   // connecting y to the main tree
            if(cut) // ensuring the ancestor node exists to connect | This won't execute if rotation took place at root
            {
                if(child_type == 'R')
                    {
                        cut->right_child = rotating_left_node;
                        //cout<<"\nin the cut\n";
                        //cout<<root->data<<" "<<root->right_child->data<<" "<<root->right_child->right_child->data<<" ";
                    }
                else
                    cut->left_child = rotating_left_node;
            }
            else    // cut won't exist if rotation occurred at root node
            {
                root = rotating_left_node; // making y the root because z would have been the root before rotation for this case
            }
            //cout<<root->data<<" "<<root->right_child->data<<" "<<root->right_child->right_child->data<<" cut at "<<cut->data;
            return cut; // return the next upper node to handle cascading
        }

        //function to perform left rotation
        B_Node* left_rotation(B_Node* rotating_node)
        {
            //cout<<root->data<<" "<<root->right_child->data<<" "<<root->right_child->right_child->data;
            B_Node* cut2 = rotating_node->parent;
            char child_type;    // parent of z node
            if(rotating_node->parent)   // when rotation is not at the root
            {
                if(rotating_node->parent->left_child == rotating_node) // if node to be rotated is a left child
                    {
                        rotating_node->parent->left_child = nullptr;
                        child_type = 'L';
                    }
                if(rotating_node->parent->right_child == rotating_node)    // if node to be rotated is a right child
                    {
                        rotating_node->parent->right_child = nullptr;
                        child_type = 'R';
                    }
                rotating_node->parent = nullptr;
                // node to be rotated cut off from the tree
            }
            B_Node* rotate_right_node = rotating_node->right_child; // y node
            B_Node* donating_child = rotate_right_node->left_child; // T2

            // separating T2 and y node
            rotate_right_node->left_child = nullptr;
            if(donating_child)  // ensuring T2 exists
                donating_child->parent = nullptr;

            //separating z and y node
            rotating_node->right_child = nullptr;
            rotate_right_node->parent = nullptr;

            // reconnecting z and T2 by making T2 as right child of z node
            rotating_node->right_child = donating_child;
            if(donating_child)  // ensuring child exists 
                donating_child->parent = rotating_node;

            // reconnecting y and z node by making z the left child of y
            rotate_right_node->left_child = rotating_node;
            rotating_node->parent = rotate_right_node;

            // reconnecting the rotated subtree to the original tree
            rotate_right_node->parent = cut2;
            if(cut2)
            {
                if(child_type == 'R')
                    cut2->right_child = rotate_right_node;
                else
                    cut2->left_child = rotate_right_node;
            }
            else    // cut won't exist if rotation occurred at root node
            {
                root = rotate_right_node; // making y the root because z would have been the root before rotation for this case
            }
            //cout<<root->data<<" "<<root->left_child->data<<" "<<root->right_child->data;
            return cut2; // return the next upper node to handle cascading
        }
        


        // avl_insertion function
        B_Node* avl_insertion(int element)
        {
            cout<<"\n\nInserting: "<<element;
            B_Node* insertion_point = insert(new B_Node(element));
            assign_height(root);
            cout<<"\nroot: "<<root->data;
            display_height(root);
            locate_xyz_for_insertion(insertion_point);
            if(z)
            {
                //cout<<"datatye of xyz: "<<typeid(x_y_z).name();
                cout<<"\nz at :"<<z->data;
                cout<<"\ny at :"<<y->data;
                cout<<"\nx at :"<<x->data;

                char rotation_type = find_rotation_case(x, y, z);
                switch(rotation_type)
                {
                    case '/':
                    cout<<"\nLeft-Left case: right rotating: "<<z->data;
                    right_rotation(z);
                    break;
                    
                    case '<':
                    cout<<"\nLeft-Right case: left rotating: "<<y->data<<" and then right rotating: "<<z->data;
                    left_rotation(y);
                    right_rotation(z);
                    break;

                    case '\\':
                    cout<<"\nRight-Right case: left rotating: "<<z->data;
                    left_rotation(z);
                    break;  

                    case '>':
                    cout<<"\nRight-Left case: right rotating: "<<y->data<<" and then left rotating: "<<z->data;
                    right_rotation(y);
                    left_rotation(z);
                    break;            
                }
                assign_height(root);
                cout<<"\nroot: "<<root->data;
                display_height(root);          
            }
            
        }
        
        // function to perform avl deletion
        B_Node* avl_deletion(int element)
        {
            cout<<"\n\nDeleting: "<<element;
            B_Node* deletion_point = delete_node(element); // delete_node() will place the cascade_point
            assign_height(root);    // height of nodes need to be assigned afresh after the tree undergoes deletion of node
            cout<<"\nroot:"<<root->data;
            display_height(root);
            do 
            {
                //assign_height(root);    // height of nodes need to be assigned afresh after the tree undergoes deletion of node
                //cout<<"\root:"<<root->data;
                //display_height(root);
                locate_xyz_for_deletion(cascade_point);
                if(z)
                {
                    //cout<<"datatye of xyz: "<<typeid(x_y_z).name();
                    cout<<"\nz at :"<<z->data;
                    cout<<"\ny at :"<<y->data;
                    cout<<"\nx at :"<<x->data;

                    char rotation_type = find_rotation_case(x, y, z);
                    switch(rotation_type)
                    {
                        case '/':
                        cout<<"\nLeft-Left case: right rotating: "<<z->data;
                        cascade_point = right_rotation(z);
                        break;
                        
                        case '<':
                        cout<<"\nLeft-Right case: left rotating: "<<y->data<<" and then right rotating: "<<z->data;
                        left_rotation(y);
                        cascade_point = right_rotation(z);
                        break;

                        case '\\':
                        cout<<"\nRight-Right case: left rotating: "<<z->data;
                        cascade_point = left_rotation(z);
                        break;  

                        case '>':
                        cout<<"\nRight-Left case: right rotating: "<<y->data<<" and then left rotating: "<<z->data;
                        right_rotation(y);
                        cascade_point = left_rotation(z);
                        break;            
                    }
                    assign_height(root);
                    cout<<"\nroot: "<<root->data;
                    display_height(root); 
                }
            }while(cascade_point != root->parent);

        }




};

int main()
{
    
    AVL_Tree avl1, avl_curr;
    cout<<"***********************DEMO INSERTIONS AND DELETIONS*************************************\n";
    int insert_data[] = { 100, 500, 250, 50, 75, 1000, 1500, 400, 300, 85, 450, 1200 };                            
    for(int i=0; i<12; i++)
    {
        avl1.avl_insertion(insert_data[i]);
    }
    avl1.avl_deletion(1500);
    avl1.avl_insertion(425);
    avl1.avl_deletion(50);
    // cout<<"\nWhere do you want to perform operations ? Enter the respective choice";
    // cout<<"\nCURRENT TREE : 1";
    // cout<<"\nNEW TREE (EMPTY TREE) : 2";
    // int choice;
    // cout<<"\nEnter your choice ";
    // cin>>choice;
    // if(choice == 1)
    //     avl_curr = avl1;

    // if(choice != 1  || choice == 2)
    //     cout<<"\nEnter 1 or 2";

    // do
    // {
    //     cout<<"What operation "

    // }while()
    
}