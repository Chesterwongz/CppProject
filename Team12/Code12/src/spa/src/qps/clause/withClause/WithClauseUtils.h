#pragma once

#include <string>
#include <unordered_map>

#include "qps/common/Keywords.h"

using std::string, std::unordered_map;

enum Entity_AttrRef_Permutation {
  STMT_STMTNUM,

  READ_STMTNUM,
  READ_VARNAME,

  PRINT_STMTNUM,
  PRINT_VARNAME,

  CALL_STMTNUM,
  CALL_PROCNAME,

  WHILE_STMTNUM,

  IF_STMTNUM,

  ASSIGN_STMTNUM,

  VAR_VARNAME,

  CONSTANT_VALUE,

  PROCEDURE_PROCNAME
};

// TODO(houten): change ATTRREF to whatever kh write in keyword.h
inline unordered_map<Entity, unordered_map<AttrRef, Entity_AttrRef_Permutation>>
    EntityAttrRefPermutationMap = {
        {STMT_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::STMT_STMTNUM}}},
        {READ_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::READ_STMTNUM},
          {ATTR_REF_VAR_NAME, Entity_AttrRef_Permutation::READ_VARNAME}}},
        {PRINT_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::PRINT_STMTNUM},
          {ATTR_REF_VAR_NAME, Entity_AttrRef_Permutation::PRINT_VARNAME}}},
        {CALL_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::CALL_STMTNUM},
          {ATTR_REF_PROC_NAME, Entity_AttrRef_Permutation::CALL_PROCNAME}}},
        {WHILE_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::WHILE_STMTNUM}}},
        {IF_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::IF_STMTNUM}}},
        {ASSIGN_ENTITY,
         {{ATTR_REF_STMT_NUMBER, Entity_AttrRef_Permutation::ASSIGN_STMTNUM}}},
        {VARIABLE_ENTITY,
         {{ATTR_REF_VAR_NAME, Entity_AttrRef_Permutation::VAR_VARNAME}}},
        {CONSTANT_ENTITY,
         {{ATTR_REF_VALUE, Entity_AttrRef_Permutation::CONSTANT_VALUE}}},
        {PROCEDURE_ENTITY,
         {{ATTR_REF_PROC_NAME, Entity_AttrRef_Permutation::PROCEDURE_PROCNAME}}}
};

inline Entity_AttrRef_Permutation getPermutation(Entity entity,
                                                 AttrRef attrRef) {
  return EntityAttrRefPermutationMap.at(entity).at(attrRef);
}
