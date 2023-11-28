#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

char display[] = "2+38*4.1 ";

int isOperator(char key)
{
  if(key == '+' || key == '-' )
    return 1;
  if(key == '*' || key == '/')
    return 2;
  return 0;
}

bool isNumber(char c) {
    return c >= '0' && c <= '9';
}
 
void toposfix(stack<char> pilha, queue<double> fila)
{
  int start = 0;
  char op;
  double num = 0;
  float decimalPlace = 0.1;
  bool isDecimal = false;
  isDecimal = false;

  while(display[start] != ' ')
  {
    if(isOperator(display[start]))//entra se for operador
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
      start++;
    }
    else //entra se for numero
    {
      num = 0;
      while (isNumber(display[start])) {
        if (display[start] == '.') {
          isDecimal = true;
          start++;
          continue;
        }
        if (!isDecimal) {
          num = num * 10 + (display[start] - '0');
        } else {
          num = num + (display[start] - '0') * decimalPlace;
          decimalPlace *= 0.1;
        }
        start++;
      }
      fila.push(num);
    }
  }

  while(!fila.empty())
  {
    printf("%f ", fila.front());
    fila.pop();
  }
  printf("\n");
  while (!pilha.empty()) {
    printf("%c ", pilha.top());
    pilha.pop();
  }
}

int main() {
    //print the display here
    printf("Display: %s\n", display);
    stack<char> pilha;
    queue<double> fila;
    toposfix(pilha, fila);
    return 0;
}