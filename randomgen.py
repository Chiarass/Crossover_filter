import numpy as np

# Generate random x values
x = np.random.uniform(-10, 10, 100)

# Calculate y values using arctan function
y = np.arctan(x)

# Print the generated data
for i in range(len(x)):
    print(f"x: {x[i]}, y: {y[i]}")
    # Create a .txt file
    file_path = "amplitudetweeter.txt"

    # Open the file in write mode
    with open(file_path, "w") as file:
        # Generate random x values
        x = np.random.uniform(-10, 10, 100)

        # Calculate y values using arctan function
        y = np.arctan(x)

        # Write the generated data to the file
        for i in range(len(x)):
            file.write(f"{x[i]} {y[i]}\n")