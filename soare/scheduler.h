#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "sosdefines.h"
#include "interrupt.h"

VOID
SosScheduleJobs(
    PCONTEXT CurrentContext
);

#endif