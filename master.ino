///////////////////////////////////// SETUP MASTER
void setupMaster(){
  Wire.begin();
}

///////////////////////////////////// UPDATE MASTER
void updateMaster(){
  //read from slave
  masterRead();
  masterWrite();
}

///////////////////////////////////// MASTER READ
void masterRead(){
  if(Wire.requestFrom(2, SLAVE_DATA_BUFFER_LENGTH)){    // request 6 bytes from slave device #2
    disconnected = false;
    isPaused = false;
    while(Wire.available()){    // slave may send less than requested
      char data_in = Wire.read(); // receive byte per byte
      switch(data_in){
      case BT_UP:
        if(Wire.read() == '1')
          highFigther(&Player2);
        break;
      case BT_DOWN:
        if(Wire.read() == '1')
          bottomFigther(&Player2);
      break;
      case BT_LEFT:
        if(Wire.read() == '1')
          leftFigther(&Player2);
      break;
      case BT_RIGHT:
        if(Wire.read() == '1')
          rightFigther(&Player2);
      break;
      case BT_A:
        if(Wire.read() == '1')
          punchFigther(&Player2);
      break;
      case BT_B:
        if(Wire.read() == '1')
          kickFigther(&Player2);
      break;
      case SLAVE_PAUSED:
        //gb.popup(F("Slave paused"),2);
        isPaused = true;
        break;
      case I_AM_MASTER:
        gb.popup(F("1 master max"),2);
        isPaused = true;
        break;
      default:
        //gb.popup(F("Wrong slave data"),2);
        //wrongSlaveData = data_in;
        //paused = true;
        break;
      }
    }
  }
  else{
    gb.popup(F("Slave disconnected"),2);
    isPaused = true;
    disconnected = true;
  }
}

///////////////////////////////////// MASTER WRITE
void masterWrite(){
  Wire.beginTransmission(2); // transmit to device #2
  /*P1*/
  Wire.write(P1_X); //identifier
  Wire.write((byte)Player1.posX); //identifier
  Wire.write(P1_Y); //identifier
  Wire.write((byte)Player1.posY); //identifier
  Wire.write(P1_STATE); //identifier
  Wire.write(Player1.currentState); //identifier
  Wire.write(P1_CURRENT_SPRITE); //identifier
  Wire.write(Player1.currentSprite); //identifier
  Wire.write(P1_H); //identifier
  Wire.write(Player1.height); //identifier
  Wire.write(P1_W); //identifier
  Wire.write(Player1.width); //identifier
  Wire.write(P1_HP); //identifier
  Wire.write(Player1.life); //identifier
  Wire.write(P1_CPT_VICTORY); //identifier
  Wire.write(Player1.cptVictory); //identifier
  /*P2*/
  Wire.write(P2_X); //identifier
  Wire.write((byte)Player2.posX); //identifier
  Wire.write(P2_Y); //identifier
  Wire.write((byte)Player2.posY); //identifier
  Wire.write(P2_STATE); //identifier
  Wire.write(Player2.currentState); //identifier
  Wire.write(P2_CURRENT_SPRITE); //identifier
  Wire.write(Player2.currentSprite); //identifier
  Wire.write(P2_H); //identifier
  Wire.write(Player2.height); //identifier
  Wire.write(P2_W); //identifier
  Wire.write(Player2.width); //identifier
  Wire.write(P2_HP); //identifier
  Wire.write(Player2.life); //identifier
  Wire.write(P2_CPT_VICTORY); //identifier
  Wire.write(Player2.cptVictory); //identifier
  
  /*General*/
  Wire.write(GAME_STATE); //identifier
  Wire.write(stateGame); //identifier
  Wire.write(STATE_FIGHT); //identifier
  Wire.write(stateFight); //identifier
  
  
  
  Wire.endTransmission();    // stop transmitting
}






