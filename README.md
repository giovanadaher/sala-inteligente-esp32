# sala-inteligente-esp32
Projeto de Internet das Coisas (IoT) desenvolvido com ESP32, no qual o próprio microcontrolador hospeda um servidor web para controle e monitoramento de uma sala inteligente via rede local.

## Objetivo
Desenvolver um sistema embarcado capaz de controlar dispositivos físicos e monitorar variáveis ambientais por meio de uma interface web acessada via IP local do ESP32.

## Tecnologias e componentes
- ESP32
- Arduino IDE
- Servo motor (simulando fechadura eletrônica)
- LEDs
- Sensor de temperatura DHT11
- Rede Wi-Fi (servidor web embarcado)

## Funcionalidades
- Acionamento de servo motor para simulação de fechadura da sala
- Controle de iluminação por LEDs
- Leitura e exibição da temperatura ambiente
- Interface acessada via navegador através do IP do ESP32

## Arquitetura do sistema
O ESP32 atua simultaneamente como:
- Microcontrolador
- Servidor web local
- Interface de controle do sistema

A comunicação ocorre via rede local, sem necessidade de serviços externos.

## Conceitos aplicados
- Servidor web embarcado
- Redes e endereçamento IP
- Leitura de sensores
- Controle de atuadores
- IoT e automação predial
- Programação em sistemas embarcados

## Demonstração
Imagens da montagem, interface web e funcionamento do sistema estão disponíveis na pasta [`docs`](./docs).

## 🚀 Possíveis melhorias
- Autenticação de usuários
- Controle remoto via internet
- Registro histórico de temperatura
- Integração com app mobile
- Substituição do servo por fechadura real

---
Projeto acadêmico – Engenharia da Computação
