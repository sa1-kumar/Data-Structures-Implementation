#include <bits/stdc++.h>
using namespace std;


class Stack_Tight
{
    public:
        int top;
        char st[1];
        char* st_ptr;
        int size;
        Stack_Tight()
        {
            top = -1;
            size = strlen(st);
            st_ptr = &st[0];
          
        }
        // grow stack  function
        char* grow_stack(char old_stack[])
        {
            char* new_stack = new char[strlen(old_stack)+1];
            for(int i = 0; i < strlen(old_stack); i++)
            {
                new_stack[i] = old_stack[i];
            }
            st_ptr = &new_stack[0];
            size = strlen(new_stack);
            return new_stack;
        }        
        // function to check if empty
        bool isEmpty()
        {
            return top == -1;
        }

        // function to check if full
        bool isFull()
        {
            return top + 1 == size;
        }

        // push function
        void push(char c)
        {
            if(isFull())
            {
                char* stack_grown = grow_stack(st_ptr);               
            }
            top++;
            st_ptr[top] = c;
        }

        // display stack
        void display()
        {
            if(!isEmpty())
            {
                cout<<"\n The stack : ";
                for(int i = top; i>=0; i--)
                {
                    cout<<st_ptr[i]<< " ";
                }
            }
            else
            {
                cout<<"\nStack is empty.\n";
            }
        }
        //pop stack
        char pop()
        {
            if(!isEmpty())
            {
                char p = st_ptr[top];
                top--;
                return p;
            }
            else
            {
                cout<<"\nStack is empty.\n";
                return 0;
            }
            
        }


};


int main()
{
    Stack_Tight s1;
    s1.push('a');
    s1.push('b');
    s1.push('c');
    s1.display();
    cout<<"\n pop "<<s1.pop()<<"\n";
    s1.display();
    cout<<"\n pop "<<s1.pop()<<"\n";
    s1.display();
    cout<<"\n pop "<<s1.pop()<<"\n";
    s1.display();
    
    

}