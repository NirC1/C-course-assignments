#include <stdio.h>

int main(void) {
    int score;
    int invalid_cnt;

    printf("Please enter the exam score (0-100):\n");

    for (invalid_cnt = 0; invalid_cnt < 3; invalid_cnt++) {

        scanf("%d", &score);

        if (score < 0 || score > 100) {
            if (invalid_cnt < 2) {
                printf("Invalid exam score: %d\n", score);
                printf("Please enter a new exam score in the range 0-100:\n");
                continue;
            } else {
                printf("The user has inserted 3 consecutive times an invalid score.\n");
                printf("Exiting the program!\n");
                return 0;
            }
        }
        else {
            break;
        }
    }

    int score_tens = score / 10;

    switch (score_tens) {
        case 10:
        case 9:
            printf("Grade: A\n");
            printf("Excellent work!\n");
            break;
        case 8:
            printf("Grade: B\n");
            printf("Well done.\n");
            break;
        case 7:
            printf("Grade: C\n");
            printf("Not bad! You can do better..\n");
            break;
        case 6:
            printf("Grade: D\n");
            printf("You passed, but there is room for improvement.\n");
            break;
        case 5:
            printf("Grade: E\n");
            printf("Barely passed - you should work harder next time.\n");
            break;
        default:
            printf("Grade: F\n");
            printf("You Failed - you need to review the material.\n");
            break;
    }

    return 0;
}