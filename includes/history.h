#ifndef SAANENS_HISTORY_H
#define SAANENS_HISTORY_H

#include <stdio.h>
#include <string.h>

struct s_hist_entry{
	int index;
	char *command;
};

int init_shistory();
int add_shistory(char *string);

#endif //SAANENS_HISTORY_H