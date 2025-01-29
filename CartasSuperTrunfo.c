#include <stdio.h>
#include <string.h>
#ifdef _WIN32 // I had to add this here, so then I could use strcasecmp to turn the function to case-insensitive
    #include <string.h>
    #define strcasecmp _stricmp // Windows equivalent
#else
    #include <strings.h> // Required for strcasecmp() on Linux/macOS
#endif

// "Super Trunfo - Countries" Challenges
/* "Super Trunfo - Countries" is a card game about countries would feature cards representing different nations, 
each with various attributes such as population, area, GDP, HDI, military power, or tourist attractions. 
Players take turns choosing an attribute from their top card to compare with their opponent’s card. 
The player with the highest (or lowest, depending on the rule) value wins the round and takes the opponent’s card. 
The game continues until one player collects all the cards.
*/
/*  - City Name (mandatory)
        - City Code (mandatory)
        - City Population (mandatory)
        - City Area (mandatory)
        - Number of Touristic Points in the City (mandatory)
        - City Populational Density (mandatory)
        - City GDP (mandatory)
        - City GDP per Capita (mandatory)
        - City HDI
        - City Year of Foundation
        - "Super Power" (mandatory) - Sum of all
    */
// i have searched for a better way to define the cities, so then I don't have to declare so many variables. this function "struct" seems like a good alternative
struct City { 

    //scanned from terminal
    char name[50];
    int population;
    float area;
    int numTouristicPoints;
    double gdp;
    float hdi;
    int yearOfFoundation; // remember when printing and scanning to show the negative sign, indicating BCE and CE
    char code [3]; //city code (first data is A to H, second is 01 to 04)

    //calculated automatically in the algorythm with data from user
    float gdpCapita; //divide GDP/population
    float popDen; //populational density, calculate population/area
    double superPower; //calculated by sum, but yearOfFoundation and popDen (these 2 we subtract)

};

void compareBiggerAttribute(float value1, float value2, char city1[], char city2[], char attributeName[]) {
    printf("%s: ", attributeName);
    if (value1 > value2) {
        printf("%s wins! Bigger %s (%s: %.2f x %s: %.2f)\n", city1, attributeName, city1, value1, city2, value2);
    } else if (value2 > value1) {
        printf("%s wins! Bigger %s (%s: %.2f x %s: %.2f)\n", city2, attributeName, city2, value2, city1, value1);
    } else {
        printf("It's a draw! Both %s and %s have %.2f %s.\n", city1, city2, value1, attributeName);
    }
}

void compareSmallerAttribute(float value1, float value2, char city1[], char city2[], char attributeName[]) {
    printf("%s: ", attributeName);
    if (value1 < value2) {
        printf("%s wins! Smaller %s (%s: %.2f x %s: %.2f)\n", city1, attributeName, city1, value1, city2, value2);
    } else if (value2 < value1) {
        printf("%s wins! Smaller %s (%s: %.2f x %s: %.2f)\n", city2, attributeName, city2, value2, city1, value1);
    } else {
        printf("It's a draw! Both %s and %s have %.2f %s.\n", city1, city2, value1, attributeName);
    }
}


int main() {
    
    int totalNumCities = 32;
    struct City cities[totalNumCities];

    //here, the "for" function will automatically repeating the algorythm within it, until it reaches 32 times (totalNumCities)
    for (int i = 0; i < totalNumCities; i++){
        
        printf("\nEnter the information for City %d:\n", i+1); // i have to add +1 to i, bc i starts 0. 

        printf("Type the city's %d NAME:\n", i+1);
        fgets(cities[i].name, sizeof(cities[i].name), stdin); //i need to use this, so the user can enter cities full names with spaces between names
        //normally, fgets catches data from an external file, but stdin catches from terminal
        //this function below removes \n. everytime that fgets was catching the full name, it was adding \n. it was necessary to add <string.h> Library 
        cities[i].name[strcspn(cities[i].name, "\n")] = 0;

        printf("Type the city's %d CODE: (FORMAT: LETTER + NUMBER ex: A01, C03)\n", i+1);
        scanf("%3s", cities[i].code); //only 3 characters

        printf("Type the city's %d POPULATION: (FORMAT: full number ex: 2000000 for 2 milion)\n", i+1);
        ; //clears any space in terminal before scanf
        scanf("%d", &cities[i].population);

        printf("Type the city's %d AREA: (FORMAT: full number ex: 2000000 for 2 milion km²)\n", i+1);
        while (getchar() != '\n');
        scanf("%f", &cities[i].area);

        printf("Type the city's %d NUMBER OF TOURISTIC POINTS:\n", i+1);
        while (getchar() != '\n');
        scanf(" %d", &cities[i].numTouristicPoints);

        printf("Type the city's %d GDP:\n", i+1);
        while (getchar() != '\n');
        scanf("%lf", &cities[i].gdp);

        printf("Type the city's %d HDI:\n", i+1);
        while (getchar() != '\n');
        scanf(" %f", &cities[i].hdi);

        printf("Type the city's %d YEAR OF FOUNDATION:\n", i+1);
        while (getchar() != '\n');
        scanf(" %d", &cities[i].yearOfFoundation);

        //now that I coul get all the data, let's calculate popDen and gdpCapita

        cities[i].popDen = cities[i].population/cities[i].area; //calculate popDen

        cities[i].gdpCapita = cities[i].gdp/cities[i].population; //calculate gdp Per Capita

        cities[i].superPower = (float)(cities[i].population) + cities[i].area + cities[i].numTouristicPoints + cities[i].gdp + cities[i].hdi + cities[i].gdpCapita;
        cities[i].superPower -= (cities[i].yearOfFoundation + cities[i].popDen);

        
        //now, let's show the user the city's infos.
        printf("\n");
        printf("OK, city %d finished! Let's check:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %d \n", cities[i].population);
        printf("City's Area: %.2f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %.lf \n", cities[i].gdp);
        printf("City's HDI: %.3f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);
        printf("City's Populational Density: %.2f \n", cities[i].popDen);
        printf("City's GDP per Capita: %.2f \n", cities[i].gdpCapita);
        printf("City's Super Power: %.2f \n", cities[i].superPower);
        
        
        // "Press Enter to continue" function
        getchar(); //clear everything
        printf("\nPress Enter to continue...");
        getchar(); // wait for user to press enter
        printf("\n"); // just to make it more beautyful :D
        //and repeat!
    }

    printf("\nEverything finished! Let's check all the cards.\n");
   
    // "Press Enter to continue" function
    while (getchar() != '\n'); //clear everything
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // wait for user to press enter
    printf("\n"); // just to make it more beautyful :D

    //now, I want to show everything again to the user, all the cards. just to check if everything is well saved.
    for (int i = 0; i < totalNumCities; i++){
        
        printf("___________________________________\n");
        printf("City number %d:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %d \n", cities[i].population);
        printf("City's Area: %.2f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %.lf \n", cities[i].gdp);
        printf("City's HDI: %.3f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);
        printf("City's Populational Density: %.2f \n", cities[i].popDen);
        printf("City's GDP per Capita: %.2f \n", cities[i].gdpCapita);
        printf("City's Super Power: %.2f \n", cities[i].superPower);
        printf("___________________________________\n");

    }

    printf("\nOK! Now, let's play. We will compare cards selected by you.\n");
    
    // "Press Enter to continue" function
    printf("Press Enter to continue...");
    while (getchar() != '\n');
    printf("\n");

    char option; // variable to continue playing (Y or N)
    char sameCards; //variable of maintaing to play with the same 2 cards (Y or N)
    do{
        
        char city1 [50];
        char city2 [50];
        char attribute;

        while (getchar() != '\n');
        //gets what is the first city to compare
        printf("Type the name of the first city: ");
        //same code as up there in first "for"
        fgets(city1, sizeof(city1), stdin);
        city1[strcspn(city1, "\n")] = 0;

        printf("\n"); //just skip a line

        //second city to compare
        printf("Type the name of the second city: ");
        fgets(city2, sizeof(city2), stdin);
        city2[strcspn(city2, "\n")] = 0;
        
        printf("\n"); //just skip a line

        printf("OK! So, what attribute would you like to compare? Type the number of which you'd like:\n");
        //repeat until user type a valid number
        do
        {

            float attributeCity1 = 0;
            float attributeCity2 = 0;

            //gets attribute to compare
            printf("1. Population\n2. Area\n3. Touristic Points\n4. GDP\n5. HDI\n6. Year of Foundation\n7. Populational Density\n8. GDP per Capita\n9. Super Power\nYour choise: ");
            scanf("%c", &attribute);
            printf("\n");

            if(attribute != '1' && attribute != '2' && attribute != '3' && attribute != '4' && attribute != '5' && attribute != '6' && attribute != '7' && attribute != '8' && attribute != '9'){
                printf("Humm... Seems like you typed something strange to me. Please, choose between 1 and 9 :D\n");
            }

            if(attribute == '1'){ //compares population
                
                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1.
                    // I changed the function, bc it was case sensitive. this now is case-insensitive
                        attributeCity1 = cities[i].population;
                        count1 = i;
                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].population;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].population, cities[count2].population, city1, city2, "Population");
                printf("\n");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '2'){ //compares Area

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].area;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].area;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].area, cities[count2].area, city1, city2, "Area");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '3'){ //compares touristic points

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].numTouristicPoints;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].numTouristicPoints;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].numTouristicPoints, cities[count2].numTouristicPoints, city1, city2, "Touristic Points");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '4'){ //compares gdp

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].gdp;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].gdp;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].gdp, cities[count2].gdp, city1, city2, "GDP");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '5'){ //compares HDI

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].hdi;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].hdi;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].hdi, cities[count2].hdi, city1, city2, "HDI");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '6'){ //compares Year of Foundation

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].yearOfFoundation;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].yearOfFoundation;
                        count2 = i;

                    }
                }

                compareSmallerAttribute(cities[count1].yearOfFoundation, cities[count2].yearOfFoundation, city1, city2, "Year of Foundation");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '7'){ //compares populational density

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].popDen;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].popDen;
                        count2 = i;

                    }
                }

                compareSmallerAttribute(cities[count1].popDen, cities[count2].popDen, city1, city2, "Populational Density");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '8'){ //compares GDP per capita

                int count1 = 0;
                int count2 = 0;

                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].gdpCapita;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].gdpCapita;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].gdpCapita, cities[count2].gdpCapita, city1, city2, "GDP per Capita");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

            if (attribute == '9'){ //compares superPower

                int count1 = 0;
                int count2 = 0;
                
                for (int i = 0; i < totalNumCities; i++){ //this for is for searching for the data inside the cities struct
                    if (strcasecmp(cities[i].name, city1) == 0){ //this function compares each of the data. if it's the same, returns 0, if not, -1

                        attributeCity1 = cities[i].superPower;
                        count1 = i;

                    }

                    if (strcasecmp(cities[i].name, city2) == 0){

                        attributeCity2 = cities[i].superPower;
                        count2 = i;

                    }
                }

                compareBiggerAttribute(cities[count1].superPower, cities[count2].superPower, city1, city2, "Super Power");

                printf("Would you like to continue with the same two cards? (Y/N): ");
                scanf("%s", &sameCards);
                while (getchar() != '\n');
                printf("\n");

            }

        } while (sameCards == 'Y' || sameCards == 'y');
        

        printf("\n");
        printf("Do you want to continue playing? Y/N: ");
        scanf(" %c",&option);
        printf("\n");
    }
    while(option == 'Y' || option == 'y');

    printf("MateCheck thanks you for using our game! Exiting program...");
    printf("\n \n");

    return 0;
}
