#include <iostream>
#include <ostream>  
#include <math.h>
using namespace std;
/*
________________________________________________________________________________

Treyarch Technical Take-home Test
________________________________________________________________________________


Please read all instructions before starting.

This exam consists of 3 questions.

Complete each of the functions below.  
State the amount of time you took for each problem on the line marked "Time:"
Do not modify function declarations.
You are welcome to use any standard library.
You may use helper functions.
You can assume well-formed input.
If you have any concerns, use your best judgment and add a comment.
Place all your code in this file only.
Do all your own work.
Double check your answers!
Do not distribute this exam.
Have Fun!

________________________________________________________________________________

*/


// A struct for representing a 3D Vector with a constructor
struct Vector3
{
	float x;
	float y;
	float z;

	Vector3( float xIn, float yIn, float zIn )
	{
		x = xIn;
		y = yIn;
		z = zIn;
	}
};

// Function Declarations
void TreyArch( int Trey, int Arch, int n );
void PlayerInfo( unsigned int stats );
bool CanHearSniper( Vector3 listenerPosition, Vector3 sniperPosition, Vector3 sniperForward, float distance, float cone );




// Main
// Calls functions with sample inputs
// No need to modify this function
int main()
{
	TreyArch( 3, 5, 15 );
	PlayerInfo( 3411782069 );
	CanHearSniper( Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 1000.0f, 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ), 1100.7f, 10 );
	return 0;
}


/////////////////////////////////////
// PLACE ALL CODE BELOW THIS BLOCK //
/////////////////////////////////////


// Problem 1

// TreyArch
// For each number starting from 1 and going up to n, this function prints the following
// "Trey" - If the number is a multiple of Trey OR contains the digit Trey
// "Arch" - If the number is a multiple of Arch OR contains the digit Arch
// "TreyArch" - If the number falls into both categories above
// The number itself if none of the rules above hold for that number
// n - the number up to which this function prints
// Trey - first digit 3 - 9
// Arch - second digit 3 - 9

/*
Sample Input
-----------------------------------------------------------
3 5 15

Sample Output
-----------------------------------------------------------
1 2 Trey 4 Arch Trey 7 8 Trey Arch 11 Trey Trey 14 TreyArch  
*/

/*
Assuming n goes to 
*/

void TreyArch( int Trey, int Arch, int n )
{

  if (((Trey < 3) || (Arch < 3)) || ((Trey > 9) || (Arch > 9))) {
    cout << "Input error" << endl;
    return;
  }
  
  for(int i = 1; i <= n; i++){
  		if(((i % Trey) == 0) && ((i % Arch) == 0)) { 
          cout << "TreyArch ";
          continue;
        }
  		
  		if( (i % Trey == 0) || ((i % 10) == Trey)){ //mod 10 for possible larger n
          cout << "Trey ";
          continue;
        }
  		
  		if((i % Arch == 0)|| ((i % 10) == Arch)){ 
          cout << "Arch ";
          continue;
        }
        
        else {
         cout << i << " "; //prints iteration number if all rules fail
        }  
   }
   cout << endl;
}

// Time: 20 minutes - rough estimates because I didn't sit down and do them all at once




// Problem 2

// PlayerInfo
// Prints the player info stored inside the stats passed in
// From least significant to most significant bits:
// Bits 0 - 7 contain the players kills															Print Number
// Bits 8 - 15 contain the players deaths														Print Number
// Bits 16 - 17 contain the players weapon class												Print "Assault" "SMG" "LMG" or "Sniper"
// Bit 18 is handedness: 1 for right, 0 for left												Print "Right Hand" or "Left Hand"
// Bits 19 - 22 contain the players setting for vertical look sensitivity						Print Number
// Bits 23 - 26 contain the players setting for horizontal look sensitivity						Print Number
// Bits 27 - 30 contain the players setting for auto-aim sensitivity							Print Number
// Bit 31 is if the player is getting an internship at Treyarch: 1 for yes, 0 for no			Print "Yes" or "No"
// stats - the stats blob passed in

/*
Sample Input
-----------------------------------------------------------
3411782069

Sample Output
-----------------------------------------------------------
Kills: 181
Deaths: 169
Class: Sniper
Hand: Left Hand
Vertical Look Sensitivity: 11
Horizontal Look Sensitivity: 6
Auto-Aim Sensitivity: 9
Internship: Yes
*/

enum PlayerWeaponClass
{
	PWD_ASSAULT,
	PWD_SMG,
	PWD_LMG,
	PWD_SNIPER,
	PWD_COUNT,
};

unsigned mask(unsigned start_bit, unsigned last_bit)
{
   unsigned new_mask = ((1 << last_bit) - 1) << start_bit;
   return new_mask;
}

void PlayerInfo( unsigned int stats )
{
  
  // Bits 0 - 7  = kills 
  unsigned kill_mask = mask(0,8);
  unsigned  kills = stats & kill_mask; //use bitwise and to mask values 
  cout << "Kills: " << kills << endl;
  
  // Bits 8 - 15 = deaths (print)
  //need to shift stats to get next relevant bits (8 in this case)
  //we can reset stats to bit shifted value because we no longer need Bits 0 - 7
  stats = stats >> 8; 
  unsigned death_mask = mask(0,8);
  unsigned deaths = stats & death_mask;
  cout << "Deaths: " << deaths << endl;
    
  	
  // Bits 16 - 17 contain the players weapon class (pwclass) (Print "Assault" "SMG" "LMG" or "Sniper")
  stats = stats >> 8;
  int pwclass = stats & 0x03; //or could call mask function
  
  if(pwclass == PWD_ASSAULT) cout<<"Class: Assault" << endl;
  if(pwclass == PWD_SMG)     cout << "Class: SMG" << endl;
  if(pwclass == PWD_LMG)     cout << "Class: LMG" << endl;
  if(pwclass == PWD_SNIPER)  cout << "Class: Sniper" << endl;
  if(pwclass == PWD_COUNT)   cout << "Class: Count" << endl;
 
  
  // Bit 18 is handedness: 1 for right, 0 for left(Print "Right Hand" or "Left Hand")
  stats = stats >> 2;
  if((stats & 1) == 1 ) cout << "Hand: Right Hand" << endl;
    else 
      cout << "Hand: Left Hand" << endl;
  
  // Bits 19 - 22 contain the players setting for vertical look sensitivity (Print Number)
   stats = stats >> 1;
   unsigned vlsensitivity_mask = mask(0,5);
   unsigned  vls = stats & vlsensitivity_mask;
   cout << "Vertical Look Sensitivity: "<< vls << endl;
  
  // Bits 23 - 26 contain the players setting for horizontal look sensitivity (Print Number)
   stats = stats >> 4;
   unsigned hlsensitivity_mask = mask(0,4);
   unsigned  hls = stats & hlsensitivity_mask;
   cout << "Horizontal Look Sensitivity: " << hls << endl;
  
  // Bits 27 - 30 contain the players setting for auto-aim sensitivity (Print Number)
  stats = stats >>  4;
  unsigned alsensitivity_mask = mask(0,4);
  unsigned  als = stats & alsensitivity_mask;
  cout << "Auto-Aim Sensitivity: " << als << endl;
  
  // Bit 31 is if the player is getting an internship at Treyarch: 1 for yes, 0 for no	(Print "Yes" or "No")
  stats = stats >> 4;
  
  if( (stats & 1) == 0) //no need for helper function for only 1 bit
  	cout << "Internship: No" << endl;
  
  else {
    cout << "Internship: Yes" << endl;
  }

}

// Time: 37 minutes




// Problem 3

// CanHearSniper
// Task - Complete the function to determine if a player can hear a sniper's gunfire
// Prints true or false for debug purposes

// listenerPosition - The 3d position of the player listening
// sniperPosition - The 3d world position of the sniper
// sniperForward - The normalized vector of the direction that the sniper is firing in
// distance - the max distance that the sniper can be heard from
// cone - the max angle in DEGREES that the sniper's gunfire can be heard in ( 0 - 360 )

/*
Sample Input
-----------------------------------------------------------
Vector3( 0.0f, 0.0f, 0.0f ), Vector3( 1000.0f, 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ), 1100.7f, 10

Sample Output
-----------------------------------------------------------
true
*/

float dot_product(Vector3 v1, Vector3 v2) {
    float product;
	product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return product;
}
 
float vector_magnitude(Vector3 vec) {
	float mag = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return mag;
}

float vector_distance(Vector3 v1, Vector3 v2) {
  float distance;
  distance = sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y) + (v1.z - v2.z) * (v1.z - v2.z));
  return distance;
}
 


bool CanHearSniper( Vector3 listenerPosition, Vector3 sniperPosition, Vector3 sniperForward, float distance, float cone )
{
  
  float x = listenerPosition.x - sniperPosition.x;
  float y = listenerPosition.y - sniperPosition.y;
  float z = listenerPosition.z - sniperPosition.z;
  
  Vector3 sniperToListenerPosition(x,y,z);
  
  if (vector_distance(listenerPosition, sniperPosition) <= distance) { //checks if listener is in max distance range
      float adjacent = dot_product(sniperForward, sniperToListenerPosition);
      float hypotenuse = (vector_magnitude(sniperForward) * vector_magnitude(sniperToListenerPosition));
      float angle = acos(adjacent / hypotenuse);
  
      if (angle <= cone / 2) { 
        cout << "true" << endl;
	    return true;
	  }
  }
  
  else 
    cout << "false" << endl; //listener not in range so no need for further calculations

  return false;
}

// Time: 60 min+ (had to review physics formulas - some I was not familiar with yet)