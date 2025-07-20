// Dual ICM-20948 SPI IMU Sensor Communication with ESP32
// Goal: Alternately read accelerometer and gyroscope data from both IMUs using SPI

#include "ICM_20948.h" // Library: http://librarymanager/All#SparkFun_ICM_20948_IMU

#define USE_SPI
#define SERIAL_PORT Serial

SPIClass SPI_PORT(VSPI);  // Using VSPI on ESP32

#define CS_PIN     16      // Chip Select for Sensor 1
#define CS_PIN_2   21      // Chip Select for Sensor 2

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
bool m;                    // Alternating sensor selector

#ifdef USE_SPI
ICM_20948_SPI myICM;       // Common IMU object reused for both sensors
#else
ICM_20948_I2C myICM;
#endif

bool initialized = false;

void setup() {
  pinMode(CS_PIN_2 , OUTPUT);
  pinMode(CS_PIN , OUTPUT);
  SERIAL_PORT.begin(115200);
  m = true; // Start with sensor 2
}

void loop() {
  while (!SERIAL_PORT);

  // Toggle sensor selection
  m = !m;

  // Set CS logic
  if (m == 0) {
    digitalWrite(CS_PIN_2, HIGH);  // Disable sensor 2
  } else {
    digitalWrite(CS_PIN, HIGH);    // Disable sensor 1
  }

  // Begin SPI for selected sensor
  if (m == 0) {
    SPI_PORT.begin(4, 19, 23, CS_PIN);  // SCLK, MISO, MOSI, CS1
  } else {
    SPI_PORT.begin(4, 19, 23, CS_PIN_2);  // SCLK, MISO, MOSI, CS2
  }

  myICM.enableDebugging();

  while (!initialized) {
    if (m == 0) {
      myICM.begin(CS_PIN, SPI_PORT, 1000000);
    } else {
      myICM.begin(CS_PIN_2, SPI_PORT, 1000000);
    }

    if (myICM.status != ICM_20948_Stat_Ok) {
      SERIAL_PORT.println("Trying again...");
      delay(500);
    } else {
      initialized = true;
    }
  }

  // Read IMU data if available
  if (myICM.dataReady()) {
    myICM.getAGMT();
    accX = myICM.accX();
    accY = myICM.accY();
    accZ = myICM.accZ();
    gyroX = myICM.gyrX();
    gyroY = myICM.gyrY();
    gyroZ = myICM.gyrZ();
    delay(30);
  } else {
    SERIAL_PORT.println("Waiting for data");
    delay(500);
  }

  // Print data
  if (m == 0) {
    Serial.println("Output from sensor 1");
  } else {
    Serial.println("Output from sensor 2");
  }

  Serial.print(accX); Serial.print(",");
  Serial.print(accY); Serial.print(",");
  Serial.print(accZ); Serial.print(",");
  Serial.print(gyroX); Serial.print(",");
  Serial.print(gyroY); Serial.print(",");
  Serial.println(gyroZ);
}
