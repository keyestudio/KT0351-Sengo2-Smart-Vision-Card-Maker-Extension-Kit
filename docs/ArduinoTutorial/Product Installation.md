# Mount the AI Visual Module onto the KS0543 Car

Here we demonstrate how to mount this module on the `Handling Robot`, a Lego mini car of our KS0543 product as shown below:

![install-1](./media/install-1.png)

Get the visual module and Lego long pins ready:

![install-2](./media/install-2.png)

Insert the Lego pins into the Lego holes on both sides of the module interface.

![install-3](./media/install-3.png)

Pass the wires of the module through the Lego gap of the car for wiring.

![install-4](./media/install-4.png)

Connect the AI terminal to this module and then mount it to the car via Lego, as shown below:

![install-5](./media/install-5.png)

Finally, connect the wire to the I2C interface. Be careful not to connect the wires wrongly:

| AI visual module | Car interfaces |
| :--------------: | :------------: |
|   T/C (yellow)   |      SCL       |
|   R/D (white)    |      SDA       |
|    V/+ (red)     |       5V       |
|   G/- (black)    |       G        |

![install-6](./media/install-6.png)