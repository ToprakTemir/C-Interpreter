#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Evaluators.c"
#include "Structs.c"
#include "parsing.c"

int main() {

    struct People *people = initializePeople(20);
    struct PlacesList *places = initializePlacesList(20);

    while (1) {

        struct Result *input = parsing();
        if (input->exit)
            break;
        if (!input->isSentenceValid) {
            printf("INVALID");
            input->freeResult(input);
            places->free(places);
            people->free(people);
            continue;
        }

        if (input->isQuestion) {
            if (input->whoAtQuestion) {

            }
            else if (input->totalQuestion) {

            }
            else if (input->totalItemQuestion) {

            }
            else if (input->whereQuestion) {

            }
        }
        else {
            int sentenceCount = 0;
            while (input->sentences[sentenceCount] != NULL) {
                sentenceCount++;
            }

            for (int i = 0; i<sentenceCount; i++) {
                char**** currSentence = input->sentences[i];
                //actions in current sentence
                for (int j = 0; currSentence[0][j] <= currSentence[1][0]; j++) {
                    char*** currAction = &currSentence[0][j];
                    char* actionType;
                    if (strcmp(*currAction[2],"buy") == 0) {
                        if (currAction[3] == NULL)
                            actionType = "buy from";
                        else
                            actionType = "buy";
                    }
                    else if (strcmp(*currAction[2],"sell") == 0) {
                        if (currAction[3] == NULL)
                            actionType = "sell to";
                        else
                            actionType = "sell";
                    }
                    else
                        actionType = "go";


                    actionArgs *arguments = (actionArgs*) calloc(1,sizeof(actionArgs));
                    //subject chain
                    int subjectsChainSize = 0;
                    for (int k = 0; currAction[0][k] <= currAction[1][0] && currAction[0][k] != NULL; k++) {
                        subjectsChainSize++;
                    }
                    char* subjectChain[subjectsChainSize];
                    for (int k = 0; currAction[0][k] <= currAction[1][0] && currAction[0][k] != NULL; k++) {
                        subjectChain[k] = currAction[0][k];
                    }
                    arguments->personChain1 = subjectChain;
                    arguments->personChain1Size = subjectsChainSize;

                    char* subjectChainFromTo;
                    if (strcmp(actionType,"sell to") == 0 || strcmp(actionType,"buy from") == 0) {
                        arguments->personChain2 = currAction[3];
                        arguments->personChain2Size = 1;
                    }

                    //item chain
                    if (strcmp(actionType, "go") == 0) {
                        arguments->place = currAction[4][0];
                    }
                    else {
                        ItemWithQuantity** items = (ItemWithQuantity**) malloc(1024*sizeof(ItemWithQuantity));
                        for (int k = 0; currAction[4][0] + k * sizeof(char *) <= currAction[5][0] &&
                                        currAction[4][0] + k * sizeof(char *) != NULL &&
                                        currAction[4][1] + k * sizeof(char *) <= currAction[5][1] &&
                                        currAction[4][1] + k * sizeof(char *) != NULL; k++) {
                            printf("%d\n",1);
                            ItemWithQuantity *item = (ItemWithQuantity*) malloc(sizeof(ItemWithQuantity));
                            item->name = currAction[4][1] + k * sizeof(char *);
                            item->quantity = atoi(currAction[4][0] + k * sizeof(char *));
                            items[k] = item;
                        }
                        arguments->itemChain = items;
                    }









                    free(arguments);







                }
            }

        }




        input->freeResult(input);
    }

    places->free(places);
    people->free(people);

    return 0;
}