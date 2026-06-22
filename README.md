Smart Bilirubin Detector



Project Overview

The Smart Bilirubin Detector is a portable, non‑invasive system designed to measure bilirubin levels and classify jaundice severity for both neonates and adults. By combining RGB color sensing with photodiode measurements, this device estimates bilirubin concentration and displays real‑time results. A complementary Python ML script processes serial data to provide refined predictive outputs.



This system aims to offer a low‑cost, accessible screening tool for early jaundice detection.

 Technology Stack



Hardware

\- \*\*ESP32 microcontroller\*\*

\- \*\*Adafruit TCS34725 RGB Color Sensor\*\*

\- \*\*Photodiode sensor\*\*

\- \*\*OLED Display (128×64)\*\*

\- \*\*2 LEDs\*\* for illumination

\- \*\*Push button\*\* for mode selection



Software

\- \*\*PlatformIO / Arduino (C++)\*\* for embedded firmware

\- \*\*Python\*\* for post‑processing and prediction  

\- \*\*Machine Learning models\*\* (scikit‑learn, pickle serialization)



Libraries Used

\- `Adafruit\_TCS34725`

\- `Adafruit\_GFX`

\- `Adafruit\_SSD1306`

\- `Wire`

\- `numpy`

\- `pickle`

\- `scikit‑learn`


Folder Structure


Smart-Bilirubin-Detector/

├── src/ ← Microcontroller code

│ └── main.ino

├── include/ ← Additional headers

├── lib/ ← (Optional) custom libraries

├── platformio.ini ← Build configuration

├── pythonpredictor.py ← Python prediction script

├── jaundice\_models.pkl ← Pretrained ML models

└── README.md ← Project documentation


 How It Works

 ESP32 Firmware

The ESP32 reads data from the RGB sensor and photodiode, normalizes values, and computes an approximate bilirubin level. It also displays results on the OLED and prints data over serial for further processing.



\- \*\*Mode button:\*\*  

&nbsp; - Pressed → Neonate mode  

&nbsp; - Released → Adult mode



\- \*\*Outputs shown:\*\*  

&nbsp; - RGB raw values  

&nbsp; - Estimated bilirubin from RGB \& photodiode  

&nbsp; - Final computed level  

&nbsp; - Jaundice category (Normal/Medium/High)



Python Prediction Script



The `pythonpredictor.py` script:

1\. Reads serial data from the ESP32.

2\. Normalizes input features.

3\. Loads pretrained models (neonate \& adult).

4\. Predicts jaundice label using ML.

5\. Prints final prediction to console.


Demo Video



Watch the full working demo here:  

👉 https://drive.google.com/file/d/1oEVtNsYqZdv\_h8SNsW02Z2oQ28EmeK40/view?usp=drivesdk



 How to Use



1\. Connect the ESP32 board to your computer.

2\. Upload the firmware from the `src/` folder using PlatformIO.

3\. Ensure the RGB sensor and photodiode are properly wired.

4\. Open a serial monitor at \*\*9600 baud\*\* to view raw sensor data.

5\. Run `pythonpredictor.py` to see machine learning‑based predictions.

6\. Use the mode button to toggle between \*\*Adult\*\* and \*\*Neonate\*\* settings.




 Author



\*\*MED\_HACKERS\*\*  

WINNER OF DEEPSPRINT HACKATHON - CHENNAI INSTITUTE OF TECHNOLOGY

OUTPUT IMAGES
<img width="720" height="1280" alt="image" src="https://github.com/user-attachments/assets/e56dfd57-d0d5-40b4-99bc-c03571b7a1e2" />

<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/22954ecf-d9d3-42cc-bb47-9f2c9951afbf" />

<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/6349d448-ae33-43e5-b851-7cbae94dc09f" />






