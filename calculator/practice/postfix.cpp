#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

int priority(char a);

int main()
{
    char letter;
    stack<char> operand;
    string output;
    while (cin.get(letter) && letter != '\n')
    {
        switch (letter)
        {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                while (!operand.empty() && priority(letter) < priority(operand.top()))
                {
                    output += operand.top();
                    operand.pop();
                }
                operand.push(letter);
                break;

            case '(':
                operand.push(letter);
                break;

            case ')':
                while (operand.top() != '(')
                {
                    output += operand.top();
                    operand.pop();
                }
                operand.pop();
                break;

            default:
                output += letter;
        }
    }
    while (!operand.empty())
    {
        output += operand.top();
        operand.pop();
    }

    cout << output << endl;
}

int priority(char a)
{
    switch (a)
    {
        case '+':
        case '-': return 1;

        case '*':
        case '/': return 2;

        case '^': return 3;
    }
    return 0;
}
