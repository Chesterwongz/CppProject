#include "ProcToProcReader.h"

std::vector<std::string> ProcToProcReader::getDirectP1ByP2(
    const std::string& proc2) {
  return ReaderUtils::readStrStore(!store.hasDirectAncestors(proc2),
                                   store.getDirectAncestors(proc2));
}

std::vector<std::string> ProcToProcReader::getTransitiveP1ByP2(
    const std::string& proc2) {
  return ReaderUtils::readStrStore(!store.hasAncestorsT(proc2),
                                   store.getAncestorsT(proc2));
}

std::vector<std::string> ProcToProcReader::getDirectP2ByP1(
    const std::string& proc1) {
  return ReaderUtils::readStrStore(!store.hasDirectSuccessors(proc1),
                                   store.getDirectSuccessors(proc1));
}

std::vector<std::string> ProcToProcReader::getTransitiveP2ByP1(
    const std::string& proc1) {
  return ReaderUtils::readStrStore(!store.hasSuccessorsT(proc1),
                                   store.getSuccessorsT(proc1));
}

std::vector<std::pair<std::string, std::string>>
ProcToProcReader::getDirectP1AndP2Pairs() {
  const auto& rawRes = store.getDirectSuccessorMap();
  return CollectionUtils::mapSetToPairVector<std::string, std::string>(rawRes);
}

std::vector<std::pair<std::string, std::string>>
ProcToProcReader::getTransitiveP1AndP2Pairs() {
  return CollectionUtils::mapSetToPairVector(store.getRelationsT());
}

bool ProcToProcReader::hasDirectRelation(const std::string& proc1,
                                         const std::string& proc2) {
  return store.hasDirectRelation(proc1, proc2);
}

bool ProcToProcReader::hasTransitiveRelation(const std::string& proc1,
                                             const std::string& proc2) {
  return store.hasRelationT(proc1, proc2);
}
