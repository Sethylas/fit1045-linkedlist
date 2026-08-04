#include <splashkit.h>
#include <string>

using std::to_string;
using std::stoi;

struct Node
{
    int data; // Values stored in Node
    Node *next; // Pointer to subsequent node in Nodes
};

class LinkedList
{
    private:
        Node *first; // Pointer to first node in Nodes
    public:
        LinkedList() {first = nullptr;} // Has no nodes currently

        // Displays values in list
        void display()
        {
            if (!first) // == nullptr
            {
                write_line("List is empty!");
                return;
            }

            Node *temp = first;
            string output = "List: "; // Starts the display with List:
            while (temp) // repeat until temp is nullptr
            {
                output += to_string(temp->data) + ", ";
                temp = temp->next; // moves to next node
            }
            output += "NULL";
            write_line(output);
        }

        // Adds new value to linked list
        void addValue(int value)
        {
            Node *newNode = new Node{value, nullptr};
            if (!first)
            {
                first = newNode;
                return;
            }

            Node *temp = first; // temp node to not 
            while (temp->next) // Keeps moving until last node
            {
                temp = temp->next;
            }
            temp->next = newNode; // At last node, adds new node
        }
        
        // Deletes a value in the linked list
        void deleteValue(int value)
        {
            if (!first)
            {
                write_line("List is empty!");
                return;
            }

            if (first->data == value) // If first value == value to delete
            {
                Node *temp = first; // Points to current first node
                first = first->next; // Sets the following node to be the new first/head
                delete temp; // Deletes original first node
                write_line(to_string(value) + " has been deleted.");
                return;
            }

            Node *current = first;
            while (current->next && current->next->data != value) // While 
            {
                current = current->next;
            }

            if (!current->next)
            {
                write_line("Value not found!");
                return; 
            }

            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
            write_line(to_string(value) + " has been deleted.");
        }

        // Inserts a value somewhere in the linked list
        void insertValue(int index, int value)
        {
            Node *newNode = new Node{value, nullptr};

            if (index == 0)
            {
                newNode->next=first; // inserts as the first node if no nodes
                first = newNode;
                return;
            }

            Node *temp = first;
            for (int i = 0; temp && i < index - 1; i++) // index - 1 as we want to stop BEFORE
            {
                temp = temp->next; //we keep pointing to the next till we get there
            }

            if (!temp)
            {
                write_line("Index not within range.");
                delete newNode;
                return;
            }
            
            newNode->next = temp->next;
            temp->next = newNode;
        }
};


//--------------------------------Main Program------------------------------------------
int main()
{
    LinkedList list; // to address class LinkedList
    while(true)
    {
        write_line("\nLinked List Actions:");
        write_line("1. See values");
        write_line("2. Add new values at the end");
        write_line("3. Delete a value");
        write_line("4. Insert a value");
        write_line("5. Quit");

        string option;
        bool valid = false;
        do
        {
            write("Option: ");
            option = read_line();
            if (is_integer(option) && stoi(option) <= 5 && stoi(option) > 0)
            {
                valid = true;
            }
        } while (!valid);
        
        if (option == "1")
        {
            list.display();
        }

        else if (option == "2")
        {
            int value;
            string temp;
            do
            {
                int value;
                write("Enter a value to add: ");
                temp = read_line();
                if (is_integer(temp))
                {
                    value = stoi(temp);
                    list.addValue(value);
                }
            } while (!is_integer(temp));
        }

        else if (option == "3")
        {
            int value;
            string temp;
            do
            {
                int value;
                write("Enter a value to delete: ");
                temp = read_line();
                if (is_integer(temp))
                {
                    value = stoi(temp);
                    list.deleteValue(value);
                }
            } while (!is_integer(temp));
        }

        else if (option == "4")
        {
            int value;
            int index;
            string tempIndex;
            string tempValue;
            do
            {
                int value;
                write("Enter index (0 based): ");
                tempIndex = read_line();
                write("Enter value: ");
                tempValue = read_line();
                if (is_integer(tempIndex) && is_integer(tempValue))
                {
                    index = stoi(tempIndex);
                    value = stoi(tempValue);
                    list.insertValue(index, value);
                }

            } while (!is_integer(tempIndex) && !is_integer(tempValue));
        }
        else if (option == "5")
        {
            write_line("Quitting...");
            break; // Breaks out of loop
        }

    }
    return 0;
}
