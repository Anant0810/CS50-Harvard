import sys
key = int(sys.argv[1])
plaintext = str(input("Plaintext: "))
print("Ciphertext: ", end="")
len_plain = len(plaintext)
for var in range(len_plain):

    if plaintext[var].isalpha() == True:
        ascii_char = ord(plaintext[var])
        if plaintext[var].islower() == True:
            ascii_to_num = (ascii_char - 97) % 26
            add_key = (ascii_to_num + key) % 26
            num_to_ascii = add_key + 97
            ciphertext = chr(num_to_ascii)
            print(ciphertext, end="")

        if plaintext[var].isupper() == True:
            ascii_to_num = (ascii_char - 65) % 26
            add_key = (ascii_to_num + key) % 26
            num_to_ascii = add_key + 65
            ciphertext = chr(num_to_ascii)
            print(ciphertext, end="")
    else:
        ciphertext = plaintext[int(var)]
        print(ciphertext, end="")
print("")