/*========  Proforma : DC Motor Control ===================================

File version: 2016_v01.0

PURPOSE     This file is a proforma for the DC Motor assignment and it is the
only document which states the requirements you must achieve.
You must extend this C++ program to cope with the functionality
identified below.

GOAL        You will go through 4 distinct steps to achieve speed control of
a small DC motor using Pulse Width Modulation.
The first 3 steps do not need a DC motor and will get you 100%.
The final step is bonus marks and requires you to provide a
plug pack DC power supply and a small DC motor.

MARKING     Marking has several components-
- commands P, A, and L will be tested using the auto-tester.
- command M will be marked by the tutor in the lab test.
- any time after the lab test you may be asked to
explain the code you wrote in that lab test.  If you cannot
make a good explanation of the code then your mark will be
adjusted downward,  to zero if you cannot explain anything.
This will be done at random and students may face from zero
to four "explain" tests.


SCHEMATIC FOR COMMANDS P, A and L
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following circuitry has been already added to a standard Open-USB-IO board.


Your C++ Program     OUSB      .  Components Soldered onto Prototype Area
on the PC            Board     .
-------------------------------+--------------------------------------------
.    J5 pin 37 --- J5 pin 39 (+5v)
.    |
.   |"| 1kohm load
Create a square wave           .   |_|
ousb pwm 1 ...                .    |      47 kohm
|"|___|"|___| -->-- J5 ------>---+---[\\\]---+
pin 27 .                |
.        +-------+----+
Read the ADC                   .        |       |    | +
ousb adc 0 ...   --<-- J5 ------<------+      |"|  ===  10 uF
pin 1  .          22   |_|   |
.          kohm  |    |
.                +----+-- J5 any even pin, 0v
.

This circuit is a simple control loop.
* The ousb board uses the PWM command to generate a square wave on
pin PB3 of the microprocessor,  which is connected to the LED3 (on PORTB),
and to the inverting buffer which outputs on connector J5 pin 27.
The command "ousb pwm-freq 1 ..." sets the frequency.
The command "ousb pwm 1 ..." sets the duty cycle.
Details can be found in chapter 6 of the Open-USB-IO manual.

* When the PWM output goes high, LED3 is turned on and pin 27 of J5
goes low thus pulling current through the load resistor (and later
the motor).
When the PWM output goes low then LED3 is turned off,  and pin 27 of J5
acts as an open circuit thus no current flows through the load resistor.
The PWM runs at 46 Hz so the human eye cannot see LED flicker.
The average current delivered to the load is roughly-
full_power_current * PWM_fraction_on_time

* The 47 kohm resistor and 22 kohm resistor form a voltage divider-
(Voltage on J5 pin 1) = (Voltage on J5 pin 27) * 22 / (22 + 47)
The capacitor acts to smooth any voltage bumps from the square wave
so J5 pin 1 sees a nice smooth voltage level, the resistors and
capacitor thus form a low pass filter.

* J5 pin 1 is connected to an analogue to digital converter on the board.
This converts the voltage to a number,  0 means 0 volts, 1023 means
+5v volts.

* Your C++ program can act as a control loop which has the aim of getting
the ADC read value to a desired target setting.
Your code can set an initial PWM value, say 50%.  It can read the ADC
value,  if this does not match the target then the PWM duty cycle can
be moved up or down 1% at a time.  After several loops the ADC read
value should be close to the target value.



SPECIFIC REQUIREMENTS FOR COMMANDS P, A , and L
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The P command just sets the PWM duty cycle,  the A command just reads the
analogue voltage on J5 pin 1.  The L command puts these two together to
form a control loop.

* In general detect errors in the order they are listed below and respond
as required.

* Any number required in an output should be an integer
unless otherwise stated.

* The command line may have no parameters and the program will
identify who you are. See the cout statement after main().
If you make a mistake here your mark will be reduced by 10%.

* Do NOT test for whether the Open-USB-IO board is properly plugged in.

* If there is not exactly two parameters after the program name then
the output shall be the single character 'P' then a newline.

* The first parameter may be only one of the letters P, A, L or M.
If it is anything else the output shall be the single character
'I' then a newline.

* The second parameter must be a number between 0 and 1023 inclusive.
If there is an error the output shall be the single character
'R' then a newline.

* If the first parameter is P then take the second parameter
as the duty cycle which must be between 0 and 100 inclusive.
If there is a problem output the single letter 'r' then a newline.
If there is not a problem send commands to the Open-USB-IO
board to set the frequency to 46 Hz, and the duty cycle to
the value defined by the second parameter, and then output
the single letter 'p' and a newline.

* If the first parameter is A then the second parameter should
be an ADC channel number 0 to 7 inclusive.
If this is wrong output 'a' then newline.
If the ADC channel is OK then use the 'ousb adc' command to
read the voltage and print the value to the output and a newline.

* If the first parameter is L then the second parameter must be
the target ADC read value that the control loop is trying to
achieve. This command implements the control loop:
- Before the loop starts you must set the pwm frequency
to 46 Hz.
- The loop shall have 60 iterations.
- On the first loop the pwm duty cycle must set to 50%.
- After setting the PWM duty cycle then you must read ADC 0.
If the value read does not match the target value then
the next PWM duty cycle may be set to +1 or -1 of
its current value.
- The PWM duty cycle must remain between 0 and 100 inclusive.
- When your loop terminates you must print out the last
PWM duty cycle you sent in the PWM command then a newline
(just the number, no % symbol). Do not print out any other
characters.
- Do not issue any more "ousb" commands when the loop terminates
so the PWM is left working. The autotester will read the board
to determine if your program has achievied the correct control
value.


SCHEMATIC FOR COMMAND M
~~~~~~~~~~~~~~~~~~~~~~~~~~
This part of the lab is for bonus marks and uses a real DC motor and
power supply that you must provide.


Your C++ Program     OUSB      .  Components Soldered onto Prototype Area
on the PC            Board     .
-------------------------------+--------------------------------------------
.    J5 pin 37 ---------+--- (Ext DC Supply)
.    |                  |
.    |              .---+---.
.   |"| 1kohm       | motor |
.   |_|  load       '---+---'
.    |                  |
.    +------------------+
ousb pwm 1 ...                 .    |      47 kohm
|"|___|"|___| -->-- J5 ------>---+---[\\\]---+
pin 27 .                |
.        +-------+----+
.        |       |    | +
ousb adc 0 ...    --<-- J5 ------<------+      |"|  ===  10 uF
pin 1  .          22   |_|   |
.          kohm  |    |
.                +----+-- J5 any even pin, 0v


* In this circuit the link to the onboard +5v is removed and DC plug
pack is plugged into the board.  A small DC motor is put in parallel
with the load resistor.

* When the PWM on LED3 goes high pin 27 J5 goes low, current flow through
the motor and drives it.



SPECIFIC REQUIREMENTS FOR COMMAND M
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The M command is a control loop very much like the L command.

* This part of the lab is for bonus marks and will be marked by the
tutor in the lab test session.

* The autotester will not test for the M command, so it would be wise
to get previous commands fully working and submitted your solution
before working on this part of the lab test.

* You must supply the DC motor and an external DC plug pack and your
own OUSB board to do this part of the test.

*	The motor must be rated at no more than 500 ma even if stalled.
The plug pack may be up to 12 volts and may be the cheaper
"unregulated" type. The plug pack must plug into the DC socket
on the Open-USB-IO.

* It is allowed for students to share a DC plug pack and motor and OUSB
board. Students in the same lab session are strongly advised to have
their own equipment and for it to be ready to use in the lab without
any major setting up or wiring.

* The M command is much like the L command but the loop runs forever
until control-C is pushed from the keyboard. Start creating the
code with a cut and paste of the L command, as there are only a
few changes that need to be made.

* At the end of each loop you shall print the line-
Target ADC0= zzzz,  Actual ADC0= yyyy,  Next PWM%= xxx
Where zzz,yyyy, and xxx are numbers.

* Work out the maximum and minimum values the ADC will see.
Given your program name is named myProgram.exe try-
myProgram.exe P 100  // motor at full.
myProgram.exe A 0    // read ADC value.
myProgram.exe P 0    // motor stopped.
myProgram.exe A 0    // read ADC value.

* Take the average of the two ADC readings to provide a good ADC
target value and start your program-
myProgram.exe M average_value
After the speed settles write down the PWM value.
Now put your finger on the motor spindle to slow it down.
Note the PWM duty cycle go up.
Remove your finger and note the PWM value go down again.
Hit ctrl-C to stop your program.

* Now set the motor going using the PWM value noted above.
myProgram.exe P PWM_value
Now apply you finger to the spindle and note that it
slows down much more than when using your M command.

* What does the tutor want to see to mark you?
The two points above.
The tutor will note if it worked or did not work.

* If you get this far congratulations you have achieved basic
speed control of a DC motor!


OTHER REQUIREMENTS
~~~~~~~~~~~~~~~~~~~

* This program must be in one file named lab2_X.cpp
where X is your student number.
For testple : lab2_1234567.cpp
Failure to correctly name your file will result in
10% being deducted from your mark.

* If exit() or return() is used to terminate the program they
must always return 0.
The main function must be the last function in the file.




HELPFUL HINTS
~~~~~~~~~~~~~~~
* If the motor is left going after a command and is annoying just
hit the reset switch on the microprocessor to stop it.

* To thoroughly test your program hit the reset switch on
Open-USB-IO then run your program.  This will ensure you
have initialized the board properly.  Ignore the usual
error message the first time Open-USB-IO is accessed after a
reset.

* Debugging the L command could be difficult and it is strongly
suggested that in development you print out a line
of information at the end of the loop-
Loop# ww,  ADC target= xx,  ADC read yy,  Next PWM zz
where ww,xx,yy and zz are numbers.
Make sure you remove or comment out this code before submitting!

* If your loop saturates the PWM at 0% or 100% try swapping the
sign when you do a +- 1% change to the PWM.
Also try changing the target value.  See the M command for
choosing a workable target for the ADC read value.
Note how to work out the range of achievable ADC values
described above.

* The Lab test 2 proforma (i.e., this file) and the following code to
interface with the OUSB board will be provided in the Lab test.


EXTENSION WORK AND THOUGHTS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Read this section if you are interested in motor control.

* DC motors with permanent magnet fields turn into generators when
the power is removed and they are still moving.
With a 46 Hz PWM the off period is small and the motor
doesn't slow down and so it becomes a generator.

* Brushed DC motors in motor mode, and especially in generator
mode, create lots of electrical noise on the power supply.
If the motor runs from the same supply at the microprocessor
then the microprocessor will probably crash.

* If you have used SPICE, try simulating the 2 resistors and
capacitor to see what how the PWM square wave is turned into
a smooth waveform.

* The M command uses the voltage on J5 pin 1 as a measure of speed.
A better measure is the voltage across the motor during
its off period when the motor is acting as a generator.
If good speed control is desired this will give a better
result.  Both methods are imperfect but give a useful level
of speed control.
Can you work out how to calculate the voltage across the
motor in generator mode?  Can you code it?

* The PWM drive pin used is PB3 but buffered by an Open-Collector
transistor (Google this term).  The open collector acts like
a switch and can be either a short to zero volts or an open circuit.
The open collector used can cope with 500ma and up to 50 volts.
Open-USB-IO has 7 of these can can be used to drive a variety of
motors and other devices.

* The voltage spikes from the motor could destroy the ADC input pin
on the microprocessor if it were directly connected to it. The
47 kohm resistor acts as a current limit,  and the capacitor helps
to smooth out the spikes into a small bump.

* See the following web links to learn more-
http://en.wikipedia.org/wiki/Electric_motor
http://en.wikipedia.org/wiki/Brushed_DC_electric_motor
http://tldp.org/LDP/LGNET/179/radcliffe.html
( Note the control loop in the article above will not
meet the requirements of this lab, do not use it.)



GENERAL INFORMATION AND HINTS
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* A plagiarism detector will be used on all student code so don't
bother copying.
The test will focus on project work so copying is a stupid idea
because you wont be able to do the test.

* Marking will result from testing your program against a whole
range of inputs.  The secret to getting a good mark is to
carefully analyse all possible errors and odd situations
BEFORE you write the code so read the project definition VERY
carefully.  Ensure in each circumstance you can detect
the error or condition and report the appropriate result.

* When text output is required you must generate EXACTLY that
output and no other output.  For testple-
Specified output: "RX"    Actual program output: "rx"      Result: zero marks.
Specified output: "RX"    Actual program output: "Got RX"  Result: zero marks.
Specified output: "RX"    Actual program output: " RX"     Result: zero marks.


*	The following code is an example of the syntax required to open a pipe to the OUSB device.
It may / may not include all of the necessary code to complete the task.

//----Start of example standalone ccp file--------------------------------------------
#include "stdafx.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
char *command = "ousb -r io PORTB 20"; // command to write 20 to OUSB board
FILE *fpipe;
char line[256] = {};

fpipe = (FILE*)_popen(command,"r");    // attempt to open pipe and execute a command
if( fpipe != NULL )					   // check that the pipe opened correctly
{
while( fgets(line, sizeof(line), fpipe) )
{   // do nothing here, or print out debug data
cout << line; // print out OUSB data for debug purposes
}
_pclose(fpipe);   // close pipe
}
else cout << "Error, problems with pipe!\n";

// do something with the value returned by the OUSB board, eg:
int portb = (int)atoi(line); // convert from char array to int
cout << "value = " << portb << endl;

return 0;
}
//----End of testple standalone ccp file----------------------------------------------

Copyright Dr. Pj Radcliffe 2011, modified by Eva Cheng 2015 and S Ippolito 2016
*/

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <windows.h> // keep it here, just in case.
#include <cmath> // keep it here, just in case.

using namespace std;

const int min_range = 0;
const int max_range = 1023;
const int max_dutyCycle_range = 100;
const int max_adcPort_range = 7;

const int pwmFrequency = 46;

const int max_iteration = 60;
const int adcPort = 0;
const int initial_dutyCycle = 50;


bool errCheck1(char* arg1)
{
	if (
		*arg1 != 'P' && *arg1 != 'A' &&
		*arg1 != 'L' && *arg1 != 'M'
		)
	{
		cerr << 'I' << endl;
		return false;
	}

	if (*(arg1 + 1) != '\0')
	{
		cerr << 'I' << endl;
		return false;
	}

	return true;
}


bool errCheck2(char* arg2)
{
	if (atoi(arg2)<min_range || atoi(arg2)>max_range)
	{
		cerr << 'R' << endl;
		return false;
	}

	return true;
}


bool errCheck2_dutyCycle(char* arg2)
{
	if (atoi(arg2)<min_range || atoi(arg2)>max_dutyCycle_range)
	{
		cerr << 'r' << endl;
		return false;
	}

	return true;
}


bool errCheck2_adcPort(char* arg2)
{
	if (atoi(arg2)<min_range || atoi(arg2)>max_adcPort_range)
	{
		cerr << 'a' << endl;
		return false;
	}

	return true;
}


bool set_PWM_frequency(int f)
{
	stringstream commandStrStream;
	commandStrStream << "ousb pwm-freq 1 " << f;

	string commandstr = commandStrStream.str();

	FILE *fpipe;
	char line[256] = {};

	fpipe = (FILE*)_popen(commandstr.c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return false;
			}
			//cout << line;
		}

		_pclose(fpipe);
	}
	else
	{
		return false;
	}

	return true;
}


bool write_DutyCycle(int dc)
{
	stringstream commandStrStream;
	commandStrStream << "ousb pwm 1 " << dc;

	string commandstr = commandStrStream.str();

	FILE *fpipe;
	char line[256] = {};

	fpipe = (FILE*)_popen(commandstr.c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{  
			if (line[0] == 'F')
			{
				return false;
			}
			//cout << line;
		}

		_pclose(fpipe);
	}
	else
	{
		return false;
	}

	return true;
}


int readADC(int pn)
{
	stringstream commandStrStream;
	commandStrStream << "ousb -r adc " << pn;

	string commandstr = commandStrStream.str();

	FILE *fpipe;
	char line[256] = {};

	fpipe = (FILE*)_popen(commandstr.c_str(), "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			if (line[0] == 'F')
			{
				return -1;
			}
			//cout << line;
		}

		_pclose(fpipe);
	}
	else
	{
		return -1;
	}

	return atoi(line);
}


int main(int argc, char *argv[])
{//--- When no parameters MUST print id string in CSV format. 
	if (argc == 1)  // no parameters print this line.
	{
		cout << "3452165,s3452165@student.rmit.edu.au,Kai_Soon" << endl;
		// Any errors in the line above,  or the naming of the file
		//  will result in 10% being deducted from your mark.
		return(0);
	}
	else if (argc == 3)
	{
		bool OP = false;


		//General error checks
		OP = errCheck1(argv[1]);
		if (OP == false)
		{
			return 0;
		}

		OP = errCheck2(argv[2]);
		if (OP == false)
		{
			return 0;
		}


		//------------------------------------------------------------Set Duty Cycle
		if (argv[1][0] == 'P')
		{
			//Duty Cycle cannot be less than 0 or more than 100
			OP = errCheck2_dutyCycle(argv[2]);
			if (OP == false)
			{
				return 0;
			}

			//Set PWM freqency to 46Hz
			OP = set_PWM_frequency(pwmFrequency);
			if (OP == false)
			{
				return 0;
			}

			//Set duty cycle
			OP = write_DutyCycle(atoi(argv[2]));
			if (OP == false)
			{
				return 0;
			}

			cout << 'p' << endl;
		}
		//------------------------------------------------------------Read ADC Port
		else if (argv[1][0] == 'A')
		{
			//ADC port number cannot be less than 0 or more than 7
			OP = errCheck2_adcPort(argv[2]);
			if (OP == false)
			{
				return 0;
			}

			//Read ADC Port
			int adc = readADC(atoi(argv[2]));
			if (adc == -1)
			{
				return 0;
			}

			cout << adc << endl;
		}
		//------------------------------------------------------------Control Loop with 60 iterations
		else if (argv[1][0] == 'L')
		{
			int dutyCycle = initial_dutyCycle;
			int currentADC = 0;
			//Convert argv[2] to integer
			int targetADC = atoi(argv[2]);
		
			//Set PWM freqency to 46Hz
			OP = set_PWM_frequency(pwmFrequency);
			if (OP == false)
			{
				return 0;
			}

			//Initial duty cycle
			OP = write_DutyCycle(dutyCycle);
			if (OP == false)
			{
				return 0;
			}


			//Control Loop
			for (int i = 0; i < max_iteration; i++)
			{
				//Display data
				//cout << "Loop#" << i << '\t';
				//cout << "targetADC: " << targetADC << '\t';
				//cout << "currentADC: " << currentADC << '\t';
				//cout << "Next dutyCycle: " << dutyCycle << endl;


				//Read current ADC value
				currentADC = readADC(adcPort);

				//If dutyCycle saturates at 100%...
				if (dutyCycle == 100)
				{
					continue;
				}
				//If dutyCycle saturates at 0%...
				else if (dutyCycle == 0)
				{
					continue;
				}
				else if (currentADC >= targetADC)
				{
					dutyCycle++;

					OP = write_DutyCycle(dutyCycle);
					if (OP == false)
					{
						return 0;
					}
				}
				else if (currentADC < targetADC)
				{
					dutyCycle--;

					OP = write_DutyCycle(dutyCycle);
					if (OP == false)
					{
						return 0;
					}
				}
			}

			cout << dutyCycle << endl;
		}
		//------------------------------------------------------------Infinite Control Loop
		else if (argv[1][0] == 'M')
		{
			int dutyCycle = initial_dutyCycle;
			int currentADC = 0;
			//Convert argv[2] to integer
			int targetADC = atoi(argv[2]);

			//Set PWM freqency to 46Hz
			OP = set_PWM_frequency(pwmFrequency);
			if (OP == false)
			{
				return 0;
			}

			//Initial duty cycle
			OP = write_DutyCycle(dutyCycle);
			if (OP == false)
			{
				return 0;
			}


			//Control Loop
			while (1)
			{
				//Display data
				cout << "targetADC: " << targetADC << '\t';
				cout << "currentADC: " << currentADC << '\t';
				cout << "Next dutyCycle: " << dutyCycle << endl;


				//Read current ADC value
				currentADC = readADC(adcPort);

				//If dutyCycle saturates at 100%...
				if (dutyCycle == 100)
				{
					continue;
				}
				//If dutyCycle saturates at 0%...
				else if (dutyCycle == 0)
				{
					continue;
				}
				else if (currentADC >= targetADC)
				{
					dutyCycle++;

					OP = write_DutyCycle(dutyCycle);
					if (OP == false)
					{
						return 0;
					}

				}
				else if (currentADC < targetADC)
				{
					dutyCycle--;

					OP = write_DutyCycle(dutyCycle);
					if (OP == false)
					{
						return 0;
					}
				}
			}

			cout << dutyCycle << endl;
		}

		return 0;
	}
	else
	{
		cerr << 'P' << endl;
		return 0;
	}

	return(0); // The convention is to return Zero to signal NO ERRORS, if you change it 
	// the AutoTester will assume you have made some major error.  
	// Leave it as zero.
}

// do NOT put any functions after this closing bracket, if you use functions add them before main


// End of File