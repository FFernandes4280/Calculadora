#include <LiquidCrystal.h>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
char display[16];
int i = 0;

void reset(int clear)
{
  i = 0;
  for (int clear = 0; clear < 16; clear++) {
    display[clear] = ' ';  
  }
}
int isNumber(char key)
{
  return key >= '0' && key <= '9' || key == '.';
}
bool isOperator(char key)
{
  return (key == '+' || key == '-' || key == '*' || key == '/');
}
int Precedence(char key) {
  if (key == '+' || key == '-')
    return 1;
  else if (key == '*' || key == '/')
    return 2;
  return 0;
}

queue<char> shuntingYard(const string& infix) {
  queue<char> outputQueue;
  stack<char> operatorStack;

  for (char c : infix) {
    if (isalnum(c))// If the character is a number or variable
      outputQueue.push(c);
    else if (isOperator(c)) { // If the character is an operator
            while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(c)) {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(c);
        } else if (c == '(') { // If the character is an opening parenthesis
            operatorStack.push(c);
        } else if (c == ')') { // If the character is a closing parenthesis
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop(); // Pop the '('
        }
    }

    // Pop remaining operators from the stack to the output queue
    while (!operatorStack.empty()) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
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
  int num;
  if(Serial.available())
  {
  	char key = Serial.read();
    if(key == '=')
    {
      num = read(0);
      lcd.clear();
      lcd.setCursor(0,0);
      reset(0);
      lcd.print(num);
      while(num>0)
  		{	
			for (int j = i; j > 0; j--)
            	display[j] = display[j - 1];
        	
        	Serial.println(num);
    		display[0] = num % 10 + '0';
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
