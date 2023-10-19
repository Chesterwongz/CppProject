#include "FollowsWriter.h"

void FollowsWriter::addFollows(int from, int to) {
  followsStore.addRelation(from, to);
}
