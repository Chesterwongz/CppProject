#pragma once

#include <memory>

#include "BaseAbstraction.h"

class AbstractionFactory {
 public:
  static unique_ptr<BaseAbstraction> createAbstraction(
      AbstractionParams &abstractionParams);
};
