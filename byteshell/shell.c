#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>

#include "headers/parse.h"
#include "headers/builtin.h"
#include "parse.c"
#include "builtin.c"

int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid==0){

		if(execvp(args[0],args) == -1){
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	}
	else if(pid<0){
		perror("lsh");
	}
	else{
		do{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int lsh_execute(char **args)
{
	if(args[0]==NULL){
		return 1;
	}

	for(int i=0; i<lsh_num_builtins(); i++){
		if(strcmp(args[0], builtin_str[i]) == 0){
			return (*builtin_func[i])(args);
		}
	}

	return lsh_launch(args);
}




int main(int argc,char **argv)
{
	char *line;
	char **args;
	int status;
	
	
	do {
		printf("shellomaniac > ");
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);
		
		free(line);
		free(args);
	    } while(status);
	
	return EXIT_SUCCESS;
 }


	    
	    
	
	
