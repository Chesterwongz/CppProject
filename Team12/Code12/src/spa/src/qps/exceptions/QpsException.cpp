#include "QpsException.h"

QpsException QpsException::InvalidQueryException() {
    return QpsException(QPSERR_INVALID_QUERY);
};
