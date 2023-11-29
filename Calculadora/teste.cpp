#include <iostream>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;

char display[] = "10.8/2.4 ";

int isOperator(char key)
{
  if(key == '+' || key == '-' )
    return 1;
  if(key == '*' || key == '/')
    return 2;
  return 0;
}

bool isNumber(char c) {
    return c >= '0' && c <= '9' || c == '.';
}
 
void toposfix(stack<char> &pilha, stack<double> &fila)
{
  int start = 0;
  char op;
  double num = 0;
  float decimalPlace = 0.1;
  bool isDecimal = false;
  bool isNegative = false;

  while(display[start] != ' ')
  {
    if(isOperator(display[start]) && isNumber(display[start-1]))//entra se for operador
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
      isDecimal = false;
      isNegative = false;
      decimalPlace = 0.1;
      
      if (display[start] == '-')
      {
        isNegative = true;
        start++;
      }

      while (isNumber(display[start])) {
        if (display[start] == '.')
        {
          isDecimal = true;
          start++;
        }

        if (!isDecimal && !isNegative)
          num = num * 10 + (display[start] - '0');
        
        else if (isNegative) {
          num = num * 10 + (display[start] - '0');
          num = num * -1;
        }else if (isDecimal) {
          num = num + (display[start] - '0') * decimalPlace;
          decimalPlace *= 0.1;
        }
        start++;
      }
      fila.push(num);
    }
  }
}

double solve()
{
  int start = 0;
  double numA, numB;
  numA = numB = 0;
  char op;
  stack<char> operand;
  stack<double> number;
  toposfix(operand, number);
  numA = number.top();
  number.pop();
  while(!number.empty() && !operand.empty())
  {
    numB = number.top();
    number.pop();
    op = operand.top();
    operand.pop();
    if(op == '+')
      numA = numA + numB;
    else if(op == '-')
      numA = numA - numB;
    else if(op == '*')
      numA = numA * numB;
    else if(op == '/')
      numA = numB / numA;
  }
  return numA;
}

int main() {
    //print the display here
    printf("Display: %s\n", display);
    printf("%f\n", solve());
    return 0;
}