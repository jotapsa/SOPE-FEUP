int teardownWorkers(){

  for (unsigned int i=0; i<NUM_WORKERS; i++){
    pthread_join (worker[i], NULL);
  }
  return 0;
}

int teardownLB(){
  pthread_join (loadBalancer, NULL);

  return 0;
}
