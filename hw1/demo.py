import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("result.csv")
# plot
plt.figure(figsize=(10, 6)) 
plt.plot(data["n"], data["t_lapack"], marker="o", label="LAPACK dgemm", color="blue")
plt.plot(data["n"], data["t_handwriting"], marker="s", label="Handwritten", color="red")

plt.title("comparison of two matrix multiplication methods")
plt.xlabel("Matrix Size (n)")
plt.ylabel("Time (seconds)")
plt.legend() 
plt.xscale("log")
plt.yscale("log")
plt.savefig("comparison.png")
plt.show()