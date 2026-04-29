import matplotlib.pyplot as plt
import os
import pandas as pd
import numpy as np

dir_path = os.path.dirname(os.path.realpath(__file__))

for x in os.listdir(dir_path):
    if x.endswith(".txt"):
        print("opening", x)
        xsplit = x.split(".")[0].split("_")
        plotname = xsplit[0] + " " + xsplit[1]

        fig, ax = plt.subplots(label=plotname)
        ax.set_title(plotname)
        ax.set_xlabel(xsplit[2])
        if len(xsplit)>3:
            ax.set_ylabel(xsplit[3])
        df = pd.read_csv(dir_path+"//"+x, sep=", ", engine='python', header=None)
        energy = df[0].values
        var = df[1].values
        ax.plot(energy, var)

        if x=="LMO_ABSORPTION_eV_mm.txt":
            xsplit = x.split(".")[0].split("_")
            plotname = xsplit[0] + " " + xsplit[1]

            fig, ax = plt.subplots(label="LMO TRANSMITTANCE")
            ax.set_title(plotname)
            ax.set_xlabel("nm")
            ax.set_ylabel("Transmittance")
            df = pd.read_csv(dir_path+"//"+x, sep=", ", engine='python', header=None)
            energy = 1240/df[0].values
            var = np.exp(-50/df[1].values)
            ax.plot(energy, var)

    
plt.show()