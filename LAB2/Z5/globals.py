import datetime
import os


from copy import deepcopy
from time import sleep
from typing import Callable


# region Abstract Classes
class Izvor:
    def next(self):
        raise NotImplementedError


class Observer:
    def update(self, **kwargs):
        raise NotImplementedError


class Target:
    def add_observer(self, observer: Observer):
        raise NotImplementedError

    def remove_observer(self, observer: Observer):
        raise NotImplementedError

    def ping(self):
        raise NotImplementedError

    def fetch_state(self):
        raise NotImplementedError
# endregion


# region Sources
class TipkovnickiIzvor(Izvor):
    def next(self):
        fetched = input()

        try:
            fetched = int(fetched)
            return fetched
        except:
            return None


class DatotecniIzvor(Izvor):
    def __init__(self, path: str = "in.txt"):
        self.__stuff = list()
        self.__index = -1

        source = open(os.path.join(os.curdir, path), mode="r")

        for line in source:
            self.__stuff.extend(map(int, line.split()))

        source.close()

        self.__stuff.append(-1)

    def next(self):
        self.__index += 1
        return self.__stuff[self.__index]
# endregion


# region Events
class Action(Observer):
    def __init__(self, target: Target, action: Callable, **kwargs):
        self.__target = target
        self.__action = action
        self.__kwargs = kwargs

    def update(self, **kwargs):
        kwargs.update({"data": self.__target.fetch_state()})
        kwargs.update(**self.__kwargs)
        return self.__action(**kwargs)


def write_to_file(**kwargs):
    with open(file=os.path.join(os.curdir, kwargs.get("path", "")), mode="a") as file:
        file.write("\n{} - {}".format(datetime.datetime.now(), kwargs.get("data", [])))


def get_sum(**kwargs):
    data = kwargs.get("data", [])

    print("The sum of {} is {}.".format(str(data), sum(data)))


def mean(**kwargs):
    data = kwargs.get("data", [])
    assert len(data) > 0

    print("Mean of {} is {}.".format(str(data), float(sum(data)) / len(data)))


def median(**kwargs):
    data = kwargs.get("data", [])
    data.sort()

    if len(data) % 2 == 1:
        value = data[int(len(data) / 2)]
    else:
        i = int(len(data) / 2)
        value = float(data[i] + data[i-1])/2

    print("Median of {} is {}.".format(str(data), value))
# endregion


# region Target Implementation
class SlijedBrojeva(Target):
    def __init__(self, source: Izvor):
        self.__numbers = list()
        self.__observers = list()
        self.__source = source

    def kreni(self):
        number = 0

        while number != -1:
            number = self.__source.next()

            if number is None:
                continue
            elif number is -1:
                print("{} entered, ending.".format(number))
            elif number < 0:
                print("The number you entered ({}) isn't positive like it should be!".format(number))
            else:
                self.__numbers.append(number)
                self.ping()

            sleep(1)

    def add_observer(self, observer: Observer):
        self.__observers.append(observer)

    def remove_observer(self, observer: Observer):
        self.__observers.remove(observer)

    def ping(self):
        for observer in self.__observers:
            observer.update()
        print()

    def fetch_state(self):
        return deepcopy(self.__numbers)
# endregion
