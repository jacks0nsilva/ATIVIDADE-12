# Datalogger de Movimento com IMU 📊

Este é um projeto de um datalogger de movimento utilizando um sensor IMU (Inertial Measurement Unit). O objetivo é registrar dados de movimento em tempo real, armazenar em um cartão SD e permitir a visualização dos dados em um gráfico gerado por um script em Python.

## Como funciona ⚙️

- O sensor IMU (MPU6050) é utilizado para capturar dados de aceleração e rotação.
- Os dados são lidos pelo Raspberry Pi Pico W e são armazenados em um cartão SD.
- Um script em Python é utilizado para ler os dados do cartão SD e gerar um gráfico de movimento.

## Pré-requisitos 📦

- Raspberry Pi Pico W
- Numpy e Matplotlib instalados no Python
- Sensor IMU (MPU6050)
- Cartão SD
- Módulo de cartão SD para Raspberry Pi Pico W
- Display OLED SSD1306 (128x64)
- Dois push buttons
- LED RGB
- Um buzzer

## Mapeamento de Pinos GPIO

| Componente         | Função                 | Pino GPIO | Nome no Código    |
| :----------------- | :--------------------- | :-------: | :---------------- |
| **Sensor MPU6050** | I2C - Dados (SDA)      |     0     | `SDA_PIN_MPU6050` |
| **Sensor MPU6050** | I2C - Clock (SCL)      |     1     | `SCL_PIN_MPU6050` |
| **Display OLED**   | I2C - Dados (SDA)      |    14     | `I2C_SDA_DISPLAY` |
| **Display OLED**   | I2C - Clock (SCL)      |    15     | `I2C_SCL_DISPLAY` |
| **Botão A**        | Controle               |     5     | `BOTAO_A`         |
| **Botão B**        | Controle               |     6     | `BOTAO_B`         |
| **LED Verde**      | Feedback Visual        |    11     | `LED_VERDE`       |
| **LED Azul**       | Feedback Visual        |    12     | `LED_AZUL`        |
| **LED Vermelho**   | Feedback Visual        |    13     | `LED_VERMELHO`    |
| **Buzzer**         | Feedback Sonoro        |    10     | `BUZZER_B`        |
| **Cartão SD**      | SPI - MISO             |    16     | `MISO_GPIO`       |
| **Cartão SD**      | SPI - Chip Select (CS) |    17     | `SS_GPIO`         |
| **Cartão SD**      | SPI - Clock (SCK)      |    18     | `SCK_GPIO`        |
| **Cartão SD**      | SPI - MOSI             |    19     | `MOSI_GPIO`       |

# Como usar 📋

**Antes de ligar o dispositivo, certifique-se de que todos os componentes estão conectados corretamente. Inclusive o cartão SD no módulo de cartão SD.**

- Ligue o Raspberry Pi Pico W à fonte de alimentação.
- Pressione o botão B para montar o cartão SD.
- Pressione o botão A para iniciar a gravação dos dados.
- Os dados serão gravados no cartão SD e o LED RGB indicará o status da gravação.
- Após a gravação, o sistema irá gerar um arquivo CSV com os dados de movimento.
- Execute o script Python para visualizar os dados em um gráfico.

---

## 🛠️ Como Executar o Projeto

### 1. Configure o ambiente

- SDK do Raspberry Pi Pico instalado.
- Extensão do VS Code para Pico configurada.

### 2. Clone o repositório

```bash
git clone https://github.com/jacks0nsilva/ATIVIDADE-12.git
```

### 3. Compile e execute

- **Clean CMake** → Limpeza do cache
- **Configure Project** → Detectar arquivos
- **Build Project** → Compilar e gerar `.uf2`
- **Run [USB]** → Gravar firmware na Pico W

### 4. Execute o script Python

**Certifique-se de ter o Python instalado e que o diretório seja o mesmo onde o arquivo .csv está localizado.**

```bash
python script.py
```

---
