#include <bits/stdc++.h>
using namespace std;

class Node
{
    public:
        string data;
        Node* next;
        Node()
        {
            data = ' ';
            next = NULL;
        }
        Node(string d)
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

                string temp = head->data;
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
                string temp = head->data;
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
                //cout<<"\nThe circular linked list : ";
                do
                {
                    cout<<ptr->data<<"  ";
                    ptr = ptr->next;
                }while(ptr!=head);
                //cout<<"\n";
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
                string temp_data;
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
                return NULL;
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

// Queue class
class Queue_CLL
{
    public:
        CircularLinkedList c1;

        // function to check if Queue is empty
        bool isEmpty()
        {
            return c1.isEmpty();
        }

        // enqueue function
        void enqueue(Node* n)
        {      
            c1.insert_End(n);
        }

        // dequeue function
        Node* dequeue()
        {
            if(!isEmpty())
            {
                return c1.delete_front();
            }
            else
            {
                cout<<"\nQueue is empty .\n";
                return new Node("No elements to dequeue .\n");
            }
            
        }

        // function to count number of elements in the queue
        int count_elements()
        {
            return c1.node_count;
        }

        // display queue
        void display()
        {
            if(!isEmpty())
            {
                cout<<"\nThe Queue is :";
                cout<<"\nFront->";
                c1.display();
                cout<<"<-Rear\n";
            }
            else
            {
                cout<<"\nQueue is empty . No elements to display .\n";
            }
        }
};

// main function
int main()
{  
    Queue_CLL queue;
    int choice = -1;
    string element;
    while(choice != 6)
    {
        cout<<"\nWhat queue operation would you like to perform ?\n";
        cout<<"Enter the respective index of operations from menu below :\n";
        cout<<"Enqueue : 1\nDequeue : 2\nDisplay Queue : 3\nCheck if queue is empty : 4\nFind number of elements in the queue : 5\nExit :6\n";
        cout<<"Enter your choice : ";
        cin >> choice;   

        
        switch(choice)
        {
            case 1:
            cout<<"\nEnter an element to enqueue :";
            fflush(stdin);
            getline(cin, element);
            queue.enqueue(new Node(element));
            break;
            
            case 2:
            cout<<"\nDequeued element is : "<<queue.dequeue()->data<<"\n";
            break;

            case 3:
            queue.display();
            break;

            case 4:
            if(queue.isEmpty())
            {
                cout<<"\nThe queue is empty .\n";
            }
            else
            {
                cout<<"\nThe queue is not empty .\n";
            }
            break;

            case 5:
            cout<<"\nNumber of elements in the queue = "<<queue.count_elements()<<"\n";
            break;

            case 6:
            cout<<"\nExiting .\n";
            exit(0);

            default:
            cout<<"\nEnter a valid choice from the menu ."; 
        }   
    }   
}