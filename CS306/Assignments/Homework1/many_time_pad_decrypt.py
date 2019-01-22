
#!/usr/bin/env python 
import string
import collections
import sets

def myxor(a, b):
    output = ''
    for (x, y) in zip(a, b):
        output += (chr(ord(x) ^ ord(y)))
    return output


# 11 unknown ciphertexts (in hex format), all encrpyted with the same key
c1 = "2d0a0612061b0944000d161f0c1746430c0f0952181b004c1311080b4e07494852"
c2 = "200a054626550d051a48170e041d011a001b470204061309020005164e15484f44"
c3 = "3818101500180b441b06004b11104c064f1e0616411d064c161b1b04071d460101"
c4 = "200e0c4618104e071506450604124443091b09520e125522081f061c4e1d4e5601"
c5 = "304f1d091f104e0a1b48161f101d440d1b4e04130f5407090010491b061a520101"
c6 = "2d0714124f020111180c450900595016061a02520419170d1306081c1d1a4f4601"
c7 = "351a160d061917443b3c354b0c0a01130a1c01170200191541070c0c1b01440101"
c8 = "3d0611081b55200d1f07164b161858431b0602000454020d1254084f0d12554249"
c9 = "340e0c040a550c1100482c4b0110450d1b4e1713185414181511071b071c4f0101"
c10 = "2e0a5515071a1b081048170e04154d1a4f020e0115111b4c151b492107184e5201"
c11 = "370e1d4618104e05060d450f0a104f044f080e1c04540205151c061a1a5349484c"
ciphers = [c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11]

# which ciphertext to crack
target = "200a054626550d051a48170e041d011a001b470204061309020005164e15484f44"

# store final key
final_key = [None]*33

# store known positions
known_key_positions = set()

for curr, ciphertext in enumerate(ciphers):
    counter = collections.Counter()
    for ind, cipher in enumerate(ciphers):
        # make sure not to xor with itself
        if curr != ind:
            dec_ciphertext = ciphertext.decode('hex')
            dec_cipher = cipher.decode('hex')
            for charind, char in enumerate(myxor(dec_ciphertext, dec_cipher)):
                # if alphanumeric -> probably a space in one of the plaintexts
                if char in string.printable and char.isalpha():
                    # increment counter
                    counter[charind] += 1
                    
    knownSpaceIndexes = []
    # loop through spaces where space is possible
    for ind, val in counter.items():
        if val >= 7:
            # keep track of all spaces
            knownSpaceIndexes.append(ind)

    # decode where each space is and store the key value at that location
    xor_spaces = myxor(ciphertext.decode('hex'), ' '*33)
    for index in knownSpaceIndexes:
        final_key[index] = xor_spaces[index].encode('hex')
        known_key_positions.add(index)

final_key_hex = ''

# create the final hex value of the key, defaulting to 00 if not found
for val in final_key:
    if val is not None:
        final_key_hex += val
    else:
        final_key_hex += '00'

# xor the key and the target to get plaintext message
output = myxor(target.decode('hex'), final_key_hex.decode('hex'))

# if key is not known at a location, default to * character
# to signify unknown value
x = ''
for ind, char in enumerate(output):
    if ind in known_key_positions:
        x += char
    else:
        x += '*'
print x

print 'Key: ', final_key_hex
print 'key array: ', final_key
