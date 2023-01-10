<h1 align="center">
  <br>
  <img src="https://user-images.githubusercontent.com/101273005/211634877-c218cebf-b6f4-4a2d-882b-d9d67f9c3cfe.png" alt="Markdownify" width="400">
  

  <br>
  Controlo de um motor de passo
  <br>
</h1>

<p align="center">
  <a href="#resumo">Resumo</a> •
  <a href="#componentes">Componentes</a> •
  <a href="#descrição-do-funcionamento">Descrição do funcionamento</a> •
  <a href="#licença">Licença</a> •
  <a href="#contacto">Contacto</a>
</p>


https://user-images.githubusercontent.com/101273005/211635364-eda2735e-4f55-4c60-899d-069b7ed95150.mp4


## Resumo

Este projeto, desenvolvido para a cadeira de Tecnologias de Acionamento e Comando, visa
o controlo de um motor de passo. Trata-se na criação de uma interface para controlar um
motor de passo. Isto inclui a definição do sistema elétrico, a criação de um programa para
comunicação e controlo do motor e, finalmente, a criação de uma Web Page que permite a
qualquer utilizador que se conecte ao ESP, o controlo do motor.
A Web Page criada permite definir o sentido de rotação, a velocidade e o ângulo de
movimento relativo que se pretende que o motor de passo execute.


## Componentes
* ESP8266
* Módulo expansor I/O PCF8574
* Stepper Drive HR4988sq
* Stepper Motor 24byj48s


## Descrição do funcionamento

O ESP8266 recebe informação de uma Web Page através de WiFi. Por I2C comunica com o
módulo de expansão fazendo ativar/desativar os pinos "P0"e “P1”, que no que lhe concerne,
estão conectados aos pinos “dir” e “step” do drive do motor. Com a ativação/desativação
destes pinos consegue-se controlar o movimento de rotação do motor.

A Web Page criada permite definir o sentido de rotação, no sentido horário
(Clockwise) ou no sentido anti-horário (Counterclockwise). Também é possível selecionar
uma velocidade baixa ou alta. Notando que com a velocidade “stopped” o motor não roda.
De forma a definir uma posição, pode-se dar o ângulo de movimento relativo que se pretende
que o motor faça.


## Licença

MIT

## Contacto

> GitHub [@TatianaResend](https://github.com/TatianaResend) &nbsp;&middot;&nbsp;
> E-mail tatianaresende@ua.pt
