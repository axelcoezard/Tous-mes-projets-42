value = raw_input()

output = ""
i = 0
for c in value:
    output += chr((ord(c) - i) % 128)
    i += 1

print (output)