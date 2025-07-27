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

# --- Gráfico de Aceleração ---
plt.figure(figsize=(10, 5))
plt.plot(tempo, acel_x, label='Aceleração X')
plt.plot(tempo, acel_y, label='Aceleração Y')
plt.plot(tempo, acel_z, label='Aceleração Z')
plt.title('Aceleração vs Tempo')
plt.xlabel('Tempo (s)')
plt.ylabel('Aceleração (raw)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

# --- Gráfico de Giroscópio ---
plt.figure(figsize=(10, 5))
plt.plot(tempo, gyro_x, label='Giroscópio X')
plt.plot(tempo, gyro_y, label='Giroscópio Y')
plt.plot(tempo, gyro_z, label='Giroscópio Z')
plt.title('Giroscópio vs Tempo')
plt.xlabel('Tempo (s)')
plt.ylabel('Giroscópio (raw)')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
