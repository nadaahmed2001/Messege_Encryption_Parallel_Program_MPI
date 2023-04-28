#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char filename[100];
char *NewMessage;
FILE *fp;
FILE *fp2;
int main(int argc, char **argv)
{
    int size,subSize, rank,np;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    char *message;
    char *subMessage;
    int length;
    int sublength;
    int key;

    int i;
    if (rank == 0)
    {

        // filename = "file.txt";
        printf("Enter file name: ");
        scanf("%s", filename);
        fp = fopen(filename, "r");
        if (fp == NULL)
        {
            printf("Could not open file %s",filename);
            return 1;
        }
        message = (char *) malloc(100 * sizeof(char));
        fgets(message, 100, fp);
        fclose(fp);

        length=strlen(message);
        sublength=length/np;

        NewMessage = (char *) malloc(length * sizeof(char));
        printf("Enter key: ");
        scanf("%d", &key);
        printf("Master can see Message before encryption: %s\n", message);
    }

    MPI_Bcast(&sublength, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scatter(message, sublength, MPI_CHAR, subMessage, sublength, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("Processor %d has subMessage : ", rank);
    for (i=0; i<sublength; i++)
        printf("%c ", subMessage[i]);
    printf("\n");

    //encrypt the message using the caesar cipher
    for (i=0; i<sublength; i++)
    {
        if(subMessage[i] >= 'a' && subMessage[i] <= 'z')
        {
            subMessage[i] = subMessage[i] + key;
            if(subMessage[i] > 'z')
            {
                subMessage[i] = subMessage[i] - 'z' + 'a' - 1;
            }
        }
        else if(subMessage[i] >= 'A' && subMessage[i] <= 'Z')
        {
            subMessage[i] = subMessage[i] + key;
            if(subMessage[i] > 'Z')
            {
                subMessage[i] = subMessage[i] - 'Z' + 'A' - 1;
            }
        }
    }


    MPI_Gather(subMessage, sublength, MPI_CHAR, message, sublength, MPI_CHAR, 0, MPI_COMM_WORLD);
    if(rank==0)
    {
        //handle remaining characters
        if(length%np!=0)
        {
            int remainder = length - (np * sublength);
            for (int i = np*sublength; i < length; ++i)
            {
                printf("%c", message[i]);
            }
     
            for (int i = np*sublength; i < length; ++i)
            {
                if(message[i] >= 'a' && message[i] <= 'z')
                {
                    message[i] = message[i] + key;
                    if(message[i] > 'z')
                    {
                        message[i] = message[i] - 'z' + 'a' - 1;
                    }
                }
                else if(message[i] >= 'A' && message[i] <= 'Z')
                {
                    message[i] = message[i] + key;
                    if(message[i] > 'Z')
                    {
                        message[i] = message[i] - 'Z' + 'A' - 1;
                    }
                }
            }

        }
        printf("Master can see Message after encryption: %s\n", message);

        fp2 = fopen("encrypted.txt","w");
        if(fp2 == NULL)
        {
            printf("Error opening file\n");
            exit(1);
        }
        //write message to file
        for(i=0; i<length; i++)
        {
            fprintf(fp2,"%c",message[i]);
        }
        fclose(fp2);

    }


    MPI_Finalize();
    return 0;
}
