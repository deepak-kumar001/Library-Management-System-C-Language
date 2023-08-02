#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include <unistd.h>

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void delay(int mseconds)
{
    clock_t target=clock();
    while(clock()<target+mseconds);
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void showcursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = TRUE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void box(int a, int c,int l,int h)
{
    gotoxy(a,c);
    printf("%c",218);
    for (int i = 0; i < l; i++)
    {
        printf("%c",196);
    }
    printf("%c\n",191);

    for (int i = 0,y=c+1; i < h; i++,y++)
    {
        gotoxy(a,y);
        printf("%c",179);
        gotoxy(a+l+1,y);
        printf("%c",179);
    }
    gotoxy(a,c+h);
    printf("%c",192);
    for (int i = 0; i < l; i++)
    {
        printf("%c",196);
    }
    printf("%c\n",217);
}

void v_line(int x, int y,int l)
{
    gotoxy(x,y);
    printf("%c",194);
    for (int i = 0; i < l; i++)
    {
        gotoxy(x, y+1+i);
        printf("%c", 179);
    }
    gotoxy(x,y+l);
    printf("%c",193);
}

void h_line(int x,int y, int l)
{
    gotoxy(x,y);
    printf("%c",195);
    for (int i = 0; i < l; i++)
    {
        printf("%c",196);
    }
    printf("%c",180);
}

void intersection_p(int x,int y)  //x-coord of v_line and y coord of h_line
{
    gotoxy(x,y);
    printf("%c",197);
}

void loader(int x,int y,int z)
{
    box(x,y,z,2);
    gotoxy(x+z/2-3,y-1);
    //gotoxy(x-+40,y-1);       dont know how but it prints at good location, must try
    printf("Loading...");
    //gotoxy(x+1,y+1);
    float j = 100.00/z;
    for (int i = 1; i <= z; i++,j+=100.00/z)
    {
        gotoxy(x+i,y+1);
        printf("\xDB");
        gotoxy(x+z+5,y+1);
        printf("%2d%%",(int)j);
        delay(10);
    }
    gotoxy(x+3,y+3);
}

void textcolor(int color)
{
    static int __BACKGROUND;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

    GetConsoleScreenBufferInfo(h, &csbiInfo);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            color + (__BACKGROUND << 4));
}

int selector(int x, int y1, int y2, char (*items)[26])
{
    hidecursor();
    int s = 1, n = (y2 - y1) / 2 + 1;
    char ch;

    for (int i = 1, j = y1+2; i < n; i++) //here we are skipping first element bcz it will be printed after this loop
    {
        gotoxy(31, j);
        printf("%s", items + i); //items can aslo be printed without derefrencing here
        j += 2;
    }

    textcolor(3);
    gotoxy(x, y1);
    printf("\xDB\xDB\xB2");
    gotoxy(x + 5, y1);
    printf("%s", *(items + 0)); //first item is printed here with different color

    int se = y1; //se = vertical axis position for selector to be printed
    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            textcolor(6);
            // printf("%d", s);
            return s;
        }
        ch = getch(); //reason of second getch() is that arrow keys give 2 output to getch() function, and 1st is common for all and second is according to their respective arrows.

        if (ch == 80) //down
        {
            textcolor(6);
            gotoxy(x, se);
            printf("     %s", *(items + s - 1));
            if (se == y2) //if 'se' is at last element
            {
                s = 1;
                se = y1;
            }
            else
            {
                s++;
                se += 2;
            }
            textcolor(3);
            gotoxy(x, se);
            printf("\xDB\xDB\xB2  %s", *(items + s - 1));
            // gotoxy(1,1); // for removing the pointer from screen for visual purpose
            //continue;
        }
        else if (ch == 72) //up
        {
            textcolor(6);
            gotoxy(x, se);
            printf("     %s", *(items + s - 1));
            if (se == y1)
            {
                s = n;
                se = y2;
            }
            else
            {
                s--;
                se -= 2;
            }
            textcolor(3);
            gotoxy(x, se);
            printf("\xDB\xDB\xB2  %s", *(items + s - 1));
            // gotoxy(1,1); // for removing the pointer from screen for visual purpose
            //continue;
        }
    }
}

int menu_selector(int x, int y1, int y2, char (*items)[26])
{
    hidecursor();
    int s = 1, n = (y2 - y1) / 2 + 1;
    char ch;

    //time
    time_t mytime = time(NULL);
    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    // printf("Current Time : %s\n", time_str);
    //date
    char da[12];
    for(int i=0;i<11;i++)
    {
        if(i<7)
        {
            da[i]=time_str[i+4];
        }
        else
        {
            da[i]=time_str[i+13];
        }
    }
    da[12]='\0';
    textcolor(3);
    gotoxy(56,5);
    printf("%s",da);
    textcolor(6);

    char hr[3], mi[3], sec[3];

    for (int i = 0; i < 2; i++)
    {
        hr[i] = time_str[i + 11];
        sec[i] = time_str[i + 17];
        mi[i] = time_str[i + 14];
    }
    hr[3] = '\0';
    int h = atoi(hr);
    mi[3] = '\0';
    int m = atoi(mi);
    sec[3] = '\0';
    int seco = atoi(sec);

    for (int i = 1, j = y1 + 2; i < n; i++) //here we are skipping first element bcz it will be printed after this loop
    {
        gotoxy(31, j);
        printf("%s", items + i); //items can aslo be printed without derefrencing here
        j += 2;
    }

    textcolor(3);
    gotoxy(x, y1);
    printf("\xDB\xDB\xB2");
    gotoxy(x + 5, y1);
    printf("%s", *(items + 0)); //first item is printed here with different color

    int se = y1; //se = vertical axis position for selector to be printed

    gotoxy(56, 7);
    printf("%02d : %02d : %02d", h, m, s);
    while (1)
    {
        if (seco == 60)
        {
            m++;
            seco = 0;
            gotoxy(61, 7);
            printf("%02d : %02d", m, seco);
        }
        if (m == 60)
        {
            h++;
            m = 0;
            gotoxy(56, 7);
            printf("%02d : %02d : %02d", h, m, seco);
        }
        delay(500);
        // sleep(1);
        seco++;
        gotoxy(66, 7);
        printf("%02d", seco);

        if (kbhit())
        {
            ch = getch();
            if (ch == 13)
            {
                textcolor(6);
                // printf("%d", s);
                return s;
            }
            ch = getch(); //reason of second getch() is that arrow keys give 2 output to getch() function, and 1st is common for all and second is according to their respective arrows.

            if (ch == 80) //down
            {
                textcolor(6);
                gotoxy(x, se);
                printf("     %s", *(items + s - 1));
                if (se == y2) //if 'se' is at last element
                {
                    s = 1;
                    se = y1;
                }
                else
                {
                    s++;
                    se += 2;
                }
                textcolor(3);
                gotoxy(x, se);
                printf("\xDB\xDB\xB2  %s", *(items + s - 1));
                // gotoxy(1,1); // for removing the pointer from screen for visual purpose
                //continue;
            }
            else if (ch == 72) //up
            {
                textcolor(6);
                gotoxy(x, se);
                printf("     %s", *(items + s - 1));
                if (se == y1)
                {
                    s = n;
                    se = y2;
                }
                else
                {
                    s--;
                    se -= 2;
                }
                textcolor(3);
                gotoxy(x, se);
                printf("\xDB\xDB\xB2  %s", *(items + s - 1));
                // gotoxy(1,1); // for removing the pointer from screen for visual purpose
                //continue;
            }
        }
        delay(500);
        // it can be removed if you want to use sleep instaed of delay.
        if (kbhit())
        {
            ch = getch();
            if (ch == 13)
            {
                textcolor(6);
                // printf("%d", s);
                return s;
            }
            ch = getch(); //reason of second getch() is that arrow keys give 2 output to getch() function, and 1st is common for all and second is according to their respective arrows.

            if (ch == 80) //down
            {
                textcolor(6);
                gotoxy(x, se);
                printf("     %s", *(items + s - 1));
                if (se == y2) //if 'se' is at last element
                {
                    s = 1;
                    se = y1;
                }
                else
                {
                    s++;
                    se += 2;
                }
                textcolor(3);
                gotoxy(x, se);
                printf("\xDB\xDB\xB2  %s", *(items + s - 1));
                // gotoxy(1,1); // for removing the pointer from screen for visual purpose
                //continue;
            }
            else if (ch == 72) //up
            {
                textcolor(6);
                gotoxy(x, se);
                printf("     %s", *(items + s - 1));
                if (se == y1)
                {
                    s = n;
                    se = y2;
                }
                else
                {
                    s--;
                    se -= 2;
                }
                textcolor(3);
                gotoxy(x, se);
                printf("\xDB\xDB\xB2  %s", *(items + s - 1));
                // gotoxy(1,1); // for removing the pointer from screen for visual purpose
                //continue;
            }
        }//can be deleted till here.
    }
}

int yes_no(int x1, int x2, int y) // x1= x coord. for 'Yes' and x2= x coord. for 'No'
{
    hidecursor();
    int s = 1;
    char ch;

    gotoxy(x2, y); //prints 'No' without line in yellow color
    printf("No");

    textcolor(3); //prints 'Yes' with line in blue color
    gotoxy(x1, y);
    printf("Yes");
    gotoxy(x1 - 1, y + 1);
    printf("%c%c%c%c%c", 205, 205, 205, 205, 205);

    while (1)
    {
        ch = getch();
        if (ch == 13)
        {
            textcolor(6);
            gotoxy(x1-1, y); // removes 'Yes' and 'No' from screen before exiting function
            printf("                                             ");
            // printf("%d", s);
            return s;
        }
        ch = getch(); //reason of second getch() is that arrow keys give 2 output to getch() function, and 1st is common for all and second is according to their respective arrows.

        if (ch == 77) //right
        {
            if (s == 2) //if we are already at 'No'
            {
                continue;
            }
            else
            {
                s++;
            }
            //removes line and blue color from 'Yes'
            textcolor(6);
            gotoxy(x1, y);
            printf("Yes");
            gotoxy(x1 - 1, y + 1);
            printf("     ");

            //add line and blue color to 'No'
            textcolor(3);
            gotoxy(x2, y);
            printf("No");
            gotoxy(x2 - 1, y + 1);
            printf("%c%c%c%c", 205, 205, 205, 205);
            // gotoxy(1,1); // for removing the pointer from screen 'for visual purpose'
        }
        else if (ch == 75) //left
        {
            if (s == 1) //if we are already at 'Yes'
            {
                continue;
            }
            else
            {
                s--;
            }
            // removes line and blue color from 'No'
            textcolor(6);
            gotoxy(x2, y);
            printf("No");
            gotoxy(x2 - 1, y + 1);
            printf("    ");

            // adds line and blue color to 'Yes'
            textcolor(3);
            gotoxy(x1, y);
            printf("Yes");
            gotoxy(x1 - 1, y + 1);
            printf("%c%c%c%c%c", 205, 205, 205, 205, 205);
            // gotoxy(1,1); // for removing the pointer from screen 'for visual purpose'
        }
    }
}

void my_gets(char *string) // used to replace spaces(' ') with underscore('_') in a string before storing it in file
{
    //there is huge drawback of this function, there must a scanf used before using it, otherwise it will eat first character of your string.
    // to solve this problem please refer to my_get_char.c or my_gets_2
    int n = 0;
    getchar();
    gets(string);
    // printf("%s",string);
    while (string[n] != '\0')
    {
        if (string[n] == ' ')
        {
            string[n] = '_';
        }
        n++;
    }
}

void my_gets_2(int type,char* string) //type ==1 , if want getchar otherwise any number
{
    int n = 0;
    
    if(type==1)
    getchar();

    gets(string);
    // printf("%s",string);
    while (string[n] != '\0')
    {
        if (string[n] == ' ')
        {
            string[n] = '_';
        }
        n++;
    }
}

void my_printf(char *string) // // used to replace underscore('_') with spaces(' ') in a string before printing it from file
{
    int n = 0;
    while (string[n] != '\0')
    {
        if (string[n] == '_')
        {
            string[n] = ' ';
        }
        n++;
    }
    printf("%s", string);
}

void my_get_i( int * number)
{
    char stoi[10];
    fgets(stoi,10,stdin);
    *number=atoi(stoi);
}

void my_get_f(float * rnumber)
{
    char stoi[10];
    fgets(stoi,10,stdin);
    *rnumber=atof(stoi);
}

