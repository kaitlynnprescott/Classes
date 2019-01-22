
#!/usr/bin/env python 
import string
import collections
import sets

# XORs two string
def strxor(a, b):     # xor two strings (trims the longer input)
    return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b)])

# 10 unknown ciphertexts (in hex format), all encrpyted with the same key
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
# The target ciphertext we want to crack
target_cipher = "200e0c4618104e071506450604124443091b09520e125522081f061c4e1d4e5601"
# To store the final key
final_key = [None]*33
# To store the positions we know are broken
known_key_positions = set()

# For each ciphertext
for current_index, ciphertext in enumerate(ciphers):

	counter = collections.Counter()
	# for each other ciphertext
	for index, ciphertext2 in enumerate(ciphers):
		if current_index != index: # don't xor a ciphertext with itself
			for indexOfChar, char in enumerate(strxor(ciphertext.decode('hex'), ciphertext2.decode('hex'))): # Xor the two ciphertexts
				# If a character in the xored result is a alphanumeric character, it means there was probably a space character in one of the plaintexts (we don't know which one)
				if char in string.printable and char.isalpha(): counter[indexOfChar] += 1 # Increment the counter at this index
	knownSpaceIndexes = []

	# Loop through all positions where a space character was possible in the current_index cipher
	for ind, val in counter.items():
		# If a space was found at least 7 times at this index out of the 9 possible XORS, then the space character was likely from the current_index cipher!
		if val >= 7: knownSpaceIndexes.append(ind)
	#print knownSpaceIndexes # Shows all the positions where we now know the key!

	# Now Xor the current_index with spaces, and at the knownSpaceIndexes positions we get the key back!
	xor_with_spaces = strxor(ciphertext.decode('hex'),' '*33)
	for index in knownSpaceIndexes:
		# Store the key's value at the correct position
		final_key[index] = xor_with_spaces[index].encode('hex')
		# Record that we known the key at this position
		known_key_positions.add(index)

# Construct a hex key from the currently known key, adding in '00' hex chars where we do not know (to make a complete hex string)
final_key_hex = ''.join([val if val is not None else '00' for val in final_key])
# Xor the currently known key with the target cipher
output = strxor(target_cipher.decode('hex'),final_key_hex.decode('hex'))
# Print the output, printing a * if that character is not known yet
print ''.join([char if index in known_key_positions else '*' for index, char in enumerate(output)])

'''
Manual step
'''
# From the output this prints, we can manually complete the target plaintext from:
# The secuet-mes*age*is: Wh** usi|g **str*am cipher, nev***use th* k*y *ore than onc*
# to:
# The secret message is: When using a stream cipher, never use the key more than once

# We then confirm this is correct by producing the key from this, and decrpyting all the other messages to ensure they make grammatical sense
target_plaintext = "The secret message is: When using a stream cipher, never use the key more than once"
print target_plaintext
key = strxor(target_cipher.decode('hex'),target_plaintext)
for cipher in ciphers:
	print strxor(cipher.decode('hex'),key)

print "key", final_key
