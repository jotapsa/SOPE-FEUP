int setupLB(){
  pthread_create (&loadBalancer, NULL, lbEntry, NULL);
  return 0;
}
