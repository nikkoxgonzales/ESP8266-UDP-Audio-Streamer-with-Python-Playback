### 📡 ESP8266 UDP Audio Streamer with Python Playback

---

## 📖 README

### **ESP8266 UDP Audio Streamer with Python Playback**

A project that captures audio using an ESP8266 microcontroller, applies gain control, and streams it over UDP to a Python-based receiver for playback. This setup enhances audio volume and quality, making it ideal for applications like wireless audio transmission and remote monitoring.

---

### **🔧 Features**

- **Volume Control:** Adjustable gain to increase audio output volume.
- **High-Quality Audio:** Optimized for clear and distortion-free sound.
- **Real-Time Streaming:** Low-latency audio transmission over WiFi using UDP.
- **Cross-Platform Playback:** Compatible with Python on Windows, macOS, and Linux.
- **Easy Setup:** Comprehensive instructions for quick deployment.

---

### **⚙️ Requirements**

#### **Hardware**

- **ESP8266 Development Board** (e.g., NodeMCU, Wemos D1 Mini)
- **I2S Microphone Module** (e.g., INMP441)
- **Jumper Wires**
- **USB Cable** for programming the ESP8266

#### **Software**

- **Arduino IDE** for uploading firmware to ESP8266
- **Python 3.x** installed on the receiver machine
- **PyAudio Library** for audio playback
- **Numpy Library** for audio processing

---

### **🛠 Installation**

#### **1. Setup ESP8266 Firmware**

Use [FakeCH340DriverFixer](https://github.com/SHWotever/FakeCH340DriverFixer) if you're having issues with communicating with ESP8266

1. **Install Arduino IDE:**
   - Download and install from [Arduino Official Website](https://www.arduino.cc/en/software).

2. **Add ESP8266 Board to Arduino IDE:**
   - Go to `File` > `Preferences`.
   - In the "Additional Board Manager URLs" field, add:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Navigate to `Tools` > `Board` > `Boards Manager`, search for "ESP8266" and install.

3. **Connect ESP8266 to Your PC:**
   - Use a USB cable to connect the ESP8266 board to your computer.

4. **Upload the Firmware:**
   - Open the provided `ESP8266_Audio_Stream.ino` sketch.
   - Configure the WiFi credentials and listener IP address in the code.
   - Select the appropriate board and port from `Tools` menu.
   - Click the upload button to flash the firmware to the ESP8266.

#### **2. Setup Python Receiver**

1. **Install Python 3.x:**
   - Download and install from [Python Official Website](https://www.python.org/downloads/).

2. **Install Required Libraries:**
   - Open a terminal or command prompt and run:
     ```bash
     pip install pyaudio numpy
     ```

3. **Download the Python Script:**
   - Save the provided `udp_audio_receiver.py` script to your desired directory.

4. **Run the Python Receiver:**
   - Navigate to the script directory in the terminal.
   - Execute the script:
     ```bash
     python udp_audio_receiver.py
     ```
   - Ensure your firewall allows traffic on the specified UDP port.

---

### **🎛 Usage**

1. **Power Up the ESP8266:**
   - Once the firmware is uploaded, reset the ESP8266 to start streaming audio.

2. **Start the Python Receiver:**
   - Run the `udp_audio_receiver.py` script on your PC.
   - The receiver will listen for incoming audio streams and play them in real-time.

3. **Adjusting Volume:**
   - Modify the `GAIN` variable in both the Arduino and Python code to increase or decrease the audio volume as needed.

---

### **📂 Repository Structure**

```
ESP8266-UDP-Audio-Streamer/
├── Arduino/
│   └── ESP8266_Audio_Stream.ino
├── Python/
│   └── udp_audio_receiver.py
├── README.md
```

---

### **🧡 Acknowledgements**

- **ESP8266 Community:** For their extensive resources and support.
- **PyAudio and Numpy Developers:** For providing robust libraries essential for this project.

---


### **📚 References**

- [ESP8266 Arduino Core](https://github.com/esp8266/Arduino)
- [PyAudio Documentation](https://people.csail.mit.edu/hubert/pyaudio/docs/)
- [Numpy Documentation](https://numpy.org/doc/)
- [ESP8266-BUG-I2S-MIC](https://github.com/aleiei/ESP8266-BUG-I2S-MICp)
- [FakeCH340DriverFixer](https://github.com/SHWotever/FakeCH340DriverFixer)
---
