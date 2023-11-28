#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

char display[] = "2+3*4";

bool isOperator(char key)
{
  if(key == '+' || key == '-' )
    return 0;
  if(key == '*' || key == '/')
    return 1;
  return 2;
}

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}
 
void toposfix(char posfix[])
{
  int start = 0;
  char op;
  char num;
  stack<char> pilha;
  queue<char> fila;

  while(display[start] != ' ')
  {
    if(isOperator(display[start]))
    {
      if(pilha.empty())
        pilha.push(display[start]);
      else
      {
        if(isOperator(pilha.top()) < isOperator(display[start]))
          pilha.push(display[start]);
        else
        {
          while(!pilha.empty() && isOperator(pilha.top()) >= isOperator(display[start]))
          {
            op = pilha.top();
            pilha.pop();
            fila.push(op);
          }
          pilha.push(display[start]);
        }
      }
    }
    else if(isNumber(display[start]))
    {
      while(isNumber(display[start]))
      {
        num = num * 10 + (display[start] - '0');
        start++;
      }
      fila.push(num);
    }
    else if(display[start] == '(')
      pilha.push(display[start]);
    else if(display[start] == ')')
    {
      while(pilha.top() != '(')
      {
        op = pilha.top();
        pilha.pop();
        fila.push(op);
      }
      pilha.pop();
    }
  }
}

int main() {
    //print the display here
    printf("Display: %s\n", display);
    char test[] = "2+3*4";
    toposfix(test);
    // Check the result here
    printf("Display: %s\n", test);
    return 0;
}