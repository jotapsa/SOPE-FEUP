int setupFifos(){
  char path[13];
  for (unsigned int i=0; i<NUM_WORKERS; i++){
    sprintf (path, "/tmp/myfifo%d", i+1);
    if (mkfifo (path, 0666) == -1){ //0666 =RW for every user
      return -1;
    }
  }
  return 0;
}
