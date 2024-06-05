import pandas as pd
import matplotlib.pyplot as plt

# Cargar datos desde los archivos CSV
data1 = pd.read_csv('linear_search.csv')
data2 = pd.read_csv('double_search.csv')
data3 = pd.read_csv('quadratic_search.csv')
data4 = pd.read_csv('unordered_map_search.csv')

# Crear dos gráficos separados
fig, axs = plt.subplots(2, 1, figsize=(10, 12))

# Graficar la primera distancia
axs[0].plot(data1['N'], data1['Tiempo'], label='LINEAR')
axs[0].plot(data2['N'], data2['Tiempo'], label='DOUBLE')
axs[0].set_xlabel('Valor de n')
axs[0].set_ylabel('Tiempo en nanosegundos')
axs[0].set_title('Análisis de Tiempo (LINEAR vs DOUBLE)')
axs[0].legend()

# Graficar la segunda distancia
axs[1].plot(data3['N'], data3['Tiempo'], label='QUADRATIC')
axs[1].plot(data4['N'], data4['Tiempo'], label='UNORDERED')
axs[1].set_xlabel('Valor de n')
axs[1].set_ylabel('Tiempo en nanosegundos')
axs[1].set_title('Análisis de Tiempo (QUADRATIC vs UNORDERED)')
axs[1].legend()

# Ajustar diseño y mostrar gráficos
plt.tight_layout()
plt.show()
