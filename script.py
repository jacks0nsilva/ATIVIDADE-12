import numpy as np
import matplotlib.pyplot as plt

# Carrega os dados do CSV (pulando o cabeçalho)
dados = np.loadtxt("dados_imu.csv", delimiter=",", skiprows=1)

# Cada coluna do arquivo:
# 0: numero_amostra
# 1: acel_x, 2: acel_y, 3: acel_z
# 4: gyro_x, 5: gyro_y, 6: gyro_z
# 7: temperatura

tempo = dados[:, 0] * 0.5  # Cada amostra é coletada a cada 0.5 segundos

# Aceleração
acel_x = dados[:, 1]
acel_y = dados[:, 2]
acel_z = dados[:, 3]

# Giroscópio
gyro_x = dados[:, 4]
gyro_y = dados[:, 5]
gyro_z = dados[:, 6]

# --- Criação de subplots: 2 linhas, 1 coluna ---
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8), sharex=True)

# --- Gráfico de Aceleração ---
ax1.plot(tempo, acel_x, label='Aceleração X')
ax1.plot(tempo, acel_y, label='Aceleração Y')
ax1.plot(tempo, acel_z, label='Aceleração Z')
ax1.set_title('Aceleração vs Tempo')
ax1.set_ylabel('Aceleração (g)')  # UNIDADE CONVERTIDA
ax1.legend()
ax1.grid(True)

# --- Gráfico de Giroscópio ---
ax2.plot(tempo, gyro_x, label='Giroscópio X')
ax2.plot(tempo, gyro_y, label='Giroscópio Y')
ax2.plot(tempo, gyro_z, label='Giroscópio Z')
ax2.set_title('Giroscópio vs Tempo')
ax2.set_xlabel('Tempo (s)')
ax2.set_ylabel('Velocidade Angular (°/s)')  # UNIDADE CONVERTIDA
ax2.legend()
ax2.grid(True)


# --- Layout e exibição ---
plt.tight_layout()
plt.show()
