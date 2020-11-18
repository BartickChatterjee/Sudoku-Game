#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

int matrix[9][9],m[9][9],i,j,ar,x,y,xx,yy,r,f,h,dd;
char t;

struct stats
{
    int win,rp,ht,hw,hh;
};

void move(int x,int y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void display()
{
    system("cls");
    int ch;
    printf("\n\n");
        for(i=0;i<9;i++)
        {
        printf("\t\t");
        ch=0;
        for(j=0;j<9;j++)
        {
            ch++;
            printf("\t");
            if(matrix[i][j]!=0)
                printf("%d",matrix[i][j]);
            else
                printf("_");
            if(ch==3 || ch==6)
                printf("   |");
        }
        if(i==2 || i==5)
        {
            printf("\n\t\t\t");
            printf("                    |                       |");
            printf("\n\t\t\t--------------------|-----------------------|---------------------");
            printf("\n\t\t\t");
            printf("                    |                       |");
            printf("\n");
        }
        else
        {
            printf("\n\t\t\t");
            printf("                    |                       |");
            printf("\n");
        }
        }
        printf("\n\n");
}

int input(int r,int c,int n)
{
    matrix[r][c]=n;
    return 0;
}

int solve()
{
    int mm,i,j=9,f;
    f=1;
    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        if (m[i][j]==0)
        break;
        if (j<9)
        {
            f=0;
            break;
        }
    }
    if (f==1)
    return 1;
    for (mm=1;mm<=9;mm++)
    {
        //printf("\n\ni=%d, j=%d, mm=%d\n",i,j,mm);
        f=1;
        for (x=0;x<9;x++)
        {
            if (m[i][x]==mm)
            {
                f=0;
                //printf("mm=%d found in [%d,%d]\n",mm,i,x);
            }
            if (m[x][j]==mm)
            {
                f=0;
                //printf("mm=%d found in [%d,%d]\n",mm,x,j);
            }
        }
        for (xx=i-i%3;xx<=i-i%3+2;xx++)
        for (yy=j-j%3;yy<=j-j%3+2;yy++)
        if (m[xx][yy]==mm)
        {
                f=0;
                //printf("mm=%d found in [%d,%d] in %d x %d\n",mm,xx,yy,i-i%3+2,j-j%3+2);
        }
        if (f==1)
        {
            m[i][j]=mm;

            /*printf("\n");
                    for (xx=0;xx<9;xx++)
                    {
                        for (yy=0;yy<9;yy++)
                        printf("%d ",m[xx][yy]);
                        printf("\n");
                    }
            getch();*/

            if (solve())
            return 1;

            m[i][j]=0;
        }
    }
    return 0;
}

int generate()
{
    srand(time(NULL));

    for (i=0;i<9;i++)
    for (j=0;j<9;j++)
    m[i][j]=0;

    for (i=0;i<9;i++)
    {
        r=1+rand()%9;
        for (j=0;j<i;j++)
        if (m[j][j]==r)
        {
            i--;
            break;
        }
        if (i==j)
        {
            m[i][i]=r;
        }
    }

    for (i=2;i<9;i+=3)
    {
        for (x=i-2;x<=i;x++)
        for (y=i-2;y<=i;y++)
        {
            if (m[x][y]==0)
            {
                r=1+rand()%9;
                f=1;
                for (xx=i-2;xx<=i;xx++)
                for (yy=i-2;yy<=i;yy++)
                if (m[xx][yy]==r)
                f=0;
                if (f==1)
                m[x][y]=r;
                else
                y--;
            }
        }
    }
    i=0;
    solve();
    for (i=0;i<9;i++)
    for (j=0;j<9;j++)
    matrix[i][j]=m[i][j];
    for (i=0;i<9;i++)
    {
        r=rand()%6;
        for (j=0;j<r;j++)
        {
            x=rand()%9;
            if (matrix[i][x]!=0)
            matrix[i][x]=0;
            else
            j--;
            Sleep(20);
        }
    }
    for (i=0;i<9;i++)
    for (j=0;j<9;j++)
    {
        if (matrix[i][j]!=0)
        m[i][j]=0;
    }
    return 0;
}

int check()
{
   system("cls");
   int x,y,f,s=0,ss=0;
   f=1;
   for (x=0;x<9 && f==1;x+=3)
   for (y=0;y<9 && f==1;y+=3)
   {
       s=0;
       for (i=x;i<x+3;i++)
       for (j=y;j<y+3;j++)
       s+=matrix[i][j];
       if (s!=45)
       f=0;
   }
    for (i=0;i<9 && f==1;i++)
    {
        s=0;
        ss=0;
        for (j=0;j<9;j++)
        {
            s+=matrix[i][j];
            ss+=matrix[j][i];
        }
        if (s!=ss)
        f=0;
    }
    return f;
}

int loadgame()
{
    FILE *fp;
    int f=1;

    if (fp = fopen("data.bin","rb"))
    {
        if (fp!=NULL)
        {
            fread(&matrix,sizeof(matrix),1,fp);
            fclose(fp);
            fp=fopen("places.bin","rb");
            fread(&m,sizeof(m),1,fp);
            fread(&h,sizeof(h),1,fp);
            fclose(fp);
        }
        else
        f=0;
    }
    else
    f=0;

    if (f==0)
    {
         system("cls");
         printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\tNo Game Data Available! Press Anything To Continue!!");
         getch();
         fclose(fp);
    }

    return f;
}

void savegame()
{
    FILE *fp = fopen("data.bin","wb");
    fwrite(&matrix,sizeof(matrix),1,fp);
    fclose(fp);
    fopen("places.bin","wb");
    fwrite(&m,sizeof(m),1,fp);
    fwrite(&h,sizeof(h),1,fp);
    fclose(fp);
}

/*int difficulty()
{
    int d;
    char t;
    char [3][10]={"Easy","Moderate","Difficult"};
}*/

int game()
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
    int c,ch,x=0,y=0,yy=2;//,a[9]={1,2,3,4,5,6,7,8,9};
    do
    {
        system("cls");
        display();
        printf("\t\t      [Arrow Keys] Navigate   ",x,y,yy);
        printf("[1-9] Enter Number   ");
        printf("[H] Hint (%d Used)   ",h);
        printf("[E] Exit\n");
        t='x';
        while (t!='e' && t!='~' && t!='c')
        {
            move(24+x,yy+y);
            t=getch();
            if (t=='h' && m[y/2][x/8]!=0)
            {
                input(y/2,x/8,m[y/2][x/8]);
                h++;
                t='~';
            }
            else if (t=='e')     //Upon pressing exit
            {
                system("cls");
                display();
                printf("\t\t\t\t  Save This Game? [Y] Yes   [N] No   [C] Cancel");
                do
                {
                    t=getch();
                    if (t=='y')
                    {
                        savegame();
                        break;
                    }
                }while (t!='n' && t!='c');
                if (t=='n' || t=='y')
                {
                    t='e';
                    break;
                }
            }
            else if (t==(char)80)   //Down
            {
                do
                {
                    if (y==16)
                    {
                        yy=2;
                        y=0;
                        if (x==64)
                        x=0;
                        else
                        x+=8;
                    }
                    else
                    y+=2;
                    if (y!=0 && (y/2)%3==0)
                    yy+=2;
               }while (m[y/2][x/8]==0);
            }
            else if (t==(char)72)    //Up
            {
               do
               {
                    if (y!=0 && (y/2)%3==0)
                    yy-=2;
                    if (y==0)
                    {
                        yy=6;
                        y=16;
                        if (x==0)
                        x=64;
                        else
                        x-=8;
                    }
                    else
                    y-=2;
               }while (m[y/2][x/8]==0);
            }
            else if (t==(char)77)   //Right
            {
               do
               {
                    if (x/8==8)
                    {
                        x=0;
                        if (y==16)
                        {
                            yy=2;
                            y=0;
                        }
                        else
                        y+=2;
                        if (y!=0 && (y/2)%3==0)
                        yy+=2;
                    }
                    else
                    x+=8;
               }while (m[y/2][x/8]==0);
            }
            else if (t==(char)75)   //Left
            {
              do
              {
                    if (x==0)
                    {
                        x=64;
                        if (y!=0 && (y/2)%3==0)
                        yy-=2;
                        if (y==0)
                        {
                            yy=6;
                            y=16;
                        }
                        else
                        y-=2;
                    }
                    else
                    x-=8;
                }while (m[y/2][x/8]==0);
            }
            else if (isdigit(t))
            {
                input(y/2,x/8,(int)t-48);
                t='~';
            }
        }
    }while(t!='e' && check()==0);
    if (check()==1)
    {
        system("cls");
        display();
        if (h==0)
        printf("\t\t\t            SUDOKU Solved | Respect + | Hints Used = 0");
        else if (h<4)
        printf("\t\t\t            SUDOKU Solved | Hintastic | Hints Used = %d",h);
        else
        printf("\t\t       SUDOKU Solved | Where There's A Hint There's A Way | Hints Used = %d",h);
        if (ar==1)
        remove("data.bin");
        getch();
    }
    else
    h=-1;
    return 0;
}

int main()
{
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
    char menu[3][40]={"New Game", "Load Game", "Exit Game"};
    FILE *fp;
    struct stats s;

    if (fp=fopen("stats.bin","rb"))
    {
        fread(&s,sizeof(s),1,fp);
        fclose(fp);
    }
    else
    {
        s.win=0;
        s.ht=0;
        s.hw=0;
        s.rp=0;
        fp=fopen("stats.bin","wb");
        fwrite(&s,sizeof(s),1,fp);
        fclose(fp);
    }
    int ii;
    char t;
    ar=0;
    h=-1;
    while (1)
    {
        system("cls");
        printf("\n\n\n\n\n\n\t\t\t\t\t\t\t  SUDOKU\n\n\n\n\n\n\n");
        for (ii=0;ii<3;ii++)
        {
            printf("\t\t\t\t\t\t\t");
            if (ii==ar)
            printf(">   ");
            printf("%s\n\n",menu[ii]);
        }
        printf("\n\n\n\n\t\t\t\t\t  Wins -> %d",s.win);
        printf("\n\t\t\t\t\t  Respect+ -> %d",s.rp);
        printf("\n\t\t\t\t\t  Hintastic -> %d",s.ht);
        printf("\n\t\t\t\t\t  Where There's A Hint There's A Way -> %d",s.hw);
        t=getch();
        if (t==(char)80)
        {
            if (ar==2)
            ar=0;
            else
            ar++;
        }
        else if (t==(char)72)
        {
            if (ar==0)
            ar=2;
            else
            ar--;
        }
        else if (t=='\r')
        {
            if (ar==0)
            {
                generate();
                h=0;
                game();
                if (h!=-1)
                {
                    s.win++;
                    if (h==0)
                    s.rp++;
                    else if (h<4)
                    s.ht++;
                    else
                    s.hw++;
                    fp=fopen("stats.bin","wb");
                    fwrite(&s,sizeof(s),1,fp);
                    fclose(fp);
                }
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
            }
            else if (ar==1)
            {
                if (loadgame())
                game();
                if (h!=-1)
                {
                    s.win++;
                    if (h==0)
                    s.rp++;
                    else if (h<4)
                    s.ht++;
                    else
                    s.hw++;
                    fp=fopen("stats.bin","wb");
                    fwrite(&s,sizeof(s),1,fp);
                    fclose(fp);
                }
                SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
            }
            else if (ar==2)
            break;
        }
    }
    return 0;
}
