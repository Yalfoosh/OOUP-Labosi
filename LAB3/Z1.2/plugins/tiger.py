class tiger:
    def __init__(self, name: str):
        self._name = name

    def name(self) -> str:
        return self._name

    @staticmethod
    def greet() -> str:
        return "Mijau!"

    @staticmethod
    def menu() -> str:
        return "mlako mlijeko"
