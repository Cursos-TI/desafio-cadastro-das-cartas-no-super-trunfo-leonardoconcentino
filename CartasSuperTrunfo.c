#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
    double population;
    float area;
    unsigned int numTouristicPoints;
    double gdp;
    float hdi;
    int yearOfFoundation; // remember when printing and scanning to show the negative sign, indicating BCE and CE
    char code [3]; //city code (first data is A to H, second is 01 to 04)

    //calculated automatically in the algorythm with data from user
    float gdpCapita; //divide GDP/population
    float popDen; //populational density, calculate population/area
    double superPower; //calculated by sum, but yearOfFoundation and popDen (these 2 we subtract)

};

struct City cities[32]; //32 will be the max range for cards

//this function aims to get 2 attributes and compare them. the winner is the biggest number
int compareBiggerAttribute(double value1, double value2, char city1[], char city2[], char attributeName[]) {
    
    printf("%s: ", attributeName);
    
    if (value1 > value2) {

        printf("%s wins! Bigger %s (%s: %.2lf x %s: %.2lf)\n", city1, attributeName, city1, value1, city2, value2);
        return 1;

    } else if (value2 > value1) {

        printf("%s wins! Bigger %s (%s: %.2lf x %s: %.2lf)\n", city2, attributeName, city2, value2, city1, value1);
        return 2;

    } else {

        printf("It's a draw! Both %s and %s have %.2lf %s.\n", city1, city2, value1, attributeName);
        return 3;

    }
}

//this function aims to get 2 attributes and compare them. the winner is the smallest number
int compareSmallerAttribute(double value1, double value2, char city1[], char city2[], char attributeName[]) {

    printf("%s: ", attributeName);

    if (value1 < value2) {

        printf("%s wins! Smaller %s (%s: %.2lf x %s: %.2lf)\n", city1, attributeName, city1, value1, city2, value2);
        return 1;

    } else if (value2 < value1) {

        printf("%s wins! Smaller %s (%s: %.2lf x %s: %.2lf)\n", city2, attributeName, city2, value2, city1, value1);
        return 2;

    } else {

        printf("It's a draw! Both %s and %s have %.2lf %s.\n", city1, city2, value1, attributeName);
        return 3;

    }
}

void collectCards(int numOfCards){

    //here, the "for" function will automatically repeating the algorythm within it, until it reaches numOfCards times (totalNumCities in main)
    for (int i = 0; i < numOfCards; i++){
        getchar();
        printf("\nEnter the information for City %d:\n", i+1); // i have to add +1 to i, bc i starts 0. 

        printf("Type the city's %d NAME:\n", i+1);
        printf("Answer: ");
        fgets(cities[i].name, sizeof(cities[i].name), stdin); //i need to use this, so the user can enter cities full names with spaces between names
        //normally, fgets catches data from an external file, but stdin catches from terminal
        //this function below removes \n. everytime that fgets was catching the full name, it was adding \n. it was necessary to add <string.h> Library 
        cities[i].name[strcspn(cities[i].name, "\n")] = 0;
        printf("\n\n");

        printf("Type the city's %d CODE: (FORMAT: LETTER + NUMBER ex: A01, C03)\n", i+1);
        printf("Answer: ");
        scanf("%3s", cities[i].code); //only 3 characters
        printf("\n\n");

        printf("Type the city's %d POPULATION: (FORMAT: full number ex: 2000000 for 2 milion)\n", i+1);
        ; //clears any space in terminal before scanf
        printf("Answer: ");
        scanf(" %lf", &cities[i].population);
        printf("\n\n");

        printf("Type the city's %d AREA: (FORMAT: full number ex: 2000000 for 2 milion km²)\n", i+1);
        printf("Answer: ");
        while (getchar() != '\n');
        scanf(" %f", &cities[i].area);
        printf("\n\n");

        printf("Type the city's %d NUMBER OF TOURISTIC POINTS:\n", i+1);
        printf("Answer: ");
        while (getchar() != '\n');
        scanf(" %u", &cities[i].numTouristicPoints);
        printf("\n\n");

        printf("Type the city's %d GDP:\n", i+1);
        printf("Answer: ");
        while (getchar() != '\n');
        scanf(" %lf", &cities[i].gdp);
        printf("\n\n");

        printf("Type the city's %d HDI:\n", i+1);
        printf("Answer: ");
        while (getchar() != '\n');
        scanf(" %f", &cities[i].hdi);
        printf("\n\n");

        printf("Type the city's %d YEAR OF FOUNDATION: (FORMAT: if CE, positive, if BCE, negative)\n", i+1);
        printf("Answer: ");
        while (getchar() != '\n');
        scanf(" %d", &cities[i].yearOfFoundation);
        printf("\n\n");

        //now that I coul get all the data, let's calculate popDen and gdpCapita

        cities[i].popDen = cities[i].population/cities[i].area; //calculate popDen

        cities[i].gdpCapita = cities[i].gdp/cities[i].population; //calculate gdp Per Capita

        cities[i].superPower = (float)(cities[i].population) + cities[i].area + cities[i].numTouristicPoints + cities[i].gdp + cities[i].hdi + cities[i].gdpCapita;
        cities[i].superPower -= (abs(cities[i].yearOfFoundation) + cities[i].popDen); //abs gets the absolute value, not the sign

        
        //now, let's show the user the city's infos.
        printf("\n");
        printf("OK, city %d finished! Let's check:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %.lf \n", cities[i].population);
        printf("City's Area: %.2f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %.lf \n", cities[i].gdp);
        printf("City's HDI: %.3f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);
        printf("City's Populational Density: %.2f \n", cities[i].popDen);
        printf("City's GDP per Capita: %.2f \n", cities[i].gdpCapita);
        printf("City's Super Power: %.2f \n", cities[i].superPower);
        
    }
}

void checkCards(int numOfCards){
    
    printf("\nEverything finished! Let's check all the cards.\n");
   
    // "Press Enter to continue" function
    while (getchar() != '\n'); //clear everything
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // wait for user to press enter
    printf("\n"); // just to make it more beautyful :D

    //now, I want to show everything again to the user, all the cards. just to check if everything is well saved.
    for (int i = 0; i < numOfCards; i++){
        
        printf("___________________________________\n");
        printf("City number %d:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %.lf \n", cities[i].population);
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

}

int searchCard(int numOfCards, char cityName [50]){

    int index = 0;
    bool exists = false;

    for (int i = 0; i < numOfCards; i++){ //this for is for searching for the data inside the cities struct
                            
        if (strcasecmp(cities[i].name, cityName) == 0){ /*this function compares each of the data. if it's the same, returns 0, if not, -1.
                                                                I changed the function, bc it was case sensitive. this now is case-insensitive */
            index = i;
            exists = true;
        }
        if (exists)
            i = numOfCards;
    }

    if (exists)
        return index;
    else
        return 99;

}

void compareCards(int numOfCards, char city1 [50], char city2 [50]){
    
    int attribute1 = 0;
    int attribute2 = 0;
    float attributeCity1 = 0;
    float attributeCity2 = 0;
    int score = 0;
    int scoreCity1 = 0;
    int scoreCity2 = 0;
    int count1;
    int count2;
        
    //repeat until user type a valid number
    do {

        //gets attribute to compare
        printf("\n");
        printf("\n");
        printf("What attribute would you like to compare first?\n");
        printf("1. Population\n2. Area\n3. Touristic Points\n4. GDP\n5. HDI\n6. Year of Foundation\n");
        printf("7. Populational Density\n8. GDP per Capita\n9. Super Power\n10. Return to main menu\nYour choise: ");
        scanf("%d", &attribute1);
        printf("\n");
        printf("\n");
            

        switch (attribute1){
                
        case 1: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].population;
            attributeCity2 = cities[count2].population;

            score = compareBiggerAttribute(cities[count1].population, cities[count2].population, city1, city2, "Population");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);
                        
            break;
                    
        case 2: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].area;
            attributeCity2 = cities[count2].area;

            score = compareBiggerAttribute(cities[count1].area, cities[count2].area, city1, city2, "Area");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 3: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].numTouristicPoints;
            attributeCity2 = cities[count2].numTouristicPoints;

            score = compareBiggerAttribute(cities[count1].numTouristicPoints, cities[count2].numTouristicPoints, city1, city2, "Touristic Points");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 4: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].gdp;
            attributeCity2 = cities[count2].gdp;

            score = compareBiggerAttribute(cities[count1].gdp, cities[count2].gdp, city1, city2, "GDP");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 5: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].hdi;
            attributeCity2 = cities[count2].hdi;

            score = compareBiggerAttribute(cities[count1].hdi, cities[count2].hdi, city1, city2, "HDI");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 6: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].yearOfFoundation;
            attributeCity2 = cities[count2].yearOfFoundation;

            score = compareSmallerAttribute(cities[count1].yearOfFoundation, cities[count2].yearOfFoundation, city1, city2, "Year of Foundation");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 7: ; //i had to put semi-colon here to avoid label error
                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].popDen;
            attributeCity2 = cities[count2].popDen;

            score = compareSmallerAttribute(cities[count1].popDen, cities[count2].popDen, city1, city2, "Populational Density");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 8: ; //i had to put semi-colon here to avoid label error
                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].gdpCapita;
            attributeCity2 = cities[count2].gdpCapita;

            score = compareBiggerAttribute(cities[count1].gdpCapita, cities[count2].gdpCapita, city1, city2, "GDP per Capita");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 9: ; //i had to put semi-colon here to avoid label error
                                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].superPower;
            attributeCity2 = cities[count2].superPower;

            score = compareBiggerAttribute(cities[count1].superPower, cities[count2].superPower, city1, city2, "Super Power");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
            
        case 10: ; //i had to put semi-colon here to avoid label error

            printf("Returing to main menu...\n");
            break;
                    
        default:
            printf("Humm... Seems like you typed something strange to me. Please, choose between 1 and 10 :D\n");
            break;

        }
    }
    while (attribute1 != 1 && attribute1 != 2 && attribute1 != 3 && attribute1 != 4 && attribute1 != 5 && attribute1 != 6 && attribute1 != 7 && attribute1 != 8 &&  attribute1 != 9 && attribute1 != 10);
    
    if (attribute1 == 10)
        return;

    printf("\n");
    printf("And the second attribute?\n");
    printf("1. Population\n2. Area\n3. Touristic Points\n4. GDP\n5. HDI\n6. Year of Foundation\n");
    printf("7. Populational Density\n8. GDP per Capita\n9. Super Power\n10. Return to main menu\nYour choise: ");
    printf("Your choise: ");
    scanf("%d", &attribute2);
    printf("\n");

    do{

        if(attribute1 == attribute2){
                
            do{
                printf("\n");
                printf("Please, type a different attribute to compare.\n");
                printf("1. Population\n2. Area\n3. Touristic Points\n4. GDP\n5. HDI\n6. Year of Foundation\n");
                printf("7. Populational Density\n8. GDP per Capita\n9. Super Power\nYour choise: ");
                scanf("%d", &attribute2);
                printf("\n");
                printf("\n");
            }
            while(attribute1 == attribute2);

        }

        switch (attribute2){
                
        case 1: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].population;
            attributeCity2 = cities[count2].population;

            score = compareBiggerAttribute(cities[count1].population, cities[count2].population, city1, city2, "Population");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);
         
            break;
                    
        case 2: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].area;
            attributeCity2 = cities[count2].area;

            score = compareBiggerAttribute(cities[count1].area, cities[count2].area, city1, city2, "Area");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 3: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].numTouristicPoints;
            attributeCity2 = cities[count2].numTouristicPoints;

            score = compareBiggerAttribute(cities[count1].numTouristicPoints, cities[count2].numTouristicPoints, city1, city2, "Touristic Points");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 4: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].gdp;
            attributeCity2 = cities[count2].gdp;

            score = compareBiggerAttribute(cities[count1].gdp, cities[count2].gdp, city1, city2, "GDP");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 5: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].hdi;
            attributeCity2 = cities[count2].hdi;

            score = compareBiggerAttribute(cities[count1].hdi, cities[count2].hdi, city1, city2, "HDI");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 6: ; //i had to put semi-colon here to avoid label error

            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].yearOfFoundation;
            attributeCity2 = cities[count2].yearOfFoundation;

            score = compareSmallerAttribute(cities[count1].yearOfFoundation, cities[count2].yearOfFoundation, city1, city2, "Year of Foundation");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 7: ; //i had to put semi-colon here to avoid label error
                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].popDen;
            attributeCity2 = cities[count2].popDen;

            score = compareSmallerAttribute(cities[count1].popDen, cities[count2].popDen, city1, city2, "Populational Density");
                
            if(score == 1){

                scoreCity1++;

            } 
            else if (score == 2){

                 scoreCity2++;

            } 
                else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 8: ; //i had to put semi-colon here to avoid label error
                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].gdpCapita;
            attributeCity2 = cities[count2].gdpCapita;

            score = compareBiggerAttribute(cities[count1].gdpCapita, cities[count2].gdpCapita, city1, city2, "GDP per Capita");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

            break;
                    
        case 9: ; //i had to put semi-colon here to avoid label error
                                
            count1 = searchCard(numOfCards, city1);
            count2 = searchCard(numOfCards, city2);

            attributeCity1 = cities[count1].superPower;
            attributeCity2 = cities[count2].superPower;

            score = compareBiggerAttribute(cities[count1].superPower, cities[count2].superPower, city1, city2, "Super Power");
                
            if(score == 1){

                scoreCity1++;
            } 
            else if (score == 2){

                scoreCity2++;

            } 
            else {

                scoreCity1++;
                scoreCity2++;

            }

            printf("\n");
            printf("\n");
            printf("Score:\n%s %d x %s %d\n", city1, scoreCity1, city2, scoreCity2);

                break;
            
        case 10: ; //i had to put semi-colon here to avoid label error

            printf("Returing to main menu...\n");
            break;
                    
        default: ; //i had to put semi-colon here to avoid label error
            printf("Humm... Seems like you typed something strange to me. Please, choose between 1 and 10 :D\n");
            break;

    }

    }
    while(attribute2 != 1 && attribute2 != 2 && attribute2 != 3 && attribute2 != 4 && attribute2 != 5 && attribute2 != 6 && attribute2 != 7 && attribute2 != 8 &&  attribute2 != 9 && attribute2 != 10);

    if (attribute1 == 10)
        return;

    if(scoreCity1 > scoreCity2){

        printf("%s is the winner!\n", city1);

    } else if (scoreCity2 > scoreCity1){

        printf("%s is the winner!\n", city2);

    } else {

        printf("That's a draw!");

    }

}


int main() {
    
    int totalNumCities = 0; //total number of cities. will be determined by the user
    int mainMenu = 0; //main menu option
    printf("Welcome to Super Trunfo by MateCheck! It's a pleasure to have you here.\n");

    do{
        
        printf("Please, choose the option to continue: \n");
        printf("1. Play!\n2. Game Rules\n3. Exit\nYour option: ");
        scanf("%d", &mainMenu);

        switch (mainMenu){
            
            //game option
            case 1: ; //i had to put semi-colon here to avoid label error  

                char continuePlaying; // variable to continue playing (Y or N)
                char sameCards; //variable of maintaing to play with the same 2 cards (Y or N)
                printf("\n");

                printf("How many cards will be in the game? (min: 2, max: 32)\n");
                printf("Number: ");
                scanf("%d", &totalNumCities);

                if(totalNumCities < 2 || totalNumCities > 32){
                    
                    do{

                        printf("\n");
                        printf("Number invalid. Please choose between 2 and 32.\n");
                        printf("Number: ");
                        scanf("%d", &totalNumCities);
                
                    }
                    while(totalNumCities < 2 || totalNumCities > 32);
                }

                collectCards(totalNumCities);

                checkCards(totalNumCities);
                
                printf("\nOK! Now, let's play. :D \n");
    
                // "Press Enter to continue" function
                printf("Press Enter to continue...");
                while (getchar() != '\n');
                printf("\n");

                char card1 [50];
                char card2 [50];

                do{
                    getchar();
                    //gets what is the first city to compare
                    printf("Type the name of the first city: ");
                    //same code as up there in first "for"
                    fgets(card1, sizeof(card1), stdin);
                    card1[strcspn(card1, "\n")] = 0;
                    printf("\n"); //just skip a line

                    int proof = searchCard(totalNumCities, card1);
                    do{

                        if(proof == 99){

                            printf("City not found. Please type a valid city: ");
                            fgets(card1, sizeof(card1), stdin);
                            card1[strcspn(card1, "\n")] = 0;
                            printf("\n"); //just skip a line
                            proof = searchCard(totalNumCities, card1);

                        }

                    }
                    while(proof == 99);

                    

                    //second city to compare
                    printf("Type the name of the second city: ");
                    fgets(card2, sizeof(card2), stdin);
                    card2[strcspn(card2, "\n")] = 0;
                    printf("\n"); //just skip a line

                    proof = searchCard(totalNumCities, card2);
                    do{

                        if(proof == 99){

                            printf("City not found. Please type a valid city: ");
                            fgets(card2, sizeof(card2), stdin);
                            card2[strcspn(card2, "\n")] = 0;
                            printf("\n"); //just skip a line
                            proof = searchCard(totalNumCities, card2);

                        }

                    }
                    while(proof == 99);
                    
                    do{

                        compareCards(totalNumCities, card1, card2);
                        printf("\n\n");
                        getchar();
                        printf("Would you like to play with the same cards? (Y to continue, anything to stop)\n");
                        printf("Answer: ");
                        scanf("%c", &sameCards);
                        printf("\n");

                    } 
                    while (sameCards == 'Y' || sameCards == 'y');
                   
                    printf("\n\n");
                    getchar();
                    printf("Would you like to continue playing and choose different cards? (Y to continue, anything to stop) \n");
                    printf("Answer: ");
                    scanf("%c", &continuePlaying);
                    printf("\n");

                }
                while(continuePlaying == 'Y' || continuePlaying == 'y');

                break;

            //rules option
            case 2: ; //i had to put semi-colon here to avoid label error 
                
                printf("'Super Trunfo - Countries' is a card game about countries would feature cards representing different nations"); 
                printf("each with various attributes such as population, area, GDP, HDI, military power, or tourist attractions."); 
                printf("Players take turns choosing an attribute from their card to compare with their opponent’s card.");
                printf("The player with the highest (or lowest, depending on the rule) value wins the round and gains a point"); 
                printf("The game finished when a player hits 2 points!\n\n");
                printf("First: Register all the cards and cards informations;\n");
                printf("Second: Choose the cards that you want to comparate by typing the name of the cities;\n");
                printf("Third: Choose the 2 attributes to compare;\n");
                printf("Fourth: The system will compare both cards and declare the winner of the round!\n");
                printf("\n \n");

                break;
            
            //finish option
            case 3: ; //i had to put semi-colon here to avoid label error 
                
                printf("MateCheck thanks you for using our game! Exiting program...");
                printf("\n \n");
                
                break;
            
            default:
                
                printf("Ops, I didn't get it. Try a valid option!\n");
                break;
        }

    } while (mainMenu != 3);

    return 0;
}
