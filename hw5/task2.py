#!/Users/annasmelova/anaconda3/envs/made_hpc/bin/python3 -u
from mpi4py import MPI
import numpy as np
from argparse import ArgumentParser

np.random.seed(0)


def ghost_handling(array, world_comm, rank, world_size, periodic=True):
    """
    # tag 1: from right to left
    # tag 0: from left to right
    """
    if world_size > 1:
        ghost_left = 0
        ghost_right = 0
        if periodic:
            ghost_left = array[1]
            ghost_right = array[-2]
        if rank < world_size:
            ghost_left = array[1]
        if rank < world_size - 1:
            ghost_right = array[-2]

        world_comm.send(ghost_left, dest=(rank - 1) % world_size, tag=0)
        world_comm.send(ghost_right, dest=(rank + 1) % world_size, tag=1)

        array[-1] = world_comm.recv(tag=0)
        array[0] = world_comm.recv(tag=1)

    else:
        if periodic:
            array[-1] = array[1]
            array[0] = array[-2]
        else:
            array[-1] = 0
            array[0] = 0

    return array


def get_one_patterns(rule):
    """
    Return combinations according to 1
    Check Rule 110: [[0, 0, 1], [0, 1, 0], [0, 1, 1], [1, 0, 1], [1, 1, 0]]
    """
    rule_b = f'{rule:08b}'
    patterns = [f'{i:03b}' for i, c in enumerate(rule_b[::-1]) if int(c) == 1]
    patterns = [[int(c) for c in pattern] for pattern in patterns]
    return patterns


def apply_rule(array, rule_patterns):
    new_array = array.copy()
    for i in range(1, len(array) - 1):
        new_array[i] = int(array[i - 1:i + 2] in rule_patterns)
    return new_array


def print_array(array):
    """
    black ▣ = 0
    white ▢ = 1
    """
    array_pic = ['▢' if x else '▣' for x in array]
    print(''.join(array_pic), flush=True)

def run_game(steps, size, rule, periodic, print_pic):
    start_time = MPI.Wtime()
    world_comm = MPI.COMM_WORLD
    rank = world_comm.Get_rank()
    world_size = world_comm.Get_size()

    part_size = size // world_size
    array = list(np.random.choice([0, 1], part_size + 2))

    rule_patterns = get_one_patterns(rule)

    for _ in range(steps):
        array = ghost_handling(array, world_comm, rank, world_size, periodic)
        array_full = world_comm.gather(array, root=0) if world_size > 1 else [array]
        if print_pic and rank == 0:
            pic_array = [x for arr in array_full for x in arr[1:-1]]
            print_array(pic_array)

        array = apply_rule(array, rule_patterns)

    array_full = world_comm.gather(array, root=0) if world_size > 1 else [array]
    if rank == 0:
        if print_pic:
            pic_array = [x for arr in array_full for x in arr[1:-1]]
            print_array(pic_array)
        print(f'World size = {world_size}, time elapsed = {MPI.Wtime() - start_time}')

    MPI.Finalize()


def setup_parser(parser):
    parser.add_argument("--steps", type=int, default=10)
    parser.add_argument("--size", type=int, default=8)
    parser.add_argument("--rule", type=int, default=110)
    parser.add_argument("--periodic", action="store_true")
    parser.add_argument("--print_pic", action="store_true")


def main():
    parser = ArgumentParser()
    setup_parser(parser)

    arguments = parser.parse_args()

    run_game(
        arguments.steps,
        arguments.size,
        arguments.rule,
        arguments.periodic,
        arguments.print_pic,
    )


if __name__ == "__main__":
    main()
