# Photosynthesis Monitor (Arduino UNO)

Arduino sketch reconstructed from the supplied photos. It reads:
- an LDR light sensor on A0,
- a thermistor circuit on A1,
- and displays temperature, light reading, and estimated efficiency on a 16x2 LCD.

An RGB LED indicates the efficiency band:
- 70–100%: green (Good)
- 40–69%: blue (Med)
- 0–39%: red (Low), with the buzzer on

## Hardware / pin mapping

| Component | Arduino pin |
|---|---|
| 16x2 LCD (RS, E, D4, D5, D6, D7) | 12, 11, 5, 4, 3, 2 |
| LDR analog output | A0 |
| Thermistor divider output | A1 |
| Red LED | 9 |
| Green LED | 10 |
| Blue LED | 6 |
| Buzzer | 8 |

The thermistor calculation assumes a 10 kΩ NTC thermistor and a 10 kΩ reference resistor, using Beta = 3950 and nominal temperature 298.15 K.

## Upload

1. Open `photosynthesis.ino` in Arduino IDE.
2. Select **Arduino Uno** and the correct serial port.
3. Install/use the built-in **LiquidCrystal** library.
4. Verify, then upload.

## Notes

This is a cleaned-up reconstruction, not a byte-for-byte transcription: the photographed code ends partway through the final `else if` branch. The missing low-efficiency branch and loop ending have been completed so the sketch is structurally complete. The photographed `efficiency == 20;` was corrected to `efficiency = 20;` because the surrounding condition clearly intends to set the value.
