#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
char display[16];
int i = 0;

void reset(int clear)
{
  i = 0;
  for (int clear = 0; clear < 16; clear++)
    display[clear] = ' ';  // Reset each element to blank
}
bool isNumber(char key)
  return key >= '0' && key <= '9' || key == '.';

bool isOperator(char key)
{
  if(key == '+' || key == '-' )
    return 0;
  if(key == '*' || key == '/')
    return 1;
  return 2;
}


double solve()
{
  int start = 0;
  double numA, numB;
  char op;
  toposfix(posfix);//precisa tratar para juntar os numeros em uma casa só
  numA = posfix[start];
  start++;
  while(posfix[start] != ' ')
  {
    numB = posfix[start];
    start++;
    op = posfix[start];
    start++;
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
