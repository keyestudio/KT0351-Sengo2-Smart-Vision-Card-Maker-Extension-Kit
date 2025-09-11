# 3.1 Arduino IDE

Arduino IDE is an integrated development environment dedicated to Arduino which is an open-source electronics platform based on easy-to-read interface and simplified programming process, aimed at students without a background in electronics. 

Its clear interface, syntax highlighting and auto-completion functions make the programming process easy and enjoyable. It also offers a wealth of tutorials, sample codes, and community support to help beginners get started quickly and solve practical  problems.

Importantly, it is published as an open source tool. Therefore,  it not only accelerates users own learning process by utilizing and referring others’ works, it is also available for extension experienced programmers to freely access, modify and distribute codes.

In one word, Arduino IDE is easy-to-use for beginners, yet flexible enough for advanced users to take advantage of as well.

# 3.2  For Windows

**Attention please, the Arduino IDE version used here is 2.3.6. For other versions, the provided codes may not be compiled or uploaded.** 

## 3.2.1 Download Arduino IDE

Enter Arduino official to download [Software | Arduino](https://www.arduino.cc/en/software/).

Arduino boasts multiple versions such as Widows, mac and Linux(as shown below), please ensure that the one you download is compatible with your computer.

Here, we will take **Windows Win 10 or newer(64-bit)** as an example to introduce how to download it. You may also choose the **Windows ZIP file**.

![a2](./media/Arduino_2.3.6-a2.png)

Two versions are provided for Windows: for installing(Windows Win 10 or newer(64-bit)) and for downloading(Windows ZIP file, a zipped file, no need to install).

## 3.2.1 Install Arduino IDE

1\. Save the .exe file downloaded from the software page to your hard drive and simply run the file .

![Arduino_2.3.6-a5](./media/Arduino_2.3.6-a5.png)

2\. Read the License Agreement and agree it.

![a6](./media/Arduino_2.3.6-a6.png)

3\. Choose the installation options.

![a7](./media/Arduino_2.3.6-a7.png)

4\. Choose the installation location.

![a8](./media/Arduino_2.3.6-a8.png)

5\. Click “finish” and run Arduino IDE.

![a9](./media/Arduino_2.3.6-a9.png)

# 3.3 For MacOS

## 3.3.1 Download Arduino IDE

Enter Arduino official to download [Software | Arduino](https://www.arduino.cc/en/software/).

Similar to Windows, here we will take **macOS Intel 10.15 Catalina or newer(64-bit)** as an example to introduce how to download it. You may also choose the **macOS Apple Silicon 11 Big Sur or newer(64-bit)**.

![](./media/Arduino_2.3.6-a4.png)

## 3.3.2 Install Arduino IDE

After then, click the file `arduino_ide_xxxx.dmg` and follow the instruction: copy and pastes the  **Arduino IDE.app** into **Applications**. A couple of seconds later, you can see the Arduino IDE icon.

![Img](./media/Arduino_2.3.6-Mac.png)

# 3.4 Arduino IDE Language

⚠️ **Note that for different systems such as Windows and MAC, the language setting methods are not the same. The followings can be used as a reference.**

1\. Open Arduino IDE.

![Img](./media/Arduino_2.3.6-ArduinoIDE.png)

2\. Click “**File** ——>**Preferences...**”. In **Preferences**, click “**English**” to select a familiar language and “**OK**”.

![Arduino_2.3.6-a29-1](./media/Arduino_2.3.6-a29-1.png)

# 3.5 Arduino IDE Page

![Arduino_2.3.6-a35](./media/Arduino_2.3.6-a35.png)

1. **File** - includes new Sketch, open Sketch, open recently used code, open sample code, close the IDE, save code, preferences, advanced Settings, etc.
2. **Edit** - includes copy, paste, automatic formatting, font size, etc. (shortcut keys are recommended).
3. **Sketch** - includes verify\compile, upload code, import library and so on.
4. **Tools** - The most important two are development board and port.
5. **Help** - Views the IDE version and official reference documents.
6. **Open Serial Plotter** - displays serial data in a method of line graph
7. **Open Serial Monitor** - opens the Serial Monitor tool, as a new tab in the console.
8. **Verify** - compiles your code to your Arduino Board.
9. **Verify / Upload** - compiles and uploads your code to your Arduino Board.
10. **Sketchbook** - here you will find all of your sketches locally stored on your computer. Additionally, you can sync with the Arduino Cloud, and also obtain your sketches from the online environment.
11. **Boards Manager** - install or remove Arduino Boards .
12. **Library Manager** - browse through thousands of Arduino libraries or import local libraries
13. **Debugger** - test and debug programs in real time.
14. **Search** - search for keywords in your code.
15. **Code editing area**
16. **IDE prompt area** (Uploading fails or succeeds) & **Serial monitor display area**



# 3.6 Import Library (Important)

⚠️ **Note: For different systems such as Windows and MAC, the methods for importing library files are similar and can be referred to each other. Here, we take the Windows as an example.**

## 3.6.1 What are Libraries?

A library is a collection of codes, and it facilitates the connection of sensors, displays and modules. 

When you see “No such file or directory”, oops, libraries are missing! For instance, we do not include library before uploading related codes:

![Arduino_2.3.6-a44](./media/Arduino_2.3.6-a44.png)



## 3.6.2 How to Install the Libraries?

We take “Sentry” as an example.

1\. Click **“Sketch” --> “Include Library” --> “Add .ZIP Library...”**

![Arduino_2.3.6-a45](./media/Arduino_2.3.6-a45.png)

2\. Find the library file(Download the ZIP file in `1. Resources Download`) and open `lib` to select `Sentry-Arduino-1.3.9.zip`. 

![Arduino_2.3.6-a46](./media/Arduino_2.3.6-a46.png)

3\. After that, you will see a prompt (Processing `Sentry-Arduino-1.3.9.zip`) and it outputs “**Library installed**”. This library is installed into Arduino IDE. There is no need to repeat the installation process when this library is needed next time.

![Arduino_2.3.6-a47](./media/Arduino_2.3.6-a47.png)

4\. For how to install libraries, all systems are the same.

# 3.7 Upload Code on Arduino IDE

Connect Nano board to your computer via the USB cable.

![Arduino_2.3.6-a36](./media/Arduino_2.3.6-a36.png)

Open Arduino IDE to select Nano board.

![Arduino_2.3.6-a37](./media/Arduino_2.3.6-a37.png)

Choose COM port. You may check your port number at Device Manager. If there are many COM ports, unplug the cable of board to see which port disappears. Then that one is the port ready to use. If there is no COM port, please check whether driver is installed.

![Arduino_2.3.6-a10](./media/Arduino_2.3.6-a10.png)

Herein, our COM port is COM10. Click “Tools” → “Port” → “COM10”.

![Arduino_2.3.6-a38](./media/Arduino_2.3.6-a38.png)

When the board is connected, both of these places appear its model. Here we provide a sample code that prints “Hello Keyestudio!” once per second in the serial monitor.

Copy and paste the following code to Arduino IDE.

```c
/*
  keyes 
  “Hello Keyes!”
  http://www.keyesrobot.com
*/
void setup() {  
    Serial.begin(9600);
}

void loop() {  
    Serial.println("Hello Keyes!");
 	delay(1000); 
}
```

![Arduino_2.3.6-a39](./media/Arduino_2.3.6-a39.png)

Click ![a40](./media/Arduino_2.3.6-a40.png) to compile and upload code. Two prompts will appear after upload is successful:

![Arduino_2.3.6-a41](./media/Arduino_2.3.6-a41.png)

After that, click ![a42](./media/Arduino_2.3.6-a42.png) to show serial monitor and set baud rate to **9600**. You will see “**Hello Keyes!**” on the monitor.

![Arduino_2.3.6-a43](./media/Arduino_2.3.6-a43.png)

1. **Toggle Auto-scroll** - Sets whether the prints scroll automatically
2. **Toggle Timestamp** - Sets whether to display print time
3. **Clear Output** - Clears printed messages
4. **Serial Input**
5. **Serial Output Format**
6. **Baud Rate** - Sets the baud rate you need
7. **Printing Window**

# 3.8 Arduino C Basic Codes

To learn more about the Arduino codes, please check out the [Language Reference | Arduino Documentation](https://docs.arduino.cc/language-reference/).
