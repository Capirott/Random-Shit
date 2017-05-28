#include "src/opengl.h"
#include "src/luainterpreter.h"

#include <iostream>

#ifdef __linux
#include <pthread.h>
#include <unistd.h>
pthread_t tid[3];
#elif _WIN32

#include <test.h>

#endif




int main(void) {	

	pthread_create(&(tid[0]), nullptr, &start, nullptr); // Starts GUI thread
    pthread_create(&(tid[1]), nullptr, &lua_interpreter, nullptr); // Starts console lua thread
	pthread_join(tid[0], 0); // Waiting for GUI thread.
    return 0;
}

