/*
 * CS61C Summer 2019
 * Name:
 * Login:
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "flights.h"
#include "flight_structs.h"
#include "timeHM.h"

/*
 *  This should be called if memory allocation failed.
 */
static void allocation_failed(void) {
  fprintf(stderr, "Out of memory.\n");
  exit(EXIT_FAILURE);
}


/*
 *  Creates and initializes a flight system, which stores 
 *  the flight schedules of several airports.
 *  Returns a pointer to the system created.
 */
flightSys_t* createSystem(void) {
  // Replace this line with your code
  flightSys_t *s = (flightSys_t *)malloc(sizeof(flightSys_t));
  s->cnt = (int *)malloc(sizeof(int));
  s->ap = (airport_t **) malloc(8);
  if (s->cnt == NULL)
  {
    allocation_failed();
  }
  
  *s->cnt = 0;
  return s;
}


/*
 *   Given a destination airport, departure and arrival times, 
 *   and a cost, return a pointer to new flight_t.
 *
 *   Note that this pointer must be available to use even after 
 *   this function returns.(What does this mean in terms of how 
 *   this pointer should be instantiated?)Additionally you CANNOT 
 *   that the `departure` and `arrival` pointers will persist after 
 *   this function completes.(What does this mean about copying dep and arr?)
 */

flight_t* createFlight(airport_t* destination, timeHM_t* departure, timeHM_t* arrival, int cost) {
  // Replace this line with your code
  flight_t *flight = (flight_t *) malloc(sizeof(flight_t));
  flight->cost = (int *) malloc(sizeof(int));
  *flight->cost = cost;
  flight->fromTime = (timeHM_t *) malloc(sizeof(timeHM_t));
  flight->fromTime = departure;
  flight->desAirPort = (airport_t*) malloc(sizeof(airport_t));
  flight->desAirPort = destination;
  flight->toTime = (timeHM_t *) malloc(sizeof(timeHM_t));
  flight->toTime = arrival;
  return flight;
}

/*  
 *  Frees all memory associated with this system; that's all 
 *  memory you dynamically allocated in your code.
 */
void deleteSystem(flightSys_t* system) {
  // Replace this line with your code
  airport_t **aps = system->ap;
  int aircnt = *system->cnt;
  for (int i = 0; i < aircnt; i++)
  {
    airport_t *ap  = aps[i];
    int flicnt = *ap->cnt;
    for (int j = 0; j < flicnt; j++)
    {
      deleteFlight(ap->flight[j]);
    }
    free(ap->cnt);
    free(ap->name);
    free(ap);
  }
  free(system->cnt);
  free(system->ap);
  free(system);
}


/*
 *  Frees all memory allocated for a single flight. You may or 
 *  may not decide
 * 
 *  to use this in delete system but you must implement it.
 */
void deleteFlight(flight_t* flight) {
  // Replace this line with your 
  free(flight->cost);
  free(flight);
}


/*
 *  Adds a airport with the given name to the system. You must 
 *  copy the string and store it.Do not store `name` (the pointer) 
 *  as the contents it point to may change.
 */
void addAirport(flightSys_t* system, char* name) {
  // Replace this line with your code

  int n = *system->cnt;
  system->ap= (airport_t **)realloc(system->ap,8*(n+1));
  system->ap[n] = (airport_t *)malloc(sizeof(airport_t));
  system->ap[n] = (airport_t *)malloc(sizeof(airport_t));

  system->ap[n]->name = (char*) malloc(strlen(name)+1);
  system->ap[n]->cnt = (int *) malloc(sizeof(int));
  *system->ap[n]->cnt = 0;
  strcpy(system->ap[n]->name,name);
  *system->cnt = n+1;
}


/*
 *  Returns a pointer to the airport with the given name.
 *  If the airport doesn't exist, return NULL.
 */
airport_t* getAirport(flightSys_t* system, char* name) {
  airport_t **airports =  system->ap;
  for (size_t i = 0; i<*system->cnt; i++)
  {    
    if (!strcmp(airports[i]->name,name))
    {
      return airports[i];
    }
  }
  return NULL;
}


/*
 *  Print each airport name in the order they were added through 
 *  , one on each line.Make sure to end with a new line. You 
 *  should compare your output with the correct output
 *  in `flights.out` to make sure your formatting is correct.
 */
void printAirports(flightSys_t* system) {
  airport_t **airports = system->ap;
  for (size_t i = 0; i < *system->cnt; i++)
  {    
    printf("%s\n",airports[i]->name);
  }
}


/*
 *  Adds a flight to source's schedule, stating a flight will 
 *  leave to destination at departure time and arriintve at arrival time.
 */
void addFlight(airport_t* source, airport_t* destinintation, timeHM_t* departure, timeHM_t* arrival, int cost) {
  int cnt = *source->cnt;
  flight_t **flights = (flight_t **) realloc(source->flight,8*(cnt+1));
  flight_t *fli = malloc(sizeof(flight_t));
  fli->cost = malloc(sizeof(int));
  fli->desAirPort = malloc(sizeof(fli));
  fli->fromTime = malloc(sizeof(fli));
  fli->toTime = malloc(sizeof(fli));
  *(fli->cost) = cost;
  fli->desAirPort = destinintation;

  timeHM_t * f = (timeHM_t *)malloc(sizeof(timeHM_t));
  timeHM_t * t = (timeHM_t *)malloc(sizeof(timeHM_t));
  f->hours = departure->hours;
  f->minutes = departure->minutes;
  t->hours = arrival->hours;
  t->minutes = arrival->minutes;

  fli->fromTime = f;
  fli->toTime = t;
  flights[cnt] = fli;
  *source->cnt = *source->cnt+1;
  source->flight = flights;
}


/*
 *  Prints the schedule of flights of the given airport.
 *
 *  Prints the airport name on the first line, then prints a 
 *  schedule entry on each  that follows, with the format: 
 *  "destination_name departure_time arrival_time $cost_of_flight".
 *
 *  You should use `printTime()` (look in `timeHM.h`) to 
 *  print times, and the order should be the same as
 *  the order they were added in through addFlight. 
 *  Make sure to end with a new line.You should compare 
 *  output with the correct output in flights.out to 
 *  make sure your formatting is correct.
 */
void printSchedule(airport_t* airport) {
  printf("%s\n",airport->name);

  int cnt = *airport->cnt;
  for (int i = 0; i < cnt; i++)
  {
    flight_t *flight =  (airport->flight)[i];
    printf("%s ",flight->desAirPort->name);
    printTime(flight->fromTime);
    printf(" ");
    printTime(flight->toTime);
    printf(" ");
    printf("$%d\n",*(flight->cost));
  }
  
}


/*
 *   Given a source and destination airport, and the time 
 *   now, finds the next flight to take based on the following rules:
 *   1) Finds the earliest arriving flight from source to 
 *   destination that departs after now.
 *   2) If there are multiple earliest flights, take the one 
 *   that costs the least.
 *
 *   If a flight is found, you should store the flight's 
 *   departure time, arrival time, and cost in the `departure`, `arrival`,
 *   and `cost` params and return true. Otherwise, return false.
 *
 *   Please use the functions `isAfter()` and `isEqual()` 
 *   from `timeHM.h` when comparing two timeHM_t objects and compare
 *   the airport names to compare airports, not the pointers.
 */
bool getNextFlight(airport_t* source, airport_t* destination, timeHM_t* now, 
timeHM_t* departure, timeHM_t* arrival,
                   int* cost) {
  flight_t **flights =  source->flight;
  int cnt = *source->cnt;
  bool bol = false;
  departure->hours = 23;
  departure->minutes = 59;
  *cost = 9999;
  for (int i = 0; i<cnt; i++)
  {  
    if (!strcmp(flights[i]->desAirPort->name,destination->name))
    {
      if (isAfter(departure,flights[i]->fromTime)&&
      isAfter(flights[i]->fromTime,now))
      {
        bol = true;
        departure->hours = flights[i]->fromTime->hours;
        departure->minutes = flights[i]->fromTime->minutes;
        arrival->hours = flights[i]->toTime->hours;
        arrival->minutes = flights[i]->toTime->minutes;
        *cost= *flights[i]->cost;        
      } else if (isEqual(departure,flights[i]->fromTime)){
        *cost= *flights[i]->cost;
        arrival->hours = flights[i]->toTime->hours;
        arrival->minutes = flights[i]->toTime->minutes;
      }
    }
  }
  return bol;
}

/*
 *  Given a list of flight_t pointers (`flight_list`) and a 
 *  list of destination airport names (`airport_name_list`),
 *  first confirm that it is indeed possible to take these 
 *  sequences of flights, (i.e. be sure that the i+1th flight departs
 *  after or at the same time as the ith flight arrives) 
 *  (HINT: use the `isAfter()` and `isEqual()` functions).
 *  Then confirm that the list of destination airport 
 *  names match the actual destination airport names of the 
 *  provided flight_t structs.
 *
 *  `size` tells you the number of flights and destination airport n
 *  ames to consider. Be sure to extensively test for errors.
 *  As one example, if you encounter NULL's for any values 
 *  you might expect to be non-NULL return -1, but test for other possible errors too.
 *
 *  Return from this function the total cost of taking these 
 *  sequence of flights.
 *  If it is impossible to take these sequence of flights,
 *  if the list of destination airport names doesn't match 
 *  the actual destination airport names provided in the flight_t struct's,
 *  or if you run into any errors mentioned previously or 
 *  any other errors, return -1.
 */
int validateFlightPath(flight_t** flight_list, char** airport_name_list, 
int size) {
  int money = 0;
  if (flight_list==NULL)
  {
    return -1;
  }
  
  timeHM_t *t =  flight_list[0]->toTime;
  for (int i = 0; i < size; i++)
  {
    flight_t *f =  flight_list[i];
    char *a =  airport_name_list[i];
    if (f==NULL||a==NULL)
    {
      return -1;
    }
    if (i!=0&&(isAfter(t,f->fromTime)))
    {
      return -1;
    }
    if (strcmp(f->desAirPort->name,a)!=0)
    {
      return -1;
    }
    money += *f->cost;
  }
  
  return money;
}

