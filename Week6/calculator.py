# input() function by design always returns a string
# to get numbers use int() function

x = int(input("x: "))
y = int(input("y: "))

print(x + y)

z = x / y
print(f"{z:.50f}")