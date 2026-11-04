#include <stdio.h>
#include <string.h>

#define maxtrains 20
#define maxseats 15
#define maxpassengers 600


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
      int seat_status[maxseats];
      char source[100];
      char journey_date[15];     
    };
int main()
{
    
     int choice ; int found =0; 
    struct Train trains[maxtrains];
    struct Passenger passengers[maxpassengers];
    int traincount = 0;
    char s[100] , d[100];
    int tn ,pnr;
    int passengercount =0;
    int seat , t ,p;
    int nextPNR = 1001;   
    int freeCount=0;  
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
        printf("Enter your choice =\n");
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
               printf("Enter journey date (dd-mm-yyyy) = \n");
               scanf(" %14s", trains[traincount].journey_date);
               
               for (int i = 0; i < maxseats; i++)
               {
                 trains[traincount].seat_status[i] = 0;
                }
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
                    printf("Journey Date = %s\n", trains[i].journey_date);
                }
            }
            break;

            case 3: //search train by source and destination
            
            printf("Enter source: ");
            scanf(" %[^\n]", s);
            printf("Enter destination: ");
            scanf(" %[^\n]", d);
            found =0;

            for(int i=0; i < traincount; i++)
            {
                if( (strcmp(trains[i].source,s ))==0&&  (strcmp( trains[i].destination,d ))==0)
                {

                    printf("Train Name = %s\n" , trains[i].tname );
                    printf("Train Number = %d\n" , trains[i].tnumber );
                    printf("From %s to %s \n" , trains[i].source , trains[i].destination);
                    printf("Train fare = %.2f\n" , trains[i].fare );
                    printf("Journey Date = %s\n", trains[i].journey_date);
                    found =1;
                }
                
            }
            if(found==0)
            printf("No train found\n");
            break;


          

          
           case 4:
           found = 0;
           freeCount = 0;
           t = -1;
           printf("Enter train number =\n");
           scanf("%d" , &tn);

           // seat layout
           for(int i=0; i<traincount ; i++)
           {
            if(tn == trains[i].tnumber)
            {
                printf("Journey Date = %s\n", trains[i].journey_date);
               for(int j =0; j<maxseats ; j++)
               {
                if(trains[i].seat_status[j] == 0)
                {
                 printf("Seat %d: free\n", j + 1);
                 freeCount++;
                }
                else
                 printf("Seat %d: booked\n", j + 1);
               }
               found = 1;
               t = i;
            }
           }

           if(found == 0)
           {
            printf("Invalid Train Number\n");
            break;
           }

           // booking
           if (passengercount >= maxpassengers)
           {
            printf("Passenger list is full.\n");
            break;
           }

           if (freeCount == 0)
           {
            printf("Train is full.\n");
            break;
           }

           do
           {
            printf("Choose a free seat = \n");
            scanf("%d" , &seat);

            if (seat < 1 || seat > maxseats)
                printf("Invalid seat number.\n");
            else if (trains[t].seat_status[seat-1] != 0)
                printf("Seat is booked.\n");

           } while (seat < 1 || seat > maxseats || trains[t].seat_status[seat-1] != 0);

           printf("Enter passenger name: ");
           scanf(" %[^\n]", passengers[passengercount].name);
           printf("Enter age: ");
           scanf("%d", &passengers[passengercount].age);
           

           trains[t].seat_status[seat-1] = 1;

           passengers[passengercount].PNR = nextPNR;
           passengers[passengercount].train_number = tn;
           passengers[passengercount].seat = seat;
           passengers[passengercount].status = 0;
           strcpy(passengers[passengercount].journey_date, trains[t].journey_date);

           // ticket
           printf("\n====== TICKET ======\n");
           printf("PNR: %d\n", passengers[passengercount].PNR);
           printf("Name: %s\n", passengers[passengercount].name);
           printf("Train: %s (%d)\n", trains[t].tname, tn);
           printf("From %s to %s\n", trains[t].source, trains[t].destination);
           printf("Seat: %d\n", seat);
           printf("Date: %s\n", passengers[passengercount].journey_date);
           printf("Fare: %.2f\n", trains[t].fare);
           printf("====================\n");

           passengercount++;
           nextPNR++;
           break;

           
           case 5:
           printf("Enter PNR = \n");
           scanf("%d", &pnr);

            p = 0;
           found = 0;
           for (int i = 0; i < passengercount; i++)
          {
           if (passengers[i].PNR == pnr)
           {
            p = i;
            found = 1;
           }
          }

         if (found == 0)
         {
          printf("PNR not found.\n");
          break;
         }
         if (passengers[p].status == 2)
         {
          printf("Ticket already cancelled.\n");
          break;
         }

          t = 0;
          for (int i = 0; i < traincount; i++)
         {
           if (trains[i].tnumber == passengers[p].train_number)
            t = i;
          }

         trains[t].seat_status[passengers[p].seat - 1] = 0;
         passengers[p].status = 2;

         printf("Ticket cancelled.\n");
         break;

           case 6:
           printf("Enter PNR = \n");
           scanf("%d", &pnr);
           found = 0;

           for (int i = 0; i < passengercount; i++)
          {
           if (passengers[i].PNR == pnr)
          {
            printf("Name = %s\n", passengers[i].name);
            printf("Age = %d\n", passengers[i].age);
            printf("Train Number = %d\n", passengers[i].train_number);
            printf("Seat = %d\n", passengers[i].seat);
            printf("Journey Date = %s\n", passengers[i].journey_date);

            if (passengers[i].status == 0)
                printf("Status = Confirmed\n");
            else if (passengers[i].status == 1)
                printf("Status = Waiting\n");
            else
                printf("Status = Cancelled\n");

            found = 1;
          }
          }

          if (found == 0)
          printf("PNR not found.\n");

          break;

        }
   


    } while (choice!=7);

    return 0;
    


}