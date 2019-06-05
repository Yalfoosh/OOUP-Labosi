from globals import Generator, DistributionTester,\
                    nearest_rank, closest_rank_lerp


def test():
    tester_nearest_rank = DistributionTester(generation_function=Generator.generate_interval,
                                             percentile_function=nearest_rank,
                                             start=5, stop=100, step=10)
    tester_lerp = DistributionTester(generation_function=Generator.generate_gaussian,
                                     percentile_function=closest_rank_lerp,
                                     mean=50, variance=50, count=10)

    n = 42

    print("From {}, the {}% of the nearest rank is {}.".format(tester_nearest_rank.get_numbers(),
                                                               n,
                                                               tester_nearest_rank.calculate_nth_percentile(n=n)))

    print("From {}, the {}% of the "
          "closest rank linear interpolation is {}.".format(tester_lerp.get_numbers(),
                                                            n,
                                                            tester_lerp.calculate_nth_percentile(n=n)))


test()
