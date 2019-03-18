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

  #define PORT 5678

int main(int argc, char **argv){
    if(argc != 3){
        printf("Usage: %s username password\n",argv[0]);
        exit(1);
    }
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

    char cred[3][100];
    char re[100];
    strcpy(cred[0],argv[1]);
    strcpy(cred[1],argv[2]);
    cred[2][0] = '1';
     for(int i = 0 ; i < 3; i++){
        send(SocketFD,cred[i],100,0);
        recv(SocketFD,re,100,0);
       if(strcmp(re,"ok")!=0){
           printf("error\n");
           exit(1);
       }
    }
    recv(SocketFD,re,100,0);
    if(!strcmp(re,"success")){
        printf("Account created\n");
    }
    else{
        printf("Error creating account\n");
        exit(1);
    }

    
    

}