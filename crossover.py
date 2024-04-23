import numpy as np
import matplotlib
matplotlib.use('TkAgg')  # Imposta il backend Agg
import matplotlib.pyplot as plt
import pandas as pnd
import math
from scipy.optimize import curve_fit

def main():
    # Initial parameters
    V0=5 # 
    R=560 #Resistance
    L=10.21e-3 
    C=26.11e-9

    # Loading data from files
    filename1 = "amplitudewoofer.txt"
    x_1, y_1=np.loadtxt(filename1, unpack=True)
    filename2 = "amplitudetweeter.txt"
    x_2, y_2=np.loadtxt(filename2, unpack=True)

    # 
    P1=[V0, R, L, C]
    P2=[V0, R, C, L]

    def woofer(x, V0, R, L):
        y=V0*R/np.sqrt(R**2+x**2*L**2)
        return y
    
    def tweeter(x, V0, R, C):
        y=V0*R/np.sqrt(R**2+1/(x*C)**2)
        return y
    
    def phasewoof(x, R, L):
        y=np.arctan(-x*L/R)
        return y
    
    def phasetweet(x, R, C):
        y=np.arctan(1/(x*R*C))
        return y
    
    popt1 =curve_fit(woofer, x_1, y_1, p0=P1, maxfev=70000)
    popt2=curve_fit(tweeter, x_2, y_2, p0=P2, maxfev=70000)

    plt.figure()
    plt.plot(x_1, y_1, '.', label="datawoofer", color="steelblue")
    plt.plot(x_2, y_2, '.', label="datatweeter", color="steelblue")
    plt.plot(x_1, woofer(x_1, *popt1), color='orange', label="Fit")
    plt.plot(x_2, woofer(x_2, *popt2), color='orange', label="Fit")
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()
