""" 
Sources: 
Google AI Overview of Color Dialog in Python
Python Documentation of File I/O
W3Schools on Tuples
Google AI Overview to Tuples to Strings
"""

import tkinter as tk
from tkinter import colorchooser

# Create the main window
root = tk.Tk()
root.withdraw()

color = colorchooser.askcolor(title="Select Clothing Color") # Array of two values, rgb = 0, hex = 1

if color[0]:
    with open("./../colorPicker/chosen_color.txt", "w", encoding="utf-8") as f:
        f.write(str(color[0][0]))
        f.write(" ")
        f.write(str(color[0][1]))
        f.write(" ")
        f.write(str(color[0][2]))
else:
    print("Error Choosing Color")

root.destroy()

# Start the Tkinter event loop
root.mainloop()
