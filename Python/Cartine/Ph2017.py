import os
import xarray as xr
import matplotlib.pyplot as plt
import numpy as np

import cartopy
from cartopy.crs import PlateCarree
from cartopy.feature import COASTLINE

import warnings
warnings.filterwarnings('ignore')

# Base path relativo
base_path = os.path.dirname(__file__)
data_path = os.path.join(base_path, "dati", "med-temperature.nc")
output_path = os.path.join(base_path, "output")

# Assicurati che la cartella di output esista
os.makedirs(output_path, exist_ok=True)

# Carica il file NetCDF
temp = xr.open_dataarray(data_path)
temp_month = temp.sel(time="07-2017")[0][0]

# Generazione della mappa
fig, ax = plt.subplots(figsize=[10, 6], subplot_kw={"projection": PlateCarree()})
ax.add_feature(COASTLINE)
ax.set_xlim([-5.54, 36.29])
ax.set_ylim([30.19, 45.98])

c = ax.contourf(temp_month.longitude, temp_month.latitude, temp_month, cmap="plasma", levels=np.arange(10, 30), extend="both")
plt.colorbar(c, ax=ax, orientation="horizontal", label="Temperatura °C")
ax.set_title("Analisi della temperatura nel Mediterraneo - Luglio 2017")

# Salva l'immagine nella directory di output
plt.savefig(os.path.join(output_path, "Ph2017.png"))
plt.show()
