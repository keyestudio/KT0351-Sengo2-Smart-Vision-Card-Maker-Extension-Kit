# 2.1 For Windows

## 2.1.1 KidsBlock  Download

* [KidsBlock for Windows](https://xiazai.keyesrobot.cn/KidsBlock.exe)

## 2.1.2 KidsBlock Installation

1\. Click “**KidsBlock.exe**”.

![kidsblock-1](./media/kidsblock-1.png)

2\. Tick “**Anyone who uses this computer (all users)**”  and “**Next**”.

![kidsblock-2](./media/kidsblock-2.png)

3\. Click “**Browse...**” to choose an installation position and “**Install**”.

![kidsblock-3](./media/kidsblock-3.png)

![kidsblock-4](./media/kidsblock-4.png)

4\. Wait for a while and “**Finish**”.

![kidsblock-5](./media/kidsblock-5.png)

And you can see:

![kidsblock-6](./media/kidsblock-6.png)

# 2.2 For MacOS

## 2.2.1 KidsBlock Download

* [KidsBlock for MacOS](https://xiazai.keyesrobot.cn/KidsBlock.dmg)

## 2.2.2 KidsBlock Installation

1\. Open “**KidsBlock.dmg**”.

![kidsblock-11](./media/kidsblock-11.png)



2\. And you will see:

![kidsblock-12](./media/kidsblock-12.png)



3\. Drag “**KidsBlock**” into **Applications** file.

![kidsblock-13](./media/kidsblock-13.png)

4\. There will be a “**Safety Prompt**” during copying.

![kidsblock-14](./media/kidsblock-14.png)

5\.  Click “**Settings**” –> “**Privacy and Security**” to “**open anyway**”. And then “ **Open “KidsBlock”**”.

![kidsblock-16](./media/kidsblock-16.png)

![Img](./media/kidsblock-17.png)

6\. A “**Privacy and Security**” box pops up, and then enter “**user name**” and “**password**”, and “**OK**”.

![Img](./media/kidsblock-18.png)

7.If prompted to update, please click on the update button to obtain the latest version of KidsBlock.

![kidsblock-20](./media/kidsblock-20.png)

8.After a while, you can open the Kidsblock IDE page.

![kidsblock-19](./media/kidsblock-19.png)

# 2.3 Use KidsBlock

⚠️ **ATTENTION**: The following is an example for Windows. For MacOS , it can serve as a reference.

## 2.3.1 Install the development board driver

1. After installing the KisdBlock software, double-click on the desktop to open![KidsBlock](./media/KidsBlock.png)

2. After entering the page, click the settings button in the upper right corner

![Equip-21](./media/Equip-21.png)

3. Click 'Install driver' again.

![Equip-21](./media/Equip-22.png)

4. After confirming in sequence according to the computer pop-up prompt, this pop-up window will finally appear. We click on 'INSTALL' and wait for the installation to succeed.

![Equip-23](./media/Equip-23.png)

## 2.3.2 Connect to Device

1\. Make sure the ESP32 main control board is successfully connected to the computer, and then click “**KidsBlock**” icon ![KidsBlock](./media/KidsBlock.png) to open it.

![Equip-18](./media/Equip-18.png)

2\. Click ![Equip](./media/Equip.png):

![Equip-1](./media/Equip-1.png)

3\. Since we use ESP32, select “**ESP32S development board**” (search `esp32` and you can see it):

![Equip-3](./media/Equip-3.png)

4\. Here the port is (COM7), and click “**Connect**”:

![](./media/Equip-4.png)



5\. “**Go to Editor**”:

![Equip-5](./media/Equip-5.png)

![Equip-6](./media/Equip-6.png)



## 2.3.3 Main Page

KidsBlock software interface is shown in the following figure:

![Equip-7](./media/Equip-7.png)

![Equip-8](./media/Equip-8.png)



## 2.3.4 Load KidsBlock Library

⚠️ **ATTENTION** : If you drag and build code blocks yourself, you must manually add library files. Without library files, you will not see the corresponding blocks for the function. If you directly import the code file we provide, there is no need to add the library file as it will be automatically added when importing.

We need to add the library `Sengo2`.

Click ![Img](./media/Extension.png) to add extensions.

![Extension1](./media/Extension1.png)

Search `sengo2` to load it.

![PRO1](./media/PRO1.png)

Loaded:

![PRO01](./media/PRO01.png)

Click ![Return](./media/Return.png) to go to the editor and you can see the functions of “Sengo2”.

![](./media/Equip-19.png)

## 2.3.5 Build Blocks / Save and Upload Codes

Make sure the ESP32 main control board is connected to the computer, and then click “**KidsBlock**” to open it.

Drag the code block directly to the code editing area. Now let’s build a program that uses serial printing, as shown in the following figure:

![Equip-9](./media/Equip-9.gif)

If you want to Save the code to your computer, click `File` –> `Save to your computer`.

![Equip-10](./media/Equip-10.png)

Select a location (preferably one that you can easily find), name it and then `Save`.

![Equip-20](./media/Equip-20.png)

Make sure the development board is connected before uploading the code ![](./media/Equip-15.png), Click ![upload](./media/upload.png) to upload the code to the ESP32 board.

![Equip-11](./media/Equip-11.png)

After uploading, the serial port will return characters “Hello KidsBlock”.

![](./media/Equip-16.png)

## 2.3.6 Load Codes from Computer

Load code from computer. 

Here we load “Hello_KidsBlock.sb3” in section `2.3.4 Build Blocks / Save and Upload Codes`. 

Click `File` to `Load from your computer`.

![Equip-12](./media/Equip-12.png)

Choose “Hello_KidsBlock.sb3” file path and open it.

![Equip-13](./media/Equip-13.png)

After opening the code file, you need to manually connect the serial port:

![Equip-14](./media/Equip-14.png)

![Img](./media/Equip-4.png)

“**Go to Editor**”:

![Img](./media/Equip-5.png)

Click ![Img](./media/upload.png) to upload the code to ESP32 board:

![Img](./media/Equip-11.png)

After uploading, the serial port will return the characters “Hello KidsBlock”.

![](./media/Equip-16.png)