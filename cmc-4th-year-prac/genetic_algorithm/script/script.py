import subprocess
import time

for i in range(10):
    for j in range(10):
        start = time.time()
        subprocess.check_call([f"../build/Genetic_Algorithm {i}  {j}"], shell=True)
        finish = time.time()
        print(f"E={i} L= {j} {time.time() - start} seconds")
        time.sleep(1) #for correct for of random