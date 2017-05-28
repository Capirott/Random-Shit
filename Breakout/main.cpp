#include "src/opengl.h"
#include <iostream>

#ifdef __linux
#include <pthread.h>
#include <unistd.h>
#elif _WIN32

#include <test.h>

#endif


#ifdef __linux
pthread_t tid[2];
#endif

//Entity *player = 0;

int main(void) {	
	pthread_create(&(tid[0]), nullptr, &start, nullptr); // Starts GUI thread
    //pthread_create(&(tid[1]), nullptr, &lua_interpreter, nullptr); // Starts console IO thread
	pthread_join(tid[0], 0); // Waiting for GUI thread.
	return 0;
}

