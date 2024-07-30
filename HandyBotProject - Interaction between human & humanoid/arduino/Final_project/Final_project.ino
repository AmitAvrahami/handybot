
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Servo.h>

#define NUM_FINGERS 5

// Define Absolute Positions:
#define FULLY_OPEN 150
#define SEMI_CLOSE 100
#define FULLY_CLOSE 50

struct FINGER 
{
  char str[7];
  Servo servor;
  int pin;
  int position;
  int status;
};

struct FINGER hand[NUM_FINGERS];

//Functions:

void generator(int status[], struct FINGER hand[])
{

  for (int i = 0; i < NUM_FINGERS; i++) { hand[i].status = status[i];}
  
  bool flag = true;
  
  while(flag)
  {
    flag = false;
    for (int i = 0; i < NUM_FINGERS; i++)
    {
      if ( hand[i].position <= FULLY_OPEN && hand[i].status == FULLY_OPEN )  
      {
        hand[i].position += 1;
        hand[i].servor.write(hand[i].position);
        flag = true;
      } else if ( hand[i].position >= FULLY_CLOSE && hand[i].status == FULLY_CLOSE )
      {
        hand[i].position -= 1;
        hand[i].servor.write(hand[i].position);
        flag = true;
      } else if ( hand[i].position < SEMI_CLOSE && hand[i].status == SEMI_CLOSE )
      {
        hand[i].position += 1;
        hand[i].servor.write(hand[i].position);
        flag = true;
      } else if ( hand[i].position > SEMI_CLOSE && hand[i].status == SEMI_CLOSE )
      {
        hand[i].position -= 1;
        hand[i].servor.write(hand[i].position);
        flag = true;
      }
    }
    delay(15); 
  }
  delay(500);
}

//The next function gets a letter and generate it to a sign letter with the switch operation:
void signLetterGenerator(char letter, struct FINGER hand[])
{
  switch (letter) 
  {
    case 'a':{
      int statuses_a[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN};
      generator(statuses_a, hand);
      break;
    }
    case 'b':{
      int statuses_b[] = {FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_b, hand);
      break;
    }
    case 'c':{
      int statuses_c[] = {SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE};
      generator(statuses_c, hand);
      break;
    }
    case 'd':{
      int statuses_d[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_d, hand);
      break;
    }
    case 'e':{
      int statuses_e[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_e, hand);
      break;
    }
    case 'f':{
      int statuses_f[] = {FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_f, hand);
      break;
    }
    case 'g':{
      int statuses_g[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE, FULLY_OPEN};
      generator(statuses_g, hand);
      break;
    }
    case 'h':{
      int statuses_h[] = {FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE, SEMI_CLOSE, FULLY_OPEN};
      generator(statuses_h, hand);
      break;
    }
    case 'i':{
      int statuses_i[] = {FULLY_OPEN, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_i, hand);
      break;
    }
    case 'j':{
      int statuses_j1[] = {FULLY_OPEN, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_j1, hand);
      delay(250);
      int statuses_j2[] = {SEMI_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_j2, hand);
      delay(150);
      break;
    }
    case 'k':{
      int statuses_k[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_OPEN, SEMI_CLOSE};
      generator(statuses_k, hand);
      break;
    }
    case 'l':{
      int statuses_l[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_OPEN};
      generator(statuses_l, hand);
      break;
    }
    case 'm':{
      int statuses_m[] = {SEMI_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE};
      generator(statuses_m, hand);
      break;
    }
    case 'n':{
      int statuses_n[] = {SEMI_CLOSE, SEMI_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE};
      generator(statuses_n, hand);
      break;
    }
    case 'o':{
      int statuses_o[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_o, hand);
      break;
    }
    case 'p':{
      int statuses_p[] = {SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, FULLY_CLOSE, FULLY_CLOSE};
      generator(statuses_p, hand);
      break;
    }
    case 'q':{
      int statuses_q[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE, SEMI_CLOSE};
      generator(statuses_q, hand);
      break;
    }
    case 'r':{
      int statuses_r[]= {FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, SEMI_CLOSE, FULLY_CLOSE};
      generator(statuses_r, hand);
      break;
    }
    case 's':{
      int statuses_s[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE};
      generator(statuses_s, hand);
      break;
    }
    case 't':{
      int statuses_t[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE, FULLY_OPEN};
      generator(statuses_t, hand);
      break;
    }
    case 'u':{
      int statuses_u[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_u, hand);
      break;
    }
    case 'v':{
      int statuses_v[] = {FULLY_CLOSE, FULLY_OPEN, FULLY_CLOSE, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_v, hand);
      break;
    }
    case 'w':{
      int statuses_w[] = {FULLY_CLOSE, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_w, hand);
      break;
    }
    case 'x':{
      int statuses_x[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, SEMI_CLOSE};
      generator(statuses_x, hand);
      break;
    }
    case 'y':{
      int statuses_y[] = {FULLY_OPEN, FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN};
      generator(statuses_y, hand);
      break;
    }
    case 'z':{
      int statuses_z1[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_z1, hand);
      delay(250);
      int statuses_z2[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, SEMI_CLOSE, FULLY_CLOSE};
      generator(statuses_z2, hand);
      delay(250);
      int statuses_z3[] = {FULLY_CLOSE, FULLY_CLOSE, FULLY_CLOSE, FULLY_OPEN, FULLY_CLOSE};
      generator(statuses_z3, hand);
      delay(150);
      break;
    }
    case ' ': {
      int statuses_1[] = {SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE};
      generator(statuses_1, hand);
      delay(250);
      int statuses_2[] = {FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN};
      generator(statuses_2, hand);
      delay(250);
      int statuses_3[] = {SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE, SEMI_CLOSE};
      generator(statuses_3, hand);
      delay(150);
      break;
    }
    case '\0':{
      int statuses_0[] = {FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN, FULLY_OPEN};
      generator(statuses_0, hand);
      delay(1000);
      break;
    }
    default:
      break;
  }
}

void processString(String str, struct FINGER hand[]) {
  for (int i = 0; i < str.length(); i++) 
  {
    // Convert to lowercase if the character is uppercase
    if (isupper(str[i])) {
        str[i] = tolower(str[i]);
    }
    Serial.println(str[i]);
    // Send the character to signLetterGenerator function
    signLetterGenerator(str[i], hand);
    delay(5000);
  }
}

void setup() 
{
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the hand array
  strcpy(hand[0].str, "pinky");
  hand[0].pin = 11;
  hand[0].position = 50;
  hand[0].status = FULLY_OPEN;
  
  strcpy(hand[1].str, "ring");
  hand[1].pin = 10;
  hand[1].position = 50;
  hand[1].status = FULLY_OPEN;
  
  strcpy(hand[2].str, "middle");
  hand[2].pin = 9;
  hand[2].position = 50;
  hand[2].status = FULLY_OPEN;
  
  strcpy(hand[3].str, "index");
  hand[3].pin = 6;
  hand[3].position = 50;
  hand[3].status = FULLY_OPEN;
  
  strcpy(hand[4].str, "toe");
  hand[4].pin = 5;
  hand[4].position = 50;
  hand[4].status = FULLY_OPEN;

  // Attach servos to their respective pins
  for (int i = 0; i < NUM_FINGERS; i++) 
  {
    hand[i].servor.attach(hand[i].pin);
    hand[i].servor.write(hand[i].position);
  }
}


void loop() 
{



  
  processString("abcdefghijklmnopqrstuvwxyz  ", hand);


  
  delay(1000); // Wait one seconds before repeating
}







