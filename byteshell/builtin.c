#include "headers/builtin.h"


int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[])(char **) = {
	&lsh_cd,
	&lsh_help,
	&lsh_exit
};

int lsh_num_builtins(){
	return sizeof(builtin_str) / sizeof(char *);
}

int lsh_cd(char **args)
{
	if(args[1] == NULL){
		fprintf(stderr, "lsh:expected argument to \"cd\"\n");
	}
	else{
		if(chdir(args[1])!=0){
				perror("lsh");
		}
	}

	return 1;
}

int lsh_help(char **args)
{
	printf("Welcome guyss\n");
	printf("Type program name and arguments to proceed\n");
        printf("Buitin functions available:\n");

	for(int i=0;i<lsh_num_builtins();i++){
		printf(" %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other program.\n");
	return 1;
}

int lsh_exit(char **args)
{
	return 0;
}
	
		
