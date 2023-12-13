#include <stdio.h>

int main() {
    
    int numberOfPeople;
    printf("Type number of people: \n");
    scanf("%d", &numberOfPeople);
    
    int treshold = 10;
    int choices[] = {0, 0, 0, 0, 0};
    int number;
    
    if(numberOfPeople == 1){
        printf("You can order everything!");
        return 0;
    }
    
    for(int i =0; i<numberOfPeople;i++){
        printf("Person : %d \n",(i+1));
        printf("What would you like to eat today?\nOrder the meals from 1 to 5\n");
        printf("\n1-Kebap\n2-Burger\n3-Pasta\n4-Lahmacun\n5-Salad\n"); 
        for(int j = 0; j<5;j++){
           printf("Choice %d ", j+1);
           scanf("%d", &number);
           if(number == 1 || number == 2 || number == 3 || number == 4 || number == 5 ){
                if(j == 0){
                    choices[number-1] += 5;
                }else if(j == 1){
                  choices[number-1] += 4;
                }else if(j == 2){
                    choices[number-1] += 3;
                }else if(j == 3){
                    choices[number-1] += 2;
                }else if(j == 4){
                    choices[number-1] += 1;
                }
           }else{
               printf("The integer must be between 1 and 5!!");
               j--;
           }
        }
    }
    //for printing the order points
    for (int i = 0; i<5;i++){
        printf("%d ", choices[i]);
    }
    printf("\n");
    
    int size = sizeof(choices)/sizeof(choices[0]);
    
    int valuesPassTreshold[] = {0, 0, 0, 0, 0};
    int yesValues;
    int noValues;
    for(int i = 0; i<size ; i++ ){
        if(treshold < choices[i]){
            valuesPassTreshold[i]++;
            yesValues++;
        }else{
            noValues++;   //eğer geçen değer yoksa noValuesi arttır
        }
    }
    
    if(yesValues == 1){
        for(int i = 0; i< size; i++){
            if(valuesPassTreshold[i]){
                if(i == 0){
                    printf("You are eating Kebap! \n");
                }else if(i == 1){
                    printf("You are eating Burger! \n");
                }else if(i == 2){
                    printf("You are eating Pasta! \n");
                }else if(i == 3){
                    printf("You are eating Lahmacun! \n");
                }else if(i == 4){
                    printf("You are eating Salad! \n");
                }
            }
        }
        return 0;
    }else if(yesValues == 0){
        printf("You are eating at home/dorm today!");
        return 0;
    }
    
    int secondChoiceMenu[yesValues];
    
    int incrementIndex = 0;
    if(noValues != size){
        for(int i = 0; i< size; i++){
            if(valuesPassTreshold[i]){
                if(i == 0){
                    printf("Kebap: %d \n", choices[i]);
                    secondChoiceMenu[incrementIndex] = 0;
                    incrementIndex++;
                }else if(i == 1){
                    printf("Burger: %d \n", choices[i]);
                    secondChoiceMenu[incrementIndex] = 1;
                    incrementIndex++;
                }else if(i == 2){
                    printf("Pasta: %d \n", choices[i]);
                    secondChoiceMenu[incrementIndex] = 2;
                    incrementIndex++;
                }else if(i == 3){
                    printf("Lahmacun: %d \n", choices[i]);
                    secondChoiceMenu[incrementIndex] = 3;
                    incrementIndex++;
                }else if(i == 4){
                    printf("Salad: %d \n", choices[i]);
                    secondChoiceMenu[incrementIndex] = 4;
                    incrementIndex++;
                }
            }
            choices[i] = 0; //to refresh the scores
        }
    }
    
    //second round
    printf("Second round! \n");
    printf("Now, choose and order your choices from the besties list \n");

    int k = 0;
    int number2 = 0;
    int point = size;
    for (int i = 0; i< numberOfPeople; i++){
        printf("Person : %d \n",(i+1));
        
        for(int j = 0; j < yesValues ; j++){
            if(secondChoiceMenu[j] == 0){
                printf("%d -Kebap \n", (j+1));
            }else if(secondChoiceMenu[j] == 1){
                printf("%d -Burger \n",(j+1)); 
            }else if(secondChoiceMenu[j] == 2){
                printf("%d -Pasta \n",(j+1));   
            }else if(secondChoiceMenu[j] == 3){
                printf("%d -Lahmacun \n",(j+1));
            }else if(secondChoiceMenu[j] == 4){
                printf("%d -Salad \n",(j+1)); 
            }
        }
        point = size;
        for(int j = 0; j < yesValues ; j++){
            printf("Choice %d: ", ((j+1)));
            scanf("%d", &number2);
            int dummy = secondChoiceMenu[number2-1];
            choices[dummy] += point;
            point--;
        }
    }
    for(int i = 0; i<yesValues; i++){
        if(secondChoiceMenu[i] == 0){
                printf("Kebap %d \n", choices[0]);
            }else if(secondChoiceMenu[i] == 1){
                printf("Burger %d \n", choices[1]); 
            }else if(secondChoiceMenu[i] == 2){
                printf("Pasta %d \n", choices[2]);   
            }else if(secondChoiceMenu[i] == 3){
                printf("Lahmacun %d \n", choices[3]);
            }else if(secondChoiceMenu[i] == 4){
                printf("Salad %d \n", choices[4]); 
            }
    }
    
    //finding the top one 
    int max = choices[0];
    int index = 0;
    for(int i = 1; i< size; i++){
        if(choices[i] > max){
            max = choices[i];
            index = i;
        }
    }
    
    if(index == 0){
        printf("You are eating Kebap");
    }else if(index == 1){
        printf("You are eating Burger");
    }else if(index == 2){
        printf("You are eating Pasta");
    }else if(index == 3){
        printf("You are eating Lahmacun");
    }else if(index == 4){
        printf("You are eating Salad");
    }else{
        printf("Error occured!");
    }

    return 0;
}