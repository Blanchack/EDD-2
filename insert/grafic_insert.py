import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Función para calcular promedios cada 1000 inserciones
def calculate_moving_average(data, step=1000):
    averaged_data = data.groupby(data.index // step).mean().reset_index(drop=True)
    averaged_data['N'] = (averaged_data.index + 1) * step
    return averaged_data

# Cargar datos desde archivos CSV
data_linear = pd.read_csv('linear_insert.csv', names=['N', 'Time'])
data_quadratic = pd.read_csv('quadratic_insert.csv', names=['N', 'Time'])
data_double = pd.read_csv('double_insert.csv', names=['N', 'Time'])
data_unordered = pd.read_csv('unordered_map_insert.csv', names=['N', 'Time'])
data_abierto = pd.read_csv('abierto_insert.csv', names=['N', 'Time'])

# Calcular promedios móviles cada 1000 inserciones
avg_linear = calculate_moving_average(data_linear)
avg_quadratic = calculate_moving_average(data_quadratic)
avg_double = calculate_moving_average(data_double)
avg_unordered = calculate_moving_average(data_unordered)
avg_abierto = calculate_moving_average(data_abierto)

# Crear figura para los datos sobrepuestos
fig, axs = plt.subplots(5, 1, figsize=(12, 36))

# Función para agregar gráficos y promedios
def add_plot(ax, data, avg_data, title):
    ax.plot(data['N'], data['Time'], label=f'{title} (Original)')
    ax.plot(avg_data['N'], avg_data['Time'], color='orange', linestyle='--', label=f'{title} (Average)', zorder=3)
    ax.set_xlabel('Nro. de insercion')
    ax.set_ylabel('Tiempo (nanosegundos)')
    ax.set_title(f'Analisis de tiempo de insercion ({title})')
    ax.legend()

# Graficar datos y promedios para Linear
add_plot(axs[0], data_linear, avg_linear, 'Linear')

# Graficar datos y promedios para Quadratic
add_plot(axs[1], data_quadratic, avg_quadratic, 'Quadratic')

# Graficar datos y promedios para Double Hashing
add_plot(axs[2], data_double, avg_double, 'Double Hashing')

# Graficar datos y promedios para Unordered Map
add_plot(axs[3], data_unordered, avg_unordered, 'Unordered Map')

# Graficar datos y promedios para Abierto
add_plot(axs[4], data_abierto, avg_abierto, 'Hasing Abierto')

plt.tight_layout()
fig.savefig('combined_data_with_averagesUsr.png')

# Crear figura para las tablas
fig_tables, axs_tables = plt.subplots(5, 1, figsize=(12, 45))  # Reducir tamaño total de la figura

# Función para agregar tablas
def add_table(ax, avg_data, title):
    ax.axis('tight')
    ax.axis('off')
    table_data = avg_data[['N', 'Time']].round(2).values
    col_labels = ['Nro. de insercion', 'Tiempo promedio (ns)']
    table = ax.table(cellText=table_data, colLabels=col_labels, cellLoc='center', loc='center')
    table.scale(1, 1)  # Ajustar el tamaño de la tabla para que sea más compacta
    table.auto_set_font_size(False)
    table.set_fontsize(12)  # Ajustar el tamaño de fuente para que la tabla sea más pequeña
    ax.set_title(f'{title} (Average Data)', pad=10)

# Agregar tablas para cada conjunto de datos
add_table(axs_tables[0], avg_linear, 'Linear')
add_table(axs_tables[1], avg_quadratic, 'Quadratic')
add_table(axs_tables[2], avg_double, 'Double Hashing')
add_table(axs_tables[3], avg_unordered, 'Unordered Map')
add_table(axs_tables[4], avg_abierto, 'Abierto')

plt.tight_layout()
fig_tables.savefig('average_data_tablesUsr.png')

# Crear figura comparativa para todas las líneas en un solo gráfico
fig_compare, ax_compare = plt.subplots(figsize=(12, 8))

# Agregar todas las líneas de promedios en un solo gráfico
ax_compare.plot(avg_linear['N'], avg_linear['Time'], label='Linear', linestyle='-', marker='o')
ax_compare.plot(avg_quadratic['N'], avg_quadratic['Time'], label='Quadratic', linestyle='-', marker='s')
ax_compare.plot(avg_double['N'], avg_double['Time'], label='Double Hashing', linestyle='-', marker='^')
ax_compare.plot(avg_unordered['N'], avg_unordered['Time'], label='Unordered Map', linestyle='-', marker='d')
ax_compare.plot(avg_abierto['N'], avg_abierto['Time'], label='Abierto', linestyle='-', marker='*')

ax_compare.set_xlabel('Tiempo de insercion')
ax_compare.set_ylabel('Tiempo promedio (nanosegundos)')
ax_compare.set_title('Comparacion de tiempo promedio')
ax_compare.legend()

plt.tight_layout()
fig_compare.savefig('comparison_of_averagesUsr.png')
