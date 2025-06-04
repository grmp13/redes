# 📡 Monitoramento de Dados com ESP, Node-RED (Aedes) e Grafana

Este projeto demonstra como coletar dados de sensores via ESP32/ESP8266 e transmiti-los via protocolo MQTT para o Node-RED com broker Aedes. Os dados são visualizados em tempo real em dashboards do Grafana.

---

## 📘 Descrição do Projeto

Um sistema de monitoramento IoT utilizando:

- **ESP32/ESP8266** para simular ou ler dados de sensores.
- **Node-RED** como orquestrador de mensagens MQTT, utilizando o broker **Aedes**.
- **Grafana** para visualização em tempo real dos dados enviados.
  
O sistema permite visualizar os dados recebidos por tópicos MQTT diretamente no dashboard, sendo ideal para aplicações de automação, monitoramento ambiental ou fins educacionais.

---

## ✅ Requisitos

### 🔧 Hardware
- ESP32
- Cabo USB

### 💻 Software
- [PlatformIO](https://platformio.org/)
- Node.js + Node-RED
- Grafana
- MQTT Broker (Aedes embutido no Node-RED)

### 📦 Bibliotecas Arduino
- `WiFi.h`
- `PubSubClient.h`

---

## 🛠️ Instalação e Execução

### 1. Configurar a ESP
- Suba o código na ESP com os dados da sua rede Wi-Fi e o IP do broker.
- Exemplo de código MQTT incluído no apêndice do relatório.

### 2. Iniciar o Node-RED com Aedes
- Instale Node-RED:
  ```bash
  npm install -g --unsafe-perm node-red
  node-red
  ```
- Acesse via navegador:
  ```bash
  http://localhost:1880
  ```
### 3. Instalação do Grafana
- Instale Grafana:
```bash
sudo apt-get install -y software-properties-common
sudo add-apt-repository "deb https://packages.grafana.com/oss/deb stable main"
wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
sudo apt-get update
sudo apt-get install grafana
```
- Inicialize o Grafana:
```bash
sudo systemctl start grafana-server
sudo systemctl enable grafana-server
```
- Acesse via navegador:
```bash
http://localhost:3000
login->admin
senha->admin
```
  
## 📈 Fluxo de Comunicação
ESP --> Wi-Fi --> MQTT (Aedes no Node-RED) --> Dashboard (Grafana)

## 📂 Estrutura do Projeto
📁 redes
├── Firmware/
│   └── src/main.cpp
├── documentos/
│   └── relatorio_rede.pdf
├── servidor/
│   └── flows.json
├── grafana/
│   └── dashboard-export.json
└── README.md

## 📌 Observações
O broker Aedes funciona localmente e não requer autenticação por padrão.

Certifique-se de que ESP e Node-RED estão na mesma rede.

O Grafana pode ser acessado via navegador para dashboards dinâmicos.
