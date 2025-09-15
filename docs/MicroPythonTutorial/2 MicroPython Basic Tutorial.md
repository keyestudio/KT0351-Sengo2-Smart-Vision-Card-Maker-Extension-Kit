MicroPython is a streamlined implementation of the Python 3 language, which includes a small part of the Python standard library and is optimized to run in microcontrollers and restricted environments. Here are the main features of MicroPython:

1. **Compatibility** : MicroPython strives to be as compatible as possible with regular Python (referred to as CPython), which means that if you know Python, you have already mastered the basics of MicroPython.
2. **Hardware Access** : In addition to implementing a series of core Python libraries, MicroPython also includes modules such as “machines” for accessing low-level hardware, enabling developers to directly control the hardware resources of microcontrollers.
3. **Interactive Prompt (REPL)** : MicroPython offers an interactive prompt (REPL) that enables users to execute commands directly from a desktop computer on an embedded platform. This is very useful for the rapid real-time testing and debugging of embedded systems.
4. **Multi-threading support** : The MicroPython firmware supports multi-threading functionality, which enables a single microcontroller to handle multiple embedded tasks simultaneously, thereby accelerating the execution of embedded applications.
5. **Open-source Project** : MicroPython is an open-source project, and its source code can be obtained on Github. It follows the MIT license and can be used freely for educational and commercial purposes.
6. **Wide Support** : MicroPython supports a variety of microcontroller boards and RTOS (Real-time Operating System), such as ESP32, ESP8266, STM32, Pico, etc. In addition, it also offers a rich library and modules to meet different development needs.

# 2.1 Download Thonny

## 2.1.1 For Windows

**Operating System: Windows 10**

Enter [Thonny IDE official](https://thonny.org) to download the Thonny for Windows version. 

![1101](./media/thonny-1.png)

![1102](./media/thonny-2.png)

## 2.1.2 For MAC

Please refer to Windows.

![1103](./media/thonny-3.png)

![1104](./media/thonny-4.png)

# 2.2 Install Thonny

Thonny supports two installation methods:

- Thonny+Python package

	Python IDE and Thonny are packaged together and can be directly installed and used. It is fast and easy so is recommended for beginners. There are also two ways to install this package:

	- Installer

		![1201](./media/thonny-5.png)

	- Portable variant

	  ![1202](./media/thonny-6.png)

- Thonny only

  Thonny is actually a package of python. When the user already has a python environment, click `pip install thonny` to install Thonny only, which is more suitable for developers.

  ![1203](./media/thonny-7.png)

Please download the corresponding version according to your requirements.

## 2.2.1 Installer

Download the app according to your operation system. Here we demonstrate under <span style="background:#ff0;color:#000">64bit Windows 10</span> to download `Installer with 64-bit Python 3.10`.

(1) Click ![1204](./media/thonny-8.png) and you will see “Select Setup Install Mode”. Choose **Install for me only**.

![1205](./media/thonny-9.png)

(2) **Next**.

![1206](./media/thonny-10.png)

(3) Tick **I accept the agreement** and Click **Next**.

![1207](./media/thonny-11.png)

(4) The default installation path is in Disk C. You may click **Browse...** to choose another disk. And then click **Next**.

![1208](./media/thonny-12.png)

(5) By default, a shortcut to the program is created in the Start menu folder. Click **Browse...** to set another path for the shortcut and **Next**.

![1209](./media/thonny-13.png)

(6) Tick **Create desktop icon** and **Next**.

![1210](./media/thonny-14.png)

(7) Install.

![1211](./media/thonny-15.png)

(8) “**Finish**”!

![1212](./media/thonny-16.png)

(9) Back to the desktop and start Thonny to choose a language.

![1213](./media/thonny-17.png)

(10) Done.

![1214](./media/thonny-18.png)

## 2.2.2 Portable Variant

Download the app according to your operation system. Here we demonstrate under <span style="background:#ff0;color:#000">64bit Windows 10</span> to download `Installer with 64-bit Python 3.10`.

(1) Click ![1105](./media/thonny-19.png) to start Thonny and choose a language.

![1213](./media/thonny-17.png)

(2) Done.

![1214](./media/thonny-18.png)

# 2.3 Burn Firmware (Important)

<span style="color:red;">Note: You need to download the required data files from `1.Download code and library files` and extract them to your desktop.</span>

To run MicroPython code on Pico, it is necessary to burn MicroPython firmware to Pico.

![thonny-22](./media/thonny-22.png)



A. Connect the board to your computer via Micro USB.

B. Press and hold the white button (BOOTSEL) on “Raspberry Pi Pico”. Then, connect the Raspberry Pi Pico to the computer via a microUSB cable.

![thonny-23](./media/thonny-23.png)

C. Release the button. After connection, open [Device Manager] and your computer will automatically recognize the removable disk (RPI-RP2) as follows:

![thonny-24](./media/thonny-24.png)

D. Copy the `RPI_PICO-20250809-v1.26.0.uf2` file from the “Firmware” folder to the removable disk (RPI-RP2), just like copying a file to a USB flash drive, and then wait for it to complete.

![thonny-25](./media/thonny-25.gif)

E. After burning the firmware, Raspberry Pi Pico will restart. After that, you can run Micropython.

# 2.4 Homepage

Click **View** and tick **Files** to open the file manager.

![1401](./media/thonny-26.png)

![1402](./media/thonny-27.png)

# 2.5 Toolbar

![1403](./media/thonny-28.png)

|              Icon              |       Function       |
| :----------------------------: | :------------------: |
| ![1404](./media/thonny-29.png) |         New          |
| ![1405](./media/thonny-30.png) |       Open...        |
| ![1406](./media/thonny-31.png) |         Save         |
| ![1407](./media/thonny-32.png) |  Run current script  |
| ![1408](./media/thonny-33.png) | Debug current script |
| ![1409](./media/thonny-34.png) |      Step over       |
| ![1410](./media/thonny-35.png) |      Step into       |
| ![1411](./media/thonny-36.png) |       Step out       |
| ![1412](./media/thonny-37.png) |        Resume        |
| ![1413](./media/thonny-38.png) | Stop/Restart backend |



# 2.6 Connect Pico to Thonny

Connect the Pico development board to the computer, then set the development board to Pico and select the port. 

Click `Tools`-->`Options...`

![thonny-42](./media/thonny-42.png)

Select `Interpreter` , then set the development board to `MicroPython(Raspberry Pi Pico)`, and choose the ports automatically recognized, and click `OK`.

![thonny-43](./media/thonny-43.png)

After connection, “Raspberry Pi Pico” will appear on the left side of Thonny and there will also be a prompt in the lower right corner.

![thonny-44](./media/thonny-44.png)

# 2.7 Load Code from Computer

<span style="color:red;">Note: You need to download the required data files from `1.Download code and library files` and extract them to your desktop.</span>

Click Files –> This computer, open the file `Resources`.

![thonny-39](./media/thonny-39.png)

Enter `codes` and you can see the codes. Click it to open the file in Thonny.

![thonny-40](./media/thonny-40.png)

# 2.8 Upload Library to Pico

Errors may be reported during running code without saving the library to Pico.

![thonny-46](./media/thonny-46.png)

**Add library:** 

In Files, open `Resources` –> `lib` to check library:

![thonny-41](./media/thonny-41.png)

Choose `Sengo2.py` to “Upload to/”.

![thonny-45](./media/thonny-45.png)



After that, `Sengo2.py` is displayed in “Raspberry Pi Pico”.

![thonny-47](./media/thonny-47.png)

# 2.9 Online Running

Here we take code file “4_1Color.py” as an example to run online.

Open “4_1Color.py” in Files and click ![1407](./media/thonny-32.png). Note that wrong wiring of Sengo2 AI and Pico will cause errors in output. If you want to stop current run, just click ![1413](./media/thonny-38.png).

![thonny-48](./media/thonny-48.png)

# 2.10 Offline Running

Here we use “4_1Color.py” again. 

Click ![thonny-50](./media/thonny-50.png) followed by “Raspberry Pi Pico” and select “New file...”.

![thonny-49](./media/thonny-49.png)

Name it to `main.py`. (Note: It must be `main.py`. This name cannot be changed or entered incorrectly.)

![thonny-51](./media/thonny-51.png)

The file was created successfully.

![thonny-52](./media/thonny-52.png)

Open the “4_1Color.py” code file and then press “Ctrl + A” and “Ctrl + C”. Open “main.py” to “Ctrl + V” in it.

![thonny-53](./media/thonny-53.png)

Click Save.

![thonny-54](./media/thonny-54.png)

Saved successfully. Now, when the Pico development board is powered on again, the code in `main.py` will run automatically. (Note: When saving, you need to stop the running of the online code; otherwise, it may fail to be saved.)

![thonny-55](./media/thonny-55.png)
