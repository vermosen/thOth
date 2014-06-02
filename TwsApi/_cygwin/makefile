# TwsApiC++ Debug Version

CC      = gcc
INCLUDE = -I../Api -I../Src -I../../Shared -I../../PosixSocketClient/src
CFLAGS  = -mthreads -D_REENTRANT -D_DEBUG

../Api/libTwsApiL0D.a: ../Api/TwsApiL0.h ../Api/TwsApiDefs.h ../Api/Enumerations.h ../Src/afxwin.h ../Src/TwsApiL0.cpp ../../PosixSocketClient/src/EClientSocketBase.cpp ../../PosixSocketClient/src/EPosixClientSocket.cpp ../../PosixSocketClient/src/EPosixClientSocket.h ../../PosixSocketClient/src/EPosixClientSocketPlatform.h
	$(CC) $(INCLUDE) $(CFLAGS) -c ../Src/TwsApiL0.cpp   -o ./debug/TwsApiL0.o
	ar rcs ../Api/libTwsApiL0D.a ./debug/TwsApiL0.o

clean:
	rm -f ../Api/libTwsApiL0D.a ./debug/TwsApiL0.o
