import os
import pandas as pd

for filename in os.listdir('.'):
    if filename.endswith('.csv'):
        pd.read_csv(filename, header=None).describe()[0].to_csv(f'{filename}.desc', header=None)
