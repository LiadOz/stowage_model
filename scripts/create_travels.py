import random


def get_full_route(min_unique, max_unique, max_duplicates):
    unique_ports_num = random.randint(min_unique, max_unique)
    ports_num = random.randint(unique_ports_num,
                               unique_ports_num + max_duplicates)
    ports = []
    containers = []
    with open('./sample_ports') as f:
        ports = [line.rstrip() for line in f]
    with open('./samples') as f:
        containers = [line.rstrip() for line in f]
    random.shuffle(ports)
    random.shuffle(containers)
    route = []
    for port in ports[:unique_ports_num]:
        route.append(port)
    return random.choices(route, k=ports_num)


print(get_full_route(3, 10, 5))
