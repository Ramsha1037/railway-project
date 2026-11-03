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
    
     int choice ; int found =0; 
    struct Train trains[maxtrains];
    int traincount = 0;
    char s[100] , d[100];
    

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
            case 1:  // adding trains
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
            
            case 2: //displaying trains
            
            if(traincount == 0)
            printf("No Trains Available\n");
            else
            {
                for(int i =0; i < traincount; i++)
                {
                    printf("Train Name = %s\n" , trains[i].tname );
                    printf("Train Number = %d\n" , trains[i].tnumber );
                    printf("From %s to %s \n" , trains[i].source , trains[i].destination);
                    printf("Train fare = %.2f\n" , trains[i].fare );
                }
            }
            break;

            case 3: //search train by source and destination
            
            printf("Enter source: ");
            scanf(" %[^\n]", s);
            printf("Enter destination: ");
            scanf(" %[^\n]", d);


            for(int i=0; i < traincount; i++)
            {
                if( (strcmp(trains[i].source,s ))==0&&  (strcmp( trains[i].destination,d ))==0)
                {

                    printf("Train Name = %s\n" , trains[i].tname );
                    printf("Train Number = %d\n" , trains[i].tnumber );
                    printf("From %s to %s \n" , trains[i].source , trains[i].destination);
                    printf("Train fare = %.2f\n" , trains[i].fare );
                    found =1;
                }
                
            }
            if(found==0)
            printf("No train found\n");
            break;
        }



    } while (choice!=7);


    


}