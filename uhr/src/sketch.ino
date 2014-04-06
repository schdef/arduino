// Pinbelegung für Arduino UNO
int reihenPins[8] = {9,3,2,12,15,11,7,6};      // Anschlüsse der Reihenpins am Arduino
int spaltenPins[8] = {13,8,17,10,5,16,4,14};   // Anschlüsse der Spaltenpins am Arduino
int imageNr=0;                                 // welches Bild wird gerade angezeigt

long timer=0;                                  // Timervariable
int timeOut=1000;                               // wie lange soll jedes Bild angezeigt werden (ms)
int counter=11;
int secCounter = 0;
String command = "";

int image[11][8][8]={{           
{1,1,1,0,0,0,0,0},  
{1,0,1,0,0,0,0,0},
{1,0,1,0,0,0,0,0},
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}

},{  
{0,0,1,0,0,0,0,0},  
{0,1,1,0,0,0,0,0},
{1,0,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}

}, {                           
// two  
{1,1,1,0,0,0,0,0},  
{0,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}

},{                             
// three  
{1,1,1,0,0,0,0,0},  
{0,0,1,0,0,0,0,0},
{0,1,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// four  
{1,0,1,0,0,0,0,0},  
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// five  
{1,1,1,0,0,0,0,0},  
{1,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// six  
{1,1,1,0,0,0,0,0},  
{1,0,0,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// seven  
{1,1,1,0,0,0,0,0},  
{0,0,1,0,0,0,0,0},
{0,1,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// eight  
{1,1,1,0,0,0,0,0},  
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// nine  
{1,1,1,0,0,0,0,0},  
{1,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,1,0,0,0,0,0},
{1,1,1,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
},{                             
// combination  
{1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1}
}
};                                              

void setup(){
  for (int i=0; i<8; i++){                       // Alle Pins werden als OUTPUT deklariert 
    pinMode(reihenPins[i],OUTPUT);
    pinMode(spaltenPins[i],OUTPUT);
  }
  Serial.begin(115200);      // start communication at 115200bps
}

void loop(){
  if (timer+timeOut<millis()){
    timer=millis();
    if(secCounter++ >= 59) {
        counter--;
        secCounter = 0;
    }
  }
  show(counter);
  if(counter <= 0) {
    counter=20;
  }
  char value;
  if( Serial.available()) 
  {
    value = Serial.read();
    Serial.print("Read");
    Serial.println(value);
    if((value-'0') >= 0 && (value-'0') <= 9) {  
      command.concat(value);
      if(command.length() > 1) {
        counter = command.toInt();
        command = "";
     
      }
    }  
  }
  
}

void show(int number) {
  
  if(number > 99) {
    return;
  }
  
  // number -> picture
  String value = String(number);
  int arrayIndex = 10;
  if(number > 9) {
    mixUp(value[0], value[1], arrayIndex);
    imageNr=arrayIndex;
  } else {
    imageNr=value[0];
  }
  
  matrix(imageNr);
}

void mixUp(int firstNumber, int secondNumber, int index) {
    for (int y=0; y<8; y++){                      
      for (int x=0; x<8; x++){
        
        image[index][x][y] = image[firstNumber][x][y];
      }
    }  
    
    for (int y=0; y<8; y++){                      
      for (int x=0; x<8; x++){                    
        int destinationY = y+4;
        if(destinationY < 8) {
          image[index][x][destinationY] = image[secondNumber][x][y];
        }
      }
    }
}
  

void matrix(int imageNr) {
  for (int y=0; y<8; y++){                       // zeilenweise werden 
    for (int x=0; x<8; x++){                     // von links nach rechts alle Einträge des Arrays geprüft
      if (image[imageNr][x][y]==1){              // ist der Eintrag = 1
        digitalWrite(spaltenPins[x],HIGH);       // wird der Spaltenpin eingeschalten
      } else {                                   // sonst
        digitalWrite(spaltenPins[x],LOW);        // abgeschalten
      }
    }
    digitalWrite(reihenPins[y],LOW);             // nun wird der Reihenpin auf LOW geschalten (da es die Kathode der LED betrifft bedeutet LOW eingeschalten: LOW = GND)
    delayMicroseconds(100);                      // das Programm hällt 100 Mikrosekunden an
    digitalWrite(reihenPins[y],HIGH);            // danach wird der Reihenpin wieder auf HIGH (in diesem Fall also abge-) schalten
  } 
}  
