#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 10

FILE *fp = NULL;
FILE *fr = NULL;

typedef struct Materia
{
    char nome[DIM];
    float media;
    float sum;
    float den;
} Materia;

//This is so underoptimized it is a miracle it works. So it is a win in my book
void calcolaMedia(Materia *m, int dim, Materia *t)
{
    fp = fopen("voti.txt", "w");
    float temp = 0;
    float sums = 0;
    float cont = 0;
    if (m->sum==0.0)
    {
        do
        {
            temp=0;
            printf("Inserire il voto da inserire (premere 0 per terminare): ");
            scanf("%f", &temp);
            sums += temp;
            cont++;
            if (temp>10)
            {
                printf("Valore sopra il limite! Reinserire voto");
                cont--;
            }
        printf("\n");
        } while(temp>10 || temp!=0);
        cont--;
        m->media = sums / cont;
        m->sum = sums;
        m->den = cont;
        
        for (int i=0;i<dim;i++)
        {
        fprintf(fp,"%s %f %f %f\n", t[i].nome, t[i].media, t[i].sum, t[i].den);
        }
        fclose(fp);
    }
    else
    {
        do
        {
            printf("Inserire il voto da inserire (premere 0 per terminare): ");
            temp=0;
            scanf("%f", &temp);
            sums += temp;
            cont++;
            if (temp>10)
            {
                printf("Valore sopra il limite! Reinserire voto");
                cont--;
            }
        printf("\n");
        } while(temp>10 || temp!=0);
        cont--;
        m->sum += sums;
        m->den += cont;
        m->media = m->sum / m->den;
       
       for (int i=0;i<dim;i++)
        {
        fprintf(fp,"%s %f %f %f\n", t[i].nome, t[i].media, t[i].sum, t[i].den);
        }
        fclose(fp);
    }
    
}

//Creates a struct Materia, simply enough
Materia creaMateria()
{
    Materia mat;
    printf("Inserire il nome della materia: ");
    scanf("%s", &mat.nome);
    printf("\n");
    mat.media = 0.0;
    mat.sum = 0.0;
    mat.den = 0.0;
    return mat;
}

//Searches fot the materia in question. Why not use an HashMap? Dunno
int trovaMateria(Materia m[], int dim)
{
    char query[DIM];
    printf("Inserire nome materia: ");
    scanf("%s", &query);
    for (int i = 0; i < dim; i++)
    {
        if(strcmp(query,m[i].nome)==0)
        {
            return i;
        }
    }
    printf("Materia non trovata");
    
}

void printMateria(Materia m)
{
    printf("La materia %s ha una media di %f\n", m.nome, m.media);
}

//Displayed only the first time you launch the program. Hope you get it right the first time fucko!
int initialize()
{
    int n=4;
    printf("Benvenuti nel nuovo calcolatore di medie v0.1\n");
    do{
        printf("Si prega di iniziare indicando il numero delle materie da inserire (minimo 4): ");
        scanf("%d", &n);
    } while (n<4);
    printf("\n");
    return n;
}

//Checks whether it is the first time you launch the program or not.What a barbaric implementation!
int isAlreadyOpen(FILE *fr)
{
   int c=0;
    if (fr!=NULL)
    {
        fscanf(fr,"%d",&c);
    }
    return c;
}

//A menu that works just enough but would suck otherwise
void myMenu(Materia *m , int dim)
{
    int choice;
    printf("Selezionare l'operazione da eseguire\n");
    printf("1. Inserire voti\n");
    printf("2. Visualizzare medie\n");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
        {
            int query = trovaMateria(m,dim);
            calcolaMedia(&m[query],dim,m);
            break;
        }
        case 2:
        {
            for (int i = 0; i < dim; i++)
                {
                    printMateria(m[i]);
                }
            break;
        }
        default:
        {
            printf("Comando non trovato");
            break;
        }

    }
}
int main (void)
{
    //Shitton of variable declarations, yay!
    Materia *materie = (Materia*)malloc(sizeof(materie));
    const int give = 1;
    int mn=0;
    int matNum=0;
    fr = fopen ("ocnt.txt","a+");
    int c = isAlreadyOpen(fr);
    fp = fopen ("voti.txt", "a+");
    
    //The first time you launch the code you write down all of the subjects you can modify
    if (c==0)
    {
        matNum = initialize();
        materie = (Materia*)realloc(materie, matNum * sizeof(materie));
        for (int i = 0; i < matNum; i++)
        {
            materie[i] = creaMateria();
        }
        fprintf(fr,"%d\n%d", give, matNum);
        fclose(fr);
    }
    //Everytime you start the program after the first time the program reads the files storing the already stored data
    else
    {
        int tc;
        fr = fopen("ocnt.txt","r+");
        fscanf(fr,"%d\n%d", &tc,&mn);
        fclose(fr);
        for (int i=0; i<mn; i++)
        {
            fscanf(fp,"%s %f %f %f\n", &materie[i].nome, &materie[i].media, &materie[i].sum, &materie[i].den);
        }
    }
    
    //This sucks, but avoids core dumps. Too bad!
    for (int i = 0; i < matNum; i++)
    {
        fprintf(fp,"%s %f %f %f\n", materie[i].nome, materie[i].media, materie[i].sum, materie[i].den);
    }
    fclose(fp);

    //Looping menu, yay!
    do
    {
    if (mn==0)
        myMenu(materie,matNum);
    else
        myMenu(materie,mn);
    } while (1);

}

