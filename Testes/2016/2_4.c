void* workerEntry(void* p){
  int *num = (int*) p;
  int fifoDes, logDes, bytes;
  char logPath[18], fifoPath[13], message[1024];
  sprintf (logPath, "/tmp/worker%d.log", *num);
  sprintf (fifoPath, "/tmp/myfifo%d", *num);

  if ((fifoDes = open (fifoPath, O_RDONLY)) == -1){
    fprintf (stderr, "Error opening FIFO %s\n",fifoPath);
    exit (1);
  }

  if ((logDes = open (logPath, O_WRONLY | O_CREAT | O_TRUNC | O_SYNC)) == -1){
    fprintf (stderr, "Error creating/opening %s\n", logPath);
    exit (1);
  }

  while (read (fifoDes, message, bytes) >0){
    if message[bytes-1] == '\0'{
      write (logDes, message, bytes);
    }
  }

  if (close (fifoDes)==-1){
    fprintf (stderr, "Error closing %s\n",fifoPath);
    exit(2);
  }

  if (close (logDes)==-1){
    fprintf (stderr, "Error closing %s\n",logPath);
    exit(2);
  }

  return 0;
}
