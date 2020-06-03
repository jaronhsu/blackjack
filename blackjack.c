#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int rng(){
    return rand()%13 + 1;
}

char conv(int n){
    if (n == 1){
        return 'A';
    }
    else if (n == 2){
        return '2';
    }
    else if (n == 3){
        return '3';
    }
    else if (n == 4){
        return '4';
    }
    else if (n == 5){
        return '5';
    }
    else if (n == 6){
        return '6';
    }
    else if (n == 7){
        return '7';
    }
    else if (n == 8){
        return '8';
    }
    else if (n == 9){
        return '9';
    }
    else if (n == 10){
        return 'T';
    }
    else if (n == 11){
        return 'J';
    }
    else if (n == 12){
        return 'Q';
    }
    else if (n == 13){
        return 'K';
    }
    else{
        return 'N';
    }
}

int sum(int handNums[], int n){
    int sum = 0;
    for (int y = 0; y < n; y++){
        if (handNums[y] <= 10){
            sum += handNums[y];
        }
        else {
            sum += 10;
        }
    }
    return sum;
}

int main(){
    char placeholder = '`';
    srand(time(NULL));// aka time(0)
    printf("Welcome to single player blackjack.\n");
    printf("Type 'hit' or 'stand' to play.\n");
    printf("Minimum bet is $100.\n");
    printf("You have $5000 to start with.\n");
    printf("Press the enter key to start.\n");
    scanf("%c", &placeholder);
    system("cls");
    int pMoney = 5000;
    int pBet = 100;
    int qPCards = 0;
    int qDCards = 0;
    int gameCount = 0;
    char playerInput[6] = "     ";

    for(int i = 0; i <= gameCount; i++){
        printf("You have $%d. Enter bet amount (min: $100, max: $1000): ", pMoney);
        scanf("%d", &pBet);
        if (pBet <= 100){
            system("cls");
            pBet = 100;
            printf("Player bet: $%d\n",pBet);
        }
        else if ((pBet <=pMoney) && (pBet > 1000)){
            system("cls");
            pBet = 1000;
            printf("Player bet: $%d\n",pBet);
        }
        else if (pBet >= pMoney){
            system("cls");
            pBet = pMoney;
            printf("Player bet: $%d\n", pBet);
        }
        else {
            system("cls");
            printf("Player bet: $%d\n", pBet);
        }

        int pNums[7] = {rng(), rng(), rng(), rng(), rng(), rng()};
        int dNums[7] = {rng(), rng(), rng(), rng(), rng(), rng()};
        char pCards[7] = {conv(pNums[0]), conv(pNums[1]), conv(pNums[2]), conv(pNums[3]), conv(pNums[4]), conv(pNums[5])};
        char dCards[7] = {conv(dNums[0]), conv(dNums[1]), conv(dNums[2]), conv(dNums[3]), conv(dNums[4]), conv(dNums[5])};

        printf("Dealer's cards: %c and ?\n", dCards[0]);
        printf("Your cards: %c and %c\n", pCards[0], pCards[1]);
        printf("Your sum: %d\n\n", sum(pNums, 2));

        for (int x = 2; x <= 9; x++) {
            printf("Type 'hit' or 'stand'.\n");
            scanf("%s", playerInput);

            if (0 == strcmp("hit", playerInput)){
                printf("New card: %c\n", pCards[x]);
                printf("Your new sum: %d\n", sum(pNums, x + 1));
                if (sum(pNums, x + 1) > 21){
                    qPCards = x + 1;
                    break;
                }
            }
            else if (0 == strcmp("stand", playerInput)){
                qPCards = x;
                break;
            }
            else {printf("incorrect entry.");}
        }
        printf("Player turn over.\n\n");
        sleep(1);
        printf("Dealer's turn\n");
        printf("Dealer's hidden card: %c\n", dCards[1]);

        for (int z = 2; z <= 9; z++){
            printf("Dealer's sum: %d\n", sum(dNums, z));
            if (sum(pNums, qPCards) > 21){
                printf("Dealer stands.\n");
                qDCards = z;
                break;
            }
            else if ((sum (dNums, z) < sum (pNums, qPCards)) && sum(dNums, z) < 21){ //dealer hits
                printf("Dealer hits. New card: %c\n", dCards[z]);
                if (sum(dNums, z + 1) > 21){
                    qDCards = z + 1;
                    break;
                }
            }
            else {
                printf("Dealer stands.\n");
                qDCards = z;
                break;
            }
        }
        printf("Dealer turn over.\n\n");

        sleep(1);


        //--------------------------------WIN DETERMINATION

        printf("Player score: %d\n", sum(pNums, qPCards));
        printf("Dealer score: %d\n\n", sum(dNums, qDCards));

        if (sum(pNums, qPCards) > 21){
            printf("Player busted. Dealer wins.\n");
            pMoney -= pBet;
        }
        else if (sum(dNums, qDCards) > 21){
            printf("Dealer busted. Player wins.\n");
            pMoney += pBet;
        }
        else if (sum(dNums, qDCards) > sum(pNums, qPCards)){
            printf("Dealer wins with higher sum.\n");
            pMoney -= pBet;
        }
        else if (sum(dNums, qDCards) < sum(pNums, qPCards)){
            printf("Player wins with higher sum.\n");
            pMoney += pBet;
        }
        else if (sum(dNums, qDCards) == sum(pNums, qPCards)){
            printf("Push. Bet returned.\n");
        }

        if (pMoney < 100){
            gameCount = i - 1;

            printf("Game over. Insufficient funds to bet.\n");
            printf("You have lost $%d in %d rounds of play.\n", 5000 - pMoney, i + 1);
        }
        else {
            printf("Enter 'c' to continue playing or 'e' to end game.\n");
            char gameEnd[6] = "     ";
            scanf("%s", gameEnd);
            if (0 == strcmp("c", gameEnd)){
                gameCount += 1;
                system("cls");
            }
            else {
                if (pMoney >= 5000){
                    printf("Congratulations! You ended with $%d.\n", pMoney);
                    printf("You made $%d in %d rounds of play.\n", pMoney - 5000, i + 1);
                    break;
                }
                else {
                    printf("Sorry! You ended with $%d.\n", pMoney);
                    printf("You lost $%d in %d rounds of play.\n", 5000 - pMoney, i + 1);
                    break;
                }
            }
        }
    }
    return 0;
}
