#include <iostream> //Inutil, uso serial

using namespace std;

struct fila
{
  double num;
  char op;
}typedef Fila;

char stack[16];
Fila queue[16];
int stackIndex = 0;
int queueFront = 0;
int queueRear = 0;

void print(){
  printf("\n");
 for (int i = queueFront; i < queueRear; i++) {
    printf("Elemento%d-> Num:%f Opr:%c",i, queue[i].num, queue[i].op);
    printf("\n");
  }
  
}
void push(char op) {
  stack[stackIndex++] = op;
}

char pop() {
  return stack[--stackIndex];
}

void enqueue(double value, char op) {
  queue[queueRear++].num = value;
  queue[queueRear++].op = op;
}

int dequeue() {
  if (queue[queueFront].op == ' ')
    return queue[queueFront++].num;  
  else
    return queue[queueFront++].op;
}

char display[] = "2+3+5 ";

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
 
void toposfix() //stack e queue são variaveis globais
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
      if(stackIndex == 0)
        push(display[start]);
    
      else
      {
        if(isOperator(stack[stackIndex]) < isOperator(display[start]))
          push(display[start]);
        else
        {
          while(!stackIndex && isOperator(stack[stackIndex]) >= isOperator(display[start]))
            enqueue(0, pop());
          
          push(display[start]);
        }
      }
      start++;
      print();
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
      print();
      enqueue(num, ' ');
    }
  }
  
  while(!(stackIndex+1))
    enqueue(0, pop());
}

double solve()
{
  int start = 0;
  double numA, numB;
  numA = numB = 0;
  char op;
  toposfix();
  print();
  numA = dequeue();
  while(!(queueRear-queueFront) && !stackIndex)
  {
    numB = dequeue();
    op = dequeue();

    if(op == '+')
      numA = numA + numB;
    else if(op == '-')
      numA = numA - numB;
    else if(op == '*')
      numA = numA * numB;
    else if(op == '/')
      numA = numA / numB;
  }
  return numA;
}

int main() {
    //print the display here
    printf("Display: %s\n", display);
    printf("%f\n", solve());
    return 0;
}