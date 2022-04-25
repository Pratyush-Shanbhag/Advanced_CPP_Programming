# (a + x) mod m = b
# x = (b - a) mod m

# (initial + slide + rotors) % 48 = encrypted
# rotors = (encrypted - (initial + slide)) % 48

'''f = open("encrypt.txt")
s2 = f.read()
f.close()'''


a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        ' ', '.', ',', ';', '!', '?', '(', ')', '-', '\'', '\\', '"']

# space: 36
# N at 13

print(len(a))

s = "BIRCH IS THE GOAT OF A COMPUTER WORLD"
print(len(s))

def encrypt(a, s, r1 = 0, r2 = 47):
    e = 0
    string = ""
    for chr in s:
            e = (a.index(chr) + r1 + r2) % len(a)
            string += a[e]
            r1 += 1
            if r1 % len(a) == len(a) - 1:
                r2 += 1

    return string

firstRotor = 46
secondRotor = 19
es = encrypt(a, s, firstRotor, secondRotor)
print(es)


def count(es, num):
    num = num + 1
    l = []
    for i in range(len(es)-num):
        if ord(es[i]) + num == ord(es[i+num]):
            l.append(i)
            #print(s[i], s[i+num])
    print(l)
    return l

indices = count(es, 1)
num = 0
for i in indices:
    r1 = a.index(es[i]) - (a.index(" ") + i)
    #print(r1)
    #print(36 - )
    num = r1 % 48
    print(r1 % 48)
    print("a" + a[(a.index(" ") + r1 + i) % 48] + "b")

    r2 = a.index(es[i+1]) - (0 + i+1)
    #print(r2)
    print(r2 % 48)
    #print((3-5) % 27)

    print(es[i])
    print((36 + i + 47) % 48)
    print(a[(36 + i + 47) % 48])


decrypted = ""
index = 0
for i in range(len(es)):
    # initial = (encrypted - (rotors + slide)) % 48
    index = (a.index(es[i]) - (num + i)) % 48
    decrypted += a[index]

print()
print(decrypted)
print()



def func(a, es, decrypted):
    for p in range(len(a)):
        for q in range(len(a)):
            if(encrypt(a, decrypted, p, q) == es):
                return (p, q)
    return (-1, -1)

#print(encrypt(a[:26]+[' '], "E THE T", a.index('N'), a.index('X')))

print(func(a, es, decrypted))





'''
l2 = []
for i in range(len(s)-2):
    if ord(s[i]) == ord(s[i+2]):
        l2.append(i)
        #print(s[i], s[i+2])
print(l2)

l3 = []

for i in range(len(s)-4):
    if ord(s[i]) == ord(s[i+4]):
        l3.append(i)
        #print(s[i], s[i+4])
print(l3)
'''



"""s = "HELLO BOB. A CAT"
# blanks: 5, 10, 12
l = []
e = 0
r1 = 0
r2 = 25
a = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        ' ', '.', ',', ';', '!', '?', '(', ')', '-', '\'', '\\', '"']
for chr in s:
    if chr != '\n':
        e = (a.index(chr) + r1 + r2) % len(a)
        l.append(e)
        r1 += 1
        if r1 % len(a) == len(a) - 1:
            r2 += 1
    else:
        l.append(-1)


'''for i in l:
    if i == -1:
        print()
    else:
        print(a[i], end='')
print()'''
s2 = ''.join([a[elem] for elem in l])
print(s2)
print(s)
print("length:", len(s))
l2 = []
for i in range(len(s)-2):
    if ord(s[i]) == ord(s[i+2]):
        l2.append(i)
        print(s[i], s[i+2])
print(l2)
"""
