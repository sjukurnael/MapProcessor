/**~*~*~*~*
   Stack template
*~*/

#ifndef STACK_ADT
#define STACK_ADT

template <class T>
class Stack
{
private:
    // Structure for the stack nodes
    struct StackNode
    {
      T value;          // Value in the node
      StackNode *next;  // Pointer to next node
    };

    StackNode *top;     // Pointer to the stack top
    int length;

public:
    // Constructor
    Stack() { top = NULL; length = 0; }
    // Destructor
    ~Stack();
    // Stack operations:
    bool push(T);
    T pop();
    T peek() { return top->value; }
    bool isEmpty() { if (length == 0) { return true; } else { return false; } }
    int getLength() { return length; }
};

/**~*~*~*~*
  Member function push inserts the argument onto
  the stack.
*~**/

template <class T>
bool Stack<T>::push(T item)
{
   StackNode *newNode;
   
   newNode = new StackNode;
   if (!newNode)
      return false;
   newNode->value = item;
   
   newNode->next = top;
   top = newNode;
   length++;
      
   return true;
}


/**~*~*~*~*
  Member function pop deletes the value at the top
  of the stack and returns it.
  Assume stack is not empty.
*~**/

template<class T>
T Stack<T>::pop()
{ 
   StackNode *temp = top;
   T data = temp->value;
   top = top->next;
   delete temp;
   length--;
   return data;
}



/**~*~*~*~*
  Destructor:
  Traverses the list deleting each node (without calling pop)
*~**/

template<class T>
Stack<T>::~Stack()
{
   StackNode *currNode;
   currNode = top;
   while (currNode)
   {
      StackNode *nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}      
   


#endif

