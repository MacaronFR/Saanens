#ifndef SAANENS_PROCESSOP_H
#define SAANENS_PROCESSOP_H

#include <cast.h>
#include <s_func.h>
#include <interpret.h>
#include <operation.h>
#include <format.h>

s_var processLog(const char *command);
s_var processAff(const char *command);
s_var processComp(const char *command);
s_var processAddSub(const char *command);
s_var processMod(const char *command);
s_var processMulDiv(const char *command);
s_var *resolve_var(const char *command);

#endif //SAANENS_PROCESSOP_H
