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

        printf("Type the city's %d AREA: (FORMAT: full number ex: 2000000 for 2 milion km²)\n", i+1);
        getchar();
        scanf("%f", &cities[i].area);

        printf("Type the city's %d NUMBER OF TOURISTIC POINTS:\n", i+1);
        getchar();
        scanf(" %d", &cities[i].numTouristicPoints);

        printf("Type the city's %d GDP:\n", i+1);
        getchar();
        scanf("%f", &cities[i].gdp);

        printf("Type the city's %d HDI:\n", i+1);
        getchar();
        scanf(" %f", &cities[i].hdi);

        printf("Type the city's %d YEAR OF FOUNDATION:\n", i+1);
        getchar();
        scanf(" %d", &cities[i].yearOfFoundation);

        //now that I coul get all the data, let's calculate popDen and gdpCapita

        cities[i].popDen = cities[i].population/cities[i].area; //calculate popDen

        cities[i].gdpCapita = cities[i].gdp/cities[i].population; //calculate gdp Per Capita


        //now, let's show the user the city's infos.
        printf("OK, city %d finished! Let's check:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %d \n", cities[i].population);
        printf("City's Area: %.2f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %.2f \n", cities[i].gdp);
        printf("City's HDI: %.3f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);
        printf("City's Populational Density: %.2f \n", cities[i].popDen);
        printf("City's GDP per Capita: %.2f \n", cities[i].gdpCapita);
        
        
        // "Press Enter to continue" function
        getchar(); //clear everything
        printf("\nPress Enter to continue...");
        getchar(); // wait for user to press enter
        printf("\n"); // just to make it more beautyful :D

        //and repeat!
    }

    printf("\n \n \nEverything finished! Let's check all the cards (press enter to continue):\n");
    getchar();

    //now, I want to show everything again to the user, all the cards. just to check if everything is well saved.
    for (int i = 0; i < totalNumCities; i++){
        
        printf("___________________________________\n");
        printf("City number %d:\n", i+1);
        printf("City's Name: %s \n", cities[i].name);
        printf("City's Code: %s \n", cities[i].code);
        printf("City's Population: %d \n", cities[i].population);
        printf("City's Area: %.2f \n",  cities[i].area);
        printf("City's Number of Touristic Points: %d \n", cities[i].numTouristicPoints);
        printf("City's GDP: %.2f \n", cities[i].gdp);
        printf("City's HDI: %.3f \n", cities[i].hdi);
        printf("City's Year of Foundation: %d \n", cities[i].yearOfFoundation);
        printf("City's Populational Density: %.2f \n", cities[i].popDen);
        printf("City's GDP per Capita: %.2f \n", cities[i].gdpCapita);
        printf("___________________________________\n");

    }

    


    /*No nível Mestre, você implementará comparações entre as cartas, utilizando operadores relacionais e manipulando grandes números com precisão.
    🆕 Diferença em relação ao Nível Aventureiro:
    Comparação de Cartas:
    O sistema permitirá ao usuário comparar duas cartas com base nas propriedades inseridas e calculadas.
    Cada carta terá um "Super Poder", que é a soma de todas as propriedades.
    ⚙️ Funcionalidades do Sistema:
    O sistema utilizará operadores relacionais para determinar a carta vencedora com base nas propriedades comparadas.
    A comparação considerará:
    Densidade Populacional: Vence a carta com menor valor.
    Outras Propriedades: Vence a carta com maior valor.
    O resultado das comparações será exibido claramente para cada propriedade.
    📥 Entrada e 📤 Saída de Dados:
    O usuário insere as cartas a serem comparadas.
    O sistema exibe os resultados das comparações, indicando a carta vencedora para cada propriedade.*/

    return 0;
}
