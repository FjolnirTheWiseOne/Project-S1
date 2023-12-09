#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LAPTOPS 100

struct laptop {
    char model[50];
    int manufacturingYear;
    int CPU;
    int RAM;
};

void saveLaptopsToFile(FILE *file, const char *filename) {
    FILE *outputFile = fopen(filename, "w");
    if (outputFile == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    struct laptop currentLaptop;
    rewind(file);
    
    // Write header for the list of laptops
    fprintf(outputFile, "List of laptops:\n");
    fprintf(outputFile, "Name | Year | CPU(Hz) | RAM(GB)\n");
    // Read each laptop from the binary file and write its details to the output text file
    while (fread(&currentLaptop, sizeof(struct laptop), 1, file) == 1) {
        fprintf(outputFile, "%s | %d | %d Hz | %d GB\n", currentLaptop.model, currentLaptop.manufacturingYear, currentLaptop.CPU, currentLaptop.RAM);
    }

    fclose(outputFile);
}

// Function to add a new laptop
void addLaptop(FILE *file) {
    // Code to input details of a new laptop and write it to the binary file
    struct laptop newLaptop;

    printf("Enter laptop model: ");
    scanf(" %[^\n]", newLaptop.model);

    printf("Enter the manufacturing year: ");
    scanf("%d", &newLaptop.manufacturingYear);

    printf("Enter the CPU of laptop (MHz): ");
    scanf("%d", &newLaptop.CPU);

    printf("Enter the RAM of laptop (GB): ");
    scanf("%d", &newLaptop.RAM);

    fwrite(&newLaptop, sizeof(struct laptop), 1, file);
}

// Function to display all laptops
void displayLaptops(FILE *file) {
    struct laptop currentLaptop;
    int index = 1;

    printf("\nList of laptops:\n");
    printf("Name | Year | CPU(Hz) | RAM(GB)\n");
    rewind(file);
    while (fread(&currentLaptop, sizeof(struct laptop), 1, file) == 1) {
        printf("%d. %s | %d | %d Hz | %d GB\n", index, currentLaptop.model, currentLaptop.manufacturingYear, currentLaptop.CPU, currentLaptop.RAM);
        index++;
    }
  // After displaying, save the laptops to the output text file
    saveLaptopsToFile(file, "laptops_output.txt");
}
// Function to check the quality of laptops
void checkQuality(FILE *file) {
  // Code to check and display the quality assessment of each laptop
    struct laptop currentLaptop;

    rewind(file);

    printf("\nQuality Assessment:\n");
    printf("Name | Year | CPU(Hz) | RAM(GB) | Quality\n");

    while (fread(&currentLaptop, sizeof(struct laptop), 1, file) == 1) {
        printf("%s | %d | %d Hz | %d GB | ", currentLaptop.model, currentLaptop.manufacturingYear, currentLaptop.CPU, currentLaptop.RAM);

        if (currentLaptop.manufacturingYear >= 2007 && currentLaptop.CPU >= 2500 && currentLaptop.RAM >= 4) {
            printf("Meets quality standards\n");
        } else {
            printf("Does not meet quality standards\n");
        }
    }
}
// Function to delete a laptop
void deleteLaptop(FILE *file, int laptopNumber) {
   // Code to delete a laptop from the binary file
    FILE *tempFile;
    struct laptop currentLaptop;
    int count = 0;
    int found = 0;

    tempFile = fopen("temp.txt", "wb+");
    if (tempFile == NULL) {
        printf("Error creating temporary file!\n");
        return;
    }

    rewind(file);

    while (fread(&currentLaptop, sizeof(struct laptop), 1, file) == 1) {
        if (++count != laptopNumber) {
            fwrite(&currentLaptop, sizeof(struct laptop), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(tempFile);
    fclose(file);

    if (remove("laptops.txt") != 0) {
        printf("Error deleting original file!\n");
        return;
    }

    if (rename("temp.txt", "laptops.txt") != 0) {
        printf("Error renaming temporary file!\n");
        return;
    }

    if (!found) {
        printf("Laptop %d not found or already deleted.\n", laptopNumber);
    } else {
        printf("Laptop %d is deleted!\n", laptopNumber);
    }

    file = fopen("laptops.txt", "ab+");
    if (file == NULL) {
        printf("Error opening File!\n");
        exit(1);
    }
}
// The main function where the program execution begins
int main() {
  // Open or create a binary file for laptops
    FILE *laptopFile;
    laptopFile = fopen("laptops.txt", "ab+");
    if (laptopFile == NULL) {
        printf("Error opening File!");
        return 1;
    }

    int choice;
    do {
      // Display menu options for the user
        printf("\nQuality Control System for Laptop Manufacturing!\n");
        printf("1. Add a new laptop\n");
        printf("2. Display all laptops available\n");
        printf("3. Check laptop quality\n");
        printf("4. Delete a laptop\n");
        printf("5. Save laptops to file\n"); 
        printf("6. Exit\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);
        // Switch case to perform actions based on user choice
        switch (choice) {
            case 1:
                addLaptop(laptopFile); // Add a new laptop
                break;
            case 2:
                displayLaptops(laptopFile); // Display all laptops
                break;
            case 3:
                checkQuality(laptopFile); // Check laptop quality
                break;
            case 4:
                // Display laptops and then prompt to delete a specific laptop
                displayLaptops(laptopFile);
                int laptopToDelete;
                printf("Enter the number of the laptop to delete: ");
                scanf("%d", &laptopToDelete);
                deleteLaptop(laptopFile, laptopToDelete); // Delete a laptop
                break;
            case 5:
                saveLaptopsToFile(laptopFile, "laptops_output.txt");  // Save laptops to a text file
                printf("Laptops saved to file!\n");
                break;
            case 6:
                printf("Exiting...\n"); // Exit the program
                break;
            default:
                printf("Invalid choice, try again!\n"); // Display for an invalid choice
        }
    } while (choice != 6);

    fclose(laptopFile);
    return 0;
}
