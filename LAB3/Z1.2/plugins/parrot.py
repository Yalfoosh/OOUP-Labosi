class parrot:
    def __init__(self, name: str):
        self._name = name

    def name(self) -> str:
        return self._name

    @staticmethod
    def greet() -> str:
        return "Sto mu gromova!"

    @staticmethod
    def menu() -> str:
        return "brazilske orahe"
