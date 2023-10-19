#include "NextWriter.h"

void NextWriter::addNext(int from, int to) {
  nextStore.addRelation(from, to);
}
