import crypt
import sys

if (len(sys.argv) != 2):
    print("Usage: python crack.py hashedPassword")

def crack():
    hashed = sys.argv[1]

    salt = "50"
    words = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    pass_word = []
    length = 1
    count = 0
    if (length <= 5):
        print("Please wait....")
        print("Password: ", end="")
        if (length == 1):
            for i in words:
                count += 1
                if crypt.crypt(i, salt) == hashed:
                    pass_word.append(i)
                    print(pass_word[0])
                    return

            length = length + 1

        if (length == 2):
            for i in words:
                for j in words:
                    word = str(i + j)
                    count += 1
                    if crypt.crypt(word, salt) == hashed:
                        pass_word.append(word)
                        pass_word = str(pass_word)
                        print(pass_word[0])
                        return

            length += 1

        if (length == 3):
            for i in words:
                for j in words:
                    for k in words:
                        count += 1
                        word = str(i + j + k)
                        if crypt.crypt(word, salt) == hashed:
                            pass_word.append(word)
                            print(pass_word[0])
                            return
            length += 1

        if (length == 4):
            for i in words:
                for j in words:
                    for k in words:
                        for l in words:
                            count += 1
                            word = str(i + j + k + l)
                            if crypt.crypt(word, salt) == hashed:
                                pass_word.append(word)
                                print(pass_word[0])
                                return
            length += 1

        if (length == 5):
            for i in words:
                for j in words:
                    for k in words:
                        for l in words:
                            for m in words:
                                count += 1
                                word = str(i + j + k+ l +m)
                                if crypt.crypt(word, salt) == hashed:
                                    pass_word.append(word)
                                    print(pass_word)
                                    return
            length += 1
    else:
        print("Password not found!")

if __name__ == "__main__":
    crack()