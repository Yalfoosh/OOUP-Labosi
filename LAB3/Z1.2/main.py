import os

from importlib import import_module
from typing import Callable


def my_factory(module_name: str) -> Callable:
    return getattr(import_module("plugins." + module_name), module_name)


def print_greeting(pet):
    print("{} pozdravlja: {}".format(pet.name(), pet.greet()))


def print_menu(pet):
    print("{} voli {}.".format(pet.name(), pet.menu()))


def test():
    pets = list()

    for module in os.listdir(os.path.join(os.curdir, "plugins")):
        module_name, module_extension = os.path.splitext(module)

        if module_extension == ".py":
            pets.append(my_factory(module_name)("Ljubimac " + str(len(pets))))

    for pet in pets:
        print_greeting(pet)
        print_menu(pet)


test()
