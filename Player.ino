
void updPlayer(Figther * player,Figther * other);
void drwPlayer(Figther * player);
void movePlayer(Figther * player);
void movePlayerSlave();
void changeBoundPlayer(Figther * player);
boolean playerIsAttack(Figther player);
void gestionAttack(Figther * pAttack, Figther * pDef);
boolean addToCombo(Figther *player, byte moveTouch);
void playerFall(byte chance,Figther *pDef);

boolean stopGame=false;

void initPlayer()
{
  initPlayer(true);
}

void initPlayer(boolean isStartGame)
{
  Player1.currentState = 0;
  Player1.currentSprite = 0;
  Player1.posX = 8;
  Player1.posY = 42;
  Player1.vx = 0;
  Player1.vy = 0;
  Player1.height = 12;
  Player1.width = 8;
  Player1.life = 100;
  Player1.oldLife = 100;
  Player1.cadance = 2;
  Player1.damage = 5;
  Player1.dir = NOFLIP;
  Player1.timeAttack = TIME_ATTACK;
  Player1.isJump = false;
  
  Player2.currentState = 0;
  Player2.currentSprite = 0;
  Player2.posX = 68;
  Player2.posY = 42;
  Player2.vx = 0;
  Player2.vy = 0;
  Player2.height = 12;
  Player2.width = 8;
  Player2.life = 100;
  Player2.oldLife = 100;
  Player2.cadance = 2;
  Player2.damage = 5;
  Player2.dir = FLIPH;
  Player2.timeAttack = TIME_ATTACK;
  Player2.isJump = false;
  
  if(isStartGame)
  {  
    Player1.cptVictory = 0;
    Player2.cptVictory = 0;
  }
  stopGame = true;
  
  //for slave 
  bt_up = false;
  bt_down = false;
  bt_left = false;
  bt_right = false;
  bt_a = false;
  bt_b = false;
}
void updatePlayerSalve()
{
  switch(stateFight)
  {
    case 0 :
       //3, 2, 1 Fight! 
    break;
    case 1 :
      movePlayerSlave();
    break;
    case 2 :
       //Figther KO 
    case 3 :
       //Time UP 
      
    break;
  }
}
void updatePlayer()
{
   
   switch(stateFight)
  {
    case 0 :
       //3, 2, 1 Fight! 

    break;
    case 1 :
       //Fight
       if(stateGame != 2)
        {
          movePlayer(&Player1);
        }
    break;
    case 2 :
       //Figther KO 
    case 3 :
       //Time UP 
       if(stopGame)
       {
         if(Player1.life != Player2.life)
         {
           if(Player1.life>Player2.life)
           {
             Player1.cptVictory++;
           }
           else
           {
             Player2.cptVictory++;
           }
         }
         stopGame=false;
       } 
       
      
    break;
    case 4 : 
    //end Player KO screen
      if(Player1.cptVictory == 3 || Player2.cptVictory == 3 ) 
      {
        if(stateGame == 2)
        {
          Player1.cptVictory = 0;
          Player2.cptVictory = 0;
          restartCombat();
        }
        else 
        {
          stateGame = 4;
        }
      }
      else 
      {
         restartCombat();
      }
    break;
  }
  
  updPlayer(&Player1,&Player2);
  updPlayer(&Player2,&Player1);
  
  //update dir player 
  if(Player1.posX<Player2.posX)
  {
    Player1.dir = NOFLIP;
    Player2.dir = FLIPH;
  }
  else 
  {
    Player1.dir = FLIPH;
    Player2.dir = NOFLIP;
  }
  
  if(playerIsAttack(Player1))
  {
    gestionAttack(&Player1,&Player2);
    
  }
  if(playerIsAttack(Player2)) 
  {
      gestionAttack(&Player2,&Player1);
  }
}

void gestionAttack(Figther * pAttack, Figther * pDef)
{
    // IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9
    byte damage = 0;
    if(pAttack->currentState == 3 || pAttack->currentState == 4)
    { 
      //4 px dist touch
      if(gb.collideRectRect(pAttack->posX - 4, pAttack->posY - 14, 14, 3, pDef->posX, (pDef->posY - pDef->height), 6, pDef->height))
      {
         damage = 5;
      }
    }
    else if(pAttack->currentState == 2 || pAttack->currentState == 8)
    {
      byte offsetY = 12;
      if(pAttack->isJump)
      {
        offsetY = 0;
      }
      //6 px dist touch
      if(gb.collideRectRect(pAttack->posX - 6, pAttack->posY - offsetY, 18, 3, pDef->posX, (pDef->posY - pDef->height), 6, pDef->height))
      {
        damage = 8;
        pAttack->timeAttack--;
        if(pAttack->currentState == 8)
        {
          playerFall(2,pDef);
        }
      }
    }
    else if(pAttack->currentState == 6)
    {
      if(gb.collideRectRect(pAttack->posX - 6, pAttack->posY - 3, 18, 3, pDef->posX, (pDef->posY - pDef->height), 6, pDef->height))
      {
        damage = 3;
        playerFall(2,pDef);
      }
    }
    
   if(pAttack->ayouken.timeLive > 0)
   {
      if(gb.collideRectRect(pAttack->ayouken.posX, pAttack->ayouken.posY, 6, 6, pDef->posX, (pDef->posY - pDef->height), 6, pDef->height))
      {
        damage = DAMAGE_AYOUKEN;
        if(pAttack->ayouken.timeLive>0)
        {
          (&pAttack->ayouken)->timeLive -= (pAttack->ayouken.timeLive>2)? 2 : 1; 
        }
        playerFall(3,pDef);
      }
      if(pDef->ayouken.timeLive > 0)
      {
        if(gb.collideRectRect(pAttack->ayouken.posX, pAttack->ayouken.posY, 6, 6, pDef->ayouken.posX, pDef->ayouken.posY, 6, 6))
        {
          if(pAttack->ayouken.timeLive>0)
          {
            (&pAttack->ayouken)->timeLive -= (pAttack->ayouken.timeLive>2)? 2 : 1; 
            (&pDef->ayouken)->timeLive -= (pDef->ayouken.timeLive>2)? 2 : 1; 
          }
        }
      }
   }
    
    if(damage)
    {
      if(pDef->isDef>0)
      {
         pAttack->timeNextAttack += 10;
        damage = damage/2;
      }
      
      pDef->life -= damage;
      if(pDef->life <0)
      {
        pDef->life = 0;
        playsoundfx(2,0);
      }
      //gestion des colisions
      if(pDef->dir == NOFLIP)
      {
        //Pdef a gauche 
        if(pDef->life > 0)
        {
          pDef->vx = -SPEED_RUN;
        }
        else 
        {
          pDef->vx = -SPEED_RUN*6;
          pDef->vy = -SPEED_RUN*6;
        }
      }
      else 
      {
        //Pdef a droite 
        if(pDef->life > 0)
        {
          pDef->vx = SPEED_RUN;
        }
        else 
        {
          pDef->vx = SPEED_RUN*6;
          pDef->vy = -SPEED_RUN*6;
        }
      }
    }
}

void playerFall(byte chance,Figther *pDef)
{
  if(random(0,chance) == 0)
  {
    pDef->currentState = 9;
    pDef->timeFall = TIME_FALL;
    changeBoundPlayer(pDef);
  }
}

void drawPlayer()
{
  drwPlayer(&Player1);
  drwPlayer(&Player2);
  //  gb.display.print(Player1.currentState);
  
  //vie P1
  gb.display.fillRect(14, 2, lifeTopixel(Player1.life), 3);
  //vie P2
  byte offsetPx = lifeTopixel(Player2.life);
  gb.display.fillRect(47 + (23-offsetPx) , 2, offsetPx , 3);
  
  for(byte i=0;i<Player1.cptVictory;i++)
  {
    //2 - 7 - 12
    gb.display.fillRect((i*5 + 2) , 8, 2 , 2);
  }
  
  for(byte i=0;i<Player2.cptVictory;i++)
  {
    //2 - 7 - 12
    gb.display.fillRect(80 - (i*5) , 8, 2 , 2);
  }
}

byte lifeTopixel(byte life)
{
  return (life*0.23);
}

void drwPlayer(Figther * player)
{
   if(player->ayouken.timeLive > 0)
  {
    gb.display.drawBitmap(player->ayouken.posX,player->ayouken.posY,(player->ayouken.timeLive>(TIME_LIVE_AYOUKEN/3))? player->ayouken.sprites.sprite1 : player->ayouken.sprites.sprite2,0,player->ayouken.dir );
  }
  
  gb.display.drawBitmap(((player->dir == NOFLIP)? player->posX : (player->posX -(player->width-6) ) ) ,(player->posY - player->height) , ((player->currentSprite == 0) ? player->sprites[player->currentState].sprite1 : player->sprites[player->currentState].sprite2 ), 0,player->dir);
}

#define SEUIL_MIN_MOVE 0.1
void updPlayer(Figther * player,Figther * other)
{
  if(gb.frameCount%player->cadance == 0)
  {
    player->currentSprite++;
    player->currentSprite = player->currentSprite%NB_SPRITE_STATE;
  }
  
  if(player->timeNextAttack>0)
  {
    player->timeNextAttack--;
  }
  if(player->timeFall>0)
  {
    player->timeFall--;
  }
  
  if(player->ayouken.timeLive > 0)
  {
    (&player->ayouken)->posX += (player->ayouken.dir == NOFLIP)? VITT_AYOUKEN : -VITT_AYOUKEN;
    (&player->ayouken)->timeLive--;
  }
  if(player->timeAttack>0)
  {
    player->timeAttack--;
  }
  
  if(player->isDef>0)
  {
    player->isDef--;
  }
  
  if(player->life>0)
  {
    if(player->timeAttack==0 && player->currentState != 0 && player->currentState != 5  && player->currentState != 9 && player->timeFall ==0)
    {
      // IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9
      if(player->currentState == 6)
        player->currentState = 5;
      else if(player->isJump)
        player->currentState = 7;
      else if(player->vx<SEUIL_MIN_MOVE && player->vx>-SEUIL_MIN_MOVE)
        player->currentState = 0;
      else 
        player->currentState = 1;
      
      changeBoundPlayer(player);
    }
  }
  else 
  {
    player->currentState = 9;
    changeBoundPlayer(player);
  }
  
  if( ((player->vx>0 && player->dir == NOFLIP) || (player->vx<0 && player->dir != NOFLIP))  && gb.collideRectRect(player->posX, (player->posY - player->height), 8, player->height, other->posX, (other->posY - other->height), 8, other->height))
  {
    player->vx = 0;
  }
  
  if(!player->isJump)
  {
    if(player->vx!=0)
    {
      player->posX += player->vx;
      player->vx = player->vx*0.4;//on ralentie rapidement
    }
    else if(player->vx<SEUIL_MIN_MOVE && player->vx>-SEUIL_MIN_MOVE)
    {
      player->vx = 0;
    }
  }
  else 
  {
    if(player->vy<-1.2)
    {
      player->vy *= 0.9;
      player->posY += player->vy;
    }
    else
    {
      if(player->vy<0) player->vy = -player->vy;
      player->vy *= 1.3;
      player->posY += player->vy;
    }
    player->posX += player->vx;
    player->vx = player->vx*0.9;//on ralentie rapidement
    
    if(player->posY>= GROUND_Y)
    {      
      player->posY = GROUND_Y;
      player->isJump = false;
      player->vy = 0;
      player->vx = 0;
      player->timeAttack = 0;
    }
  }
  
  if(player->posX<0)
  {
    player->posX = 0;
  }
  else if((player->posX + player->width) >84)
  {
    player->posX = (84 - player->width);
  }
}



void movePlayerSlave()
{
   if(gb.buttons.repeat(BTN_RIGHT, 1))
  {
    bt_right = true;
  }
  else if(gb.buttons.repeat(BTN_LEFT, 1))
  {
    bt_left = true;
  }
  if(gb.buttons.pressed(BTN_UP))
  {
    bt_up = true;
  }
  else if(gb.buttons.repeat(BTN_DOWN, 1))
  {
    bt_down = true;
  }
  
  if(gb.buttons.pressed(BTN_A))
  {
    playsoundfx(1,0);
     bt_a = true;
  }
  else if(gb.buttons.pressed(BTN_B))
  {
    playsoundfx(0,0);
    bt_b = true;
  }
}

void movePlayer(Figther * player)
{
  if(gb.buttons.repeat(BTN_RIGHT, 1))
  {
    rightFigther(player);
  }
  else if(gb.buttons.repeat(BTN_LEFT, 1))
  {
    leftFigther(player);
  }
  if(gb.buttons.pressed(BTN_UP))
  {
    highFigther(player);
  }
  else if(gb.buttons.repeat(BTN_DOWN, 1))
  {
    bottomFigther(player);
  }
  
  if(gb.buttons.pressed(BTN_A))
  {
    punchFigther(player);
  }
  else if(gb.buttons.pressed(BTN_B))
  {
    kickFigther(player);
  }
}

void moveIAPlayer(Figther * player,Figther * human)
{
  //return;
  if(stateFight == 1)
  {
    byte isFireBall = 0;
    byte isCrunch = 0;
    byte fuiteStrategique = 0;
    byte dist = abs(player->posX - human->posX);
    
    //Brain storming
    if(human->currentState == 5 || human->currentState == 6 || human->currentState == 9)
    {
      isCrunch = 5;
    }
    int8_t diffLife = player->life - human->life;
    if(human->ayouken.timeLive>0)
    {
      isFireBall = 5;
    }
    if(isCrunch>0 && diffLife>0)
    {
      fuiteStrategique = 10;
    }
    
    byte rdm = random(0,100);
    
    //Attack ?
    if(rdm <=(20 - isCrunch + diffLife - dist))
    {
      punchFigther(player);
    }
    else if(rdm >65 && rdm <90 - dist +diffculty)
    {
      kickFigther(player);
    }
    else if(rdm >45 && rdm <(48 + isCrunch + fuiteStrategique - diffLife + isFireBall))
    {
      bottomFigther(player);
      if(player->dir == NOFLIP) rightFigther(player);
      else leftFigther(player);
      punchFigther(player);
    }
    
    //Move
    if(rdm >(95-fuiteStrategique+diffLife -diffculty ))
    {
      //backward
      if(player->dir != NOFLIP) rightFigther(player);
      else leftFigther(player);
    }
    else if(rdm <=(40+isCrunch+diffLife-fuiteStrategique+diffculty))
    {
      if(player->dir == NOFLIP) rightFigther(player);
      else leftFigther(player);
    }
    if(rdm >19 && rdm <25 + isFireBall)
    {
      highFigther(player);
    }
    else if(rdm >(39-isCrunch+diffLife) && rdm <45+isCrunch)
    {
      bottomFigther(player);
    }
  }
}

// IDL : 0 ,run : 1, kick : 2, punchLeft : 3, punchRight : 4,  duck1 : 5, duck1Kick : 6,jump1 : 7,jumpKick1 : 8 , dead1 : 9
void leftFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(addToCombo(player,((player->dir == NOFLIP)? 4 : 3)))
    return;
  if(!player->isJump)
  {
    
    if(player->dir == NOFLIP)
    {
      //recule
      player->isDef = TIME_DEF;
      
      if(player->timeNextAttack>0)
        return;
      player->vx =  -SPEED_RUN/2;
    }
    else 
    {
      
      if(player->timeNextAttack>0)
        return;
      //avance
      player->vx =  -SPEED_RUN;
    }
  
    if(!playerIsAttack(*player)) player->currentState = 1;
  }
  else 
  {
    
    if(player->timeNextAttack>0)
      return;
    if(player->vx>-SPEED_RUN) player->vx -= 0.1;
  }
  
    changeBoundPlayer(player);
}

void rightFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(addToCombo(player,((player->dir == NOFLIP)? 3 : 4)))
    return;
  if(!player->isJump)
  {
    if(player->dir == FLIPH)
    {
      //recule
      player->isDef = TIME_DEF;
      
      if(player->timeNextAttack>0)
        return;
      player->vx =  SPEED_RUN/2;
    }
    else 
    {
      if(player->timeNextAttack>0)
        return;
      //avance
      player->vx =  SPEED_RUN;
    }
    if(!playerIsAttack(*player))player->currentState = 1;
  }
  else 
  {
      if(player->timeNextAttack>0)
        return;
    if(player->vx<SPEED_RUN) player->vx += 0.1;
  }
    changeBoundPlayer(player);
}

void highFigther(Figther * player)
{
  if(player->timeNextAttack>0)
    return;
  if(player->life==0)
    return;
  if(addToCombo(player,1))
    return;
 if(!player->isJump)
 {
    player->currentState = 7;
    changeBoundPlayer(player);
    player->isJump = true;
    player->vy = -SPEED_RUN;
 }
}

void bottomFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(player->timeNextAttack>0)
    return;
  if(addToCombo(player,2))
    return;
  player->currentState = 5;
  changeBoundPlayer(player);
}

void punchFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(player->timeNextAttack>0)
    return;
  playsoundfx(1,0);
 
  if(addToCombo(player,5))
    return;
  if(player->currentState == 5)
  {
     player->currentState = 6;
     player->timeAttack = TIME_ATTACK;
  }
  else if(!player->isJump)
  {
    player->currentState = random(3,5);
    player->timeAttack = TIME_ATTACK;
  }
  else 
  {
    player->currentState = 8;
    player->timeAttack = TIME_ATTACK*4;
  }
  player->timeNextAttack = TIME_ATTACK+1; // puch are fast 
  changeBoundPlayer(player);
}

void kickFigther(Figther * player)
{
  if(player->life==0)
    return;
  if(player->timeNextAttack>0)
    return;
  playsoundfx(0,0);
  if(addToCombo(player,6))
    return;
  if(player->currentState == 5)
 {
   player->currentState = 6;
   player->timeAttack = TIME_ATTACK;
 }
 else  if(!player->isJump)
 {
  player->timeAttack = TIME_ATTACK;
  player->currentState = 2;
 }
 else 
 {
    player->timeAttack = TIME_ATTACK*4;
  player->currentState = 2;
 }
  player->timeNextAttack = TIME_ATTACK+3; // Kick are slow 
  changeBoundPlayer(player);
}

void changeBoundPlayer(Figther * player)
{
  player->width = pgm_read_byte(player->sprites[player->currentState].sprite1);
  player->height = pgm_read_byte(player->sprites[player->currentState].sprite1 + 1);
}

boolean playerIsAttack(Figther player)
{
  return (player.timeAttack>0 || player.ayouken.timeLive > 0);
}

boolean addToCombo(Figther *player, byte moveTouch) // moveTouch : 1=>up, 2=>down, 3=>forward, 4=>backward, 5=>A, 6=>B
{
  if(player->combo[0] == moveTouch)
    return false;
  for(byte i=(NB_MOVE_SAVE-1);i>0;i--)
  {
    player->combo[i] = player->combo[i-1];
  }
  player->combo[0] = moveTouch;
  
  if(player->ayouken.timeLive == 0 && player->combo[0] == 5 && player->combo[1] == 3 && player->combo[2] == 2 )
  {
    //gb.popup(F("AYOUKEN"),5);
    //test combo et fire ball
    player->currentState = 10;
    (&player->ayouken)->timeLive = TIME_LIVE_AYOUKEN;
    (&player->ayouken)->posX = player->posX;
    (&player->ayouken)->posY = (player->posY - 8);
    (&player->ayouken)->dir = player->dir;
    player->timeNextAttack = TIME_ATTACK+5; //fire ball are very slow
    return true;
  }
  
  return false;
}

const uint8_t soundfx[3][8] = {
    {0,22,54,1,7,0,7,10}, // coup de pied {1,14,25,6,1,4,1,12}
    {0,22,48,1,7,5,7,10}, // coup de poing{1,42,31,2,1,3,1,22}
    {0,24,55,1,0,0,7,7} //mort selon jerom
};

void playsoundfx(uint8_t fxno, uint8_t channel) {
    gb.sound.command(0,soundfx[fxno][6],0,channel);
    // set volume
    gb.sound.command(1,soundfx[fxno][0],0,channel);
    // set waveform
    gb.sound.command(2,soundfx[fxno][5],-soundfx[fxno][4],channel);
    // set volume slide
    gb.sound.command(3,soundfx[fxno][3],soundfx[fxno][2]-58,channel);
    // set pitch slide
    gb.sound.playNote(soundfx[fxno][1],soundfx[fxno][7],channel);
    // play note
}


