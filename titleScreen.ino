
const byte sfStartMenu[] PROGMEM = {64,30,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xF8,0x0,0x6,0x73,0x0,0x0,0x0,0x3,0x4,0x6,0x19,0x5C,0x80,0x0,0x0,0x4,0xC,0x3A,0x26,0x53,0x0,0x0,0x0,0x8,0x73,0xA6,0x48,0x4C,0x0,0x0,0x0,0x8,0x8C,0xB4,0x4E,0xA8,0x0,0x0,0x0,0x4,0x51,0x94,0x9E,0xB4,0x0,0x0,0x0,0x2,0x52,0x16,0xFC,0xEE,0x0,0x0,0x0,0x2,0x5A,0x3E,0x70,0xE7,0x0,0x0,0x0,0xC,0xCB,0x38,0x0,0x0,0x0,0x0,0x0,0x31,0x8F,0x0,0x7,0xFF,0xFF,0x0,0x0,0x47,0xC,0x7,0xF8,0x0,0x2,0x0,0x0,0x3E,0x3,0x88,0x7,0xFC,0xFC,0xFC,0x0,0x18,0x3C,0xCF,0xF8,0x5,0x0,0x43,0x0,0x7,0xC3,0x0,0x7,0x75,0x7F,0x40,0x80,0x38,0xC,0x1,0xF5,0x55,0x41,0x4C,0x40,0x40,0x30,0x6,0x15,0x55,0x5F,0x4A,0x40,0x4C,0x40,0x68,0x65,0x55,0x41,0x4C,0x40,0x74,0x4E,0xA9,0x85,0x55,0x5F,0x40,0x80,0x44,0x72,0xAA,0x5,0xD5,0x5F,0x44,0x80,0x4,0xE,0xAA,0x74,0x15,0x41,0x4A,0x40,0x8,0x70,0xAA,0x95,0xD5,0x7F,0x49,0x20,0x4,0x40,0xAB,0xB5,0x57,0x7F,0x58,0xF0,0x4,0x40,0xA4,0x27,0x73,0x0,0xF0,0x70,0x4,0x40,0xA3,0xE3,0x30,0x1,0xE0,0x20,0x3,0x20,0xA0,0xE0,0x0,0x0,0xC0,0x0,0x3,0xE0,0xE0,0x0,0x0,0x0,0x0,0x0,0x3,0xE0,0xC0,0x0,0x0,0x0,0x0,0x0,0x0,0xE0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};

void goTitleScreen()
{
  gb.titleScreen(sfStartMenu);
  initGame();
}

