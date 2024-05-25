#include <SoftwareSerial.h>

// Decralation for NPK sensor
#define DE 6
#define RE 7
#define DI 2
#define RO 1

const byte nitro[] = { 0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c };
const byte phos[] = { 0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc };
const byte pota[] = { 0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0 };

byte values[11];
SoftwareSerial mod(DI, RO);
byte nitro_val, phos_val, pota_val;

// Methode to initialize NPK sensor
void initializeNPK() {
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  mod.begin(9600);
}

void DE_RE_State(bool state) {
  digitalWrite(DE, state);
  digitalWrite(RE, state);
}

byte nitrogen() {
  DE_RE_State(HIGH);
  delay(50);
  if (mod.write(nitro, sizeof(nitro)) == 8) {
    DE_RE_State(LOW);
    for (byte i = 0; i < 7; i++) values[i] = mod.read();
  }
  return values[4];
}

byte phosphorous() {
  DE_RE_State(HIGH);
  delay(50);
  if (mod.write(phos, sizeof(phos)) == 8) {
    DE_RE_State(LOW);
    for (byte i = 0; i < 7; i++) values[i] = mod.read();
  }
  return values[4];
}

byte potassium() {
  DE_RE_State(HIGH);
  delay(50);
  if (mod.write(pota, sizeof(pota)) == 8) {
    DE_RE_State(LOW);
    for (byte i = 0; i < 7; i++) values[i] = mod.read();
  }
  return values[4];
}