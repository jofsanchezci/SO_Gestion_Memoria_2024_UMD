import psutil

# Obtener la memoria total instalada
mem = psutil.virtual_memory()
print(f"Memoria total instalada: {mem.total / 1024**2:.2f} MB")

# Obtener la memoria disponible actualmente
print(f"Memoria disponible: {mem.available / 1024**2:.2f} MB")

# Obtener el porcentaje de uso de la memoria
print(f"Porcentaje de uso de memoria: {mem.percent}%")