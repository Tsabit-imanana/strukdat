#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

class Node {
    char value;
    Node* next;

	public:
    Node(char val) : value(val), next(NULL) {} //menginisiasikan value menjadi val dan next node null
    char getValue() { return value; }
    Node* getNext() { return next; }
    void setNext(Node* n) { next = n; }
};

class Stack {
    Node* top; // menujuk node teratas stack

	public: 
	// karena menggunkan class maka jika perlu menggunakan public, jika tidak ingin menggunakan public gunakan typedef struct
    Stack() : top(NULL) {} //menunjukan stack itu kosong

    bool isEmpty() { //jika kosong, boolean seperti if atau else
        return top == NULL;
    }

    void push(char value) {
        Node* newNode = new Node(value);
        newNode->setNext(top);
        top = newNode;
    }

    char pop() {
        if (!isEmpty()) {
            char poppedValue = top->getValue();
            Node* temp = top;
            top = top->getNext();
            delete temp;
            return poppedValue;
        }
        return '\0'; // null menggunakan \0
    }

    char peek() { // mengintip nilai didalam stack
        return isEmpty() ? '\0' : top->getValue();
    }
};

int precedence(char op) { // untuk menciptakan hirarki antara +- dan */
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2; //lebiih tinggi */
    return 0;
}

string infixToPostfix(const string& expression) {
    Stack stack;
    string output; // untuk menyimpan hasil output

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isalnum(ch)) { // untuk menyimpan angka yang dimasukan
            output += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                output += stack.pop(); // Pop dari stack ke output sampai menemukan '('
            }
            stack.pop();
        } else { // operator/ tanda +-*/
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                output += stack.pop(); // Pop operator dari stack ke output jika prioritas operator di stack lebih tinggi atau sama
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) { // pop semua operator
        output += stack.pop();
    }

    return output;
}

string infixToPrefix(const string& expression) {
    string reversedExpression(expression.rbegin(), expression.rend());
    for (size_t i = 0; i < reversedExpression.length(); ++i) {
        if (reversedExpression[i] == '(') {
            reversedExpression[i] = ')';
        } else if (reversedExpression[i] == ')') {
            reversedExpression[i] = '(';
        }
    }
    string postfix = infixToPostfix(reversedExpression); // Mengonversi ekspresi terbalik menjadi postfix
    return string(postfix.rbegin(), postfix.rend()); // Membalik hasil postfix menjadi prefix
}

int evaluatePostfix(const string& postfix) {
    Stack stack;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isdigit(ch)) { // Memeriksa apakah karakter adalah digit (0-9), char '5' menjadi int 5
            stack.push(ch - '0'); // mengubah char menjadi int
        } else {
            int b = stack.pop();
            int a = stack.pop();
            switch (ch) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }
    return stack.pop();
}

int main() {
    string expression;
    char choice;
    
    do {
        system("cls");
        cout << "Masukkan kalimat matematika infix (contoh: 3+(5*2)): ";
        getline(cin, expression);

        string postfix = infixToPostfix(expression);
        string prefix = infixToPrefix(expression);
        int result = evaluatePostfix(postfix);

        cout << "Bentuk Infix: " << expression << endl;
        cout << "Bentuk Postfix: " << postfix << endl;
        cout << "Bentuk Prefix: " << prefix << endl;
        cout << "Hasil: " << result << endl;

        cout << "Apakah anda ingin memasukkan kalimat matematika lain? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

