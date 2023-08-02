#include "madebyd.h"

// Global Variables
FILE *fp;

struct books
{
    char categ[17];
    int id;
    char name[30];
    char author[25];
    int quantity;
    int available;
    int issued;
    float price;
    int rack_no;
} a;

struct issue
{
    int book_id;
    char book_name[30];
    int student_id;
    char student_name[30];
    char number[11];
    char issue_date[11];
    char return_date[11];
    // struct date issued_date;
    // struct date return_date;
} s;

int checkid(int id)
{
    rewind(fp);
    while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
    {
        if (id == a.id)
        {
            return 0;
        }
    }
    return 1;
}

void main_menu();
void book_management();
void book_transaction();

void add_new_book()
{
    int id;

    system("cls");
    // categories
    box(23, 4, 71, 18);
    h_line(23, 6, 71);
    box(23, 23, 71, 2);
    gotoxy(55, 5);
    printf("Categories");

    char items[7][26] = {"1. Arts", "2. Commerce", "3. Science", "4. Computers", "5. General Knowledge", "6. Environment", "7. Back to Previous Menu"};

    gotoxy(25, 24);
    printf("Use Up/Down Arrows keys for Navigation.");

    int sel = selector(26, 8, 20, items);

    switch (sel)
    {
    case 1:
        strcpy(a.categ, "Arts");
        break;
    case 2:
        strcpy(a.categ, "Commerece");
        break;
    case 3:
        strcpy(a.categ, "Science");
        break;
    case 4:
        strcpy(a.categ, "Computers");
        break;
    case 5:
        strcpy(a.categ, "General Knowlegde");
        break;
    case 6:
        strcpy(a.categ, "Environment");
        break;
    case 7:
        return book_management();
        break;
    }

    // add books
    system("cls");
    box(23, 4, 15, 2);
    gotoxy(27, 5);
    printf("Add Books");
    box(23, 6, 71, 16);
    for (int i = 0, j = 8; i < 7; i++)
    {
        gotoxy(39, j + 1);
        printf(":");
        h_line(23, j, 71);
        j += 2;
    }
    gotoxy(46, 7);
    printf("Enter the Information Below:");
    gotoxy(27, 9);
    printf("Category");
    gotoxy(27, 11);
    printf("Book ID");

    showcursor();
    gotoxy(43, 9);
    printf("%s", a.categ);
    gotoxy(43, 11);
    my_get_i(&id);

    fp = fopen("data.dat", "ab+");

    if (checkid(id) == 0) // checking if ID already exists
    {
        gotoxy(43, 24);
        printf("Book Id already exists");
        gotoxy(44, 26);
        printf("Press Any To Continue.....");
        getch();
        return add_new_book(); // scope of improvement i.e. man kiya to baad me modify quantity type ka kuch add kr dunga.
    }

    gotoxy(27, 13);
    printf("Book Name");
    gotoxy(27, 15);
    printf("Author");
    gotoxy(27, 17);
    printf("Quantity");
    gotoxy(27, 19);
    printf("Price");
    gotoxy(27, 21);
    printf("Rack No.");

    showcursor();
    // entering of elements
    a.id = id;
    gotoxy(43, 13);
    my_gets_2(0, a.name);
    // my_gets(a.name);
    // scanf("%s", a.name);
    gotoxy(43, 15);
    my_gets_2(0, a.author);
    // scanf("%s", a.author);
    gotoxy(43, 17);
    my_get_i(&a.quantity);
    gotoxy(43, 19);
    my_get_f(&a.price);
    gotoxy(43, 21);
    my_get_i(&a.rack_no);

    gotoxy(43, 24);
    printf("Are you sure want to SAVE it?");
    if (yes_no(47, 65, 25) == 1)
    {
        a.available = a.quantity;
        a.issued = 0;
        fseek(fp, 0, SEEK_END);
        fprintf(fp, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
        // fwrite(&a, sizeof(a), 1, fp);
        fclose(fp);
        gotoxy(43, 24);
        printf("  Record saved successfully  ");

        gotoxy(44, 26);
        printf("Press Any To Continue.....");
        getch();
        return book_management();
    }
    else
    {
        fclose(fp);
        return main_menu();
    }
}

void delete_books()
{
    FILE *fd;
    int id;

    system("cls");
    box(20, 8, 18, 2);
    gotoxy(24, 9);
    printf("Delete Books");
    box(20, 10, 85, 2);
    v_line(39, 10, 2);
    gotoxy(26, 11);
    printf("Enter ID");

    showcursor();
    gotoxy(45, 11);
    my_get_i(&id);

    fp = fopen("data.dat", "a+");

    if (checkid(id) == 0)
    {
        system("cls");
        box(20, 6, 18, 2);
        gotoxy(24, 7);
        printf("Delete Books");
        box(20, 8, 85, 4);
        h_line(20, 10, 85);
        gotoxy(43, 9);
        printf(":");
        gotoxy(43, 11);
        printf(":");

        gotoxy(24, 9);
        printf("ID");
        gotoxy(24, 11);
        printf("Name");

        gotoxy(50, 9);
        printf("%d", a.id);
        gotoxy(50, 11);
        my_printf(a.name);

        gotoxy(46, 14);
        printf("Are you sure want to 'DELETE' it?");
        if (yes_no(50, 72, 15) == 1)
        {
            rewind(fp);
            fd = fopen("new.dat", "a+");
            while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
            {
                if (a.id == id)
                {
                    continue;
                }
                else
                {
                    fprintf(fd, "%s %d %s %s %d %f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                }
            }

            fclose(fp);
            fclose(fd);
            remove("data.dat");
            rename("new.dat", "data.dat");

            gotoxy(46, 14);
            printf("    Record deleted successfully   ");

            gotoxy(50, 16);
            printf("Press Any To Continue.....");
            getch();
            return book_management();
        }
        return book_management();
    }
    fclose(fp);
    gotoxy(53, 14);
    printf("NO record found...");
    gotoxy(52, 16);
    printf("Want to try Again...");
    if (yes_no(55, 64, 17) == 1)
    {
        return delete_books();
    }
    return main_menu();
}

void search_books()
{
    int id, n_search = 0, y = 4, i = 5;
    char name[25];
    system("cls");
    box(23, 4, 19, 2);
    gotoxy(27, 5);
    printf("Search Books");
    box(23, 6, 71, 8);
    h_line(23, 8, 71);
    box(23, 15, 71, 2);
    gotoxy(50, 7);
    printf("Select The Option");

    char items[2][26] = {"1. Search Book By ID", "2. Search Book By Name"};

    gotoxy(25, 16);
    printf("Use Up/Down Arrows keys for Navigation.");
    int sel = selector(26, 10, 12, items);

    system("cls");
    box(20, 8, 18, 2);
    gotoxy(24, 9);
    printf("Search Books");
    box(20, 10, 85, 2);
    v_line(43, 10, 2);
    gotoxy(28, 11);

    fp = fopen("data.dat", "r");

    showcursor();
    switch (sel)
    {
    case 1:
        printf("Enter ID");
        gotoxy(50, 11);
        my_get_i(&id);
        break;
    case 2:
        printf("\bEnter Name");
        gotoxy(50, 11);
        my_gets_2(0, name); // type = 0, because we dont need getcahr here
        break;
    }

    while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
    {
        if (sel == 1)
        {
            if (a.id == id)
            {
                system("cls");
                box(6, 1, 105, 2);
                box(6, 4, 105, 8);
                gotoxy(50, 2);
                printf("Total 1 Record Found");
                gotoxy(9, 5);
                printf("Category");
                gotoxy(9, 6);
                printf("Book ID");
                gotoxy(9, 7);
                printf("Book Name");
                gotoxy(9, 8);
                printf("Author");
                gotoxy(9, 9);
                printf("Quantity");
                gotoxy(9, 10);
                printf("Price");
                gotoxy(9, 11);
                printf("Rack No.");
                gotoxy(75, 6);
                printf("Available");
                gotoxy(75, 9);
                printf("Issued");
                for (int j = i + 7; i < j; i++)
                {
                    gotoxy(22, i);
                    printf(":");
                }
                gotoxy(28, 5);
                printf("%s", a.categ);
                gotoxy(28, 6);
                printf("%d", a.id);
                gotoxy(28, 7);
                my_printf(a.name);
                gotoxy(28, 8);
                my_printf(a.author);
                gotoxy(28, 9);
                printf("%d", a.quantity);
                gotoxy(28, 10);
                printf("%.2f", a.price);
                gotoxy(28, 11);
                printf("%d", a.rack_no);
                gotoxy(77, 7);
                printf("%d", a.available);
                gotoxy(77, 10);
                printf("%d", a.issued);
                n_search++;

                break;
            }
            // else
            // {
            //     printf("NO record found");
            // }
        }
        else if (sel == 2)
        {
            if (strcmp(a.name, name) == 0) // a.name == name i.e, we cant use == in string
            {
                if (n_search == 0)
                {
                    system("cls");
                    box(6, 1, 105, 2);
                }
                n_search++;

                box(6, y, 105, 8);
                gotoxy(50, 2);
                printf("Total %d Record Found", n_search);
                gotoxy(9, y + 1);
                printf("Category");
                gotoxy(9, y + 2);
                printf("Book ID");
                gotoxy(9, y + 3);
                printf("Book Name");
                gotoxy(9, y + 4);
                printf("Author");
                gotoxy(9, y + 5);
                printf("Quantity");
                gotoxy(9, y + 6);
                printf("Price");
                gotoxy(9, y + 7);
                printf("Rack No.");
                gotoxy(75, y + 2);
                printf("Available");
                gotoxy(75, y + 5);
                printf("Issued");
                for (int j = i + 7; i < j; i++)
                {
                    gotoxy(22, i);
                    printf(":");
                }
                gotoxy(28, y + 1);
                printf("%s", a.categ);
                gotoxy(28, y + 2);
                printf("%d", a.id);
                gotoxy(28, y + 3);
                my_printf(a.name);
                gotoxy(28, y + 4);
                my_printf(a.author);
                gotoxy(28, y + 5);
                printf("%d", a.quantity);
                gotoxy(28, y + 6);
                printf("%.2f", a.price);
                gotoxy(28, y + 7);
                printf("%d", a.rack_no);
                gotoxy(77, y + 3);
                printf("%d",a.available);
                gotoxy(77, y + 6);
                printf("%d",a.issued);

                // we are incrementing it to print next record
                y += 9;
                i += 2; // i has been already incremented by 7 in loop, 7+2=9
            }
            // else
            // {
            //     my_printf(a.name);
            //     my_printf(name);
            //     printf("NO Record Found");
            // }
        }
    }
    fclose(fp);

    // all yes_no functions
    if (n_search != 0)
    {
        if (sel == 1)
        {
            gotoxy(50, 14);
            printf("Search Another Record?");
            if (yes_no(53, 65, 15) == 1)
            {
                // getchar(); // to avoid buffer overflow by/(due to) scanf
                return search_books();
            }
            else
            {
                // printf("Exit");
                return book_management();
            }
        }
        else if (sel == 2)
        {
            gotoxy(45, y + 1);
            printf("Want To Search Another Record?");
            if (yes_no(50, 67, y + 2) == 1)
            {
                // getchar(); // to avoid buffer overflow by/(due to) scanf
                return search_books();
            }
            return book_management();
            // printf("Exit");
        }
    }
    gotoxy(53, 14);
    printf("NO Record Found");
    gotoxy(51, 16);
    printf("Want to Try Again...");
    if (yes_no(52, 64, 17) == 1)
    {
        // if (s == 1)    // only applied if search was done using id
        //     getchar(); // to avoid buffer overflow by/(due to) scanf

        return search_books();
    }
    else
    {
        // printf("Exit");
        return book_management();
    }
}

void edit_books()
{
    struct books a2;
    FILE *fd;
    system("cls");
    box(19, 8, 18, 2);
    gotoxy(24, 9);
    printf("Edit Books");
    box(19, 10, 85, 2);
    v_line(38, 10, 2);
    gotoxy(25, 11);
    printf("Enter ID");

    showcursor();
    gotoxy(44, 11);
    my_get_i(&a2.id);

    fp = fopen("data.dat", "r");

    if (checkid(a2.id) == 0)
    {
        system("cls");
        box(22, 4, 15, 2);
        gotoxy(26, 5);
        printf("Edit Book");
        box(22, 6, 71, 16);
        for (int i = 0, j = 8; i < 7; i++)
        {
            gotoxy(38, j + 1);
            printf(":");
            h_line(22, j, 71);
            j += 2;
        }
        gotoxy(45, 7);
        printf("The Following Record Found");
        gotoxy(26, 9);
        printf("Category");
        gotoxy(26, 11);
        printf("Book ID");
        gotoxy(26, 13);
        printf("Book Name");
        gotoxy(26, 15);
        printf("Author");
        gotoxy(26, 17);
        printf("Quantity");
        gotoxy(26, 19);
        printf("Price");
        gotoxy(26, 21);
        printf("Rack No.");

        // printing of elements
        gotoxy(43, 9);
        printf("%s", a.categ);
        gotoxy(43, 11);
        printf("%d", a.id);
        gotoxy(43, 13);
        my_printf(a.name);
        // my_gets(a.name);
        // scanf("%s", a.name);
        gotoxy(43, 15);
        my_printf(a.author);
        // scanf("%s", a.author);
        gotoxy(43, 17);
        printf("%d", a.quantity);
        gotoxy(43, 19);
        printf("%f", a.price);
        gotoxy(43, 21);
        printf("%d", a.rack_no);

        gotoxy(43, 24);
        printf("Are you sure want to EDIT it?");
        if (yes_no(47, 65, 25) == 1)
        {
            system("cls");
            box(22, 4, 15, 2);
            gotoxy(26, 5);
            printf("Edit Book");
            box(22, 6, 80, 16); // 54
            v_line(76, 6, 16);
            for (int i = 0, j = 8; i < 7; i++)
            {
                gotoxy(38, j + 1);
                printf(":");
                h_line(22, j, 80);
                intersection_p(76, j);
                j += 2;
            }
            gotoxy(41, 7);
            printf("Modify The Record");
            gotoxy(83, 7);
            printf("Previous Value");
            gotoxy(26, 9);
            printf("Category");
            gotoxy(26, 11);
            printf("Book ID");
            gotoxy(26, 13);
            printf("Book Name");
            gotoxy(26, 15);
            printf("Author");
            gotoxy(26, 17);
            printf("Quantity");
            gotoxy(26, 19);
            printf("Price");
            gotoxy(26, 21);
            printf("Rack No.");

            // printing of previous elements
            gotoxy(80, 9);
            printf("%s", a.categ);
            gotoxy(80, 11);
            printf("%d", a.id);
            gotoxy(80, 13);
            my_printf(a.name);
            gotoxy(80, 15);
            my_printf(a.author);
            gotoxy(80, 17);
            printf("%d", a.quantity);
            gotoxy(80, 19);
            printf("%.2f", a.price);
            gotoxy(80, 21);
            printf("%d", a.rack_no);

            // unchangable values
            gotoxy(43, 9);
            strcpy(a2.categ, a.categ);
            printf("%s", a2.categ);
            gotoxy(43, 11);
            printf("%d", a2.id);

            showcursor();
            // getting new values
            gotoxy(43, 13);
            my_gets_2(0, a2.name);
            gotoxy(43, 15);
            my_gets_2(0, a2.author);
            gotoxy(43, 17);
            my_get_i(&a2.quantity);
            gotoxy(43, 19);
            my_get_f(&a2.price);
            gotoxy(43, 21);
            my_get_i(&a2.rack_no);

            gotoxy(43, 24);
            printf("Are you sure want to confirm the edit?");
            if (yes_no(50, 70, 25) == 1)
            {
                rewind(fp);
                fd = fopen("new.dat", "a+");
                while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
                {
                    if (a.id == a2.id)
                    {
                        a2.available = a2.quantity - a.issued;
                        if (a2.available < 0)
                        {
                            a2.available = 0;
                        }
                        if (a2.quantity < a.issued)
                        {
                            a2.quantity = a.issued;
                            gotoxy(26, 2);
                            printf("NOTE : Quantity have been set to total no. of issued books");
                        }
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a2.categ, a2.id, a2.name, a2.author, a2.quantity, a2.price, a2.rack_no, a2.available, a.issued);
                    }
                    else
                    {
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                    }
                }

                fclose(fp);
                fclose(fd);
                remove("data.dat");
                rename("new.dat", "data.dat");

                gotoxy(43, 24);
                printf("     Record Modified successfully     ");

                gotoxy(49, 26);
                printf("Press Any To Continue.....");
                getch();

                return book_management();
                // return edit_books();
            }
            else
            {
                // delay(3000);
                return book_management();
            }

            getch();
        }
        return book_management();
    }
    fclose(fp);
    gotoxy(52, 14);
    printf("NO record found...");
    gotoxy(51, 16);
    printf("Want to try Again...");
    if (yes_no(54, 63, 17) == 1)
    {
        return edit_books();
    }
    return book_management();
}

void view_all_books()
{
    int n_search = 0, y = 10, i = 11, n_books = 0;

    fp = fopen("data.dat", "r");
    system("cls");
    box(6, 1, 105, 2);
    gotoxy(53, 2);
    printf("View All Books");

    while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
    {
        n_search++;
        n_books += a.quantity;

        box(6, y, 105, 8);
        gotoxy(9, y + 1);
        printf("Category");
        gotoxy(9, y + 2);
        printf("Book ID");
        gotoxy(9, y + 3);
        printf("Book Name");
        gotoxy(9, y + 4);
        printf("Author");
        gotoxy(9, y + 5);
        printf("Quantity");
        gotoxy(9, y + 6);
        printf("Price");
        gotoxy(9, y + 7);
        printf("Rack No.");
        gotoxy(75, y + 2);
        printf("Available");
        gotoxy(75, y + 5);
        printf("Issued");
        for (int j = i + 7; i < j; i++)
        {
            gotoxy(22, i);
            printf(":");
        }
        gotoxy(28, y + 1);
        printf("%s", a.categ);
        gotoxy(28, y + 2);
        printf("%d", a.id);
        gotoxy(28, y + 3);
        my_printf(a.name);
        gotoxy(28, y + 4);
        my_printf(a.author);
        gotoxy(28, y + 5);
        printf("%d", a.quantity);
        gotoxy(28, y + 6);
        printf("%.2f", a.price);
        gotoxy(28, y + 7);
        printf("%d", a.rack_no);
        gotoxy(77, y + 3);
        printf("%d", a.available);
        gotoxy(77, y + 6);
        printf("%d", a.issued);

        // we are incrementing it print next record
        y += 9;
        i += 2; // i has been already incremented by 7 in loop, 7+2=9
    }
    fclose(fp);

    gotoxy(8, 5);
    printf("LIBRARY STATS:");
    gotoxy(10, 7);
    printf("Total Records Found       :");
    gotoxy(10, 8);
    printf("Total no. of Books        :");
    gotoxy(44, 7);
    printf("%d Records", n_search);
    gotoxy(44, 8);
    printf("%d", n_books);

    gotoxy(45, y + 1);
    printf("Press Any Key to Contine...");
    getch();
    return book_management();
    // printf("Exit");
}

void book_management()
{
    system("cls");
    box(23, 4, 71, 18);
    h_line(23, 6, 71);
    box(23, 23, 71, 2);
    gotoxy(52, 5);
    printf("Book Management");
    char items[7][26] = {"1. Add New Book", "2. Delete Book", "3. Search Book", "4. Edit Book Record", "5. View All Book", "6. Goto Main Menu", "7. Close Application"};

    gotoxy(25, 24);
    printf("Use Up/Down Arrows keys for Navigation.");

    int s = selector(26, 8, 20, items);

    switch (s)
    {
    case 1:
        add_new_book();
        break;
    case 2:
        delete_books();
        break;
    case 3:
        search_books();
        break;
    case 4:
        edit_books();
        break;
    case 5:
        view_all_books();
        break;
    case 6:
        main_menu();
        break;
    case 7:
        exit(0);
        break;
    }
}

void issue_books()
{
    FILE *fd;
    int id;

    system("cls");
    box(19, 8, 22, 2);
    gotoxy(25, 9);
    printf("Issue Books");
    box(19, 10, 83, 2);
    v_line(42, 10, 2);
    gotoxy(24, 11);
    printf("Enter Book ID");

    showcursor();
    gotoxy(47, 11);
    // scanf("%d", &id);
    my_get_i(&id);

    fp = fopen("data.dat", "a+");

    if (checkid(id) == 0)
    {
        if (a.quantity != 0 && a.available != 0)
        {

            system("cls");
            box(23, 3, 22, 2);
            gotoxy(29, 4);
            printf("Issue Books");
            box(23, 5, 71, 12);
            for (int i = 0, j = 7; i < 5; i++)
            {
                gotoxy(46, j + 1);
                printf(":");
                h_line(23, j, 71);
                j += 2;
            }
            gotoxy(49, 6);
            printf("Issue Book To Student");
            gotoxy(27, 8);
            printf("Enter Student Id");
            gotoxy(27, 10);
            printf("Student Name");
            gotoxy(27, 12);
            printf("Phone Number");
            gotoxy(27, 14);
            printf("Enter Issue Date");
            gotoxy(27, 16);
            printf("Enter Return Date");
            h_line(23, 19, 71);
            box(23, 17, 71, 6);
            gotoxy(50, 18);
            printf("Book Information:");
            gotoxy(27, 20);
            printf("Book Name            :");

            strcpy(s.book_name, a.name);// copying it before my_printf(a.name), because after that '_'(underscore) will be removed and give error in other functions

            gotoxy(51, 20);
            my_printf(a.name);
            gotoxy(27, 21);
            printf("Available Quantity   :  %d", a.quantity);
            gotoxy(27, 22);
            printf("Price                :  %.2f", a.price);

            // getting information
            gotoxy(49, 8);
            my_get_i(&s.student_id);
            gotoxy(49, 10);
            my_gets_2(0, s.student_name);
            gotoxy(49, 12);
            my_gets_2(0, s.number);
            gotoxy(80, 14);
            printf("(dd-mm-yyyy)");
            gotoxy(80, 16);
            printf("(dd-mm-yyyy)");
            gotoxy(49, 14);
            my_gets_2(0, s.issue_date);
            // scanf("%d %d %d",s.issued_date.dd,s.issued_date.mm,s.issued_date.yy);
            gotoxy(49, 16);
            my_gets_2(0, s.return_date);
            // scanf("%d %d %d",s.return_date.dd,s.return_date.mm,s.return_date.yy);
            // fflush(stdin);

            gotoxy(43, 24);
            printf("Are you sure want to ISSUE it?");
            if (yes_no(47, 65, 25) == 1)
            {
                s.book_id = a.id;
                fd = fopen("issue.dat", "a");
                fseek(fd, 0, SEEK_END);
                fprintf(fd, "%d %s %d %s %s %s %s ", s.book_id, s.book_name, s.student_id, s.student_name, s.number, s.issue_date, s.return_date);
                // fwrite(&s, sizeof(s), 1, fd);
                fclose(fd);
                // code to  minus 1 quantity from book record, i will do it later. edit -- Did it.
                rewind(fp);
                fd = fopen("new.dat", "a+");
                while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
                {
                    if (a.id == id)
                    {
                        a.issued += 1;
                        a.available -= 1;
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                    }
                    else
                    {
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                    }
                }
                fclose(fp);
                fclose(fd);

                remove("data.dat");
                rename("new.dat","data.dat");

                gotoxy(43, 24);
                printf("   Book issued successfully   ");

                gotoxy(46, 26);
                printf("Press Any To Continue.....");
                getch();
                // exit(0);
                return book_transaction();
            }
            else
            {
                // return issue_books();
                return main_menu();
            }
        }
        else
        {
            system("cls");
            box(23, 3, 22, 2);
            gotoxy(29, 4);
            printf("Issue Books");
            h_line(23, 7, 71);
            box(23, 5, 71, 11);
            gotoxy(50, 6);
            printf("Book Information:");
            gotoxy(27, 8);
            printf("Book ID              :  %d", a.id);
            gotoxy(27, 9);
            printf("Book Name            :");
            gotoxy(51, 9);
            my_printf(a.name);
            gotoxy(27, 10);
            printf("Available Quantity   :  %d", a.quantity);
            gotoxy(27, 11);
            printf("Price                :  %.2f", a.price);
            h_line(23, 12, 71);
            gotoxy(35, 14);
            printf("Currently this Book is not available to issue.");

            gotoxy(47, 18);
            printf("Issue Another Books");
            if (yes_no(50, 61, 19) == 1)
            {
                return issue_books();
            }
            return book_transaction();
            // exit(0);
        }

        getch();
    }
    fclose(fp);
    gotoxy(53, 14);
    printf("NO record found...");
    gotoxy(52, 16);
    printf("Want to try Again...");
    if (yes_no(55, 64, 17) == 1)
    {
        return issue_books();
    }
    return book_transaction();
}

void search_issued_books()
{
    int id, n_search = 0, y = 4, i = 5;
    system("cls");
    box(23, 4, 25, 2);
    gotoxy(27, 5);
    printf("Search Issued Books");
    box(23, 6, 71, 8);
    h_line(23, 8, 71);
    box(23, 15, 71, 2);
    gotoxy(50, 7);
    printf("Select The Option");

    char items[2][26] = {"1. Search By Book ID", "2. Search By Student ID"};

    gotoxy(25, 16);
    printf("Use Up/Down Arrows keys for Navigation.");
    int se = selector(26, 10, 12, items);

    system("cls");
    box(20, 8, 25, 2);
    gotoxy(24, 9);
    printf("Search Issued Books");
    box(20, 10, 85, 2);

    fp = fopen("issue.dat", "r");

    showcursor();
    switch (se)
    {
    case 1:
        v_line(47, 10, 2);
        gotoxy(27, 11);
        printf("Enter Book ID");
        gotoxy(54, 11);
        my_get_i(&id);
        break;
    case 2:
        v_line(47, 10, 2);
        gotoxy(25, 11);
        printf("Enter Student ID");
        gotoxy(54, 11);
        my_get_i(&id);
        break;
    }
    while (fscanf(fp, "%d %s %d %s %s %s %s", &s.book_id, s.book_name, &s.student_id, s.student_name, s.number, s.issue_date, s.return_date) != EOF)
    {
        int k = 0;
        if (se == 1)
        {
            if (s.book_id == id)
            {
                k = 1;
            }
        }
        else
        {
            if (s.student_id == id)
            {
                k = 1;
            }
        }
        if (k == 1)
        {
            if (n_search == 0)
            {
                system("cls");
                box(6, 1, 105, 2);
            }
            n_search++;

            box(6, y, 105, 6);
            gotoxy(49, 2);
            printf("Total %d Record Found", n_search);
            gotoxy(9, y + 1);
            printf("Book ID");
            gotoxy(9, y + 2);
            printf("Book Name");
            gotoxy(9, y + 3);
            printf("Student ID");
            gotoxy(9, y + 4);
            printf("Student Name");
            gotoxy(9, y + 5);
            printf("Phone No.");
            gotoxy(75, y + 1);
            printf("Issued Date");
            gotoxy(75, y + 4);
            printf("Return Date");
            for (int j = i + 5; i < j; i++)
            {
                gotoxy(24, i);
                printf(":");
            }
            textcolor(3);
            gotoxy(28, y + 1);
            printf("%d", s.book_id);
            gotoxy(28, y + 2);
            my_printf(s.book_name);
            gotoxy(28, y + 3);
            printf("%d", s.student_id);
            gotoxy(28, y + 4);
            my_printf(s.student_name);
            gotoxy(28, y + 5);
            printf("%s", s.number);
            gotoxy(78, y + 2);
            printf("%s", s.issue_date);
            gotoxy(78, y + 5);
            printf("%s", s.return_date);
            textcolor(6);

            // we are incrementing it print next record
            y += 7;
            i += 2; // i has been already incremented by 5 in loop, 5+2=7
        }
    }
    fclose(fp);

    if (n_search != 0)
    {
        gotoxy(48, y + 1);
        printf("Search Another Record?");
        if (yes_no(51, 63, y + 2) == 1)
        {
            return search_issued_books();
        }
        else
        {
            // printf("Exit");
            return book_transaction();
        }
    }
    gotoxy(53, 14);
    printf("NO Record Found");
    gotoxy(51, 16);
    printf("Want to Try Again...");
    if (yes_no(52, 64, 17) == 1)
    {
        return search_issued_books();
    }
    else
    {
        // printf("Exit");
        return book_transaction();
    }
}

void view_issued_book()
{
    // FILE *fd;
    fp = fopen("issue.dat", "r");
    // fd = fopen("issue.dat", "r");
    int y = 7, n_search = 0;
    system("cls");
    box(6, 1, 105, 2);
    gotoxy(47, 2);
    printf("All Issued Books Record");

    gotoxy(8, 5);
    printf("Book ID");
    gotoxy(21, 5);
    printf("Book Name");
    gotoxy(36, 5);
    printf("Student ID");
    gotoxy(51, 5);
    printf("Student Name");
    gotoxy(69, 5);
    printf("Phone No.");
    gotoxy(83, 5);
    printf("Issued Date");
    gotoxy(99, 5);
    printf("Return Date");
    h_line(7, 6, 102);
    gotoxy(7, 6);
    printf("%c", 196);
    gotoxy(110, 6);
    printf("%c", 196);

    textcolor(3);

    while (fscanf(fp, "%d %s %d %s %s %s %s", &s.book_id, s.book_name, &s.student_id, s.student_name, s.number, s.issue_date, s.return_date) != EOF)
    {
        n_search++;
        gotoxy(8, y);
        printf("%d", s.book_id);
        gotoxy(21, y);
        my_printf(s.book_name);
        gotoxy(36, y);
        printf("%d", s.student_id);
        gotoxy(51, y);
        my_printf(s.student_name);
        gotoxy(69, y);
        printf("%s", s.number);
        gotoxy(83, y);
        my_printf(s.issue_date);
        gotoxy(99, y);
        my_printf(s.return_date);

        y += 2;
    }
    textcolor(6);
    gotoxy(8, y + 1);
    printf("Total Records  :  %d", n_search);
    fclose(fp);
    gotoxy(45, y + 3);
    printf("Press Any Key To Continue...");

    getch();
    return book_transaction();
}

void return_books()
{
    FILE *fd = NULL;
    int b_id, s_id;
    system("cls");
    box(20, 8, 25, 2);
    gotoxy(24, 9);
    printf("Search Issued Books");
    box(20, 10, 85, 4);
    h_line(20, 12, 85);

    fp = fopen("issue.dat", "r");

    showcursor();
    v_line(46, 10, 2);
    v_line(46, 12, 2);
    gotoxy(27, 11);
    printf("Enter Book ID");
    gotoxy(25, 13);
    printf("Enter Student ID");
    gotoxy(53, 11);
    my_get_i(&b_id);
    gotoxy(53, 13);
    my_get_i(&s_id);

    while (fscanf(fp, "%d %s %d %s %s %s %s", &s.book_id, s.book_name, &s.student_id, s.student_name, s.number, s.issue_date, s.return_date) != EOF)
    {
        if (b_id == s.book_id && s_id == s.student_id)
        {
            system("cls");
            box(20, 6, 18, 2);
            gotoxy(24, 7);
            printf("Return Books");
            box(20, 8, 85, 10);

            gotoxy(24, 9);
            printf("Book ID        :");
            gotoxy(24, 11);
            printf("Book Name      :");
            gotoxy(24, 13);
            printf("Student ID     :");
            gotoxy(24, 15);
            printf("Student Name   :");
            gotoxy(24, 17);
            printf("Return Date    :");

            gotoxy(44, 9);
            printf("%d", s.book_id);
            gotoxy(44, 11);
            my_printf(s.book_name);
            gotoxy(44, 13);
            printf("%d", s.student_id);
            gotoxy(44, 15);
            my_printf(s.student_name);
            gotoxy(44, 17);
            my_printf(s.return_date);

            gotoxy(46, 20);
            printf("Are you sure want to 'DELETE' it?");
            if (yes_no(50, 72, 21) == 1)
            {
                rewind(fp);
                fd = fopen("new.dat", "w");
                while (fscanf(fp, "%d %s %d %s %s %s %s", &s.book_id, s.book_name, &s.student_id, s.student_name, s.number, s.issue_date, s.return_date) != EOF)
                {
                    if (b_id == s.book_id && s_id == s.student_id)
                    {
                        continue;
                        // printf("hello");
                    }
                    else
                    {
                        fprintf(fd, "%d %s %d %s %s %s %s ", s.book_id, s.book_name, s.student_id, s.student_name, s.number, s.issue_date, s.return_date);
                    }
                }

                fclose(fp);
                fclose(fd);
                remove("issue.dat");
                rename("new.dat", "issue.dat");

                fp = fopen("data.dat", "r");
                rewind(fp);
                fd = fopen("new.dat", "a+");
                while (fscanf(fp, "%s %d %s %s %d %f %d %d %d", a.categ, &a.id, a.name, a.author, &a.quantity, &a.price, &a.rack_no, &a.available, &a.issued) != EOF)
                {
                    if (a.id == b_id)
                    {
                        a.available+=1;
                        a.issued-=1;
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                    }
                    else
                    {
                        fprintf(fd, "%s %d %s %s %d %.2f %d %d %d ", a.categ, a.id, a.name, a.author, a.quantity, a.price, a.rack_no, a.available, a.issued);
                    }
                }

                fclose(fp);
                fclose(fd);

                remove("data.dat");
                rename("new.dat","data.dat");

                gotoxy(46, 20);
                printf("    Record deleted successfully   ");

                gotoxy(50, 22);
                printf("Press Any To Continue.....");
                getch();
                return book_transaction();
            }
            // exit(0);
            return main_menu();
        }
    }
    fclose(fp);
    gotoxy(53, 16);
    printf("NO record found...");
    gotoxy(52, 18);
    printf("Want to try Again...");
    if (yes_no(55, 64, 19) == 1)
    {
        return return_books();
    }
    return book_transaction();
}

void book_transaction()
{
    system("cls");
    box(23, 4, 71, 16);
    h_line(23, 6, 71);
    box(23, 21, 71, 2);
    gotoxy(51, 5);
    printf("Book Transaction");
    char items[6][26] = {"1. Issue A Book", "2. View Issued Book", "3. Search Issued Book", "4. Return Book", "5. Goto Main Menu", "6. Close Application"};

    gotoxy(25, 22);
    printf("Use Up/Down Arrows keys for Navigation.");
    int s = selector(26, 8, 18, items);

    switch (s)
    {
    case 1:
        issue_books();
        break;
    case 2:
        view_issued_book();
        break;
    case 3:
        search_issued_books();
        break;
    case 4:
        return_books();
        break;
    case 5:
        main_menu();
        break;
    case 6:
        exit(0);
        break;
    }
}

void reset()
{
    system("cls");
    box(30,7,50,7);
    remove("data.dat");
    remove("issue.dat");
    gotoxy(36,10);
    printf("Reset Successful");
    gotoxy(36,12);
    printf("Press Any Key To Continue.....");
    getch();
    return main_menu();
}

void settings()
{
    system("cls");
    box(23, 4, 71, 18);
    h_line(23, 6, 71);
    box(23, 23, 71, 2);
    gotoxy(50, 5);
    printf("Settings");

    char items[7][26] = {"1. Reset", "2. Goto Main Memu", "3. Close Application"/*, "4. Edit Student Record", "5. View All Student List", "6. Goto Main Menu", "7. Close Application"*/};

    gotoxy(25, 24);
    printf("Use Up/Down Arrows keys for Navigation.");

    int s = selector(26, 8, 12, items);

    switch (s)
    {
    case 1:
        reset();
        break;
    /* case 2:
        remove_student();
        break;
    case 3:
        search_student_record();
        break;
    case 4:
        edit_student_record();
        break;
    case 5:
        view_all_student_list();
        break; */
    case 2:
        main_menu();
        break;
    case 3:
        exit(0);
        break;
    }
}

void main_menu()
{
    system("cls");
    system("color 6");
    char ch;
    box(6, 1, 105, 2);
    textcolor(3);
    box(23, 4, 71, 4);
    gotoxy(33, 5);
    printf("Current Date     :     ");
    gotoxy(33, 7);
    printf("Current Time     :     ");
    textcolor(6);
    box(23, 9, 71, 14);
    h_line(23, 11, 71);
    h_line(23, 21, 71);
    gotoxy(47, 2);
    printf("Welcome To ACEM Library");
    gotoxy(54, 10);
    printf("Main Menu");

    char items[4][26] = {"1. Book Management", "2. Book Transaction", "3. Settings", "4. Close Application"};

    gotoxy(25, 22);
    printf("Use Up/Down Arrows keys for Navigation.");

    int s = menu_selector(26, 13, 19, items);
    switch (s)
    {
    case 1:
        return book_management();
        break;
    case 2:
        return book_transaction();
        break;
    case 3:
        return settings();
        break;
    case 4:
        getch();
        break;
    }
}

void password(int x, int y)
{
    int i = 0;
    char ch, pass[15], t[17] = "Enter Password: ";
    gotoxy(x, y);
    for (int i = 0; i < 17; i++)
    {
        printf("%c", t[i]);
        delay(8);
    }
label1:
    while (1)
    {
        ch = getch();
        if (ch == 0x08)
        {
            if (i != 0)
            {
                i--;
                printf("\b \b");
            }
            else
            {
                printf("\a");
            }
        }
        else if (ch == 13)
        {
            break;
        }
        else
        {
            if (i < 15)
            {
                pass[i] = ch;
                printf("*");
                i++;
            }
            else
            {
                printf("\a");
            }
        }
    }
    pass[i] = '\0';
    if (strcmp(pass, "Developer-Dk") == 0)
    {
        gotoxy(x + 17, y + 2);
        printf("   ");
        gotoxy(x + 20, y + 2);
        system("color A");
        printf("Correct Password");
    }
    else
    {
        system("color 4");
        gotoxy(x + 17, y + 2);
        printf("\atry again...");
        delay(1000);
        gotoxy(x + 16, y);
        for (int i = 0; i < strlen(pass) + 1; i++)
        {
            printf(" ");
        }
        gotoxy(x + 16, y);
        i = 0;
        goto label1;
    }
}

void splash_s(int x, int y, int l, int h)
{
    for (int i = 0; i < h; i++)
    {
        gotoxy(x, y + i);
        printf("\xDB");
        delay(5);
    }
    for (int i = 0; i < l - 2; i++)
    {
        printf("\xDB");
        delay(3);
    }
    for (int i = y + h; i > y; i--)
    {
        gotoxy(x + l - 1, i - 1);
        printf("\xDB");
        delay(5);
    }
    for (int i = x + l - 2; i > x; i--)
    {
        gotoxy(i, y);
        printf("\xDB");
        delay(3);
    }
    char a[11] = "Welcome to";
    gotoxy(55, 9);
    for (int i = 0; i < 10; i++)
    {
        printf("%c", a[i]);
        delay(8);
    }
    char b[27] = "Library Management System";
    gotoxy(47, 11);
    for (int i = 0; i < 26; i++)
    {
        printf("%c", b[i]);
        delay(8);
    }
}

void main()
{
    SetConsoleTitle("LIBRARY MANAGEMENT SYSTEM");
    system("cls");
    system("color 9");
    splash_s(24, 5, 71, 20);
    password(30, 15);
    loader(29, 20, 54);
    main_menu();
}