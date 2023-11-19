import json
import pandas as pd 


content = pd.read_json("content.jsonl", lines=True)
print(content.head())
print(content.columns)

# read json

# with open("content.jsonl", "r") as f:
#     content = json.load(f)

# print(content)
