//
//  main.c
//  horses
//
//  Created by Jeffrey Thompson on 2/8/16.
//  Copyright © 2016 Jeffrey Thompson. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define PREDEFINED_INPUT
//#define SAVE_DYNAMIC

#ifdef PREDEFINED_INPUT
size_t horse_count = 9;
size_t stable_count = 2;
char* horses = "010001110";
#endif

size_t min(size_t a, size_t b){
    return a < b ? a : b;
}

enum color {WHITE = 0, BLACK = 1, NONE};
typedef enum color Color;

struct result{
    size_t so_far;
    Color color[2];
};
typedef struct result Result;

Color decode(char ch){
    return ch-'0';
}

void initResult(Result* put_here, const Result* copy_this){
    if(copy_this){
        put_here->so_far = copy_this->so_far;
        put_here->color[WHITE] = copy_this->color[WHITE];
        put_here->color[BLACK] = copy_this->color[BLACK];
    }
    else{
        put_here->so_far = 0;
        put_here->color[WHITE] = 0;
        put_here->color[BLACK] = 0;
    }
}

size_t scoreResult(const Result* score_this){
    return score_this->so_far + score_this->color[WHITE] * score_this->color[BLACK];
}

void addResult(Result* put_here, const Result* from_this, Color horse){
    initResult(put_here,from_this);
    if(horse != NONE)
        ++put_here->color[horse];
}

void nextResult(Result* put_here, const Result* from_this, Color horse){
    initResult(put_here, NULL);
    put_here->so_far = scoreResult(from_this);
    if(horse != NONE)
        ++put_here->color[horse];
}



size_t dpHorses(const char* colors, size_t horse_count, size_t stable_count){
#ifdef SAVE_DYNAMIC
    Result** DP = (Result**)malloc(sizeof(Result*)*horse_count);
    for(size_t i = 0 ; i < horse_count; ++i){
        DP[i] = (Result*)malloc(sizeof(Result)*stable_count);
    }
#else
    Result DP[horse_count][stable_count];
#endif
    for(size_t horse_num = 0; horse_num<horse_count; ++horse_num){
        size_t top = min(stable_count, horse_num+1);
        for(size_t stable_num = 0; stable_num < top; ++stable_num){
            Color horse = decode(colors[horse_num]);
            if(horse_num == 0 || stable_num == horse_num){
                addResult(&DP[horse_num][stable_num], NULL, horse);
            }
            else if(stable_num == 0){
                addResult(&DP[horse_num][stable_num], &DP[horse_num-1][stable_num], horse);
            }
            else{
                Result a, b;
                addResult(&a, &DP[horse_num-1][stable_num], horse);
                nextResult(&b, &DP[horse_num-1][stable_num-1], horse);
                if( scoreResult(&a) < scoreResult(&b) ){
                    initResult(&DP[horse_num][stable_num], &a);
                }
                else{
                    initResult(&DP[horse_num][stable_num], &b);
                }
                
            }
        }
    }
    size_t score = scoreResult(&DP[horse_count-1][stable_count-1]);
#ifdef SAVE_DYNAMIC
    for(size_t i = 0 ; i < horse_count; ++i){
        free(DP[i]);
    }
    free(DP);
#endif
    return score;
}



int main(int argc, const char * argv[]) {
#ifndef PREDEFINED_INPUT
    size_t horse_count;
    size_t stable_count;
    char* horses;
    
    printf("Enter two positive intergers (horse_count stable_count) :");
    scanf("%zu %zu", &horse_count, &stable_count);
    
    horses = malloc(sizeof(char)*(horse_count+1));
    printf("Enter a string of 0's and 1's representing the horses (0=white,1=black)\n:");
    scanf("%s",horses);
#endif
    size_t ans = dpHorses(horses, horse_count, stable_count);
    printf("\nanswer: %zu\n",ans);
    return 0;
}
