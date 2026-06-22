#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//SAFE INPUT HELPER
void clearBuffer() {
    while (getchar() != '\n');
}



struct Customer {
    int id;
    char name[50];
    char password[20];
};

struct Appointment {
    int id;
    char timeSlot[20];
    int confirmed;
};

struct DietPlan {
    int id;
    char plan[200];
};

struct Payment {
    int id;
    int paid;
};

struct Log {
    int id;
    int calories;
};

struct Goal {
    int id;
    int goal;
};

FILE *fp;

void adminMenu();
void customerMenu();
void generalMenu();

// ADMIN
void addCustomer();
void viewCustomers();
void searchCustomer();
void deleteCustomer();
void editCustomer();
void assignDietPlan();
void verifyPayment();
void confirmAppointment();

// CUSTOMER
void bookAppointment();
void checkAppointment();
void makePayment();
void viewDietPlan();
void calorieCalculator();
void dailyLog();

// GENERAL
void systemInfo();
void signup();
void login();
void setGoal();
void enterFood();
int userExists(int id);

int main() {
    int choice;

    while (1) {
        printf("\n===== DIET TRACKER SYSTEM =====\n");
        printf("1. Admin Module\n");
        printf("2. Customer Module\n");
        printf("3. General User Module\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: customerMenu(); break;
            case 3: generalMenu(); break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}


void adminMenu() {
    int c;

    while (1) {
        printf("\n--- ADMIN MENU ---\n");
        printf("1 Add\n2 View\n3 Search\n4 Delete\n5 Edit\n6 Diet Plan\n7 Payment\n8 Appointment\n9 Back\n");
        printf("Enter choice: ");

        if (scanf("%d", &c) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (c) {
            case 1: addCustomer(); break;
            case 2: viewCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: editCustomer(); break;
            case 6: assignDietPlan(); break;
            case 7: verifyPayment(); break;
            case 8: confirmAppointment(); break;
            case 9: return;
            default: printf("Invalid choice!\n");
        }
    }
}



void addCustomer() {
    struct Customer c;

    fp = fopen("customers.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter ID: ");
    if (scanf("%d", &c.id) != 1) {
        printf("Invalid ID!\n");
        clearBuffer();
        return;
    }

    printf("Enter Name: ");
    scanf("%s", c.name);

    printf("Enter Password: ");
    scanf("%s", c.password);

    fprintf(fp, "%d %s %s\n", c.id, c.name, c.password);

    fclose(fp);
    printf("Customer added successfully.\n");
}


void viewCustomers() {
    struct Customer c;

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--- CUSTOMER LIST ---\n");

    while (fscanf(fp, "%d %s %s", &c.id, c.name, c.password) != EOF) {
        printf("ID: %d | Name: %s\n", c.id, c.name);
    }

    fclose(fp);
}


void searchCustomer() {
    struct Customer c;
    int id, found = 0;

    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %s", &c.id, c.name, c.password) != EOF) {
        if (c.id == id) {
            printf("Found Customer: %s\n", c.name);
            found = 1;
        }
    }

    fclose(fp);

    if (!found)
        printf("Customer not found.\n");
}


void deleteCustomer() {
    struct Customer c;
    int id;
    FILE *temp;

    printf("Enter ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %s", &c.id, c.name, c.password) != EOF) {
        if (c.id != id) {
            fprintf(temp, "%d %s %s\n", c.id, c.name, c.password);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    printf("Customer deleted successfully.\n");
}


void editCustomer() {
    struct Customer c;
    int id;
    FILE *temp;

    printf("Enter ID to edit: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %s", &c.id, c.name, c.password) != EOF) {

        if (c.id == id) {
            printf("Enter new name: ");
            scanf("%s", c.name);
        }

        fprintf(temp, "%d %s %s\n", c.id, c.name, c.password);
    }

    fclose(fp);
    fclose(temp);

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    printf("Customer updated successfully.\n");
}


void assignDietPlan() {
    struct DietPlan d;

    fp = fopen("dietplans.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Customer ID: ");
    if (scanf("%d", &d.id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    clearBuffer();
    printf("Enter Diet Plan: ");
    fgets(d.plan, sizeof(d.plan), stdin);
    d.plan[strcspn(d.plan, "\n")] = 0;

    fprintf(fp, "%d %s\n", d.id, d.plan);

    fclose(fp);

    printf("Diet plan assigned.\n");
}


void verifyPayment() {
    struct Payment p;
    int id;
    FILE *temp;

    printf("Enter Customer ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("payments.txt", "r");
    if (fp == NULL) {
        printf("No payment records.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %d", &p.id, &p.paid) != EOF) {
        if (p.id == id)
            p.paid = 1;

        fprintf(temp, "%d %d\n", p.id, p.paid);
    }

    fclose(fp);
    fclose(temp);

    remove("payments.txt");
    rename("temp.txt", "payments.txt");

    printf("Payment verified.\n");
}


void confirmAppointment() {
    struct Appointment a;
    int id;
    FILE *temp;

    printf("Enter Customer ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("No appointment records.\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %d", &a.id, a.timeSlot, &a.confirmed) != EOF) {
        if (a.id == id)
            a.confirmed = 1;

        fprintf(temp, "%d %s %d\n", a.id, a.timeSlot, a.confirmed);
    }

    fclose(fp);
    fclose(temp);

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    printf("Appointment confirmed.\n");
}


void customerMenu() {
    int c;

    while (1) {
        printf("\n--- CUSTOMER MENU ---\n");
        printf("1. Book Appointment\n");
        printf("2. Check Appointment\n");
        printf("3. Make Payment\n");
        printf("4. View Diet Plan\n");
        printf("5. Calorie Calculator\n");
        printf("6. Daily Log\n");
        printf("7. Back\n");
        printf("Enter choice: ");

        if (scanf("%d", &c) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (c) {
            case 1: bookAppointment(); break;
            case 2: checkAppointment(); break;
            case 3: makePayment(); break;
            case 4: viewDietPlan(); break;
            case 5: calorieCalculator(); break;
            case 6: dailyLog(); break;
            case 7: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void bookAppointment() {
    struct Appointment a;

    fp = fopen("appointments.txt", "a");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Customer ID: ");
    if (scanf("%d", &a.id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    printf("Enter Time Slot: ");
    scanf("%s", a.timeSlot);

    a.confirmed = 0;

    fprintf(fp, "%d %s %d\n", a.id, a.timeSlot, a.confirmed);

    fclose(fp);

    printf("Appointment booked (pending approval).\n");
}

void checkAppointment() {
    struct Appointment a;
    int id, found = 0;

    printf("Enter Customer ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("No appointments found.\n");
        return;
    }

    while (fscanf(fp, "%d %s %d", &a.id, a.timeSlot, &a.confirmed) != EOF) {
        if (a.id == id) {
            found = 1;
            printf("Time Slot: %s\n", a.timeSlot);
            printf("Status: %s\n", a.confirmed ? "Confirmed" : "Pending");
        }
    }

    fclose(fp);

    if (!found)
        printf("No appointment found.\n");
}

void makePayment() {
    struct Payment p;

    fp = fopen("payments.txt", "a");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Customer ID: ");
    if (scanf("%d", &p.id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    p.paid = 1;

    fprintf(fp, "%d %d\n", p.id, p.paid);

    fclose(fp);

    printf("Payment successful.\n");
}


void viewDietPlan() {
    struct DietPlan d;
    int id, found = 0;

    printf("Enter Customer ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("dietplans.txt", "r");
    if (fp == NULL) {
        printf("No diet plans available.\n");
        return;
    }

    while (fscanf(fp, "%d %[^\n]", &d.id, d.plan) != EOF) {
        if (d.id == id) {
            found = 1;
            printf("\nDiet Plan:\n%s\n", d.plan);
        }
    }

    fclose(fp);

    if (!found)
        printf("No diet plan found.\n");
}


void calorieCalculator() {
    int calories;

    printf("Enter calories consumed today: ");

    if (scanf("%d", &calories) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    printf("Total Calories: %d\n", calories);

    if (calories < 2000)
        printf("Healthy range.\n");
    else
        printf("High intake warning.\n");
}

void dailyLog() {
    int breakfast, lunch, dinner, total;

    printf("\n===== DAILY DIET LOG =====\n");

    // INPUT BREAKFAST
    printf("Enter Breakfast Calories: ");
    if (scanf("%d", &breakfast) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    // INPUT LUNCH
    printf("Enter Lunch Calories: ");
    if (scanf("%d", &lunch) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    // INPUT DINNER
    printf("Enter Dinner Calories: ");
    if (scanf("%d", &dinner) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    // CALCULATE TOTAL
    total = breakfast + lunch + dinner;

    // DISPLAY SUMMARY
    printf("\n----- SUMMARY -----\n");
    printf("Breakfast: %d calories\n", breakfast);
    printf("Lunch    : %d calories\n", lunch);
    printf("Dinner   : %d calories\n", dinner);
    printf("-------------------\n");
    printf("Total Calories: %d\n", total);

    // OPTIONAL MESSAGE
    if (total < 1200) {
        printf("Light diet day \n");
    } else if (total <= 2000) {
        printf("Balanced diet \n");
    } else {
        printf("High calorie intake \n");
    }
}


void generalMenu() {
    int c;

    while (1) {
        printf("\n--- GENERAL USER ---\n");
        printf("1. System Info\n");
        printf("2. Signup\n");
        printf("3. Login\n");
        printf("4. Set Goal\n");
        printf("5. Enter Food\n");
        printf("6. Back\n");
        printf("Enter choice: ");

        if (scanf("%d", &c) != 1) {
            printf("Invalid input!\n");
            clearBuffer();
            continue;
        }

        switch (c) {
            case 1: systemInfo(); break;

            // REUSE existing function (no duplication)
            case 2: addCustomer(); break;

            case 3: login(); break;
            case 4: setGoal(); break;
            case 5: enterFood(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    }
}


void systemInfo() {
    printf("\n--- DIET TRACKER SYSTEM ---\n");
    printf("Diet Tracker System is designed to help users maintain a healthy lifestyle\n");
    printf("by tracking calorie intake and comparing it with set goals.\n\n");
    printf("It also helps DietGo Clinic manage customer data, diet plans,\n");
    printf("appointments, and payments in a structured way.\n\n");
    printf("The system ensures better organization and easy record keeping\n");
    printf("for both users and administrators.\n");
}


void login() {
    int id;
    char pass[20];

    struct Customer c;
    int found = 0;

    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    printf("Enter Password: ");
    scanf("%s", pass);

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("No users registered yet.\n");
        return;
    }

    while (fscanf(fp, "%d %s %s",
                  &c.id,
                  c.name,
                  c.password) == 3) {

        if (c.id == id && strcmp(c.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("Login successful.\n");
    } else {
        printf("Invalid ID or password.\n");
    }
}


void setGoal() {
    struct Goal g;

    printf("Enter Customer ID: ");
    if (scanf("%d", &g.id) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    // CHECK IF USER EXISTS
    if (!userExists(g.id)) {
        printf("User not registered. Cannot set goal.\n");
        return;
    }

    printf("Enter Calorie Goal: ");
    if (scanf("%d", &g.goal) != 1) {
        printf("Invalid input!\n");
        clearBuffer();
        return;
    }

    fp = fopen("goals.txt", "a");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fprintf(fp, "%d %d\n", g.id, g.goal);
    fclose(fp);

    printf("Goal set successfully.\n");
}


void enterFood() {
    struct Log l;
    struct Goal g;

    int foundGoal = 0;
    int remaining;

    // GET USER ID
    printf("Enter Customer ID: ");
    if (scanf("%d", &l.id) != 1) {
        printf("Invalid input! ID must be a number.\n");
        clearBuffer();
        return;
    }

    //  CHECK IF USER EXISTS
    if (!userExists(l.id)) {
        printf("User not registered. Cannot log food.\n");
        return;
    }

    // GET CALORIES
    printf("Enter Calories Consumed: ");
    if (scanf("%d", &l.calories) != 1) {
        printf("Invalid input! Calories must be a number.\n");
        clearBuffer();
        return;
    }

    // SAVE DAILY LOG
    fp = fopen("logs.txt", "a");
    if (fp == NULL) {
        printf("File error! Cannot open logs file.\n");
        return;
    }

    fprintf(fp, "%d %d\n", l.id, l.calories);
    fclose(fp);

    // OPEN GOALS FILE
    fp = fopen("goals.txt", "r");
    if (fp == NULL) {
        printf("No calorie goal set yet for this user.\n");
        return;
    }

    // SEARCH USER GOAL
    while (fscanf(fp, "%d %d", &g.id, &g.goal) != EOF) {
        if (g.id == l.id) {
            foundGoal = 1;

            remaining = g.goal - l.calories;

            printf("\n===== DAILY REPORT =====\n");
            printf("Calorie Goal   : %d\n", g.goal);
            printf("Calories Consumed: %d\n", l.calories);

            if (remaining > 0) {
                printf("Status: Within goal \n");
                printf("Remaining: %d calories\n", remaining);
            }
            else if (remaining == 0) {
                printf("Status: Perfect balance \n");
            }
            else {
                printf("Status: Goal exceeded \n");
                printf("Exceeded by: %d calories\n", -remaining);
            }

            break;
        }
    }

    fclose(fp);

    // IF NO GOAL FOUND
    if (!foundGoal) {
        printf("No calorie goal found for this user ID.\n");
    }
}

int userExists(int id) {
    struct Customer c;
    FILE *fp;

    fp = fopen("customers.txt", "r");

    if (fp == NULL) {
        return 0;
    }

    while (fscanf(fp, "%d %s %s",
                  &c.id,
                  c.name,
                  c.password) == 3) {

        if (c.id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
