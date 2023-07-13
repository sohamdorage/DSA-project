#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_ITEMS 100
#define HASH_TABLE_SIZE 100
#define MAX_USERS 100


typedef struct
{
    int itemId;
    char itemName[50];
    float itemPrice;
    int itemSize;
} Item;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    User users[MAX_USERS];
    int userCount;
} UserDatabase;

typedef struct Node
{
    Item item;
    struct Node *next;
} Node;

typedef struct
{
    Node *itemHashTable[HASH_TABLE_SIZE];
    int itemCount;
} OnlineCartSystem;

// initialize online cart system
void initializeSystem(OnlineCartSystem *system)
{
    system->itemCount = 0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        system->itemHashTable[i] = NULL;
    }
}

void initializeUserDatabase(UserDatabase *database) {
    database->userCount = 0;
}

void registerUser(UserDatabase *database, const char *username, const char *password) {
    if (database->userCount >= MAX_USERS) {
        printf("User database is full. Cannot register more users.\n");
        return;
    }

    // Check if username contains only alphabetic characters
    for (int i = 0; username[i] != '\0'; i++) {
        if (!isalpha(username[i])) {
            printf("Invalid username. Only alphabetic characters are allowed.\n");
            return;
        }
    }

    User newUser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);

    database->users[database->userCount] = newUser;
    database->userCount++;

    printf("User '%s' registered successfully.\n", username);
}

bool loginUser(UserDatabase *database, const char *username, const char *password) {
    for (int i = 0; i < database->userCount; i++) {
        User currentUser = database->users[i];
        if (strcmp(currentUser.username, username) == 0 && strcmp(currentUser.password, password) == 0) {
            printf("User '%s' logged in successfully.\n", username);
            return true;
        }
    }
    printf("Invalid username or password. Login failed.\n");
    return false;
}


//  add an item to the item hash table
void addItemToHashTable(OnlineCartSystem *system, Item *item)
{
    int index = item->itemId % HASH_TABLE_SIZE;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->item = *item;
    newNode->next = NULL;

    if (system->itemHashTable[index] == NULL)
    {
        system->itemHashTable[index] = newNode;
    }
    else
    {
        Node *currentNode = system->itemHashTable[index];
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    system->itemCount++;
}

// delete  item from the item hash table
void deleteItemFromHashTable(OnlineCartSystem *system, int itemId)
{
    int index = itemId % HASH_TABLE_SIZE;
    Node *currentNode = system->itemHashTable[index];
    Node *previousNode = NULL;

    while (currentNode != NULL && currentNode->item.itemId != itemId)
    {
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode != NULL)
    {
        if (previousNode == NULL)
        {
            system->itemHashTable[index] = currentNode->next;
        }
        else
        {
            previousNode->next = currentNode->next;
        }

        free(currentNode);
        system->itemCount--;
        printf("Item with ID %d deleted.\n", itemId);
    }
    else
    {
        printf("Item with ID %d not found.\n", itemId);
    }
}

// display all items in the hash table
void displayItems(OnlineCartSystem *system)
{
    printf("Items in the cart:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        Node *currentNode = system->itemHashTable[i];
        while (currentNode != NULL)
        {
            printf("Item ID: %d, Item Name: %s, Item Price: %.2f, Item Size: %d (Position: %d)\n",
                   currentNode->item.itemId,
                   currentNode->item.itemName,
                   currentNode->item.itemPrice,
                   currentNode->item.itemSize,
                   i);
            currentNode = currentNode->next;
        }
    }
}

// get user input and add item to the cart
void addItemToCart(OnlineCartSystem *system, bool isAuthenticated) {
    if (!isAuthenticated) {
        printf("You need to login first.\n");
        return;
    }
    int numItems;
    printf("Enter the number of items to add: ");
    scanf("%d", &numItems);

    for (int i = 0; i < numItems; i++)
    {
        Item newItem;
        printf("Item id 1 for Nike Air Max\n ");
        printf("Item id 2 for Adidas Ultraboost\n ");
        printf("Item id 3 for Puma RS-X \n");
        printf("Item id 4 for Jordan Shoes\n ");
        printf("Item id 5 for Woodland Shoes\n ");
        printf("Item id 6 for Puma sandle RS-X \n");
        printf("Item id 7 for Nike Air 1ST copy\n ");
        printf("Item id 8 for Sparx Shoes\n ");
        printf("Item id 9 for Puma Sandle \n");
        printf("Item id 10 for Sparx Sandle\n ");
        printf("Item id 11 for Adidas Chapples\n ");
        printf("Item id 12 for Puma R-1 \n");
        printf("Item id 13 for Nike cmp\n ");
        printf("Item id 14 for Bata Sandles\n ");
        printf("Item id 15 for Bata Shoes \n");
        printf("Item id 16 for Reebok Sandles\n ");
        printf("Item id 17 for Reebok Shoes\n ");
        printf("Item id 18 for Asks Sandles \n");
        printf("Item id 19 for Asks Shoes\n ");
        printf("Item id 20 for Metro Shoes\n ");
        printf("Item id 21 for Metro Sandles \n");
        printf("Item id 22 for Metro 1cpy\n ");
        printf("Item id 101 for Crocs Shoes\n ");
        printf("Item id 102 for Crocs Sandles \n");
        printf("Enter the Item ID:\n ");
        scanf("%d", &newItem.itemId);

        switch (newItem.itemId)
        {
        case 1:
            strcpy(newItem.itemName, "Nike Air Max");
            newItem.itemPrice = 1520.0;
            break;
        case 2:
            strcpy(newItem.itemName, "Adidas Ultraboost");
            newItem.itemPrice = 1280.0;
            break;
        case 3:
            strcpy(newItem.itemName, "Puma RS-X");
            newItem.itemPrice = 1220.0;
            break;
        case 4:
            strcpy(newItem.itemName, "Jordan Shoes");
            newItem.itemPrice = 1520.0;
            break;
        case 5:
            strcpy(newItem.itemName, "Woodland Shoes");
            newItem.itemPrice = 2180.0;
            break;
        case 6:
            strcpy(newItem.itemName, "Puma sandle RS-X");
            newItem.itemPrice = 12220.0;
            break;
        case 7:
            strcpy(newItem.itemName, "Nike Air 1ST copy");
            newItem.itemPrice = 1520.0;
            break;
        case 8:
            strcpy(newItem.itemName, "Sparx Shoes");
            newItem.itemPrice = 1820.0;
            break;
        case 9:
            strcpy(newItem.itemName, "Puma Sandle");
            newItem.itemPrice = 12220.0;
            break;
        case 10:
            strcpy(newItem.itemName, "Sparx Sandle");
            newItem.itemPrice = 1520.0;
            break;
        case 11:
            strcpy(newItem.itemName, "Adidas Chapple");
            newItem.itemPrice = 1280.0;
            break;
        case 12:
            strcpy(newItem.itemName, "Puma R-1");
            newItem.itemPrice = 80000.0;
            break;
        case 13:
            strcpy(newItem.itemName, "Nike Air Max");
            newItem.itemPrice = 1520.0;
            break;
        case 14:
            strcpy(newItem.itemName, "Bata SAndle");
            newItem.itemPrice = 1820.0;
            break;
        case 15:
            strcpy(newItem.itemName, "Bata Shoes");
            newItem.itemPrice = 1220.0;
            break;
        case 16:
            strcpy(newItem.itemName, "Reebok Sandles");
            newItem.itemPrice = 12250.0;
            break;
        case 17:
            strcpy(newItem.itemName, "Reebok Shoes");
            newItem.itemPrice = 4580.0;
            break;
        case 18:
            strcpy(newItem.itemName, "Asks SAndles");
            newItem.itemPrice = 1201.0;
            break;
        case 19:
            strcpy(newItem.itemName, "Asks Shoes");
            newItem.itemPrice = 15110.0;
            break;
        case 20:
            strcpy(newItem.itemName, "Metro Shoes");
            newItem.itemPrice = 1810.0;
            break;
        case 21:
            strcpy(newItem.itemName, "Metro Sandles");
            newItem.itemPrice = 1201.0;
            break;
        case 22:
            strcpy(newItem.itemName, "Metro 1cpy");
            newItem.itemPrice = 1150.0;
            break;
        case 101:
            strcpy(newItem.itemName, "Crocs Shoes");
            newItem.itemPrice = 12280.0;
            break;
        case 102:
            strcpy(newItem.itemName, "Crocs Sandles");
            newItem.itemPrice = 11120.0;
            break;
        default:
            printf("Invalid Item ID. Item not added.\n");
            continue;
        }

        printf("Enter the Item Size: ");
        scanf("%d", &newItem.itemSize);

        addItemToHashTable(system, &newItem);
        printf("Item added to the cart.\n");
    }
}

// calculate the total price of items
float calculateTotalPrice(OnlineCartSystem *system)
{
    float totalPrice = 0.0;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        Node *currentNode = system->itemHashTable[i];
        while (currentNode != NULL)
        {
            totalPrice += currentNode->item.itemPrice;
            currentNode = currentNode->next;
        }
    }
    return totalPrice;
}

int main() {
    OnlineCartSystem system;
    initializeSystem(&system);
    bool isAuthenticated = false;

    UserDatabase userDB;
    initializeUserDatabase(&userDB);

    int choice;
    do {
        printf("\n----- Online Cart System -----\n");
        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. Add Item to Cart\n");
        printf("4. Delete Item from Cart\n");
        printf("5. Calculate Total Cost\n");
        printf("6. Display Items in Cart\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char username[50], password[50];
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                registerUser(&userDB, username, password);
                break;
            }
             case 2: {
                char username[50], password[50];
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);

                if (loginUser(&userDB, username, password)) {
                    isAuthenticated = true;  // Set user authentication status to true
                    // printf("User '%s' logged in successfully.\n", username);
                }
                break;
            }
            case 3:
                addItemToCart(&system, isAuthenticated);  // Pass the authentication status
                break;
            case 4: {
                int itemIdToDelete;
                printf("Enter the ID of the item to delete: ");
                scanf("%d", &itemIdToDelete);
                deleteItemFromHashTable(&system, itemIdToDelete);
                break;
            }
            case 5: {
                float totalPrice = calculateTotalPrice(&system);
                printf("Total Price: %.2f\n", totalPrice);
                break;
            }
            case 6:
                displayItems(&system);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

