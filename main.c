
#include <stdio.h>
#include <string.h>

#define maxtrains 20
#define maxseats 15
#define maxpassengers 600



int isValidDate(int d, int m, int y)
{
    int monthDays[] = {31,28,31,30,31,30, 31,31,30,31,30,31};
    if (y < 1 || m < 1 || m > 12)
        return 0;
    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        monthDays[1] = 29;
    if (d < 1 || d > monthDays[m-1])
        return 0;
    return 1;
}


void nextDay(int *d, int *m, int *y)
{
    int monthDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if ((*y % 400 == 0) ||(*y % 4 == 0 && *y % 100 != 0))
        monthDays[1] = 29;
        (*d)++;

        if (*d > monthDays[*m-1])
        {
        *d = 1;
        (*m)++;
        if (*m > 12)
        {
            *m = 1;
            (*y)++;
        }
        }
}

int daysBetween(int d1, int m1, int y1, int d2, int m2, int y2)
{
    int days = 0;

    if (!isValidDate(d1,m1,y1) || !isValidDate(d2,m2,y2))
        return -999999;

    int direction = 1;

    if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2))
    {
        direction = -1;

        int temp;

        temp = d1;
        d1 = d2;
        d2 = temp;

        temp = m1;
        m1 = m2;
        m2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    while (d1 != d2 || m1 != m2 || y1 != y2)
    {
        nextDay(&d1,&m1,&y1);
        days++;
    }

    return days * direction;
}

// Passenger structure
struct Passenger
{
    char name[100];
    int age;
    int PNR;
    int train_number;
    int seat;
    char journey_date[15];
    int status;
};


// Train structure
struct Train
{
    int tnumber;
    char tname[100];
    char destination[100];
    float fare;
    int seat_status[maxseats];
    char source[100];
    char journey_date[15];
};


// Waiting-list promotion function
void promoteWaiting(struct Passenger passengers[],struct Train trains[],int passengercount,int t,int seat)
{
    int waitingFound = 0;
    // Search passengers in booking order
    for (int i = 0; i < passengercount; i++)
    {
        if (passengers[i].train_number == trains[t].tnumber &&
            passengers[i].status == 1)
        {
            // Give the freed seat to first waiting passenger
            passengers[i].seat = seat;
            passengers[i].status = 0;
            trains[t].seat_status[seat-1] = 1;
            waitingFound = 1;
            break;
        }
    }
    if (waitingFound == 0)
    {
        printf("No waiting passengers for this train.\n");
    }
}


void bookTicket(struct Train trains[], struct Passenger passengers[],int traincount, int *passengercount, int *nextPNR)
{   
                int found = 0;
                int  freeCount = 0;
                int  t = -1;
                int seat =0;
                int n = *passengercount; 
                int tn;
                printf("Enter train number =\n");
                scanf("%d", &tn);
                // Display seat layout
                for(int i = 0; i < traincount; i++)
                {
                    if(tn == trains[i].tnumber)
                    {
                        printf("Journey Date = %s\n", trains[i].journey_date);

                        for(int j = 0; j < maxseats; j++)
                        {
                            if(trains[i].seat_status[j] == 0)
                            {
                                printf("Seat %d: free\n", j+1);
                                freeCount++;
                            }
                            else
                            {
                                printf("Seat %d: booked\n", j+1);
                            }
                        }

                        found = 1;
                        t = i;
                        break;
                    }
                }


                if(found == 0)
                {
                    printf("Invalid Train Number.\n");
                    return;
                }


                // Check passenger capacity
                if(n >= maxpassengers)
                {
                    printf("Passenger list is full.\n");
                    return;
                }


                seat = 0;


                // If seats are available, confirm booking
                if(freeCount > 0)
                {
                    do
                    {
                        printf("Choose a free seat = \n");
                        scanf("%d", &seat);

                        if(seat < 1 || seat > maxseats)
                        {
                            printf("Invalid seat number.\n");
                        }
                        else if(trains[t].seat_status[seat-1] != 0)
                        {
                            printf("Seat is booked.\n");
                        }

                    } while(seat < 1 || seat > maxseats ||trains[t].seat_status[seat-1] != 0);
                }
                else
                {
                    printf("\nTrain is full.\n");
                    printf("You will be added to the waiting list.\n");
                }


                // Get passenger details
                printf("Enter passenger name: ");
                scanf(" %99[^\n]", passengers[n].name);
                printf("Enter age: ");
                scanf("%d", &passengers[n].age);
                // Generate PNR
                passengers[n].PNR = *nextPNR;
                passengers[n].train_number = tn;
                passengers[n].seat = seat;
                strcpy(passengers[n].journey_date,trains[t].journey_date);


                if(freeCount > 0)
                {
                    trains[t].seat_status[seat-1] = 1;
                    passengers[n].status = 0;
                    printf("\nTicket Confirmed!\n");
                }
                else
                {
                    passengers[n].status = 1;
                    printf("\nPassenger added to Waiting List!\n");
                }


                // Display ticket details
                printf("\n====== TICKET DETAILS ======\n");
                printf("PNR: %d\n",passengers[n].PNR);
                printf("Name: %s\n", passengers[n].name);
                printf("Age: %d\n", passengers[n].age);
                printf("Train: %s (%d)\n",trains[t].tname, tn);
                printf("From %s to %s\n", trains[t].source,trains[t].destination);

                if(passengers[n].status == 0)
                {
                    printf("Seat: %d\n", seat);
                    printf("Status: Confirmed\n");
                }
                else
                {
                    printf("Seat: Not Allotted\n");
                    printf("Status: Waiting\n");
                }

                printf("Journey Date: %s\n",passengers[n].journey_date);
                printf("Fare: %.2f\n", trains[t].fare);
                printf("============================\n");


                (*passengercount)++;
                (*nextPNR)++;


}
float calcrefund(int days)

{
    if (days >= 3)
        return 0.90;
    else if (days >= 1)
        return 0.60;
    else if (days == 0)
        return 0.25;
    else
        return 0.0;


}

int main()
{
    int choice;
    int found = 0;
    struct Train trains[maxtrains];
    struct Passenger passengers[maxpassengers];
    int traincount = 0;
    char s[100], d[100];
    int  pnr;
    int passengercount = 0;
    int seat, t, p;
    int nextPNR = 1001;
    float percentage, refund;
    do
    {
        printf("\n====== SMART RAILWAY RESERVATION AND WAITLIST MANAGEMENT SYSTEM ======\n");
        printf("1: Add Trains\n");
        printf("2: Display Trains\n");
        printf("3: Search trains by source and destination\n");
        printf("4: Book Train Tickets\n");
        printf("5: Cancel Train Tickets\n");
        printf("6: Check PNR and booking status\n");
        printf("7: EXIT\n");
        printf("Enter your choice =\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:  // Adding trains
                if(traincount < maxtrains)
                {
                    printf("Add Train\n");
                    printf("Enter train name = \n");
                    scanf(" %99[^\n]", trains[traincount].tname);
                    printf("Enter train number = \n");
                    scanf("%d", &trains[traincount].tnumber);
                    printf("Enter destination = \n");
                    scanf(" %99[^\n]", trains[traincount].destination);
                    printf("Enter train fare = \n");
                    scanf("%f", &trains[traincount].fare);
                    printf("Enter train source = \n");
                    scanf(" %99[^\n]", trains[traincount].source);
                    printf("Enter journey date (dd-mm-yyyy) = \n");
                    scanf(" %14s", trains[traincount].journey_date);
                    for(int i = 0; i < maxseats; i++)
                    {
                        trains[traincount].seat_status[i] = 0;
                    }
                    traincount++;
                    printf("Train added successfully!\n");
                }
                else
                {
                printf("Traincount exceeded.\n");
                }  
                break;
            case 2: // Displaying trains
                if(traincount == 0)
                {
                    printf("No Trains Available\n");
                }
                else
                {
                    for(int i = 0; i < traincount; i++)
                    {
                        printf("\nTrain Name = %s\n", trains[i].tname);
                        printf("Train Number = %d\n", trains[i].tnumber);
                        printf("From %s to %s\n", trains[i].source, trains[i].destination);
                        printf("Train fare = %.2f\n", trains[i].fare);
                        printf("Journey Date = %s\n",  trains[i].journey_date);
                    }
                }

                break;


            case 3: // Search train by source and destination

                printf("Enter source =\n");
                scanf(" %99[^\n]", s);

                printf("Enter destination =\n");
                scanf(" %99[^\n]", d);

                found = 0;

                for(int i = 0; i < traincount; i++)
                {
                    if(strcmp(trains[i].source,s) == 0 && strcmp(trains[i].destination,d) == 0)
                    {
                        printf("\nTrain Name = %s\n", trains[i].tname);
                        printf("Train Number = %d\n", trains[i].tnumber);
                        printf("From %s to %s\n", trains[i].source, trains[i].destination);
                        printf("Train fare = %.2f\n", trains[i].fare);
                        printf("Journey Date = %s\n", trains[i].journey_date);

                        found = 1;
                    }
                }

                if(found == 0)
                {
                    printf("No train found.\n");
                }

                break;


            case 4: // Booking train tickets
            bookTicket(trains, passengers, traincount, &passengercount, &nextPNR); break;

            case 5: // Cancelling tickets and refund

                printf("Enter PNR = \n");
                scanf("%d", &pnr);

                p = -1;
                found = 0;


                // Find passenger
                for(int i = 0; i < passengercount; i++)
                {
                    if(passengers[i].PNR == pnr)
                    {
                        p = i;
                        found = 1;
                        break;
                    }
                }


                if(found == 0)
                {
                    printf("PNR not found.\n");
                    break;
                }


                if(passengers[p].status == 2)
                {
                    printf("Ticket already cancelled.\n");
                    break;
                }


                // Find train
                t = -1;

                for(int i = 0; i < traincount; i++)
                {
                    if(trains[i].tnumber == passengers[p].train_number)
                    {
                        t = i;
                        break;
                    }
                }


                if(t == -1)
                {
                    printf("Train not found.\n");
                    break;
                }


                // Cancel waiting-list ticket
                if(passengers[p].status == 1)
                {
                    passengers[p].status = 2;

                    printf("Waiting-list ticket cancelled.\n");
                    printf("No refund applicable for waiting-list ticket.\n");

                    break;
                }


                // Enter cancellation date
                int cd, cm, cy;
                int jd, jm, jy;

                printf("Enter cancellation date (DD MM YYYY): ");
                scanf("%d %d %d", &cd, &cm, &cy);


                // Extract journey date
                if(sscanf(passengers[p].journey_date, "%d-%d-%d", &jd, &jm, &jy) != 3)
                {
                    printf("Invalid journey date.\n");
                    break;
                }


                // Calculate days remaining
                int days = daysBetween(cd, cm, cy, jd, jm, jy);


                if(days == -999999)
                {
                    printf("Invalid date entered.\n");
                    break;
                }


                // Calculate refund
    
                percentage = calcrefund(days);
                refund = trains[t].fare * percentage; 

                printf("\n====== REFUND DETAILS ======\n");
                printf("Journey Date: %s\n",passengers[p].journey_date);
                printf("Days before journey: %d\n", days);
                printf("Ticket Fare: Rs. %.2f\n", trains[t].fare);
                printf("Refund Percentage: %.0f%%\n", percentage * 100);
                printf("Refund Amount: Rs. %.2f\n", refund);
                printf("============================\n");


                // Store the cancelled seat
                seat = passengers[p].seat;


                // Release seat
                trains[t].seat_status[seat-1] = 0;

                passengers[p].status = 2;

                printf("Ticket cancelled successfully.\n");


                // Promote first waiting passenger
                promoteWaiting(passengers, trains,passengercount, t, seat);

                break;


            case 6: // Check PNR and booking status

                printf("Enter PNR = \n");
                scanf("%d", &pnr);

                found = 0;

                for(int i = 0; i < passengercount; i++)
                {
                    if(passengers[i].PNR == pnr)
                    {
                        printf("\n====== BOOKING DETAILS ======\n");

                        printf("Name = %s\n", passengers[i].name);
                        printf("Age = %d\n",passengers[i].age);
                        printf("Train Number = %d\n",passengers[i].train_number);

                        if(passengers[i].status == 1)
                        {
                            printf("Seat = Not Allotted\n");
                            printf("Status = Waiting\n");
                        }
                        else if(passengers[i].status == 0)
                        {
                            printf("Seat = %d\n", passengers[i].seat);
                            printf("Status = Confirmed\n");
                        }
                        else
                        {
                            printf("Seat = %d\n",  passengers[i].seat);

                            printf("Status = Cancelled\n");
                        }

                        printf("Journey Date = %s\n", passengers[i].journey_date);

                        printf("=============================\n");

                        found = 1;
                        break;
                    }
                }


                if(found == 0)
                {
                    printf("PNR not found.\n");
                }

                break;


            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while(choice != 7);


    return 0;
}
