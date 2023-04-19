# CAN Transceiver MCP2518 board Arduino library

[![Make docs and publish to GitHub Pages](https://github.com/SolderedElectronics/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/actions/workflows/make_docs.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/actions/workflows/make_docs.yml)
[![Arduino Library Manager Compatibility](https://github.com/SolderedElectronics/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/actions/workflows/arduino_lint.yml/badge.svg?branch=dev)](https://github.com/SolderedElectronics/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/actions/workflows/arduino_lint.yml)


| ![CAN Transceiver MCP2518 board](https://github.com/SolderedElectronics/CAN-Transceiver-MCP2518-board-hardware-design/blob/main/OUTPUTS/V1.1.1/333020.jpg) |
| :--------------------------------------------------------------------------------------------------------------------------------------------------------: |
|                                               [CAN Transceiver MCP2518 board](https://www.solde.red/333020)                                                |

Controller Area Network (CAN) is a network technology that enables fast communication between microcontrollers, and is the most commonly used standard in cars. Our CAN breakout uses an MCP2518FD CAN whose communication between microcontrollers takes place on SPI protocol. In addition there is a CAN transceiver. This breakout allows use of both standards (CAN 2.0B and CAN Flexible Data (FD)). Access to the CAN bus is possible via CANH and CANL pins on the screw terminal. The 120ohm terminator resistor is also located on the board and can be connected to a jumper.

- Standards: CAN 2.0B i CAN FD
- Voltage: 2.7V i 5V
- Current: from 10uA to 12mA
- SPI interface
- Dimensions: 38 x 22 mm

### Repository Contents

- **/src** - source files for the library (.h & .cpp)
- **/examples** - examples for using the library
- **_other_** - _keywords_ file highlights function words in your IDE, _library.properties_ enables implementation with Arduino Library Manager.

### Hardware design

You can find hardware design for this board in [_CAN Transceiver MCP2518 board_](https://github.com/SolderedElectronics/CAN-Transceiver-MCP2518-board-hardware-design) hardware repository.

### Documentation

Access Arduino library documentation [here](https://SolderedElectronics.github.io/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/).

- Tutorial for using the CAN Transceiver MCP2518 board
- Installing an Arduino library

### Board compatibility

The library is compatible with board & microcontroller families shown in green below:

[![Compile Sketches](http://github-actions.40ants.com/e-radionicacom/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/matrix.svg?branch=dev&only=Compile%20Sketches)](https://github.com/SolderedElectronics/Soldered-CAN-Bus-Breakout-MCP2518-Arduino-Library/actions/workflows/compile_test.yml)

### About Soldered

<img src="https://raw.githubusercontent.com/e-radionicacom/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Community & Technical support](https://soldered.com/community)

### Original source

​
This library is possible thanks to original [Longan Labs CAN FD Library](https://github.com/Longan-Labs/Longan_CANFD) library. Thank you, Longan Labs.

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
