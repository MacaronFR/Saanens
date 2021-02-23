#ifndef SAANENS_CAST_H
#define SAANENS_CAST_H

#include <variable.h>
#include <parse.h>

boolean cast(s_var *variable, type type_to_cast);
boolean castString(s_var *variable);
boolean castInt(s_var *variable);
boolean castFloat(s_var *variable);
boolean castChar(s_var *variable);
boolean castBool(s_var *variable);

#endif //SAANENS_CAST_H
