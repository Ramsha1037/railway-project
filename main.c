#include <stdio.h>
#include <string.h>

    struct Passenger
    {
       //name, age, PNR, train number, seat, journey date, status
       char name[100];
       int age;
       int PNR;
       int train_number;
       int seat;
       char journey_date[15];
       int status;
    };

    struct Train
    {
      //number, name, source, destination, fare, seat-status array
      int tnumber;
      char tname[100];
      char destination[100];
      float fare;
      int seat_status;
      char source[100];
    }
int main()
{
    printf("Smart Railway System");
    return 0;

}