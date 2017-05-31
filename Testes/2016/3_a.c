pthread_t tid;
info_t par;

par = get_info ();

pthread_create (&tid, NULL, t2, (void*) par);
