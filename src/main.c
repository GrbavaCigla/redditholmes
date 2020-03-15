#include <ctype.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define SUBREDDIT_COUNT 198

char *countries[SUBREDDIT_COUNT] = {"United Arab Emirates", "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antiqua & Deps", "United Arab Emirates", "Argentina", "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados", "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "Bosna and Herzegovina", "Bolivia", "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina", "Burundi", "Cambodia", "Cameroon", "Canada", "Cape Verde", "Chad", "Chile", "China", "Colombia", "Comoros", "Congo", "Costa Rica", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czech", "Denmark", "Djibouti", "Dominica", "Dominican", "Ecuador", "Egypt", "Eritrea", "Estonia", "Ethiopia", "Fiji", "Finland", "France", "Gabon", "Gambia", "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guyana", "Haiti", "Honduras", "Hungary", "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland", "Israel", "Italy", "Ivory Coast", "Jamaica", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati", "Korea", "Kosovo", "Kuwait", "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Macedonia", "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique", "Myanmar", "Namibia", "Nauru", "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria", "Norway", "Oman", "Papau New Guinea", "Pakistan", "Palau", "Panama", "Paraguay", "Peru", "Philippines", "Poland", "Portugal", "Qatar", "San Marino", "Romania", "Russia", "Rwanda", "Saint Vincent & the Grenadines", "Samoa", "San Marino", "San Marino", "Sao Tome & Principe", "Saudi Arabia", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia", "Slovenia", "Solomon Islands", "Somalia", "South Africa", "South Sudan", "Spain", "Sri Lanka", "d Srpska", "St Kitts & Nevis", "st Lucia", "Sudan", "Suriname", "Swaziland", "Sweden", "Switzerland", "Syria", "Taiwan", "Tajikistan", "Tanzania", "Thailand", "Timor", "Togo", "Tonga", "Trinidad & Tobago", "Tunisia", "Turkey", "Turkmenistan", "Tuvalu", "United Arab Emirates", "USA", "Uganda", "Ukraine", "United Arab Emirates", "UnitedKingdom", "USA", "Uruguay", "Uzbekistan", "Vanuatu", "Vatican", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"};
char *subreddit[SUBREDDIT_COUNT] = {"Abudhabi", "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "AntiguaBarbuda", "Arabs", "Argentina", "Armenia", "Australia", "Austria", "Azerbaijan", "Bahamas", "Bahrain", "Bangladesh", "Barbados", "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "BiH", "Bolivia", "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina", "Burundi", "Cambodia", "Cameroon", "Canada", "CapeVerde", "Chad", "Chile", "China", "Colombia", "Comoros", "Congo", "CostaRica", "Costa_Rica", "Croatia", "Cuba", "Cyprus", "Czech", "Denmark", "Djibouti", "Dominica", "Dominican", "Ecuador", "Egypt", "Eritrea", "Estonia", "Ethiopia", "Fiji", "Finland", "France", "Gabon", "Gambia", "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guyana", "Haiti", "Honduras", "Hungary", "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland", "Israel", "Italy", "IvoryCoast", "Jamaica", "Japan", "Jordan", "Kazakhstan", "Kenya", "Kiribati", "Korea", "Kosovo", "Kuwait", "Kyrgyzstan", "Laos", "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg", "Macedonia", "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "MarshallIslands", "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique", "Myanmar", "Namibia", "Nauru", "Nepal", "Netherlands", "NewZealand", "Nicaragua", "Niger", "Nigeria", "Norway", "Oman", "PNG", "Pakistan", "Palau", "Panama", "Paraguay", "Peru", "Philippines", "Poland", "Portugal", "Qatar", "RepubblicaDiSanMarino", "Romania", "Russia", "Rwanda", "Saintvincent", "Samoa", "SanMarino", "San_Marino", "SaoTomePrincipe", "SaudiArabia", "Senegal", "Serbia", "Seychelles", "SierraLeone", "Singapore", "Slovakia", "Slovenia", "Solomon_Islands", "Somalia", "SouthAfrica", "SouthSudan", "Spain", "SriLanka", "Srpska", "StKitts", "StLucia", "Sudan", "Suriname", "Swaziland", "Sweden", "Switzerland", "Syria", "Taiwan", "Tajikistan", "Tanzania", "Thailand", "Timor", "Togo", "Tonga", "TrinidadandTobago", "Tunisia", "Turkey", "Turkmenistan", "Tuvalu", "UAE", "USA", "Uganda", "Ukraine", "UnitedArabEmirates", "UnitedKingdom", "UnitedStatesOfAmerica", "Uruguay", "Uzbekistan", "Vanuatu", "Vatican", "Venezuela", "Vietnam", "Yemen", "Zambia", "Zimbabwe"};
int times[SUBREDDIT_COUNT] = {0};
int sum = 0;

struct url_data {
    size_t size;
    char *data;
};

int count(char *arr[], char *x, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (strcasecmp(arr[i], x) == 0) {
            result++;
        }
    }
    return result;
}

int search(char *arr[], char *x, int n) {
    for (int i = 0; i < n; i++) {
        if (strcasecmp(arr[i], x) == 0) {
            return i;
        }
    }
    return -1;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char *tmp;

    data->size += (size * nmemb);

    tmp = realloc(data->data, data->size + 1); /* +1 for '\0' */

    if (tmp) {
        data->data = tmp;
    } else {
        if (data->data) {
            free(data->data);
        }
        fprintf(stderr, "Failed to allocate memory.\n");
        return 0;
    }

    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

char *get(char *url) {
    CURL *curl;

    struct url_data data;
    data.size = 0;
    data.data = malloc(4096);
    if (NULL == data.data) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return NULL;
    }

    data.data[0] = '\0';

    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    return data.data;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        puts("./rholmes [username]\n");
        return 1;
    }

    int new_size = strlen(*(argv + 1)) + 34;

    char *url = (char *)malloc(new_size);

    strcpy(url, "https://www.reddit.com/user/");
    strcat(url, *(argv + 1));
    strcat(url, ".json");

    char *text = get(url);

    cJSON *json = cJSON_Parse(text);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error before: %s\n", error_ptr);
        }
    }

    json = cJSON_GetObjectItemCaseSensitive(json, "data");
    json = cJSON_GetObjectItemCaseSensitive(json, "children");

    cJSON *post = NULL;

    bool found = false;

    cJSON_ArrayForEach(post, json) {
        cJSON *data = cJSON_GetObjectItemCaseSensitive(post, "data");
        data = cJSON_GetObjectItemCaseSensitive(data, "subreddit");
        char *subreddit_name = data->valuestring;

        int searched = search(subreddit, subreddit_name, SUBREDDIT_COUNT);
        if (searched != -1) {
            times[searched]++;
            sum++;
            found = true;
        }
    }

    if (found) {
        for (int i = 0; i < SUBREDDIT_COUNT; i++) {
            if (times[i] != 0) {
                float precent = (float)times[i] / sum * 100;
                printf("%s %.2f%%\n", countries[i], precent);
            }
        }
    } else {
        printf("This user is not member of any country subreddit or doesn't exist. If this is not true, raise an issue on github.");
        return 1;
    }

    cJSON_Delete(json);
    cJSON_Delete(post);

    free(url);

    return 0;
}