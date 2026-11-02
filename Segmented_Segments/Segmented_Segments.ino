//This file has test cycles and test cycles only. This is a first version.

const int DATA_PIN  = 11;  // SER
const int CLOCK_PIN = 13;  // SRCLK
const int LATCH_PIN = 10;  // RCLK

// Typical 14-segment bit definitions
enum Segments {
  SEG_A  = 0,
  SEG_B  = 1,
  SEG_C  = 2,
  SEG_D  = 3,
  SEG_E  = 4,
  SEG_F  = 5,
  SEG_G1 = 6,
  SEG_G2 = 7,
  SEG_H  = 8,
  SEG_I  = 9,
  SEG_J  = 10,
  SEG_K  = 11,
  SEG_L  = 12,
  SEG_M  = 13
};

// 16-bit value used even though only 14 segments exist
void writeSegments(uint16_t pattern)
{
  digitalWrite(LATCH_PIN, LOW);

  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, highByte(pattern));
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, lowByte(pattern));

  digitalWrite(LATCH_PIN, HIGH);
}

// Approximate font table
struct CharacterMap {
  char c;
  uint16_t pattern;
};

CharacterMap fontTable[] =
{
  {'0', 0b0000000000111111},
  {'1', 0b0000000000000110},
  {'2', 0b0000000011011011},
  {'3', 0b0000000010001111},
  {'4', 0b0000000011100110},
  {'5', 0b0000000011101101},
  {'6', 0b0000000011111101},
  {'7', 0b0000000000000111},
  {'8', 0b0000000011111111},
  {'9', 0b0000000011101111},

  {'A', 0b0011111101110111},
  {'B', 0b0011010110001111},
  {'C', 0b0000000000111001},
  {'D', 0b0011000100001111},
  {'E', 0b0000000011111001},
  {'F', 0b0000000011110001},
  {'G', 0b0000000010111101},
  {'H', 0b0011111101110110},
  {'I', 0b0011000100001001},
  {'J', 0b0000000000011110},
  {'K', 0b1100110001110000},
  {'L', 0b0000000000111000},
  {'M', 0b0001010100110110},
  {'N', 0b1001010100110110},
  {'O', 0b0000000000111111},
  {'P', 0b0011111101110011},
  {'Q', 0b1000000000111111},
  {'R', 0b1011111101110011},
  {'S', 0b0000000011101101},
  {'T', 0b0011000100000001},
  {'U', 0b0000000000111110},
  {'V', 0b0100010000110000},
  {'W', 0b1000010100110110},
  {'X', 0b1101000100000000},
  {'Y', 0b0010100100000110},
  {'Z', 0b0100010000001001},
};

const int FONT_COUNT = sizeof(fontTable) / sizeof(fontTable[0]);

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
}

void loop()
{
  // Test 1: Segment chase
  for (int segment = 0; segment < 14; segment++)
  {
    writeSegments(1 << segment);
    delay(250);
  }

  delay(1000);

  // Test 2: Numbers 0-9
  for (int i = 0; i < 10; i++)
  {
    writeSegments(fontTable[i].pattern);
    delay(500);
  }

  delay(1000);

  // Test 3: Letters A-Z
  for (int i = 10; i < FONT_COUNT; i++)
  {
    writeSegments(fontTable[i].pattern);
    delay(500);
  }

  delay(1000);

  // Test 4: All segments on
  writeSegments(0x3FFF);
  delay(2000);

  // Test 5: All segments off
  writeSegments(0x0000);
  delay(1000);
}
