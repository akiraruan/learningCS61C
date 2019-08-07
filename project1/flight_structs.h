/*
 * CS61C Summer 2019
 * Name:
 * Login:
 */

#ifndef FLIGHT_STRUCTS_H
#define FLIGHT_STRUCTS_H

#include "timeHM.h"

typedef struct flightSys flightSys_t;
typedef struct airport airport_t;
typedef struct flight flight_t;

struct flightSys {
  // Place the members you think are necessary for the flightSys struct here.
  airport_t **ap;
  int *cnt;
};

struct airport {
  // Place the members you think are necessary for the airport struct here.
  char *name;
  flight_t **flight;
  int *cnt;
};

struct flight {
  // Place the members you think are necessary for the flight struct here.
  airport_t *desAirPort;
  timeHM_t *fromTime;
  timeHM_t *toTime;
  int *cost;
};

#endif

