#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

struct fila
{
  double num;
  char op;
}typedef Fila;

char display[16];
int i = 0;
char stack[16];
Fila queue[16];
int stackIndex = 0; //topo da pilha
int queueFront = 0;
int queueRear = 0;

void reset(int clear)
{
  memset(display, ' ', sizeof(display));
}
bool isNumber(char key)
{
  if (key >= '0' && key <= '9' || key == '.')
    return true;
  else
    return false;
}
int isOperator(char key)
{
  if(key == '+' || key == '-' )
    return 1;
  if(key == '*' || key == '/')
    return 2;
  return 0;
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

void setup()
{
  Serial.begin(9600);
  
  lcd.begin(16, 2);		//inicializa
  lcd.setCursor(0, 0);	//coloca o cursor em (0, 0)
  lcd.clear();			//limpa a tela
}

void loop()
{
  double num;
  if(Serial.available())
  {
  	char key = Serial.read();
    if(key == '=')
    {
      num = solve(); // resolve a operação	
      lcd.clear();
      lcd.setCursor(0,0);
      reset(0);
      lcd.print(num);
      while(num>0)
  		{	
			  for (int j = i; j > 0; j--) //shift para a direita
          display[j] = display[j - 1];
    	  display[0] = num % 10 + '0';//transcreve a resposta para ser usada nas proximas operações
        num = num / 10;
    		i++;
  		}
    }
    else
    {
      if(key == 'C')
      {
        reset(0);
        lcd.clear();
        lcd.setCursor(0,0);
      }
      else
      {
        display[i]= key;
        i++;
  	    lcd.write(key);
      }
    }
  }
}
