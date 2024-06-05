import pandas as pd
import matplotlib.pyplot as plt
import numpy as np  # Import the numpy package

# Load data from CSV files
data_linear = pd.read_csv('linear_insert.csv', names=['N', 'Time'])
data_quadratic = pd.read_csv('quadratic_insert.csv', names=['N', 'Time'])
data_double = pd.read_csv('double_insert.csv', names=['N', 'Time'])  # New line
data_unordered = pd.read_csv('unordered_map_insert.csv', names=['N', 'Time'])  # New line

# Create a new figure
fig, axs = plt.subplots(4, 1, figsize=(10, 24))  # Modified line


# Plot data for linear
axs[0].plot(data_linear['N'], data_linear['Time'], label='Linear')
axs[0].set_xlabel('Insertion Number')
axs[0].set_ylabel('Time (nanoseconds)')
axs[0].set_title('Insertion Time Analysis (Linear)')
axs[0].legend()


# Plot data for quadratic
axs[1].plot(data_quadratic['N'], data_quadratic['Time'], label='Quadratic')
axs[1].set_xlabel('Insertion Number')
axs[1].set_ylabel('Time (nanoseconds)')
axs[1].set_title('Insertion Time Analysis (Quadratic)')
axs[1].legend()

# Plot data for double hashing  # New block
axs[2].plot(data_double['N'], data_double['Time'], label='Double Hashing')
axs[2].set_xlabel('Insertion Number')
axs[2].set_ylabel('Time (nanoseconds)')
axs[2].set_title('Insertion Time Analysis (Double Hashing)')
axs[2].legend()

# Plot data for unordered map  # New block
axs[3].plot(data_unordered['N'], data_unordered['Time'], label='Unordered Map')
axs[3].set_xlabel('Insertion Number')
axs[3].set_ylabel('Time (nanoseconds)')
axs[3].set_title('Insertion Time Analysis (Unordered Map)')
axs[3].legend()

plt.tight_layout()
plt.show()