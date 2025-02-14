import numpy as np # pip install numpy
import os

data_dir = "data"
os.makedirs(data_dir, exist_ok=True)

num_elements = int(input("Digite o número de elementos: "))
file_name = input("Digite o nome do arquivo (sem o .bin): ")

output_file = os.path.join(data_dir, file_name + ".bin")

data = np.random.randint(0, 1000000, size=num_elements, dtype=np.int32)

data.tofile(output_file)

print(f"Arquivo salvo em: {output_file}")
