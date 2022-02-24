#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float grade(char grad[5]);

int main()
{
    struct semester
    {
        char semname[12];
        int n;
        char code[5][7];
        char title[5][64];
        char grad[5][5];
        float cr[5];
        float cgpaS;
    };
    struct semester sem[15];

    char id[14],fname[18],name[32],degree[64];
    int i,fcn;
    float cgpa;
    printf("\t\t\t    EAST WEST UNIVERSITY!\n\t\t\t       CGPA Calculator\n-------------------------------------------------------------------------------");
    printf("\t\tInput student ID : ");
    scanf("%s",id);
    printf("-------------------------------------------------------------------------------\n");
    strcpy(fname,id);
    strcat(fname,".txt");

    FILE *ptw,*ptr;
    while(1)
    {
        printf("\t\t\t\tCHOOSE FUNCION:\n\t1.Input Student Information\n\t2.Read and calculate data\n\t3.Change Student ID\n\t0.Exit\n");
        printf("\nFunction : ");
        scanf("%d",&fcn);
        printf("\n-------------------------------------------------------------------------------\n");
        getchar(); // To clear up the \n character
        if(fcn==1)
        {
            ptw=fopen(fname,"a");
            ptr=fopen(fname,"r");

            fseek (ptr, 0, SEEK_END);
            int size = ftell(ptr);
            if(size==0)
            {
                printf("\nFile is empty.\nInput user's full name: \n");
                gets(name);
                printf("\nInput Degree:\n");
                gets(degree);
                fprintf(ptw,"%s\n%s\n",name,degree);
                fclose(ptw);
                fclose(ptr);
            }
            else
                {
                printf("\nInput semester name: (eg:Summer-2018) \n");
                gets(sem[0].semname);
                fputs(sem[0].semname,ptw);
                do
                    {
                    printf("Input courses in semester : ");
                    scanf("%d",&sem[0].n);
                }
                while(sem[0].n<1||sem[0].n>5);
                fprintf(ptw,"\t%d\n",sem[0].n);

                for(i=0;i<sem[0].n;i++)
                {
                    do
                    {
                        printf("\nInput course code for course %d: ",i+1);
                        scanf("%s",sem[0].code[0]);
                        int j;
                        for(j=0;j<3;j++)
                        {
                            if(sem[0].code[0][j]>='a'&&sem[0].code[0][j]<='z')
                                sem[0].code[0][j]=sem[0].code[0][j]-32;
                        }
                    }while(strlen(sem[0].code[0])!=6);

                    printf("Input course Title : ");
                    getchar();
                    gets(sem[0].title[0]);
                    do
                    {
                        printf("Input course credit : ");
                        scanf("%f",&sem[0].cr[0]);
                    } while(sem[0].cr[0]>5||sem[0].cr[0]<1);

                    printf("Input Course Grade Letter : ");
                    scanf("%s",sem[0].grad[0]);
                    if(sem[0].grad[0][0]>='a'&&sem[0].grad[0][0]<='z')
                    {
                            sem[0].grad[0][0]=sem[0].grad[0][0]-32;
                    }
                    fprintf(ptw,"%s\t%f\t%s\t%s\n",sem[0].code[0],sem[0].cr[0],sem[0].grad[0],sem[0].title[0]);
                    printf("\n");
                }
                printf("-------------------------------------------------------------------------------\n");
                fclose(ptw);
                fclose(ptr);
            }


        }
        else if(fcn==2)
        {
            ptr=fopen(fname,"r");
            if(ptr==NULL)
            {
                printf("\nStudent data does not exist!\n\n");
                return 0;
            }

            i=0;
            int j;
            float crT,crS,crgpa,crgpaT,crgpaS;
            crT=0;
            crgpaT=0;


            fgets(name,32,ptr);
            fgets(degree,64,ptr);
            printf("Name : \t%s",name);
            printf("ID : \t%s\n",id);
            printf("Degree:\t%s\n",degree);
            printf("-------------------------------------------------------------------------------\n");
            while(1)
            {
                fscanf(ptr,"%s\t%d\n",sem[i].semname,&sem[i].n);
                printf("\n%s\n\n",sem[i].semname);
                printf("Course\tTitle of the Course\t\t\tCredits\tGrade\tGPACredits\n");
                crS=0;
                crgpaS=0;
                for(j=0;j<sem[i].n;j++)
                {
                    fscanf(ptr,"%s\t%f\t%s\t",sem[i].code[j],&sem[i].cr[j],sem[i].grad[j]);
                    fgets(sem[i].title[j],64,ptr);
                    sem[i].title[j][(strlen(sem[i].title[j]))-1]='\0'; // To remove the \n from fgets
                    crS+=sem[i].cr[j];
                    crgpa=sem[i].cr[j]*(grade(sem[i].grad[j]));
                    crgpaS+=crgpa;
                    printf("%s\t%s",sem[i].code[j],sem[i].title[j]);
                    if(strlen(sem[i].title[j])<8)
                        printf("\t\t\t\t\t");
                    else if(strlen(sem[i].title[j])<16)
                        printf("\t\t\t\t");
                    else if(strlen(sem[i].title[j])<24)
                        printf("\t\t\t");
                    else if(strlen(sem[i].title[j])<32)
                        printf("\t\t");
                    else if(strlen(sem[i].title[j])<38)
                        printf("\t");
                    else
                        printf(" ");

                    printf("%1.1f\t%s\t%2.2f\n",sem[i].cr[j],sem[i].grad[j],crgpa);
                }
                sem[i].cgpaS=(crgpaS/crS);
                crT+=crS;
                crgpaT+=crgpaS;
                cgpa=(crgpaT/crT);
                printf("\n\t\tCGPA = %1.2f\t\tTerm GPA = %1.2f\n",cgpa,sem[i].cgpaS);
                fscanf(ptr,"\n");
                printf("-------------------------------------------------------------------------------\n");
                i++;
                if(feof(ptr))
                    break;
            }
            cgpa=(crgpaT/crT);
            printf("\nSummery:\tTotal CGPA = %1.2f\t\tCredits Earned = %3.1f\n",cgpa,crT);
            fclose(ptr);

        }
        else if(fcn==3)
        {
            printf("\tInput student ID : ");
            scanf("%s",id);
            strcpy(fname,id);
            strcat(fname,".txt");
        }
        else if(fcn==0)
        {
            printf("\t\t\tProgram exited successfully!\n\t\t      Thank you for using the program!\n-------------------------------------------------------------------------------\n\n");
            return 0;
        }
        else
        {
            printf("Invalid function\n");
        }
        printf("-------------------------------------------------------------------------------\n");
    }

    return 0;
}

float grade(char grad[5])
{
    float g;  // In case user inputs integer instead of grade letter
    if(grad[0]>='a'&&grad[0]<='z')
    {
            grad[0]=grad[0]-32;
    }
    g=atof(grad);
    if(g>0&&g<=4)
        return g;


    if((strcmp(grad,"A+"))==0)
        return 4;
    else if((strcmp(grad,"A"))==0)
        return 4;
    else if((strcmp(grad,"A-"))==0)
        return 3.7;
    else if((strcmp(grad,"B+"))==0)
        return 3.3;
    else if((strcmp(grad,"B"))==0)
        return 3;
    else if((strcmp(grad,"B-"))==0)
        return 2.7;
    else if((strcmp(grad,"C+"))==0)
        return 2.3;
    else if((strcmp(grad,"C"))==0)
        return 2;
    else if((strcmp(grad,"C-"))==0)
        return 1.7;
    else if((strcmp(grad,"D+"))==0)
        return 1.3;
    else if((strcmp(grad,"D"))==0)
        return 1;
    else if((strcmp(grad,"F"))==0)
        return 0;
    else
        return 0;
}
