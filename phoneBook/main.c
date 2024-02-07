#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_CHAR_LENGTH 256
#define CONTACT_FIELD_TOTAL 7 //the length of our Contact struct

typedef struct
{
    char firstName[MAX_CHAR_LENGTH];
    char lastName[MAX_CHAR_LENGTH];
    long int number;
    char twitter[MAX_CHAR_LENGTH];
    char discord[MAX_CHAR_LENGTH];
    char website[MAX_CHAR_LENGTH];
    int groupId;
} Contact;

typedef struct
{
    int id;
    char name[MAX_CHAR_LENGTH];
} Group;

typedef struct
{
    int totalContacts;
    Contact* contacts;
    int totalGroups;
    Group* groups;
} Data;

typedef enum 
{
    MAINMENU,
    NEW_CONTACT,
    EDIT_CONTACT,
    DELETE_CONTACT,
    NEW_GROUP,
    EDIT_GROUP,
    DELETE_GROUP,
    EXIT
} Mode;


char* readFile(int* size);
Mode mainMenu(Data* data);
void loadContacts(Data* data);
void saveContacts();
void newContact();
void editContact();
void cleanup();

int main(void)
{
    //init ncurses
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE); 

    Data data;
    loadContacts(&data);

    bool running = TRUE;
    Mode mode = MAINMENU;

    while(running)
    {
        switch(mode)
        {
            case MAINMENU: mode = mainMenu(&data);
                break;
        }
        running = FALSE;
    }

    // cleanup
    free(data.contacts);
    free(data.groups);
    endwin(); 
    return 0;
}

Mode mainMenu(Data* data)
{
    Mode mode;
    int option;

    

    clear();
    printw("Welcome to contacts!\n");
    printw("Groups: %d \n", data->totalGroups);
    printw("Contacts: %d \n", data->totalContacts );
    
    refresh();

    scanw("%d", &option);
}

void loadContacts(Data* data)
{
    // read file and save it to a char array
    int size;
    char* file = readFile(&size);

    if(file == NULL)
    {
        return;
    }

    // read though array and find total contacts and groups
    char c;
    bool flag = FALSE;
    int groupSize = 1; // we assume the first line is a group 
    int contactSize = 0;
    for(int c = 0; c < size; c++)
    {

        if(flag)
        {
            switch(file[c])
            {
                case 'c': contactSize++;
                    break;
                case 'g': groupSize++;
                    break; // contacts first because group size will likely be less
            }
            flag = FALSE;
        }

        if(file[c] == '\n')
        {
            flag = TRUE;
        }

        
        
    }
    
    // Arrays to hold our data
    Contact* contacts = (Contact*)malloc(contactSize * sizeof(Contact));
    Group* groups = (Group*)malloc(groupSize * sizeof(Group));

    // now we read our data
    char state = 's'; // states are start = s, and then first char of linebreak
    char buffer[MAX_CHAR_LENGTH];
    // reusing variables because im insane
    int b = 0;
    contactSize = 0;
    groupSize = 0;
    int mode = 0; // just to keep track of the order of the contacts data
    for(int c = 0; c < size; c++)
    {   

        if(file[c] == ':')
        {
            switch(state)
            {
                case 'c': 
                    switch(mode)
                    {
                        case 0: strcpy(contacts[contactSize].firstName, buffer);
                            break;
                        case 1: strcpy(contacts[contactSize].lastName, buffer);
                            break;
                        case 2: contacts[contactSize].number = atoi(buffer);
                            break;
                        case 3: strcpy(contacts[contactSize].twitter, buffer);
                            break;
                        case 4: strcpy(contacts[contactSize].discord, buffer);
                            break;
                        case 5: strcpy(contacts[contactSize].website, buffer);
                            break;
                        case 6: contacts[contactSize].groupId = atoi(buffer);
                            break;
                    }
                    break;
                case 'g': strcpy(groups[groupSize].name, buffer); // only one field 
                        groups[groupSize].id = groupSize; // we are not relying on position in array
                    break;
            }
            mode++;
            if(mode == CONTACT_FIELD_TOTAL)
            {
                mode = 0;
            }
            memset(buffer, 0, sizeof(buffer));
        }

        switch(state)
        {
            case 'c': buffer[b] = file[c];
                break;
            case 'g': buffer[b] = file[c];
                break;
        }

        if(state == 's')
        {
            state = file[c];
        }
        // End of line resets the state
        if(file[c] == '\n')
        {  
            switch(state)
            {
                case 'c': contactSize++;
                    break;
                case 'g': groupSize++;
                    break;
            }
            state = 's';
        }
        
    }

    data->contacts = contacts;
    data->groups = groups;
    data->totalContacts = contactSize;
    data->totalGroups = groupSize;
    
    free(file);

}

char* readFile(int* size)
{
    FILE *fh;
    fh = fopen("contacts.txt", "r");

    if(fh == NULL)
    {
        printw("Cannot read quiz data (contacts.txt)\n");
        getch(); 
        refresh();
        endwin(); 
        return NULL; 
    }

    fseek(fh, 0, SEEK_END);
    *size = ftell(fh);
    rewind(fh);


    char* buffer = (char*)malloc(*size + 1); 
    if(buffer == NULL)
    {
        perror("Failed to allocate memory");
        endwin();
        return NULL;
    }

    fread(buffer, 1, *size, fh); 
    buffer[*size] = '\0';

    fclose(fh);

    return buffer;
}


