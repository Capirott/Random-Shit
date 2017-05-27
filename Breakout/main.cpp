#include "opengl.h"
#include <iostream>

#ifdef __linux
#include <pthread.h>
#include <unistd.h>
#elif _WIN32

#include <test.h>

#endif


#ifdef __linux

pthread_t tid[2];

void* consoleInput(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();
    float a;
    std::cin >> a;
    while (a) {
	tmp += glm::vec3(a, 0.0f, 0.0f);
	std::cin >> a;
    }

    return NULL;
}

#endif

int main(void) {	
	pthread_create(&(tid[0]), NULL, &start, NULL); // Starts GUI thread
	pthread_create(&(tid[1]), NULL, &consoleInput, NULL); // Starts console IO thread
	pthread_join(tid[0], 0);
	return 0;
}

