#include <stdio.h>
#include <string.h>

#define QUESTION_MAX_COUNT 10
#define QUESTION_DESCRIPTION_MAX_LENGTH 256
#define QUESTION_ANSWER_RESPONSE_TEXT_MAX_LENGTH 256
#define QUESTION_ANSWER_MAX_LENGTH 12
#define QUESTION_ANSWER_MAX_COUNT 3

struct question
{
    int id;
    char description[QUESTION_DESCRIPTION_MAX_LENGTH];
    char answers[QUESTION_ANSWER_MAX_COUNT][QUESTION_ANSWER_MAX_LENGTH];
    int correct;
};

struct quiz
{
    int n;
    struct question questions[QUESTION_MAX_COUNT];
    int correct[QUESTION_MAX_COUNT];
    int total_points;
};

struct answer_response
{
    int correct;
    char text[QUESTION_ANSWER_RESPONSE_TEXT_MAX_LENGTH];
};

int answer_char_to_int(char answer_char)
{
    return answer_char - 'a';
}

char answer_int_to_char(int answer_int)
{
    return answer_int + 'a';
}

void quiz_create_questions(struct question questions[], int *n)
{
    int i = 0;

    questions[i].id = i;
    strncpy(questions[i].description, "Które ze środowisk wykorzystuje inną bibliotekę niż pozostałe?", QUESTION_DESCRIPTION_MAX_LENGTH);
    strncpy(questions[i].answers[0], "MATE", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[1], "GNOME", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[2], "KDE", QUESTION_ANSWER_MAX_LENGTH);
    questions[i].correct = 2;

    i++;

    questions[i].id = i;
    strncpy(questions[i].description, "Licencją FLOSS nie jest licencja?", QUESTION_DESCRIPTION_MAX_LENGTH);
    strncpy(questions[i].answers[0], "freeware", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[1], "BSD", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[2], "GPL", QUESTION_ANSWER_MAX_LENGTH);
    questions[i].correct = 0;

    i++;

    questions[i].id = i;
    strncpy(questions[i].description, "Komercyjne pochodne Uniksa AT&T bazują na systemie o nazwie?", QUESTION_DESCRIPTION_MAX_LENGTH);
    strncpy(questions[i].answers[0], "Release 3", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[1], "System V ", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[2], "AIX", QUESTION_ANSWER_MAX_LENGTH);
    questions[i].correct = 1;

    i++;

    questions[i].id = i;
    strncpy(questions[i].description, "Shell Bourne'a to pełna nazwa shella?", QUESTION_DESCRIPTION_MAX_LENGTH);
    strncpy(questions[i].answers[0], "sh", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[1], "csh", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[2], "ksh", QUESTION_ANSWER_MAX_LENGTH);
    questions[i].correct = 0;

    i++;

    questions[i].id = i;
    strncpy(questions[i].description, "Zgodnie w powszechnie przyjętą konwencją znak zachęty w shellu zwykłego użytkownika kończy się znakiem?", QUESTION_DESCRIPTION_MAX_LENGTH);
    strncpy(questions[i].answers[0], "@", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[1], "#", QUESTION_ANSWER_MAX_LENGTH);
    strncpy(questions[i].answers[2], "$", QUESTION_ANSWER_MAX_LENGTH);
    questions[i].correct = 0;

    *n = i + 1;
}

void quiz_print_answer_index_string(char answer_char)
{
    switch (answer_char)
    {
    case 'a':
        printf("B27");
        break;
    case 'b':
        printf("B47");
        break;
    case 'c':
        printf("B11");
        break;
    default:
        printf("NONE");
    }
}

void quiz_print_question(struct question questions[], int i)
{
    printf("\n");
    printf("PYTANIE %d. %s\n", questions[i].id, questions[i].description);

    for (int j = 0; j < QUESTION_ANSWER_MAX_COUNT; j++)
    {
        quiz_print_answer_index_string(answer_int_to_char(j));
        printf(") %s\n", questions[i].answers[j]);
    }

    printf("\n");
}

void quiz_reset_answers(struct quiz *quiz)
{
    for (int i = 0; i < quiz->n; i++)
    {
        quiz->correct[i] = -1;
    }

    quiz->total_points = 0;
}

void quiz_read_user_answer(int *user_answer)
{
    char ans[QUESTION_ANSWER_MAX_LENGTH];

    printf("Naciśnij odpowiedni przycisk: ");
    scanf("%s", ans);
    *user_answer = answer_char_to_int(ans[0]);
}

void quiz_answer_question(struct quiz *quiz, int i, int user_answer, struct answer_response *response)
{
    if (user_answer == quiz->questions[i].correct)
    {
        snprintf(response->text, QUESTION_ANSWER_RESPONSE_TEXT_MAX_LENGTH, "Brawo! Dobra odpowiedź!");
        quiz->total_points++;
    }
    else
    {
        snprintf(response->text, QUESTION_ANSWER_RESPONSE_TEXT_MAX_LENGTH, "Zła odpowiedź!");
    }
}

void quiz_answer_print_response(struct answer_response *response)
{
    printf("%s\n", response->text);
}

int main(int argc, char **argv)
{
    char ans_c = 'b';
    char ans_i = 2;

    struct quiz quiz;

    quiz_create_questions(quiz.questions, &quiz.n);
    quiz_reset_answers(&quiz);

    printf("%c -> %d\n", ans_c, answer_char_to_int(ans_c));
    printf("%d -> %c\n", ans_i, answer_int_to_char(ans_i));

    for (int i = 0; i < quiz.n; i++)
    {
        struct answer_response response;
        int user_answer;

        quiz_print_question(quiz.questions, i);
        quiz_read_user_answer(&user_answer);
        quiz_answer_question(&quiz, i, user_answer, &response);
        quiz_answer_print_response(&response);
    }

    return 0;
}
