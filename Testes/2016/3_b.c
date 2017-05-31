//Colocadas no inicio do nosso codigo para poderem ser utilizadas por ambas as threads
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cvar = PTHREAD_COND_INITIALIZER;
