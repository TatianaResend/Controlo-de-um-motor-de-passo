[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/TatianaResend/Controlo-de-um-motor-de-passo/edit/main/README.md)
[![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](https://github.com/TatianaResend/Controlo-de-um-motor-de-passo/edit/main/README_pt.md)





<h1 align="center">
  <br>
  <img src="https://user-images.githubusercontent.com/101273005/211634877-c218cebf-b6f4-4a2d-882b-d9d67f9c3cfe.png" alt="Markdownify" width="400">
  

  <br>
  Control of a stepper motor
  <br>
</h1>

<p align="center">
  <a href="#summary">Summary</a> •
  <a href="#components">Components</a> •
  <a href="#Functioning-description">Functioning description</a> •
  <a href="#license">License</a> •
  <a href="#contact">Contact</a>
</p>


https://user-images.githubusercontent.com/101273005/211635364-eda2735e-4f55-4c60-899d-069b7ed95150.mp4


## Summary

This project, developed for the Drive and Command Technologies course, aims to control a stepper motor. It is about creating an interface to control a stepper motor. This includes the definition of the electrical system, the creation of a program for communication and control of the motor and, finally, the creation of a Web Page that allows any user to connect to ESP, the motor control.
The Web Page created allows defining the direction of rotation, the speed and the angle of relative movement that the stepper motor is intended to execute.


## Components
* ESP8266
* Expander module I/O PCF8574
* Stepper Drive HR4988sq
* Stepper Motor 24byj48s


## Functioning description

The ESP8266 receives information from a Web Page over WiFi. It communicates with the expansion module via I2C by activating/deactivating pins "P0" and "P1", which, as far as you are concerned, are connected to pins "dir" and "step" of the motor drive. By activating/deactivating these pins, it is possible to control the rotation of the motor.

The Web Page created allows you to define the direction of rotation, clockwise or counterclockwise. It is also possible to select a low or high speed. Note that with the speed “stopped” the motor does not rotate.
In order to define a position, you can give the relative movement angle that you want the motor to make.

## License

MIT

## Contact

> GitHub [@TatianaResend](https://github.com/TatianaResend) &nbsp;&middot;&nbsp;
> E-mail tatianaresende@ua.pt
