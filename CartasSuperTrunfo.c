#include <stdio.h>
#include <string.h>

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
    */
// i have searched for a better way to define the cities, so then I don't have to declare so many variables. this function "struct" seems like a good alternative
struct City { 

    //scanned from terminal
    char name[50];
    int population;
    float area;
    int numTouristicPoints;
    float gdp;
    float hdi;
    int yearOfFoundation; // remember when printing and scanning to show the negative sign, indicating BCE and CE
    char code [3]; //city code (first data is A to H, second is 01 to 04)

    //calculated automatically in the algorythm with data from user
    float gdpCapita; //divide GDP/population
    float popDen; //populational density, calculate population/area

};

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
        scanf("%s", cities[i].code);

        printf("Type the city's %d POPULATION: (FORMAT: full number ex: 2000000 for 2 milion)\n", i+1);
        getchar(); //clears any space in terminal before scanf
        scanf("%d", &cities[i].population);

        printf("Type the city's %d AREA: (FORMAT: full number ex: 2000000 for 2 milion m²)\n", i+1);
        getchar();
        scanf(" %f", &cities[i].area);

        printf("Type the city's %d NUMBER OF TOURISTIC POINTS:\n", i+1);
        getchar();
        scanf(" %d", &cities[i].numTouristicPoints);

        printf("Type the city's %d GDP:\n", i+1);
        getchar();
        scanf(" %f", &cities[i].gdp);

        printf("Type the city's %d HDI:\n", i+1);
        getchar();
        scanf(" %f", &cities[i].hdi);

        printf("Type the city's %d YEAR OF FOUNDATION:\n", i+1);
        getchar();
        scanf(" %d", &cities[i].yearOfFoundation);
        
        printf("OK, city %d finished! Let's check:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %d \n", cities[i].population);
        printf("City's Area: %f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %f \n", cities[i].gdp);
        printf("City's HDI: %f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);

    }




    
    
    // Cadastro das Cartas:
    // Sugestão: Utilize a função scanf para capturar as entradas do usuário para cada atributo.
    // Solicite ao usuário que insira as informações de cada cidade, como o código, nome, população, área, etc.
    
    // Exibição dos Dados das Cartas:
    // Sugestão: Utilize a função printf para exibir as informações das cartas cadastradas de forma clara e organizada.
    // Exiba os valores inseridos para cada atributo da cidade, um por linha.

    return 0;
}
