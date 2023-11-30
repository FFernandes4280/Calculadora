#include <iostream> //Inutil, uso serial

using namespace std;

char display[] = "2.5*1.73+55/2+1 ";

struct fila
{
  double num;
  char op;
}typedef Fila;

char stack[16];
Fila queue[16];
int stackIndex = 0; //topo da pilha
int queueFront = 0;
int queueRear = 0;

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

void push(char op) {
  if(isOperator(stack[stackIndex]))
  {
    stackIndex++;
    stack[stackIndex] = op;
  }
  else
  {
    stack[stackIndex] = op;
  }
}
char pop() {
  char op = stack[stackIndex];
  if(stackIndex == 0)
    stack[stackIndex] = ' ';
  else 
  {
    stack[stackIndex] = ' ';
    stackIndex--;
  }
  return op;
}

void enqueue(double value, char op) {
  queue[queueRear].num = value;
  queue[queueRear].op = op;
  queueRear++;
}

int dequeue() {
  if (queue[queueFront].op == ' ')
    return queue[queueFront++].num;  

  else
    return queue[queueFront++].op;
}
 
void shiftQueue(int start, double num) {
  int stop = start - 2;
  queue[stop].num = num;
  queue[stop].op = ' ';  
  while(queue[stop].op != '\000')
  {
    queue[stop+1].num = queue[stop+2].num;
    queue[stop+1].op = queue[stop+2].op;
    stop++;
  }
  stop = start - 2;  
  while(queue[stop].op != '\000')
  {
    queue[stop+1].num = queue[stop+2].num;
    queue[stop+1].op = queue[stop+2].op;
    stop++;
  }
  queueRear -= 2;
} 

void empilhar(int start, char *op)
{
  if(!isOperator(stack[stackIndex]))
  {
    push(display[start]);
    return;
  }
  else
  {
    if(isOperator(stack[stackIndex]) < isOperator(display[start]))
    {
      push(display[start]);
      return;
    }
    else
    {
      *op = pop();
      enqueue(0, *op);
      empilhar(start, op);
    }
  }
}

void toposfix() //stack e queue são variaveis globais
{
  int start = 0;
  double num = 0;
  char op = ' ';
  float decimalPlace = 0.1;
  bool isDecimal = false;
  bool isNegative = false;

  while(display[start] != ' ')
  {
    if(isOperator(display[start]) && isNumber(display[start-1]))
    {
      empilhar(start, &op);
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
      enqueue(num, ' ');
    }
  }
  
  while(isOperator(stack[stackIndex]))
  {
    op = pop();
    enqueue(0, op);
  }
}

double solve()
{
  int start = 0;
  double numA, numB;
  numA = numB = 0;
  char op;
  toposfix(); 
  while(queueRear - queueFront > 1)
    {
      start = 0;
      while(queue[start].op == ' ')
        start++;

      numA = queue[start-2].num;
      numB = queue[start-1].num;
      op = queue[start].op;
      if(op == '+')
        numA = numA + numB;
      else if(op == '-')
        numA = numA - numB;
      else if(op == '*')
        numA = numA * numB;
      else if(op == '/')
        numA = numA / numB;
    shiftQueue(start, numA);
  }
return numA;
}

int main() {
    //print the display here
    printf("Display: %s\n", display);
    printf("%f\n", solve());
    return 0;
}