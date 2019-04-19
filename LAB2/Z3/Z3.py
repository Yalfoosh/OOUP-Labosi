from typing import Iterable, Callable


def my_max(iterable: Iterable, key: Callable = lambda x: x):
    max_element, max_key = None, None

    for x in iterable:
        if max_key is None or key(x) > max_key:
            max_element = x
            max_key = key(x)

    return max_element


def main():
    ints = [1, 3, 5, 7, 4, 6, 9, 2, 0]
    chars = "Suncana strana ulice"
    strings = ["Gle", "malu", "vocku", "poslije", "kise", "Puna", "je", "kapi", "pa", "ih", "njise"]

    for category in [ints, chars, strings]:
        print("Max from {} is {}.".format(str(category), my_max(iterable=category)))

    print("\nLongest word in {} is \"{}\".\n".format(str(strings), my_max(iterable=strings, key=lambda x: len(x))))

    item_to_price_dict = {"burek": 8, "buhtla": 5}

    print("The most expensive object in {} is {}.\n".format(str(item_to_price_dict),
                                                            my_max(iterable=item_to_price_dict,
                                                                   key=item_to_price_dict.get)))

    people =\
        {
            ("Miljenko", "Šuflaj"),
            ("Ana", "Andrašek"),
            ("Tomislav", "Vidović"),
            ("Hrvoje", "Jurić"),
            ("Nikola", "Osredek"),
            ("Tea", "Kalenski")
        }

    def lex_reverse(x):
        return "{}{}".format(x[1], x[0])

    people_sorted = list(people)
    people_sorted.sort(key=lex_reverse)

    print("The last person in {} lexicographically is {}".format(str(people_sorted),
                                                                 my_max(iterable=people, key=lex_reverse)))


main()
