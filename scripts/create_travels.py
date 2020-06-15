import random
import os
import shutil


def get_full_route(min_unique, max_unique, max_duplicates):
    unique_ports_num = random.randint(min_unique, max_unique)
    ports_num = random.randint(unique_ports_num,
                               unique_ports_num + max_duplicates)
    ports = []
    with open('./sample_ports') as f:
        ports = [line.rstrip() for line in f]
    random.shuffle(ports)
    route = []
    for port in ports[:unique_ports_num]:
        route.append(port)
    return random.choices(route, k=ports_num)


def init_travel(full_route, directory, max_size, max_height):
    if os.path.exists(directory):
        shutil.rmtree(directory)
    os.makedirs(directory)
    with open(os.path.join(directory, 'a.route'), 'w') as f:
        for route in full_route:
            f.write(route + '\n')
    with open(os.path.join(directory, 'a.ship_plan'), 'w') as f:
        f.write(str(random.randint(1, max_height)) + ','
                + str(random.randint(1, max_size)) + ','
                + str(random.randint(1, max_size)))


def write_travel(full_route, directory, max_size, max_height, max_containers):
    full_route.sort()
    prev_route = ''
    iteration = 1
    for route in full_route:
        if route == prev_route:
            iteration += 1
        else:
            iteration = 1
        prev_route = route
        cargo_num = random.randint(0, max_containers)
        cargo = random.sample(containers, cargo_num)
        cargo_dest = random.choices(full_route, k=cargo_num)
        p = os.path.join(directory,
                         route + '_' + str(iteration) + '.cargo_data')
        with open(p, 'w') as f:
            for cargo, dest in zip(cargo, cargo_dest):
                f.write(cargo + ', 0, ' + dest + '\n')


directory = './temp/'
max_size = 5
max_height = 5
max_containers = 100
full_route = get_full_route(3, 10, 5)
init_travel(full_route, directory, max_size, max_height)
containers = []
with open('./samples') as f:
    containers = [line.rstrip() for line in f]

main_directory = './scripted_travels'
for i in range(300):
    d = os.path.join(main_directory, 'travel_' + str(i))
    full_route = get_full_route(3, 10, 5)
    init_travel(full_route, d, max_size, max_height)
    write_travel(full_route, d, max_size, max_height, max_containers)
