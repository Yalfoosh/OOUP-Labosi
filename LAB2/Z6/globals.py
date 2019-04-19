from typing import List, Set, Dict


def extract_expressions(expression: str) -> List[str]:
    try:
        return [str(eval(expression))]
    except NameError:
        if "+" in expression:
            return list(map(lambda x: x.strip(), expression.split("+")))
        else:
            return [expression]


class Cell:
    def __init__(self, expression: str, sheet: "Sheet"):
        assert sheet is not None

        self.__sheet = sheet
        self.__value = 0
        self.__observers: Set = set()
        self.__targets: Set = set()
        self.__expression = extract_expressions(expression)
        self.resolve_expression(self.__expression)

    def resolve_expression(self, extracted_expression):
        if len(extracted_expression) is 1:
            try:
                self.update_value(int(extracted_expression[0]))
            except:
                self.update_value(self.__sheet.cell(extracted_expression[0]).__value)

                target = self.__sheet.cell(extracted_expression[0])

                self.__targets.add(target)
                target.subscribe(self)
        else:
            self.update_value(self.__sheet.cell(extracted_expression[0]).__value
                              + self.__sheet.cell(extracted_expression[1]).__value)

            for observer_ref in extracted_expression:
                target = self.__sheet.cell(observer_ref)

                self.__targets.add(target)
                target.subscribe(self)

    def update_expression(self, expression: str):
        self.__expression = extract_expressions(expression)
        self.update()

    def update_value(self, value: int or float):
        self.__value = value
        self.notify()

    def update(self):
        for target in self.__targets:
            target.unsubscribe(self)

        self.__targets.clear()

        self.resolve_expression(self.__expression)

    def subscribe(self, observer):
        self.__observers.add(observer)

    def unsubscribe(self, observer):
        if observer in self.__observers:
            self.__observers.remove(observer)

    def notify(self):
        for observer in self.__observers:
            observer.update()

    def __str__(self):
        return str(self.__value)


class Sheet:
    def __init__(self, rows: int = 5, columns: int = 5, predefined_table: Dict[int, Cell] = None):
        if predefined_table is None:
            self.table = dict()

            for space in range(0, rows*columns):
                self.table[space] = Cell("0", self)
        else:
            self.table = predefined_table

        self.name_to_coordinates: Dict[str, int] = dict()
        self.__last_value = 0

    def cell(self, ref):
        if ref in self.name_to_coordinates:
            return self.table[self.name_to_coordinates[ref]]

    def set(self, ref, expression):
        cell = self.cell(ref)

        if cell is None:
            self.name_to_coordinates[ref] = self.__last_value
            self.__last_value += 1
            cell = Cell(expression, self)
        else:
            cell.update_expression(expression)

        self.table[self.name_to_coordinates[ref]] = cell

    def __str__(self):
        to_return = ""

        table_names = list(self.name_to_coordinates.keys())
        table_names.sort()

        for entry in table_names:
            to_return += "[{}] {}\n".format(entry, self.table[self.name_to_coordinates[entry]])

        return to_return
