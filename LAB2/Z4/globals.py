import numpy as np

from copy import deepcopy
from math import ceil
from typing import List, Callable


# region Number generation
class Generator:
    @staticmethod
    def __fibonacci_sequence(count: int = 1) -> List[int]:
        assert count > 0

        fibonacci_numbers: List[int] = list()

        for i in range(0, count):
            if i < 2:
                fibonacci_numbers.append(1)
            else:
                fibonacci_numbers.append(fibonacci_numbers[i - 1] + fibonacci_numbers[i - 2])

        return fibonacci_numbers

    @staticmethod
    def generate_interval(**kwargs):
        return list(range(kwargs.get("start", 0), kwargs.get("stop", 10), kwargs.get("step", 1)))

    @staticmethod
    def generate_gaussian(**kwargs):
        return list(map(lambda x: int(x),
                        np.random.normal(kwargs.get("mean", 0),
                                         kwargs.get("variance", 1),
                                         kwargs.get("count", 10))))

    @staticmethod
    def generate_fibonacci(**kwargs):
        return Generator.__fibonacci_sequence(kwargs.get("count", 10))
# endregion


# region Percentiles
def nearest_rank(numbers: List[int], n: int = 80) -> int:
    assert 0 < n < 101

    numbers.sort()
    return numbers[int(ceil(float(n) * len(numbers) / 100)) - 1]


def closest_rank_lerp(numbers: List[int], n: int = 80) -> int:
    assert 0 < n < 101
    assert len(numbers) > 0

    numbers.sort()

    def get_index_percentile(i: int, N: int):
        return 100. * (i + 0.5) / N

    p = list()

    for i, number in enumerate(numbers):
        p.append(get_index_percentile(i, len(numbers)))

    if n < p[0]:
        return numbers[0]
    elif n > p[-1]:
        return numbers[-1]
    else:
        index = 0

        for i, number in enumerate(p):
            if number > n:
                index = i - 1
                break

        return round(numbers[index] + len(numbers) * (n - p[index]) * (numbers[index + 1] - numbers[index]) / 100.)


class DistributionTester:
    def __init__(self,
                 generation_function: Callable = None,
                 percentile_function: Callable = None,
                 **kwargs):
        if generation_function is None:
            kwargs.update({"start": 0, "stop": 100, "step": 2})
            generation_function = Generator.generate_interval

        self._numbers = generation_function(**kwargs)
        self._numbers.sort()
        self.percentile_function = percentile_function

    def get_numbers(self):
        return deepcopy(self._numbers)

    def calculate_nth_percentile(self, n: int = 80, percentile_function: Callable = None):
        if percentile_function is None:
            if self.percentile_function is None:
                percentile_function = nearest_rank
            else:
                percentile_function = self.percentile_function

        return percentile_function(self._numbers, n)
# endregion
