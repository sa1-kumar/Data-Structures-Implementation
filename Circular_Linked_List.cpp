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
            return node_count==0;
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
                cout<<"\nThe circular linked list : ";
                do
                {
                    cout<<ptr->data<<"  ";
                    ptr = ptr->next;
                }while(ptr!=head);
                cout<<"\n";
            }
            else
            {
                cout<<"\nThe list is empty.\n";
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



// main function
int main()
{
    Node* n1 = new Node('a');
    Node* n2 = new Node('b');
    Node* n3 = new Node('c');
    Node* n4 = new Node('d');

    CircularLinkedList c2;
    c2.display();
    cout<<"\nInserting 'a' in the begining .\n";
    c2.insert_Beg(n1);
    c2.display();
    cout<<"\nInserting 'b' in the begining . \n";
    c2.insert_Beg(n2);
    c2.display();
    cout<<"\nInserting 'c' at the end .\n";
    c2.insert_End(n3);
    c2.display();
    cout<<"\nInserting 'd' at the end .\n";
    c2.insert_End(n4); 
    c2.display();
    cout<<"\nDeleting at front :\n";
    cout<<"\nDeleted elemet is  "<<c2.delete_front()->data<<"\n ";
    c2.display();
    cout<<"\nDeleting at the end : \n";
    cout<<"\nDeleted elemet is "<<c2.delete_end()->data<<"\n";
    c2.display();

    return 0;


}