import sys
greeting = input("Greeting: ").strip().lower()

for word in greeting.split():
        print(word)
        if word.count("hello") > 0:
            print("$0")
            quit()

if greeting[0] == "h":
    print("$20")
else:
    print("$100")