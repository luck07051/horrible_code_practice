#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cctype>
using namespace std;

const string file_name {"temp.txt"};

int priority(char a);
void calculate(stack<double> &va, char op);
bool is_operand(char ch);

int main()
{
    stack<char> operand;
    stack<double> value;
    map<char, double> variable;

    // temp variable
    char letter;
    double number;

    // keyborad to txt
    {
        fstream fout {file_name, ios::out | ios::trunc};
        string input;
        cout << "Enter expression: ";
        getline(cin, input);
        fout << input;
        fout.close();
    }


    fstream file {file_name, ios::in};
    unsigned int variable_number = 0;
    do
    {
        while (file.peek() != EOF)
        {
            // delete ' '
            if (file.peek() == ' ')
            {
                file.get();
            }
            // for number
            else if (isdigit(file.peek()))
            {
                file >> number;
                value.push(number);

                if (file.peek() != EOF && !is_operand(file.peek()))
                {
                    operand.push('*');
                }
            }
            // for character
            else
            {
                file >> letter;
                switch (letter)
                {
                    case '+': case '-': case '*': case '/': case '^':
                        while (!operand.empty() && priority(letter) <= priority(operand.top()))
                        {
                            calculate(value, operand.top());
                            operand.pop();
                        }
                        operand.push(letter);
                        break;

                        // special character
                    case 'l':
                        if (file.peek() == 'n') // ln
                        {
                            file.get();
                            operand.push('l');
                            break;
                        }

                    default:
                        if (variable.find(letter) == variable.end())
                        {
                            ++variable_number;
                            cout << letter << ": ";
                            cin >> number;
                            if (!cin)
                            {
                                return 0;
                            }
                            variable[letter] = number;
                            value.push(number);
                        }
                        else
                        {
                            value.push(variable[letter]);
                        }
                        if (file.peek() != EOF && !is_operand(file.peek()))
                        {
                            operand.push('*');
                        }
                        break;


                    case '(':
                        operand.push(letter);
                        break;

                    case ')':
                        while (operand.top() != '(')
                        {
                            calculate(value, operand.top());
                            operand.pop();
                        }
                        operand.pop();
                        break;
                }
            }
        }
        while (!operand.empty())
        {
            calculate(value, operand.top());
            operand.pop();
        }

        cout << "Solution: " << value.top() << endl;
        value.pop();
        variable.clear();

        file.clear();
        file.seekg(0, ios::beg);

    } while (variable_number != 0);

    file.close();
    return 0;
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

        default : return 0;
    }
}

void calculate(stack<double> &va, char op)
{
    double a, b;
    b = va.top();
    va.pop();

    switch (op)
    {
        case 'l':
            va.push(log(b));
            return;
    }

    a = va.top();
    va.pop();

    switch (op)
    {
        case '+':
            va.push(a+b);
            return;
        case '-':
            va.push(a-b);
            return;
        case '*':
            va.push(a*b);
            return;
        case '/':
            va.push(a/b);
            return;
        case '^':
            va.push(pow(a, b));
            return;
    }
}

bool is_operand(char ch)
{
    switch (ch)
    {
        case '+': case '-': case '*': case '/': case '^': case ')':
            return true;

        default:
            return false;
    }
}
