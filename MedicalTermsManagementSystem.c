#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 100

struct Term {
    char name[50];
    char definition[100];
    char subfield[50];
};

//Add the terms.
void add_term(struct Term *terms, int *num_terms) {
    if (*num_terms >= MAX_TERMS) {
        printf("Error: Maximum number of terms reached\n");
        return;
	}
	
    printf("Enter the name of the term: ");
    scanf("%s", terms[*num_terms].name);
    printf("Enter the definition of the term: ");
    scanf("%s", terms[*num_terms].definition);
    printf("Enter the subfield of the term: ");
    scanf("%s", terms[*num_terms].subfield);
    
    (*num_terms)++;
    
    FILE *fp = fopen("Medical_Term.txt", "a");
    fprintf(fp,"%s,%s,%s\n", terms[*num_terms-1].name, terms[*num_terms-1].definition, terms[*num_terms-1].subfield);
    fclose(fp);
    printf("Term added successfully\n");
}

//Display all the terms in the alphabetical order. 
void display_terms(struct Term *terms, int num_terms) {
	
    for (int i = 0; i < num_terms-1; i++) {
        for (int j = i+1; j < num_terms; j++) {
            if (strcmp(terms[i].name, terms[j].name) > 0) {
                struct Term temp = terms[i];
                terms[i] = terms[j];
                terms[j] = temp;
            }
        }
    }

    printf("Terms in alphabetical order:\n");
    for (int i = 0; i < num_terms; i++) {
        printf("%s: %s %s\n", terms[i].name, terms[i].definition, terms[i].subfield);
    }
}

//Update the term
void update_term(struct Term *terms, int num_terms) {
    char name[50];
    printf("Enter the name of the term to update: ");
    scanf("%s", name);
    
    int index = -1;
    for (int i = 0; i < num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        printf("Enter the new definition of the term: ");
        scanf("%s", terms[index].definition);

        FILE *fp = fopen("Medical_Term.txt", "w");
        for (int i = 0; i < num_terms; i++) {
            fprintf(fp, "%s,%s,%s\n", terms[i].name, terms[i].definition, terms[i].subfield);
        }
        fclose(fp);
        
        printf("Term updated successfully\n");
    } else {
        printf("Error: Term not found\n");
    }
}

//Search the terms.
void search_term(struct Term *terms, int num_terms) {

    char name[50];
    printf("Enter the name of the term to search for: ");
    scanf("%s", name);

    int index = -1;
    for (int i = 0; i < num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
            index = i;
            break; 
		}
	}

    if (index != -1) {
        printf("%s: %s (%s)\n", terms[index].name, terms[index].definition, terms[index].subfield);
    } else {
        printf("Error: Term not found\n");
    }  
}

//Delete the terms.
void delete_term(struct Term *terms, int *num_terms) {
    char name[50];
    printf("Enter the name of the term to delete: ");
    scanf("%s", name);

    int index = -1;
    for (int i = 0; i < *num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
            index = i;
            break; 
		}
	}
	
	
    if (index != -1) {

        for (int i = index; i < *num_terms-1; i++) {
            terms[i] = terms[i+1];
        }

        (*num_terms)--;

        FILE *fp = fopen("Medical_Term.txt", "w");
        for (int i = 0; i < *num_terms; i++) {
            fprintf(fp, "%s,%s,%s\n", terms[i].name, terms[i].definition, terms[i].subfield);
        }
        fclose(fp);
        
        printf("Term deleted successfully\n");
    } else {
        printf("Error: Term not found\n");
    }   
}

int main() {
	
    struct Term terms[MAX_TERMS];
    int num_terms = 0;
    
    FILE *fp = fopen("Medical_Term.txt", "r");
    if (fp != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *name = strtok(line, ",");
            char *definition = strtok(NULL, ",");
            char *subfield = strtok(NULL, ",");
            strcpy(terms[num_terms].name, name);
            strcpy(terms[num_terms].definition, definition);
            strcpy(terms[num_terms].subfield, subfield);
            num_terms++; 
		}
        fclose(fp);
    }
    
    // Menu loop
    int choice;
    do {
    	printf("______________________________________________\n");
        printf("\nMedical Terminology Dictionary Management\n");
        printf("______________________________________________\n");
        printf("1. Add term\n");
        printf("2. Display all the term\n");
        printf("3. Update record\n");
        printf("4. Search term\n");
        printf("5. Delete record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
        	
        case 1:
            add_term(terms, &num_terms);
            break;
        
        case 2:
            display_terms(terms, num_terms);
            break;
        
        case 3:
            update_term(terms, num_terms);
            break;
        
        case 4:
            search_term(terms, num_terms);
            break;
        
        case 5:
            delete_term(terms, &num_terms);
            break;
        
        case 6:
            printf("Record Exiting...\n");
            break;
        
        default:
            printf("Error!! Invalid choice\n");
            break;
	} 
} while (choice != 6);
return 0; 
}