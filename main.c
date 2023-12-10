#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LAPTOPS 100 // Maximum number of laptops

// Structure representing a laptop
struct laptop {
    char model[50]; // Model name of the laptop
    int manufacturingYear; // Manufacturing year of the laptop
    int CPU; // CPU speed of the laptop in MHz
    int RAM; // RAM capacity of the laptop in GB
};

/**
 * @brief Function to save laptops' details to a text file
 * 
 * @param file Pointer to the binary file containing laptop details
 * @param filename Name of the output text file to save laptop details
 */
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

/**
 * @brief Function to add a new laptop to the binary file
 * 
 * @param file Pointer to the binary file to add the new laptop
 */
void addLaptop(FILE *file) {
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

/**
 * @brief Function to display all laptops' details from the binary file
 * 
 * @param file Pointer to the binary file containing laptop details
 */
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

    saveLaptopsToFile(file, "laptops_output.txt");
}

/**
 * @brief Function to check the quality of laptops based on certain criteria
 * 
 * @param file Pointer to the binary file containing laptop details
 */
void checkQuality(FILE *file) {
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

/**
 * @brief Function to delete a specific laptop from the binary file
 * 
 * @param file Pointer to the binary file to delete the laptop from
 * @param laptopNumber Number of the laptop to be deleted
 */
void deleteLaptop(FILE *file, int laptopNumber) {
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

/**
 * @brief Main function where the program execution begins
 * 
 * @return int Exit status of the program
 */
int main() {
    FILE *laptopFile;
    laptopFile = fopen("laptops.txt", "ab+");
    if (laptopFile == NULL) {
        printf("Error opening File!");
        return 1;
    }

    int choice;
    do {
        printf("\nQuality Control System for Laptop Manufacturing!\n");
        printf("1. Add a new laptop\n");
        printf("2. Display all laptops available\n");
        printf("3. Check laptop quality\n");
        printf("4. Delete a laptop\n");
        printf("5. Save laptops to file\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addLaptop(laptopFile);
                break;
            case 2:
                displayLaptops(laptopFile);
                break;
            case 3:
                checkQuality(laptopFile);
                break;
            case 4:
                displayLaptops(laptopFile);
                int laptopToDelete;
                printf("Enter the number of the laptop to delete: ");
                scanf("%d", &laptopToDelete);
                deleteLaptop(laptopFile, laptopToDelete);
                break;
            case 5:
                saveLaptopsToFile(laptopFile, "laptops_output.txt");
                printf("Laptops saved to file!\n");
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, try again!\n");
        }
    } while (choice != 6);

    fclose(laptopFile);
    return 0;
}
