#include<stdio.h>

int lruFinder(int clock[], int x)
{
    int i, smallest = clock[0], place = 0;
    for(i = 1; i < x; ++i)
    {
      if(clock[i] < smallest)
      {
          smallest = clock[i];
          place = i;
      }
    }
    return place;
}
int main()
{
    int amountOfFrames, amountOfPages, thesePages[30], theseFrames[10], count = 0, clock[10], flagThis1, flagThis2, i, j, place, numOfFaults = 0;
    printf("If you please, I'd like you to enter number of frames which you desire: ");
    scanf("%d", &amountOfFrames);
    printf("If you please, I'd like you to enter number of pages which you desire: ");
    scanf("%d", &amountOfPages);
    printf("If you please, I'd like you to enter reference string you had in mind: ");
    for(i = 0; i < amountOfPages; ++i)
    {
        scanf("%d", &thesePages[i]);
    }
    for(i = 0; i < amountOfFrames; ++i)
    {
        theseFrames[i] = -1;
    }
    for(i = 0; i < amountOfPages; ++i)
    {
        flagThis1 = flagThis2 = 0;
        for(j = 0; j < amountOfFrames; ++j)
        {
            if(theseFrames[j] == thesePages[i])
            {
                count++;
                clock[j] = count;
                flagThis1 = flagThis2 = 1;
                break;
            }
       }
        if(flagThis1 == 0)
        {
            for(j = 0; j < amountOfFrames; ++j)
            {
                if(theseFrames[j] == -1)
                {
                    count++;
                    numOfFaults++;
                    theseFrames[j] = thesePages[i];
                    clock[j] = count;
                    flagThis2 = 1;
                    break;
                }
            }
        }
        if(flagThis2 == 0)
        {
            place = lruFinder(clock, amountOfFrames);
            count++;
            numOfFaults++;
            theseFrames[place] = thesePages[i];
            clock[place] = count;
        }
        printf("\n");
        for(j = 0; j < amountOfFrames; ++j)
        {
            printf("%d\t", theseFrames[j]);
        }
    }
printf("\n\nTotal Page Faults = %d", numOfFaults);
return 0;
}
