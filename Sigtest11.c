#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/wait.h>

void build_tree(int level,int maxlevel,int oddcount,int evencount,int maxcount){
    if(level==maxlevel){
        return;
    }
    else{
        int key=1;
        int i,pid;
        int count=(getpid()%2==0)?evencount:oddcount;
        int queue[count];
        for(i=0;i<count;i++){
            pid=fork();
            queue[i]=pid;
            if(pid==0){
                i=count;
                //printf("child accepted\n");
                build_tree(level+1,maxlevel,oddcount,evencount,maxcount);
                //printf("del%d\tdel\n",getpid());
                //fflush(stdout);
                return;
            }
            else{
                kill(pid,SIGSTOP);
                //printf("%d\t%d\n",pid,getpid());
                //fflush(stdout);
            }
        }
    
        for(int j=0;j<count && pid;j++){
        //printf("%d\n",queue[j]);
        int signal;
        kill(queue[j],SIGCONT);
        waitpid(queue[j],&signal,0);
        if(!signal){
            key=key+1;
        }
        if(key==2){
            printf("\n\'%d\tchild of %d\n",getpid(),getppid());
        }
        }
    }
}


int main(){
    build_tree(0,2,3,2,2);
    return 0;
}