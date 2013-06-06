unsigned long oldPressTime = 0;
boolean oneClick = false;

void clickHold(){}
void singleHold(){Serial.println("Single Hold");}
void doubleHold(){Serial.println("Double Hold");}

void doubleHoldUp(){Serial.println("double Hold Finish");}
void singleHoldUp(){Serial.println("single Hold Finish");}

void clickDown(){}
void firstDown(){Serial.println("single Click");}
void doubleDown(){Serial.println("double Click");}

void clickUp(){}
void firstUp(){Serial.println("single Up");}
void doubleUp(){Serial.println("double Up");}

void soloUp(){Serial.println("solo click");}

void clickWatcher(byte pin)
{
  static const int doubleWait = 400;
  static const int holdDelay = 500;
  static const int debounce = 150;
  static unsigned long pressTime;
  static boolean clicked;
  static boolean doubleClick;
  static boolean holdFlag;
  static boolean doubleFlag = false;
  
  boolean pinStatus = digitalRead(pin);
  
  if(pinStatus && millis()-pressTime>debounce)
  {
    if (!clicked && !doubleClick && millis()-pressTime<doubleWait && !holdFlag)
    {
      doubleClick= true;
      doubleFlag=true;
    }
    if (clicked && (millis()-pressTime)>holdDelay)
    {
      holdFlag = true;
      clickHold();
      if(doubleClick) doubleHold();
      else singleHold();
    }
    else if(!clicked)
    {
      clickDown();
      clicked = true;
      holdFlag=false;
      pressTime = millis();
      if(doubleClick) doubleDown();
      else firstDown();
    }
  }
  else if(clicked && millis()-pressTime>debounce)
  {
    clickUp();
    if(holdFlag)
    {
      if(doubleClick) doubleHoldUp();
      else {
        singleHoldUp();
        doubleFlag = true;
      }
    }
    else
    {
      if(doubleClick) doubleUp();
      else {
        firstUp();
        doubleFlag = false; 
      }
    }
    clicked=false;
    doubleClick=false;
  }
  else if(!doubleFlag && millis()-pressTime>doubleWait){soloUp(); doubleFlag = true;}
}


void setup()
{
  Serial.begin(9600);  
}

void loop()
{
  clickWatcher(2);  
}
