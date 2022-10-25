#!/Users/annasmelova/anaconda3/envs/made_hpc/bin/python
from mpi4py import MPI
import numpy as np


def main():
    world_comm = MPI.COMM_WORLD
    my_rank = world_comm.Get_rank()
    world_size = world_comm.Get_size()
    new_faces = list(range(1, world_size))
    letters = list('abcdefghijklmnopqrstuvwxyz')
    name = ''.join(np.random.choice(letters, 8)) + '_' + str(my_rank)

    if my_rank == 0:
        known_faces = [my_rank]
        target_face = np.random.choice(new_faces)
        msg = name
        world_comm.ssend((name, msg, known_faces), dest=target_face)
    else:
        prev_name, msg, known_faces = world_comm.recv()
        print(f"{prev_name} say hello to {name}")
        msg += ' ' + name
        known_faces.append(my_rank)
        new_faces = [r for r in new_faces if r not in known_faces]
        if new_faces:
            target_face = np.random.choice(new_faces)
            world_comm.ssend((name, msg, known_faces), dest=target_face)
        else:
            print()
            print(msg)
        
    MPI.Finalize()


if __name__ == "__main__":
    main()
