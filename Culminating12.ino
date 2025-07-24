// library for the LCD and the pitches
#include <LiquidCrystal.h>
#include "pitches.h"

// pins for the buzzer, the LCD, LEDs
int buzzer= 3;
int playerRed = 13, playerBlue = 2;
int buttonRed, buttonBlue;
int button1 = A5, button2 = 10, button3 = 9, button4 = 8;
int choice1, choice2, choice3, choice4;
int ledRed = A0, ledBlue = A1;
const int rs = 11, enable = 12, d4= 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs,enable, d4, d5, d6, d7);
int player1Score = 0 , player2Score = 0;
int buttonPressed=0;
unsigned long redPressed, bluePresses;
unsigned long startmillis;

// These are the ten songs which are the ten levels of the game.
// There are three lists: one for the notes, one for duration of each note, and one for the choices.
int song1[] = {NOTE_D5, NOTE_F5, NOTE_C5, NOTE_AS4, 0, NOTE_D5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_DS5, NOTE_D5, NOTE_C5, 0, NOTE_D5, NOTE_F5, NOTE_C5, NOTE_AS4};
int duration1[] = {4, 8, 4, 3, 4, 4, 4, 4, 8, 4, 3, 8, 4, 4, 8, 4, 3 };
String choices1[] = {"I love you so", "Die with a Smile", "Snooze", "Saturn"};

int song2[]= { NOTE_F5, NOTE_DS5, 0, NOTE_F5, 0, NOTE_DS5, NOTE_F5, 0, NOTE_AS4, NOTE_F5, NOTE_DS5, 0, NOTE_F5, 0, NOTE_DS5, NOTE_F5, 0, NOTE_AS4, NOTE_F5, NOTE_DS5, 0, NOTE_F5, 0, NOTE_DS5, NOTE_F5, 0, NOTE_GS5,NOTE_F5, NOTE_DS5 };
int duration2[] = { 2, 4, 8, 4, 8, 3, 4, 8, 4, 4, 4, 8, 4, 8, 3, 4, 8, 4, 4, 4, 8, 4, 8, 3, 4, 8, 4, 4, 2};
String choices2[] = {"Promise", "From the Start", "Unconditional", "Reckless"};

int song3[] = {NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_DS5, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_D5, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_DS5, NOTE_D5, NOTE_A4, NOTE_A4, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, NOTE_D5, NOTE_C5};
int duration3[] = { 8, 8, 4, 8, 4, 8, 4, 8, 8, 8, 8, 3, 3, 2, 8, 8, 4, 8, 4, 8, 4, 8, 4, 8, 4, 8, 4, 8, 8, 3};
String choices3[] = {"Until I found u", "Fall in Love", "Unconditional", "Die for you"};

int song4[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4};
int duration4[] = {8, 8, 8, 8, 2, 8, 8, 8, 2, 8, 4, 4, 4, 8, 8, 8, 4, 4};
String choices4[] = {"Poker Face", "Paparazzi", "Bad Romance", "Single Ladies"};

int song5[] = { NOTE_GS3, NOTE_B3, NOTE_DS4, NOTE_GS3, NOTE_B3, NOTE_DS4, NOTE_CS4, 0, NOTE_GS3, NOTE_B3, NOTE_DS4, NOTE_FS3, NOTE_FS3, NOTE_CS4, NOTE_B3};
int duration5[] = {4, 4, 2, 4, 4, 8, 4, 4, 4, 4, 2, 4, 4, 8, 4};
String choices5[] = {"Seven", "Fever", "Moonstruck", "No Doubt"};

int song6[] = { NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_AS4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_C5};
int duration6[] = {8, 8, 8, 4, 4, 4, 4, 8,  4, 8, 2, 4, 4, 4, 4, 8, 4, 8, 2};
String choices6[] = {"Stay", "Baby", "Mistletoe", "Be Mine"};

int song7[] = {NOTE_AS4, NOTE_GS4, NOTE_FS4, NOTE_F4, NOTE_F4, NOTE_DS4, 0, NOTE_AS4, NOTE_GS4, NOTE_FS4, NOTE_GS4, NOTE_GS4, NOTE_AS4};
int duration7[] = {8, 8, 8, 8, 4, 8, 6, 8, 8, 8, 8, 4, 8};
String choices7[] = {"Attention", "Light Switch", "Real man", "My heart"};

int song8[] = { NOTE_A4, NOTE_B4, NOTE_B4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_DS5, 0, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_E4, NOTE_B4, NOTE_B4, NOTE_B4, 0, NOTE_B4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_GS4, NOTE_E4, NOTE_FS4, 0, NOTE_E4};
int duration8[] = {  8, 8, 3, 1, 2, 2, 2, 8, 4, 2.2, 3, 2.2, 8, 4, 4, 6, 16, 4, 3, 4, 4, 4, 4, 8, 4, 16, 1};
String choices8[] = {"Santa Baby", "Only", "Here with me", "Golden Hour"};

int song9[] = {  NOTE_A3, NOTE_B3, NOTE_CS4, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_F4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_FS4, NOTE_CS5, NOTE_B4, NOTE_A4, NOTE_D5, NOTE_CS5, NOTE_B4, NOTE_CS5, NOTE_A4};
int duration9[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 1};
String choices9[] = {"Starboy", "Light", "Peach Eyes", "Love"};

int song10[] = { NOTE_F4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_G4, NOTE_F4, 0, NOTE_A3, NOTE_A3, NOTE_AS3, NOTE_C4, NOTE_A4, NOTE_G4, 0, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_DS4, NOTE_F4, NOTE_G4, NOTE_A4};
int duration10[] = {8, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4};
String choices10[] = {"The cutest Pair", "Down Bad", "Double Take", "In 2 Deep"};







//This function run each level of the game
/*It has six parameters: The list for the song, duration, and choices plus 
the length of the song, the level of the song, and the right choice. */
void playTheSong(int song[], int songLength, int duration[], int level, String choice[],int right){
 /*This block of the code stop the code until the red button is pressed
 which shows that player1 is ready to play.*/
  digitalWrite(ledRed,LOW);
  digitalWrite(ledBlue, LOW);
  lcd.clear();
  delay(5);
  buttonRed= digitalRead(playerRed);
  while(buttonRed == LOW){
   buttonRed= digitalRead(playerRed);
   lcd.setCursor(1,0);
   lcd.print("Player1 Press");
   lcd.setCursor(3,1);
   lcd.print("the button");
   digitalWrite(ledRed, HIGH);
  }

/*Similar as the block of the code above, this code is for making 
sure player2 is ready*/
 lcd.clear();
 delay(5);
 buttonBlue = digitalRead(playerBlue);
  while(buttonBlue == LOW){
   buttonBlue = digitalRead(playerBlue);
   lcd.setCursor(1,0);
   lcd.print("Player2 Press");
   lcd.setCursor(3,1);
   lcd.print("the button");
   digitalWrite(ledBlue, HIGH);
 }
 digitalWrite(ledBlue, LOW);
 digitalWrite(ledRed, LOW);

 /*This block of the code shows the what level we are and do the countdown 
 before the level start */
 lcd.clear();
 delay(5);
 lcd.setCursor(3,0);
 lcd.print("Level "+ String(level));
 delay(1500);
 lcd.clear();
 delay(5);
 lcd.setCursor(5,0);
 lcd.print("Ready!");
 delay(1000);
 for (int i=3; i>0; i--){
  lcd.clear();
  delay(5);
  lcd.setCursor(7,0);
  lcd.print(i);
  delay(1000);
 }
 lcd.clear();

 /*This block of the code is looping through the list which contains the notes
 of the song. By matching the notes and the durations in the lists song and duration
 it will play the song of this level. */
 for (int i=0;i < songLength; i++){
   tone(buzzer, song[i]);
   delay(1200/duration[i]);
   noTone(buzzer);
   delay(50);}

   /*This block of the code loop throught the choices to display them so the 
   players can choose the song. We used millis so if one of the player press the 
   button it will start the countdown for the players to choose the answer. */
   buttonRed= LOW;
   buttonBlue = LOW;
   while (buttonRed == LOW && buttonBlue == LOW){
     for (int x = 1; x < 5; x++){
       lcd.clear();
       delay(5);
       startmillis = millis();
       while (millis() - startmillis <=  1500){
         lcd.setCursor(4,0);
         lcd.print("choice"+ String(x) + ":");
         lcd.setCursor(0,1);
         lcd.print(choice[x-1]);
         buttonRed= digitalRead(playerRed);
         buttonBlue = digitalRead(playerBlue);
         //Here is for breaking the loop if one of the player press the button. 
         if (buttonRed == HIGH || buttonBlue == HIGH){
           break;
         }
       }
     }
   }
  
/* Depending on who press the buttons sooner, it will shows which player 
need to choose while showing a countdown of three seconds. The player
only have three seconds to choose after the button is pushed. */
bool selected = false;
 lcd.clear();
 delay(5);
 lcd.setCursor(0, 0);
 if (buttonRed == HIGH){
   startmillis = millis();
   while (millis()-startmillis<=1000){
     lcd.setCursor(0, 0);
     lcd.print("Player 1's Turn");
     digitalWrite(ledRed, HIGH);
   }
   lcd.clear();
   delay(5);
 }
 else if (buttonBlue == HIGH) {
   startmillis = millis();
   while (millis()-startmillis<=1000){
     lcd.setCursor(0,0);
     lcd.print("Player 2's Turn");
     digitalWrite(ledBlue, HIGH);
    }
 }

 //This is the countdown
   for (int z= 3; z > 0 ; z--){
       lcd.clear();
       delay(5);
       digitalWrite(ledRed, LOW);
       startmillis = millis();
        /*Here we check what button is pressed and store it the number
        into buttonPressed variable so we can check whether the player chose
        the right choce. If the players press the button it will break the 
        loop.*/
       while(millis()- startmillis<=1000){
         lcd.setCursor(7,0);
         lcd.print(z);
         digitalWrite(ledRed,HIGH);
        choice1 = digitalRead(button1);
        choice2 = digitalRead(button2);
        choice3 = digitalRead(button3);
        choice4 = digitalRead(button4);
     
   if (choice1 == HIGH){
     buttonPressed = 1;
     selected =true;
     break;
   }
    else if (choice2 == HIGH) {
     buttonPressed = 2;
     selected = true;
     break;
   }
   else if (choice3 == HIGH) {
     buttonPressed = 3;
     selected = true;
     break;
   }
   else if (choice4 == HIGH) {
     buttonPressed = 4;
     selected = true;
     break;
   }
       }
   }

   /* Here if they chose the right button the lcd will display correct! and add
   one point to the score of the player who chose the right button*/
   lcd.clear();
   delay(5);
   if (selected) {
     if (buttonPressed == right) {
       lcd.setCursor(4, 0);
       lcd.print("Correct!");
       delay(1000);
       if (buttonRed == HIGH) {
         player1Score = player1Score+2;
         
       }
       else if (buttonBlue == HIGH) {
         player2Score = player2Score+2;
            
     }
   }

   /*If they chose the wrong answer or ran out of time the LCD will display to them
   and the deduct a point from the player who made the mistake. */
   else {
     lcd.setCursor(3, 0);
     lcd.print("Wrong Answer!");
     delay(2000);
     if ( buttonRed == HIGH){
      
      player1Score = player1Score-1;
     }
     else if( buttonBlue == HIGH){
      player2Score = player2Score-1;

     }
    }
   }
 else {
   lcd.setCursor(3, 0);
   lcd.print("Time's up!");
   delay(2000);
    if ( buttonRed == HIGH){
      player1Score = player1Score-1;
     }
     else if( buttonBlue == HIGH){
      player2Score = player2Score-1;
     }
 }

 //Here the LCD shows the right answer and the score of the each player. 
 lcd.clear();
 delay(5);
  lcd.setCursor(0,0);
  lcd.print("Answer:");
  lcd.setCursor(0,1);
  lcd.print(choice[right-1]);
  delay(2000);
  lcd.clear();
  delay(5);
  lcd.setCursor(0,0);
  lcd.print("Player1 Score:" + String(player1Score));
  delay(2000);
  lcd.clear();
  delay(5);
  lcd.setCursor(0,0);
  lcd.print("player2 Score:"+ String(player2Score));
  delay(2000);
 
}

void setup() {
 //Here we just set up the lEDs, LCD, and the buttons, while welcoming the players to the game
  lcd.begin(16,2);
 pinMode(ledRed, OUTPUT);
 pinMode(ledBlue, OUTPUT);
 pinMode(button1, INPUT);
 pinMode(button2, INPUT);
 pinMode(button3, INPUT);
 pinMode(button4, INPUT);
 pinMode(playerBlue, INPUT);
 pinMode(playerRed, INPUT);
 pinMode(buzzer, OUTPUT);
 lcd.setCursor(0,0);
 lcd.print("Welcome to Guess");
 lcd.setCursor(2,1);
 lcd.print("The Song2025");
 delay(1500);
 lcd.clear();
 delay(5);
}

void loop() {
  //Here we run each level
  playTheSong(song1, 17, duration1, 1, choices1, 1);
  playTheSong( song2, 29, duration2, 2, choices2, 2);
  playTheSong( song3, 30, duration3, 3, choices3, 1);
  playTheSong( song4, 18, duration4, 4, choices4, 3);
  playTheSong( song5, 15, duration5, 5, choices5, 4);
  playTheSong( song6, 19, duration6, 6, choices6, 2);
  playTheSong( song7, 12, duration7, 7, choices7, 1);
  playTheSong( song8, 27, duration8, 8, choices8, 3);
  playTheSong( song9, 25, duration9, 9, choices9, 4);
  playTheSong( song10, 29, duration10, 10, choices10, 1);
  
    /* This part of the game will show the winner or if there was a tie 
    according to who has a higher score. */
    lcd.setCursor(0, 0);
    lcd.print("The winner is: ");
    lcd.setCursor(4,1);
    if (player1Score < player2Score){
      lcd.print("Player2");
      delay(3000);}
    else if( player1Score>player2Score){
      lcd.print("Player1");
      delay(3000);
    }
    else{
      lcd.clear();
      delay(5);
      lcd.setCursor(0,0);
      lcd.print("Tie :(");
      delay(3000);
    }
    // Ask if the players want to replay the game
    lcd.clear();
    delay(5);
    lcd.setCursor(5,0);
    lcd.print("Again?");
    delay(1000);
    buttonRed= digitalRead(playerRed);
    buttonBlue = digitalRead(playerBlue);
    /* To replay the game, both players need to press the buttons at 
    the same time*/
    while (buttonRed == LOW || buttonBlue == LOW){
      lcd.setCursor(3,0);
      lcd.print("Press the ");
      lcd.setCursor(0,1);
      lcd.print("buttons together");
      buttonRed= digitalRead(playerRed);
      buttonBlue = digitalRead(playerBlue);
    }
}
