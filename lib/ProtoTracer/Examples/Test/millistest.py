from math import floor

for sec in range(5000):
    face = floor((sec%300)/30)
    print(f"Seconds: {sec}, current face is {face}")