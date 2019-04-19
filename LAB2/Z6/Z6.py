from globals import Sheet


def main():
    s = Sheet(5, 5)
    print()

    s.set('A1', '2')
    s.set('A2', '5')
    s.set('A3', 'A1+A2')
    print(s)

    s.set('A1', '4')
    s.set('A4', 'A1+A3')
    print(s)

    try:
        s.set('A1', 'A3')
    except RuntimeError as e:
        print("Caught exception:", e)
    print(s)

main()
