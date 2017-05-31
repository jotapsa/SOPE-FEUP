//t1
pthread_mutex_lock(&mut);
C = !C;
pthread_cond_broadcast (&cvar);
pthread_mutex_unlock(&mut);

//t2
pthread_mutex_lock(&mut);
while (!C){
  pthread_cond_wait (&cvar, &mut);
}
//B

pthread_mutex_unlock(&mut);
