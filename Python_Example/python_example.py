eimport sys
import random
import math

jobid = int(sys.argv[1])
procid = int(sys.argv[2])
total = jobid+procid

print ("JobID: %d, ProcID: %d, Total: %d" % (jobid,procid,total))
random.seed(jobid+procid)

keep=0
n=int(sys.argv[3])
for i in range(1,n+1):
        x=random.random()
        y=random.random()
        if math.sqrt(x*x+y*y)<=1:
                keep+=1
pi=4.0*keep/n
error = 100*abs(pi - math.pi)/math.pi
print ("pi is approximately %.16f, error is %.16f" % (pi, error))



