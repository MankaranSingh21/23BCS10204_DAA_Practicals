#include <iostream>
using namespace std;

#define MAX 5

class Stack {
    int arr[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }
    bool isEmpty() {
        return top == -1;
    }
    bool isFull() {
        return top == MAX - 1;
    }
    void push(int x) {
        if (isFull()) {
            cout << "Stack Overflow!" << endl;
        } else {
            arr[++top] = x;
            cout << x << " pushed into stack." << endl;
        }
    }
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
        } else {
            cout << arr[top--] << " popped from stack." << endl;
        }
    }
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty!" << endl;
            return -1;
        } else {
            return arr[top];
        }
    }
};
int main() {
    Stack st;
    st.push(10);
    st.push(20);
    st.push(30);
    cout << "Top element: " << st.peek() << endl;
    st.pop();
    cout << "Top element after pop: " << st.peek() << endl;
    return 0;
}
