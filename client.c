  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <string.h>
  #include <sys/ioctl.h>
  #include <pthread.h>
  #define PORT 5678
  #define BUFSIZE 1024

  void* recv_message(void* x){

    char res[1024];
    int fd = *(int *)x;
    for(;;){
      if((recv(fd,res,1024,0)) <= 0 ){
        pthread_exit(0);
      }
      printf("%s\n",res);
    }
  }

  void login(int fd){
    char buff[1024];
    char res[1024];
    char cred[3][100];
    printf("username:");
    scanf("%s",cred[0]);
    printf("password:");
    scanf("%s",cred[1]);
    cred[2][0] = '0' + 2;
    cred[2][1] = '\0';
 
     for(int i = 0 ; i < 3; i ++){
        send(fd,cred[i],100,0);
        recv(fd,res,100,0);
        
       if(strcmp(res,"ok")!=0){
           printf("error\n");
           exit(1);
       }
    }

    recv(fd,res,100,0);
    
    if(!strcmp(res,"success")){
        printf("You are now logged in\n");
    }
    else{
        printf("Wrong username or password (or maybe another error)\n");
        return;
    }
    pthread_t thread;
    pthread_create(&thread,NULL,&recv_message,(void *)&fd);

      for(;;){
       fgets(buff,1024,stdin);
   
       char *pos; 
       if ((pos=strchr(buff, '\n')) != NULL)
       *pos = '\0';
           if(!strcmp(buff,"exit")){
         return;
       }
       send(fd,buff,1024,0);
        
    }
}
  
  int main(void)
  {
    struct sockaddr_in sa;
    int res;
    int SocketFD;
    int o=0;
    SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    res = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);

    if (connect(SocketFD, (struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    login(SocketFD);

    shutdown(SocketFD, SHUT_RDWR);
  
    close(SocketFD);
    
  }