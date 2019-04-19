from globals import Action, SlijedBrojeva, TipkovnickiIzvor, DatotecniIzvor,\
                    write_to_file, get_sum, mean, median


def main():
    mock_keyboard = SlijedBrojeva(source=TipkovnickiIzvor())
    mock_file = SlijedBrojeva(source=DatotecniIzvor())

    writer_1 = Action(target=mock_keyboard, action=write_to_file, path="out.txt")
    writer_2 = Action(target=mock_file, action=write_to_file, path="out.txt")

    summator_1 = Action(target=mock_keyboard, action=get_sum)
    summator_2 = Action(target=mock_file, action=get_sum)

    meaner_1 = Action(target=mock_keyboard, action=mean)
    meaner_2 = Action(target=mock_file, action=mean)

    medianer_1 = Action(target=mock_keyboard, action=median)
    medianer_2 = Action(target=mock_file, action=median)

    mock_keyboard.add_observer(writer_1)
    mock_keyboard.add_observer(summator_1)
    mock_keyboard.add_observer(meaner_1)
    mock_keyboard.add_observer(medianer_1)

    mock_file.add_observer(writer_2)
    mock_file.add_observer(summator_2)
    mock_file.add_observer(meaner_2)
    mock_file.add_observer(medianer_2)

    mock_keyboard.kreni()
    mock_file.kreni()


main()
