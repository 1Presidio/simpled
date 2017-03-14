#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

/* *Fork off the parent process
   *Change file mode mask (umask)
   *Open any logs for writing
   *Create a unique Session ID (SID)
   *Change the current working directory to a safe place
   *Close standard file descriptors */

int main()

{
  //creating child process from parent
  FILE *fp = NULL;
  pid_t pid, sid;
  pid  = fork();
  printf("%d\n",pid);
  if (pid < 0)
    {
      exit(EXIT_FAILURE);
    }


  if (pid > 0)
    {
      exit(EXIT_SUCCESS);
    }

  //file mode is not mask
  umask(0);

  //create new SID for child
  //defensive programming
  sid = setsid();
  printf("%d\n",sid);
  if (sid<0)
    {
      exit(EXIT_FAILURE);
    }

  // change wrkingDir to root
  if ((chdir("/")) <= 0 )
    {
      exit(EXIT_FAILURE); 
    }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  //logging
  
  fp = fopen("Log.txt","w+");
  if (!fp)
    {
      printf("File Not Found:\n");
      exit(EXIT_FAILURE); 
    }
  while (1)
    {
      printf("process exited");
      fprintf(fp, "Logging info...\n");
      fflush(fp);
      sleep(30);
    }
  fclose(fp);
  exit(EXIT_SUCCESS);

}
