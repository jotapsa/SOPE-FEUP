int setupWorkers(){
  int par[NUM_WORKERS];

  for (unsigned int i=0; i<NUM_WORKERS; i++){
    par[i]=i+1;
    pthread_create (&worker[i], NULL, workerEntry, (void *) &p[i]);
  }
  
  return 0;
}
