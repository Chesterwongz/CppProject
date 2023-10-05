#pragma once

#include <string>

enum class StmtType { INVALID, IF, WHILE, CALL, ASSIGN, READ, PRINT, STMT };

typedef int LineNum;
typedef int ConstVal;
typedef std::string VarName;
typedef std::string ProcName;
