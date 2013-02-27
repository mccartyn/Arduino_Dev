//Nick McCarty

//These pins are currently controlling Scene 1 inside lights
int BluePin6 = 6;                   // Digital Pin 9 Connected to B on Amp
int GreenPin5 = 5;                 // Digital Pin 10 Connected to G on Amp
int RedPin3 = 3;                   // Digital Pin 11 Connected to R on Amp

//These pins are currently controlling Scene 2 and 3 outside lights
int BluePin11 = 11;                   // Digital Pin 9 Connected to B on Amp
int GreenPin10 = 10;                 // Digital Pin 10 Connected to G on Amp
int RedPin9 = 9;                   // Digital Pin 11 Connected to R on Amp


  //Current global color variables
int g_curR_o1; //current outside scene 1 colors
int g_curG_o1 = 255;
int g_curB_o1 = 255;

int g_curR_o2 = 255; //current outside scene 2 colors
int g_curG_o2 = 255;
int g_curB_o2 = 255;

int g_curR_i1 = 255; //current inside scene 1 colors
int g_curG_i1 = 255;
int g_curB_i1 = 255;


enum SCENE{
  scene1 = 0,
  scene2 = 1,
  scene3 = 2};

enum SCENE curScene;

void setup()
{
  pinMode(BluePin6, OUTPUT);      // sets the digital pin as output
  pinMode(GreenPin5, OUTPUT);      // sets the digital pin as output
  pinMode(RedPin3, OUTPUT);      // sets the digital pin as output
  pinMode(BluePin11, OUTPUT);      // sets the digital pin as output
  pinMode(GreenPin10, OUTPUT);      // sets the digital pin as output
  pinMode(RedPin9, OUTPUT);      // sets the digital pin as output

  digitalWrite(BluePin6, HIGH);
  digitalWrite(GreenPin5, HIGH);
  digitalWrite(RedPin3, HIGH);
  digitalWrite(BluePin11, HIGH);
  digitalWrite(GreenPin10, HIGH);
  digitalWrite(RedPin9, HIGH);
  
  
}

void loop()
{

  
  
  curScene = scene1;
  fadeToColorRGB(g_curR_i1, g_curG_i1, g_curB_i1, 100, 150, 255);
  
  curScene = scene2;
  fadeToColorRGB(g_curR_o2, g_curG_o2, g_curB_o2, 255, 150, 130);
  
  curScene = scene1;
  fadeToColorRGB(g_curR_i1, g_curG_i1, g_curB_i1,50, 100, 255);
  
  curScene = scene2;
  fadeToColorRGB(g_curR_o2, g_curG_o2, g_curB_o2,220, 100, 100);
  
   curScene = scene1;
  fadeToColorRGB(g_curR_i1, g_curG_i1, g_curB_i1,220, 220, 255);
  
   curScene = scene2;
  fadeToColorRGB(g_curR_o2, g_curG_o2, g_curB_o2,255, 140, 180);
 
  curScene = scene1;
  fadeToColorRGB(g_curR_i1, g_curG_i1, g_curB_i1,50, 125, 255);
  
  curScene = scene2;
  fadeToColorRGB(g_curR_o2, g_curG_o2, g_curB_o2,220, 100, 100);
 

}
  
  
void fadeToColorRGB(int &curR, int &curG, int &curB, int R, int G, int B)
{
  
  //Start moving colors to their target color
  while(1)
  {
    if(curR == R && curG == G && curB == B)
      break;
      if(curR < R)
        curR++;
      else if (curR > R)
        curR--;   
      
      if(curG< G)
        curG++;
      else if(curG > G)
        curG--; 
      
      if(curB < B)
        curB++;
      else if(curB > B)
        curB--; 
        
      switch(curScene)
      {
        case scene1:
          analogWrite(RedPin3, curR);
          analogWrite(GreenPin5, curG);
          analogWrite(BluePin6, curB);
          delay(30);
        break;
        case scene2:
          analogWrite(RedPin9, curR);
          analogWrite(GreenPin10, curG);
          analogWrite(BluePin11, curB);
          delay(30);
        break;
        case scene3:
          analogWrite(RedPin9, curR);
          analogWrite(GreenPin10, curG);
          analogWrite(BluePin11, curB);
          delay(30);
        break;
        default:
        break;
      
      }
  }
  
  
}
  
