#ifndef SAANENS_REGFUNC_H
#define SAANENS_REGFUNC_H

#include <variable.h>
#include <regex.h>
#include <function.h>

#define regpresent(exp, command) (s_testreg(exp, command, NULL, REG_NOSUB | REG_EXTENDED))
#define regretrieve(exp, command, pmatch) (s_testreg(exp, command, pmatch, REG_EXTENDED))

boolean process_pmatch(const char *string, regmatch_t *pmatch, size_t nmatch, char **info);
boolean s_testreg(const char *exp, const char *command, regmatch_t **pmatch,int cflags);

#endif //SAANENS_REGFUNC_H