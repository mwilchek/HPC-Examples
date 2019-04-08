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

fig = plt.figure()
start = time.time()

prob = 0.2
COLS = 400
ROWS = 198

if size > ROWS:
    print("Not enough ROWS")
    exit()
subROWS = ROWS // size + 2

generations = 200


# Function definitions
def msgUp(subGrid):
    # Sends and Recvs rows with Rank+1
    comm.send(subGrid[subROWS - 2, :], dest=rank + 1)
    subGrid[subROWS - 1, :] = comm.recv(source=rank + 1)
    return 0


def msgDn(subGrid):
    # Sends and Recvs rows with Rank-1
    comm.send(subGrid[1, :], dest=rank - 1)
    subGrid[0, :] = comm.recv(source=rank - 1)
    return 0


def computeGridPoints(subGrid):
    for subROWelem in range(1, subROWS + 1):
        for COLelem in range(1, COLS - 1):

            try:
                sum = (subGrid[subROWelem - 1, COLelem - 1] + subGrid[subROWelem - 1, COLelem] + subGrid[
                    subROWelem - 1, COLelem + 1]
                       + subGrid[subROWelem, COLelem - 1] + subGrid[subROWelem, COLelem + 1]
                       + subGrid[subROWelem + 1, COLelem - 1] + subGrid[subROWelem + 1, COLelem] + subGrid[
                           subROWelem + 1, COLelem + 1])
            except IndexError:
                pass

            try:
                if subGrid[subROWelem, COLelem] == 1:
                    if sum < 2:
                        intermediateM[subROWelem, COLelem] = 0
                    elif sum > 3:
                        intermediateM[subROWelem, COLelem] = 0
                    else:
                        intermediateM[subROWelem, COLelem] = 1
            except IndexError:
                pass

            try:
                if subGrid[subROWelem, COLelem] == 0:
                    if sum == 3:
                        intermediateM[subROWelem, COLelem] = 1
                    else:
                        intermediateM[subROWelem, COLelem] = 0
            except IndexError:
                pass

    return 0


def compareGridPoints(oldGrid, newGrid):
    threshold = 1
    OG = numpy.asarray(oldGrid)
    NG = numpy.asarray(newGrid)
    if OG.size != NG.size:
        print('Grid sizes do not match')
        return 1
    for i in range(OG.size):
        if threshold < numpy.any(numpy.abs(numpy.subtract(OG, NG))):
            print('Change detected at iteration: %d' % (i))
            return newGrid
        else:
            print('No Change detected at iteration: %d' % (i))
            return oldGrid


N = numpy.random.binomial(1, prob, size=(subROWS + 2) * COLS)
M = numpy.reshape(N, (subROWS + 2, COLS))

M[0, :] = 0
M[subROWS + 1, :] = 0
M[:, 0] = 0
M[:, COLS - 1] = 0

print("First Generation for rank: " + str(rank))

generation = 0
ims = []

# BC for all ranks.
M[:, 0] = 1

# BC for rank 0.
if rank == 0:
    M[0, :] = 1

# The main body of the algorithm
# compute new grid and pass rows to neighbors
oldGrid = comm.gather(M[1:subROWS - 1, :], root=0)
for i in tqdm(range(generations)):
    generation = generation + 1
    if i % 10 == 0:
        newGrid = comm.gather(M[1:subROWS - 1, :], root=0)
        if 0 == rank:
            oldGrid = compareGridPoints(oldGrid, newGrid)

    intermediateM = numpy.copy(M)
    computeGridPoints(M)

    # exchange edge rows for next iteration
    if rank == 0:
        msgUp(M)
    elif rank == size - 1:
        msgDn(M)
    else:
        msgUp(M)
        msgDn(M)

    M = numpy.copy(intermediateM)
    im = plt.imshow(M, animated=True, interpolation='None')
    ims.append([im])
    if numpy.sum(M) == 0:
        print("Extinction Occurs at generation = ", generation)
        break

newGrid = comm.gather(M[1:subROWS - 1, :], root=0)

if rank == 0:
    result = numpy.vstack(newGrid)

    print("Present Generation = %d" % generation)
    ani = animation.ArtistAnimation(fig, ims, interval=25, blit=True, repeat_delay=500)
    # ani.save('animate_life.mp4')
    end = time.time()
    print("Total time of execution is: " + str(end - start))
    plt.show()
