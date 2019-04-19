from enum import Enum
from sys import stderr
from typing import List


class Point:
    def __init__(self, x : int = 0, y: int = 0):
        self.x = x
        self.y = y

    def __str__(self):
        return "({}, {})".format(self.x, self.y)


class Shape:
    class EType(Enum):
        circle = 0,
        square = 1,
        rhomb = 2,

    def __init__(self, e_type: EType = None):
        self.type_ = e_type

    def draw(self):
        print("in draw_{}".format(str(type(self).__name__).lower()), file = stderr)

    def move(self, diff_x, diff_y):
        raise NotImplementedError


# region Old code
"""class Circle:
    def __init__(self, e_type: Shape.EType = Shape.EType.square, radius: float = 1, center: Point = None):
        self.type_ = e_type
        self.radius_ = radius

        if center is None:
            center = Point(0, 0)

        self.center_ = center


class Square:
    def __init__(self, e_type: Shape.EType = Shape.EType.square, side: float = 1, center: Point = None):
        self.type_ = e_type
        self.side_ = side

        if center is None:
            center = Point(0, 0)

        self.center_ = center


class Rhomb:
    def __init__(self, e_type: Shape.EType = Shape.EType.square,
                 side: float = 1,
                 angle: float = 90,
                 center: Point = None):
        self.type_ = e_type
        self.side_ = side
        self.angle = angle

        if center is None:
            center = Point(0, 0)

        self.center_ = center


def draw_square(square: Square):
    print("in draw_square", file=stderr)


def draw_circle(circle: Circle):
    print("in draw_circle", file=stderr)


def draw_rhomb(rhomb: Rhomb):
    print("in draw_rhomb", file=stderr)


def draw_shapes(shapes: List, n: int):
    for i in range(0, min(n, len(shapes))):
        s = shapes[i]

        if s.type_ is Shape.EType.square:
            draw_square(s)
        elif s.type_ is Shape.EType.circle:
            draw_circle(s)
        elif s.type_ is Shape.EType.rhomb:
            draw_rhomb(s)
        else:
            assert False


def move_shapes(shape, diff_x: int = 0, diff_y: int = 0):
    shape.center_.x += diff_x
    shape.center_.y += diff_y

    print("{}'s center is now {} (from {})".format(type(shape).__name__,
                                                   shape.center_,
                                                   (shape.center_.x - diff_x, shape.center_.y - diff_y)),
          file=stderr)


def main():
    shapes = list()

    shapes.append(Circle(e_type=Shape.EType.circle))
    shapes.append(Square(e_type=Shape.EType.square))
    shapes.append(Square(e_type=Shape.EType.square))
    shapes.append(Circle(e_type=Shape.EType.circle))

    draw_shapes(shapes, 4)

    for shape in shapes:
        move_shapes(shape, *(1, 1))

    shapes.append(Rhomb(e_type=Shape.EType.rhomb))

    draw_shapes(shapes[4:], 1)"""

# endregion


# region New Code
class Circle(Shape):
    def __init__(self, radius: int = 1, center: Point = None):
        super().__init__(Shape.EType.square)
        self.side_ = radius

        if center is None:
            center = Point(0, 0)

        self.center_ = center

    def draw(self):
        super(Circle, self).draw()

    def move(self, diff_x, diff_y):
        self.center_.x += diff_x
        self.center_.y += diff_y


class Square(Shape):
    def __init__(self, side: int = 1, center: Point = None):
        super().__init__(Shape.EType.square)
        self.side_ = side

        if center is None:
            center = Point(0, 0)

        self.center_ = center

    def draw(self):
        super(Square, self).draw()

    def move(self, diff_x, diff_y):
        self.center_.x += diff_x
        self.center_.y += diff_y


class Rhomb(Shape):
    def __init__(self, side: int = 1, angle: float = 90., center: Point = None):
        super().__init__(Shape.EType.square)
        self.side_ = side
        self.angle_ = angle % 360.

        if center is None:
            center = Point(0, 0)

        self.center_ = center

    def draw(self):
        super(Rhomb, self).draw()

    def move(self, diff_x, diff_y):
        self.center_.x += diff_x
        self.center_.y += diff_y


def main():
    shapes = list()

    shapes.append(Square())
    shapes.append(Circle())
    shapes.append(Rhomb())

    for shape in shapes:
        shape.draw()
        shape.move(1, 1)
        print("{} moved to {}.".format(type(shape).__name__, shape.center_), file=stderr)
# endregion


main()
