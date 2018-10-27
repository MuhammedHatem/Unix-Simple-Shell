#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

char* Sec_Command = NULL;
char command[100]; // an array to store the command
char* arr_of_strings[100]; // an array of pointers to work as an array of strings to store each word of the command
char* directed_file = NULL ;
int y;

void NProcess();
void readcommand ();
int AndCheck(char temp[]);
void splitter ();
void writing(int );
int main()
{
    printf("SIMPLE SHELL\nMADE AND DESINGED FOR YOU BY ME\nPLEASE ENTER YOUR INPUT : ");
    readcommand();

    while (strcasecmp(command,"exit")!=0) // creating a new process and then reads another command as long the commands are not cd or exit
    {
        splitter();
        NProcess();
        printf("\nPLEASE ENTER YOUR INPUT :");
        readcommand();
    }
    if(strcasecmp(command,"exit")==0)
        exit(0);

    else if(strcasecmp(command,"cd")==0)
        chdir(arr_of_strings[1]);

    return 0;
}


void readcommand () //a function to read the command and to remove the \n at the end
{
    fgets(command, 100, stdin);
    int x = strlen(command);
    command[x - 1] = '\0';
}


int AndCheck(char* temp) //checks if there is an & or if the string itself is an &
{
    if (temp[strlen(temp) - 1] == '&')
        return 1;
    return 0;

}


void NProcess()  // a function that creates a new process
{
    int x;
    pid_t pid = fork();

    if (pid == 0)
        execvp(arr_of_strings[0],arr_of_strings);

    else if (y)
        signal(SIGCHLD,writing); // if a child dies it writes it in a file

    else
        waitpid(pid, NULL, 0);
}


void splitter ()  //splits the command into separated words
{
    int x, lastArgument;
    int i = 0;
    int j = 0;
    arr_of_strings[i] = strtok(command," ");

    while (arr_of_strings[i]!= NULL)
        arr_of_strings[++i]= strtok(NULL," ");

    lastArgument = i - 1;

    y = AndCheck(arr_of_strings[lastArgument]);

 /*   if(x) // it means that it did find an &
    {
        *(*(arr_of_strings + lastArgument)+(strlen(arr_of_strings[lastArgument]) - 1)) = '\0';
        NProcess();

    } */
}


void writing(int x) // a function that is responsible for writing in a file
{
   FILE *fp;
   fp = fopen("children.txt", "a");
   fprintf(fp, "Child Is Dead...\n");
   fclose(fp);
}
