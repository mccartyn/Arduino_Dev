#include <ps2.h>
#include <PureData.h>

/*
 * an arduino sketch to interface with a ps/2 mouse.
 * Also uses serial protocol to talk back to the host
 * and report what it finds.
 */

/*
 * Pin 5 is the mouse data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
PS2 mouse(6, 5);

char firstChar; 
char secondChar;
int debouce = 0;

/*
 * initialize the mouse. Reset it, and place it into remote
 * mode, so we can get the encoder data on demand.
 */
void mouse_init()
{
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
}

void setup()
{
  //Serial.begin(115200);
  mouse_init();
  // Have the PureData library setup
  PureData.begin(); 
}

/*
 * get a reading from the mouse and report it back to the
 * host via the serial line.
 */
void loop()
{
  char mstat;
  char mx;
  char my;
 

  /* get a reading from the mouse */
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  mx = mouse.read();
  my = mouse.read();

if((mstat != 8) && (debouce == 0))
{
  //need some sort of debouce
  debouce = 20;
  PureData.send("mstat",mstat);
}
if(mx != 0)  
  PureData.send("mx",mx);
if(my != 0)
  PureData.send("my",my);
  
  if(debouce > 0)
    debouce--;
 // delay(20);  /* twiddle */
}
