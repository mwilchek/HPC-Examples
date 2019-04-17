import numpy
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from tqdm import tqdm
from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
stat = MPI.Status()

print("First Generation for rank: " + str(rank))

fig = plt.figure()
start = time.time()

prob = 0.2
COLS = 400
ROWS = 200 + 2

if size > ROWS:
    print("Not enough ROWS")
    exit()
subROWS = ROWS // size + 2

M = numpy.random.binomial(1, prob, size=subROWS * COLS)
subGrid = numpy.reshape(M, (subROWS, COLS))

subGrid[0, :] = 0
subGrid[subROWS - 1, :] = 0
subGrid[:, 0] = 0
subGrid[:, COLS - 1] = 0

ims = []

# BC for all ranks.
subGrid[:, 0] = 1

# BC for rank 0.
if rank == 0:
    subGrid[0, :] = 1

newSubGrid = numpy.copy(subGrid)

generations = 200

# Function definitions
def msgUp():
    comm.send(subGrid[subROWS - 2, :], dest=rank + 1)
    subGrid[subROWS - 1, :] = comm.recv(source=rank + 1)
    return 0


def msgDown():
    comm.send(subGrid[1, :], dest=rank - 1)
    subGrid[0, :] = comm.recv(source=rank - 1)
    return 0


def computeGridPoints():
    global subGrid
    for subROWelem in range(1, subROWS - 1):
        for COLelem in range(1, COLS - 1):
            sum = (subGrid[subROWelem, (COLelem - 1) % COLS] + subGrid[subROWelem, (COLelem + 1) % COLS]
                   + subGrid[(subROWelem - 1) % COLS, COLelem] + subGrid[(subROWelem + 1) % COLS, COLelem]
                   + subGrid[(subROWelem - 1) % COLS, (COLelem - 1) % COLS] + subGrid[(subROWelem - 1) % COLS,
                                                                                      (COLelem + 1) % COLS]
                   + subGrid[(subROWelem + 1) % COLS, (COLelem - 1) % COLS] + subGrid[(subROWelem + 1) % COLS,
                                                                                      (COLelem + 1) % COLS])

            if subGrid[subROWelem, COLelem] == 0:
                if sum == 3:
                    newSubGrid[subROWelem, COLelem] = 1
                else:
                    newSubGrid[subROWelem, COLelem] = 0

            if subGrid[subROWelem, COLelem] == 1:
                if sum < 2:
                    newSubGrid[subROWelem, COLelem] = 0
                elif sum > 3:
                    newSubGrid[subROWelem, COLelem] = 0
                else:
                    newSubGrid[subROWelem, COLelem] = 1

    subGrid = numpy.copy(newSubGrid)


# The main body of the algorithm
# compute new grid and pass rows to neighbors
for i in tqdm(range(0, generations)):
    # exchange edge rows for next iteration
    if rank == 0:
        msgUp()
    elif rank == size - 1:
        msgDown()
    else:
        msgUp()
        msgDown()

    computeGridPoints()

    mainGrid = comm.allgather(subGrid[1:subROWS - 1, :])
    mainGrid = numpy.asarray(mainGrid)
    grid4Plot = numpy.vstack(mainGrid)
    M = numpy.copy(grid4Plot)

    im = plt.imshow(M, animated=True, interpolation='None')
    ims.append([im])

    finalGrid = comm.gather(subGrid[1:subROWS - 1, 1:COLS - 1], root=0)

    if rank == 0:
        result = numpy.vstack(finalGrid)

        if numpy.sum(result) == 0:
            print("Extinction Occurs at generation = ", i)
            # print(result)
            comm.Abort()

finalGrid = comm.gather(subGrid[1:subROWS - 1, 1:COLS - 1], root=0)

if rank == 0:
    ani = animation.ArtistAnimation(fig, ims, interval=25, blit=True, repeat_delay=500)
    end = time.time()
    print("Total time of execution is: " + str(end - start))
    plt.show()
