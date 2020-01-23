default: main

main: cdCommand.c checkLeftRedirection.c checkPipe.c checkRightRedirection.c findIndexOfNextPipe.c functions.h getArgumentCount.c getTermCount.c getTermIndices.c getUser.c headers.h lsCommand.c main.c pinfoCommand.c separateArguments.c
	gcc cdCommand.c checkLeftRedirection.c checkPipe.c checkRightRedirection.c findIndexOfNextPipe.c getArgumentCount.c getTermCount.c getTermIndices.c getUser.c lsCommand.c main.c pinfoCommand.c separateArguments.c -g -o shell

