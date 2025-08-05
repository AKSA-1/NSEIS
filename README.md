# NeuralSense Environmental Intelligence System (NSEIS)

**A** compact, IoT-based system for real-time air quality and meteorological monitoring. Using low-power sensors and **cloud analytics, it provides accurate pollutant and climate assessments for smart cities, homes, and environmental studies.**

## 📋 Table of Contents

* [Features](https://www.google.com/search?q=%23-features)

* [Components Required](https://www.google.com/search?q=%23-components-required)

* [Hardware Setup](https://www.google.com/search?q=%23-hardware-setup)

  * [Pin Connections](https://www.google.com/search?q=%23pin-connections)

  * [Wiring Diagram](https://www.google.com/search?q=%23wiring-diagram)

* [Software & Libraries](https://www.google.com/search?q=%23-software--libraries)

* [Cloud](https://www.google.com/search?q=%23-cloud-setup-firebase) Setup (Firebase)

* [Getting Started](https://www.google.com/search?q=%23-getting-started)

  * [1. Setup Arduino IDE](https://www.google.com/search?q=%231-setup-arduino-ide)

  * [2. Install Libraries](https://www.google.com/search?q=%232-install-libraries)

  * [3. Configure the Code](https://www.google.com/search?q=%233-configure-the-code)

  * [4. Upload to NodeMCU](https://www.google.com/search?q=%234-upload-to-nodemcu)

* [Future Enhancements](https://www.google.com/search?q=%23-future-enhancements)

* [Contributing](https://www.google.com/search?q=%23-contributing)

* [License](https://www.google.com/search?q=%23-license)

## ✨ Features

* **Real-Time Monitoring**: Measures Temperature, Humidity, and Air Quality (VOCs, smoke, CO2).

* **Wi-Fi Enabled**: Uses the ESP8266 to send data wirelessly to the cloud.

* **Cloud Integration**: Seamlessly connects to cloud platforms like Firebase or Thingspeak for data storage and analysis.

* **Data Visualization**: Data can be viewed on web and mobile dashboards.

* **Low Power & Compact**: Ideal for deployment in various indoor and outdoor environments.

* **Extensible**: Easily add more sensors or integrate with other systems.

## 🛠️ Components Required

| Component | Purpose | 
| ----- | ----- | 
| NodeMCU ESP8266 V3 (LUA CH340) | Wi-Fi enabled microcontroller | 
| MQ-135 Gas Sensor Module | Detects air pollutants (VOCs, Smoke) | 
| DHT11 Temperature & Humidity Sensor | Measures temperature and humidity | 
| Breadboard | For creating the circuit | 
| Jumper Wires | To connect the components | 
| Micro-USB Cable | To power and program the NodeMCU | 

## 🔌 Hardware Setup

### Pin Connections

Connect the components according to the table below. It's recommended to use a breadboard to keep the connections stable.

| Sensor | Sensor Pin | NodeMCU ESP8266 Pin | 
| ----- | ----- | ----- | 
| **DHT11** (Temp/Humidity) | VCC / `+` | `3V3` | 
|  | GND / `-` | `GND` | 
|  | DATA / OUT | `D4` (GPIO2) | 
| **MQ-135** (Air Quality) | VCC | `3V3` | 
|  | GND | `GND` | 
|  | `AOUT` | `A0` | 

### Wiring Diagram

This visual diagram shows the complete circuit layout on a breadboard.

## 💻 Software & Libraries

### Software

* [**Arduino IDE**](https://www.arduino.cc/en/software): The development environment used to program the NodeMCU.

### Arduino Libraries

You will need to install the following libraries through the Arduino IDE's Library Manager (`Sketch` > `Include Library` > `Manage Libraries...`):

1. **DHT** sensor **library** by Adafruit

2. **Adafruit Unified Sensor** by Adafruit

3. **Firebase ESP8266 Client** by Mobizt (if using Firebase)

4. **ThingSpeak** by MathWorks (if using ThingSpeak)

## ☁️ Cloud Setup (Firebase)

This guide uses Firebase as the cloud backend.

1. **Create a Firebase Project**: Go to the [Firebase Console](https://console.firebase.google.com/) and create a new project.

2. **Create a Realtime Database**:

   * In your project, go to `Build` > `Realtime Database`.

   * Click `Create Database` and start in **test mode** (this allows read/write access without authentication for development).

   * **Important**: For production, you should set up proper security rules.

3. **Get Credentials**:

   * Find your **Database** URL on the Realtime Database dashboard. It will look like `https://your-project-name-default-rtdb.firebaseio.com/`.

   * Go to `Project settings` (gear icon) > `Service accounts`.

   * Click `Database secrets` and copy your **Database** secret (legacy **token)**.

## 🚀 Getting Started

### 1. Setup Arduino IDE

* Open Arduino IDE.

* Go to `File` > `Preferences`.

* Add the following URL to the `Additional Boards Manager URLs` field:

  ```
  [http://arduino.esp8266.com/stable/package_esp8266com_index.json](http://arduino.esp8266.com/stable/package_esp8266com_index.json)
  
  ```

* Go to `Tools` > `Board` > `Boards Manager...`, search for `esp8266`, and install the package.

* Select your board: `Tools` > `Board` > `NodeMCU 1.0 (ESP-12E Module)`.

### 2. Install Libraries

* Open the Library Manager (`Sketch` > `Include Library` > `Manage Libraries...`).

* Search for and install the libraries listed in the [Software & Libraries](https://www.google.com/search?q=%23-software--libraries) section.

### 3. Configure the Code

* Copy the Arduino code from the `src/` directory of this repository (or create a new sketch).

* Update the following placeholder values in the code with your credentials:

```
// Wi-Fi Credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Firebase Credentials
#define FIREBASE_HOST "YOUR_FIREBASE_PROJECT_URL" // without "https://"
#define FIREBASE_AUTH "YOUR_FIREBASE_DATABASE_SECRET"

```

### 4. Upload to NodeMCU

* Connect your NodeMCU to your computer via a micro-USB cable.

* Select the correct COM port under `Tools` > `Port`.

* Click the `Upload` button in the Arduino IDE. The code will be compiled and flashed to the device.

* Open the `Serial Monitor` (`Tools` > `Serial Monitor`) with a baud rate of `115200` to see a sensor readings and status messages.

## 🔮 Future Enhancements

* **Machine Learning**: Implement a TensorFlow Lite model on-device (TinyML) or in the cloud to predict air quality trends and detect anomalies.

* **Custom Dashboard**: Build a web dashboard using React or Vue.js to visualize data with custom charts and alerts.

* **More Sensors**: Integrate additional sensors like a dust sensor (PM2.5), UV sensor, or a barometer.

* **Mobile App**: Create a mobile application with Flutter or React Native for push notifications and on-the-go monitoring.

## 🤝 Contributing

Contributions are welcome! If you have ideas for improvements or find any issues, please open an issue or submit a pull request.

1. Fork the Project.

2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`).

3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`).

4. Push to the Branch (`git` push origin` feature/AmazingFeature`).

5. Open a Pull Request.

## 📄 License

This project is licensed under the **MIT License**. See the `LICENSE` file for more details.
