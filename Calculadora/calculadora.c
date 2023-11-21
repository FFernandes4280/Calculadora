// C++ code
//
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
char display[16];
int i = 0;

void reset(int clear)
{
  i = 0;
  for (int clear = 0; clear < 16; clear++) {
    Serial.println(display[clear]);  // Use display[clear] instead of display[i]
  }

  for (int clear = 0; clear < 16; clear++) {
    display[clear] = ' ';  // Reset each element to ''
  }
}
int isNumber(char key)
{
  return key >= '0' && key <= '9';
}
int read(int start)
{
  if(start >= 16)
    return 0;
  
  int numA = 0;
  int numB = 0;
  
  while(isNumber(display[start]))
  {
    numA = numA * 10 + (display[start] - '0');
    start++;
  }
  char op = display[start];
  start++;
  numB = read(start);
  if(op == '+')
    numA = numA + numB;
  else if(op == '-')
    numA = numA - numB;
  else if(op == '*')
    numA = numA * numB;
  else if(op == '/')
    numA = numA / numB + (numA % numB > 0);
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
