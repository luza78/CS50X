text = "In the great green room"
words = text.split()

print()

# Round 1
print("Round 1")
for word in words:
    print(word.capitalize())
print()

# Round 2
print("Round 2")
for word in words:
    for c in word:
        print(c)
print()

# Round 3
print("Round 3")
for word in words:
    if word[1] == "r":
        print(word)
print()

# Round 4
print("Round 4")
for word in words[1:]:
    print(word.capitalize())
print()

# Round 5
print("Round 5")
for word in words:
    print("Goodnight Moon")
print()