// Libraries importeren
#include <BH1750.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

// Pinnen definiëren
#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)

// Sensor definiëren
BH1750 lightMeter;
Adafruit_BMP280 bmp; // I2C

// Setup word 1 keer uitgevoerd
void setup()
{
    // Start serial monitor
    Serial.begin(9600);
    // Initialize the I2C bus (BH1750 library doesn't do this automatically)
    Wire.begin();
    lightMeter.begin();
    if (!bmp.begin(0x76))
    {
        Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                         "try a different address!"));
        while (1)
            delay(10);
    }

    // Default settings from datasheet.
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

// Loop blijft draaien
void loop()
{
    Serial.println("Marnick Goossens 1IT05");

    // Uitlezen van licht sensor en de data printen
    float lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    // Uitlezen van de temperatuur uit de BMP280 en de data printen
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    // Uitlezen van de druk uit de BMP280 en de data printen
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    // Uitlezen van de hoogte uit de BMP280 en de data printen
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");
    Serial.println("----------------------");

    // Wacht 1 seconden voor de loop terug start
    delay(1000);
}
