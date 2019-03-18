  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <pthread.h>
  #include "auth.h"
  
  #define PORT 5678

int ConnectFD[50];
int count = 0;

void send_to_all(char* buff, int fd, char* usr){
    char finalbuff[1024];
    strcpy(finalbuff,usr);
    strcat(finalbuff,": ");
    strcat(finalbuff,buff);
    for(int i = 0 ; i < count; i++){
        if(ConnectFD[i]!=fd)
            send(ConnectFD[i],finalbuff,1024,0);
    }
}

void* process(void *x){
    int fd = *(int *)x;
    char cred[3][100];
    for(int i = 0 ; i < 3; i ++){
        recv(fd,cred[i],100,0);
        send(fd,"ok",100,0);
    }
    int o = cred[2][0] - '0';
    int t;
  
    if(o==1){
        t = create(cred[0],cred[1]);
        send(fd, t ? "success":"error",100,0);
        pthread_exit(0);
    }
    else if(o==2){
        t = login(cred[0],cred[1]);
        if(t){
            send(fd, "success",100,0);
            printf("%s connected\n",cred[0]);
        }
        else{
            send(fd, "error",100,0);
            pthread_exit(0);
        }
    }
    char buff[1024];
    
    recv(fd,buff,1024,0);
    send_to_all("Now connected!",fd,cred[0]);
    for(;;){
        if(recv(fd,buff,1024,0) <= 0){
            printf("%s disconnected\n",cred[0]);
            send_to_all("Now disconnected!",fd,cred[0]);
            pthread_exit(0);
        }
      
        send_to_all(buff,fd,cred[0]);

        memset(buff,0,1024);
    }

}

  
  int main(void)
  {
      
    struct sockaddr_in sa;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (SocketFD == -1) {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
  
    memset(&sa, 0, sizeof sa);
  
    sa.sin_family = AF_INET;
    sa.sin_port = htons(PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
  
    if (bind(SocketFD,(struct sockaddr *)&sa, sizeof sa) == -1) {
      perror("bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
  
    if (listen(SocketFD, 10) == -1) {
      perror("listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    pthread_t thread[50];
  
    for (;;) {
        ConnectFD[count] = accept(SocketFD, NULL, NULL);
        if (0 > ConnectFD) {
            perror("accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
  
        if(pthread_create(thread+count,NULL,&process,(void *)&ConnectFD[count]) < 0 ){
            printf("error pthread_create\n");
            exit(1);
        }
        count++;
     
    }

}