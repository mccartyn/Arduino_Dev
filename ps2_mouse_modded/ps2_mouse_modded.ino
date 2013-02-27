#include <ps2.h>
#include <SimpleMessageSystem.h>

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
  Serial.begin(115200);
  mouse_init();
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

if (messageBuild()) { // Checks to see if the message is complete 
      firstChar = messageGetChar(); { // Gets the first word as a character 

     if (firstChar = 'r') { // Checking for the character 'r' 
          secondChar = messageGetChar(); // Gets the next word as a character 
          if (firstChar = 'd') // The next character has to be 'd' to continue 
               messageSendChar('d');  // Echo what is being read 

//       for (int i=0;i<=5;i++) { 
//       messageSendInt(analogRead(i)); // Read analog pins 0 to 5
//          }
//
//       for (int m=2;m<=12;m++) { 
//       messageSendInt(digitalRead(m)); // Read digital pins 2 to 12, 13 is onboard LED on Arduino NG
//          }
      messageSendInt(mx);
      messageSendInt(my);
            
       messageEnd(); // Terminate the message being sent 
       
          
                    } 
      }
   }

  /* send the data back up */
  //Serial.print(mstat, BIN);
  //Serial.print("\tX=");
  //Serial.print(mx, DEC);
  //Serial.print("\tY=");
  //Serial.print(my, DEC);
  //Serial.println();
  
//  delay(20);  /* twiddle */
}
