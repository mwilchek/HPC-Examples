import numpy
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from tqdm import tqdm

fig = plt.figure()

prob = 0.7
COLS = 400
ROWS = 198

generations = 200  # 200

N = numpy.random.binomial(1, prob, size=(ROWS + 2) * COLS)
M = numpy.reshape(N, (ROWS + 2, COLS))

M[0, :] = 0
M[ROWS + 1, :] = 0
M[:, 0] = 0
M[:, COLS - 1] = 0

initM = numpy.copy(M)
print("First Generation")

generation = 0
ims = []
for i in tqdm(range(generations)):
    generation = generation + 1
    intermediateM = numpy.copy(M)
    for ROWelem in range(1, ROWS + 1):
        for COLelem in range(1, COLS - 1):
            sum = (M[ROWelem - 1, COLelem - 1] + M[ROWelem - 1, COLelem] + M[ROWelem - 1, COLelem + 1]
                   + M[ROWelem, COLelem - 1] + M[ROWelem, COLelem + 1]
                   + M[ROWelem + 1, COLelem - 1] + M[ROWelem + 1, COLelem] + M[ROWelem + 1, COLelem + 1])
            if M[ROWelem, COLelem] == 1:
                if sum < 2:
                    intermediateM[ROWelem, COLelem] = 0
                elif sum > 3:
                    intermediateM[ROWelem, COLelem] = 0
                else:
                    intermediateM[ROWelem, COLelem] = 1
            if M[ROWelem, COLelem] == 0:
                if sum == 3:
                    intermediateM[ROWelem, COLelem] = 1
                else:
                    intermediateM[ROWelem, COLelem] = 0
    M = numpy.copy(intermediateM)
    im = plt.imshow(M, animated=True, interpolation='None')
    ims.append([im])
    if numpy.sum(M) == 0:
        print("Extinction Occurs at generation = ", generation)
        break

print("Present Generation = %d" % (generation))
ani = animation.ArtistAnimation(fig, ims, interval=25, blit=True, repeat_delay=500)
# ani.save('animate_life.mp4')

plt.show()
