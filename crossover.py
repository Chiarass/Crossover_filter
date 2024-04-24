import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
import pandas as pd
import math
from scipy.optimize import curve_fit

def main():
    # Initial parameters
    V0 = 5
    R = 560
    L = 10.21e-3 
    C = 26.11e-9

    # Loading data from files
    filename1 = "datiLab2/SweepAmpiezzaLargoWoofer.txt"
    x_1, y_1 = np.loadtxt(filename1, unpack=True)
    filename2 = "datiLab2/SweepAmpiezzaLargoTweeter.txt"
    x_2, y_2 = np.loadtxt(filename2, unpack=True)

    # Initial guesses for parameters
    P1 = [V0, R, L]
    P2 = [V0, R, C]

    def woofer(x, V0, R, L):
        y = V0 * R /(np.sqrt(R**2 + x**2 * L**2))
        return y
    
    def tweeter(x, V0, R, C):
        y = V0 * R /(np.sqrt(R**2 + (1/(x * C))**2))
        return y
    
    # Fitting the woofer model to the first set of data
    popt1, _ = curve_fit(woofer, x_1, y_1, p0=P1, maxfev=70000)
    
    # Fitting the tweeter model to the second set of data
    popt2, _ = curve_fit(tweeter, x_2, y_2, p0=P2, maxfev=70000)


    # Print the results
    print("Woofer parameters: ")
    print("V0: ", popt1[0])
    print("R: ", popt1[1])
    print("L: ", popt1[2])

    print("Tweeter parameters: ")
    print("V0: ", popt2[0])
    print("R: ", popt2[1])
    print("C: ", popt2[2])

    # Plotting
    plt.figure()
    plt.plot(x_1, y_1, '.', label="Data woofer", color="steelblue")
    plt.plot(x_2, y_2, '.', label="Data tweeter", color="orange")
    plt.plot(x_1, woofer(x_1, *popt1), color='black', label=" Fit woofer")
    plt.plot(x_2, tweeter(x_2, *popt2), color='red', label="Fit tweeter")
    plt.title('Ampiezza in funzione della frequenza', fontsize='x-large', fontweight='bold')
    plt.xlabel('Frequenza (Hz)')  # Add x-axis label
    plt.ylabel('Ampiezza (V)')  # Add y-axis label
    plt.grid()
    plt.legend(fontsize='x-large')
    plt.show()

if __name__ == "__main__":
    main()

