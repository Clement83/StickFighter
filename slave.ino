///////////////////////////////////// SETUP SLAVE
void setupSlave(){
  Wire.begin(2);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

///////////////////////////////////// UPDATE SLAVE
void updateSlave(){
  byte timout = 0;
  isPaused = false;
  while(slave_updated == false){
    //wait for the master's interrupt
    delay(1);
    timout++;
    if(timout >= 40){
      gb.popup(F("No master"),2);
      disconnected = true;
      isPaused = true;
      slave_updated = false;
      break;
    }
  }
  slave_updated = false;
}

///////////////////////////////////// SLAVE SEND
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
char output[SLAVE_DATA_BUFFER_LENGTH];
void requestEvent()
{

  //the slave can only answer with one "write" so you have to put all the variables in an string
  output[0] = BT_UP; //identifier
  output[1] = bt_up? '1' : '0';
  output[2] = BT_DOWN; 
  output[3] = bt_down? '1' : '0'; 
  output[4] = BT_LEFT; 
  output[5] = bt_left? '1' : '0';
  output[6] = BT_RIGHT; 
  output[7] = bt_right? '1' : '0';
  output[8] = BT_A; 
  output[9] = bt_a? '1' : '0';
  output[10] = BT_B; 
  output[11] = bt_b? '1' : '0';

  if(isPaused){
    output[0] = SLAVE_PAUSED;
    output[1] = SLAVE_PAUSED;
    output[2] = SLAVE_PAUSED;
    output[3] = SLAVE_PAUSED;
    output[4] = SLAVE_PAUSED;
    output[5] = SLAVE_PAUSED;
    output[6] = SLAVE_PAUSED;
    output[7] = SLAVE_PAUSED;
    output[8] = SLAVE_PAUSED;
    output[9] = SLAVE_PAUSED;
    output[10] = SLAVE_PAUSED;
    output[11] = SLAVE_PAUSED;
  }

  if(isMaster){
    output[0] = I_AM_MASTER;
    output[1] = I_AM_MASTER;
    output[2] = I_AM_MASTER;
    output[3] = I_AM_MASTER;
    output[4] = I_AM_MASTER;
    output[5] = I_AM_MASTER;
    output[6] = I_AM_MASTER;
    output[7] = I_AM_MASTER;
    output[8] = I_AM_MASTER;
    output[9] = I_AM_MASTER;
    output[10] = I_AM_MASTER;
    output[11] = I_AM_MASTER;
  }
  
  bt_up = false;
  bt_down = false;
  bt_left = false;
  bt_right = false;
  bt_a = false;
  bt_b = false;

  Wire.write(output);
}

///////////////////////////////////// SLAVE RECEIVE
// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available())    // slave may send less than requested
  {
    char data_in = Wire.read(); // receive byte per byte
    byte numLevelTmp;
    switch(data_in){
    case GAME_STATE:
      stateGame = Wire.read();
      break;
    case STATE_FIGHT:
      stateFight = Wire.read();
      break;
      
    case P1_X:
      Player1.posX = Wire.read();
      break;
    case P1_Y:
      Player1.posY = Wire.read();
      break;
    case P1_STATE:
      Player1.currentState = Wire.read();
      break;
    case P1_CURRENT_SPRITE:
      Player1.currentSprite = Wire.read();
      break;
    case P1_H:
      Player1.height = Wire.read();
      break;
    case P1_W:
      Player1.width = Wire.read();
      break;
    case P1_HP:
      Player1.life = Wire.read();
      break;
    case P1_CPT_VICTORY:
      Player1.cptVictory = Wire.read();
      break;
      
    case P2_X:
      Player2.posX = Wire.read();
      break;
    case P2_Y:
      Player2.posY = Wire.read();
      break;
    case P2_STATE:
      Player2.currentState = Wire.read();
      break;
    case P2_CURRENT_SPRITE:
      Player2.currentSprite = Wire.read();
      break;
    case P2_H:
      Player2.height = Wire.read();
      break;
    case P2_W:
      Player2.width = Wire.read();
      break;
    case P2_HP:
      Player2.life = Wire.read();
      break;
    case P2_CPT_VICTORY:
      Player2.cptVictory = Wire.read();
      break;
    
    default:
      break;
    }
  }
  slave_updated = true;
  disconnected = false;
}








