
from mpi4py import MPI

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
stat = MPI.Status()


destination = (rank+1)%size

message = "I am a message from rank %s" % rank

comm.send(message, dest=destination)

incoming_message = comm.recv(source=MPI.ANY_SOURCE, status=stat)
sender = stat.Get_source()

print "Rank: %d\tSender: %d\n\tMessage: %s" % (rank,sender,incoming_message)


