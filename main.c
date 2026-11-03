#include <stdio.h>
#include <string.h>

#define maxtrains 20
#define maxseats 15


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
    };
int main()
{
    
     int choice;
    struct Train trains[maxtrains];
    int traincount = 0;


    do
    {
       
        printf("======SMART RAILWAY RESERVATION AND WAITLIST MANAGEMENT SYSTEM=====\n");
        printf(" 1:Add Trains \n");
        printf(" 2:Display Trains \n");
        printf(" 3:Search trains by source and destination \n");
        printf(" 4:Book Train Tickets \n");
        printf(" 5:Cancel Train Tickets \n");
        printf(" 6:Check PNR and booking status \n");
        printf(" 7:EXIT \n");

        scanf("%d" , &choice);

        //using switch for using features
        switch(choice)
        {
            case 1: 
            if(traincount < maxtrains)
            {
               printf("Add Train\n");
               printf("Enter train name = \n");
               scanf(" %[^\n]", trains[traincount].tname);
               printf("Enter train number = \n");
               scanf("%d" , &trains[traincount].tnumber );
               printf("Enter destination = \n");
               scanf(" %[^\n]", trains[traincount].destination);
               printf("Enter train fare = \n");
               scanf("%f" , &trains[traincount].fare );
               printf("Enter train source = \n");
               scanf(" %[^\n]", trains[traincount].source);
               

               traincount++;
               
               
            }
            else
            printf("Traincount exceeded");
            break;

        }


    } while (choice!=7);


    


}