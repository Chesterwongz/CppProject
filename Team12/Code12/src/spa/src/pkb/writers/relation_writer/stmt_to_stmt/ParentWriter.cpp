#include "ParentWriter.h"

void ParentWriter::addParent(int parent, int child) {
  parentStore.addRelation(parent, child);
}

void ParentWriter::setParentStarRelationship(int parent, int child) {
//  parentStore.setParentStar(parent, child);
}
