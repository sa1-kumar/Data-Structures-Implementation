#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
        char data;
        Node* next;
        Node()
        {
            data = ' ';
            next = NULL;
        }
        Node(char d)
        {
            data = d;
            next = NULL;
        }
};

//Circular linked list class

class CircularLinkedList
{
    public:
        Node* head;
        int node_count;
        CircularLinkedList()
        {
            head = NULL;
            node_count = 0;
        }

        // function to check if list is empty
        bool isEmpty()
        {
            return node_count == 0;
        }

        // insert at begining function 
        void insert_Beg(Node* n)
        {
            if(head == NULL)
            {
                head = n;
                head -> next = head;
                node_count++;
            }
            else
            {
                // inserting a new node next to head
                n->next = head->next;
                head->next = n;

                // exchanging data element of head node and n node to maintain the adding sequence  

                int temp = head->data;
                head->data = head->next->data;
                head->next->data = temp;

                node_count++;

            }
        }
        // insert at the end function
        void insert_End(Node* n)
        {
            if(head == NULL)
            {
                head = n;
                head -> next = head;
                node_count++;
            }
            else
            {
                
                // inserting a new node next to head
                n->next = head->next;
                head->next = n;

                // exchanging data element of head node and n node to maintain the adding sequence  
                int temp = head->data;
                head->data = head->next->data;
                head->next->data = temp;

                // moving head 1 node ahead so the newly added node becomes he last node
                head = head->next;

                node_count++;

            }

        }
        // function to display the circular linked list
        void display()
        {
            Node* ptr;
            ptr = head;
            if(!isEmpty())
            {
                do
                {
                    cout<<ptr->data<<"  ";
                    ptr = ptr->next;
                }while(ptr!=head);
                cout<<"\n";
            }
        }
        // delete at the front function
        // can be used for both stack and queue
        // for stack : delete_front() = pop()       : LIFO   FO   FIRST OUT
        // for queue : delete_front() = dequeue()   : FIFO   FO   FIRST OUT
        // Both stack and queues uses FIRST OUT
        Node* delete_front()
        {
            if(!isEmpty())
            {
                
                //exchanging head node data and head->next node data
                char temp_data;
                temp_data = head->next->data;
                head->next->data = head->data;
                head->data = temp_data;

                //putting second node out of list
                Node* deleted_node = new Node(head->next->data);
                Node* temp;
                temp = head->next;
                head->next = head->next->next;
                delete temp;

                node_count--;

                return deleted_node;
            }
            else
            {
                cout<<"List is empty.";
                return 0;
            }
        }

        // delete at the end function
        Node* delete_end()
        {
            Node* ptr;
            ptr = head;
            if(!isEmpty())
            {
                do
                {
                    ptr=ptr->next;
                }while(ptr->next->next != head);

                Node* deleted_node = new Node(ptr->next->data);
                delete ptr->next;
                ptr->next = head;

                node_count--;
                
                return deleted_node;
            }
            else
            {
                cout<<"List is empty .";
                return 0;
            }
        
            
        }

};

// Stack class using the above circular linked list
class Stack_CLL
{
    public:
        CircularLinkedList c1;

        // push function 
        void push(Node* n)
        {
            c1.insert_Beg(n);
        }

        // pop function
        Node* pop()
        {
             return c1.delete_front();
        }

        // peep function
        Node* peep()
        {
            return c1.head;
        }

        // display stack 
        void display()
        {
            cout<<"\nThe stack is : ";
            c1.display();
            cout<<"\n";
        }

        // function to check if stack is empty
        bool isEmpty()
        {
            return c1.isEmpty();
        }
};



int main()
{
   
    Stack_CLL s1;
    Node* n1 = new Node('a');
    Node* n2 = new Node('b');
    Node* n3 = new Node('c');
    Node* n4 = new Node('d');
    Node* n5 = new Node('e');

    cout<<"\nPushing 'a':\n";
    s1.push(n1);
    s1.display();
    cout<<"\nPushing 'b':\n";
    s1.push(n2);
    s1.display();
    cout<<"\nPushing 'c':\n";
    s1.push(n3);
    s1.display();
    cout<<"\nPeeping:\nPeeped element is : "<<s1.peep()->data<<"\n";
    s1.display();
    cout<<"\nPushing 'd':\n";
    s1.push(n4);
    s1.display();
    cout<<"\nPushing 'e':\n";
    s1.push(n5);
    s1.display();
    cout<<"\nPeeping:\nPeeped element is : "<<s1.peep()->data<<"\n";
    s1.display();
    cout<<"\nPopping:\nPoped elemet is : "<<s1.pop()->data<<"\n";
    s1.display();

    return 0;

}