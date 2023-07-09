import os
import pandas as pd
import re

axis = {
    "index" : range(2,41),
    "columns" : [(n,m) for n in range(2,6) for m in range(2,6) if n*m <= 16 and n*m > 4]
}

results = {
    "ai" : {
        "mean" : pd.DataFrame(**axis),
        "std" : pd.DataFrame(**axis),
        "count" : pd.DataFrame(**axis),
        "summary" : pd.DataFrame(**axis)
    },
    "mdp" : {
        "mean" : pd.DataFrame(**axis),
        "std" : pd.DataFrame(**axis),
        "count" : pd.DataFrame(**axis),
        "summary" : pd.DataFrame(**axis)
    },
    "nl" : {
        "mean" : pd.DataFrame(**axis),
        "std" : pd.DataFrame(**axis),
        "count" : pd.DataFrame(**axis),
        "summary" : pd.DataFrame(**axis)
    }
}

for filename in os.listdir('.'):
    if re.match(r'^netstat_(ai|mdp|nl)_(\d+)_(\d+)_(\d+).csv$', filename):
        df = pd.read_csv(f"{filename}", header=None)
        n, m, h = tuple(map(int, re.findall(r'\d+', filename)))
        char = re.findall(r'^netstat_(.*?)_', filename)[0]
        if char == "ai":
            max_char = ((m*n)//2) + ((m*n)%2)
        elif char == "nl":
            max_char = (2**(n*m-1) - 2**(n*m/2-1))
        elif char == "mdp":
            max_char = 2**(n*m)
        else:
            raise Exception(f"NOTE: {filename} contains unknow char")

        results[char]["count"][(n,m)].loc[h] = df.count()[0]
        results[char]["mean"][(n,m)].loc[h] = df.mean()[0]
        results[char]["std"][(n,m)].loc[h] = df.std()[0]
        results[char]["summary"][(n,m)].loc[h] = "{:.2f} ± {:.2f} ({})".format(
            df.mean()[0] / max_char * 100,
            df.std()[0] / max_char * 100,
            df.count()[0]
        )

for char, result in results.items():
    for field in result:
        df = results[char][field].fillna('-')
        df[df.nunique(axis=1) > 1].loc[:,df.nunique(axis=0) > 1 ].to_csv(
            f"report-{char}-{field}.csv"
        )
