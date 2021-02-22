#ifndef SAANENS_REGFUNC_H
#define SAANENS_REGFUNC_H

#define PCRE2_STATIC
#define PCRE2_CODE_UNIT_WIDTH 8

#include <variable.h>
#include <regex.h>
#include <function.h>
#include <pcre2.h>

#define regpresent(exp, command) (s_testreg(exp, command, NULL, REG_NOSUB | REG_EXTENDED))
#define regretrieve(exp, command, pmatch) (s_testreg(exp, command, pmatch, REG_EXTENDED))

boolean s_testreg_pcre(const char *exp, const char *command, regmatch_t **pmatch,int cflags);

boolean process_pmatch(const char *string, regmatch_t *pmatch, size_t nmatch, char **info);
boolean s_testreg(const char *exp, const char *command, regmatch_t **pmatch,int cflags);
boolean regparenthesis(const char *input, char **match);

#endif //SAANENS_REGFUNC_H