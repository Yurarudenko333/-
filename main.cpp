#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>
#include <iterator>

using namespace std;

class song;
class band;
void home();
void add_band();
void add_janre();
void show_ganres();
void show_songs();
void show_bands();

map<string, int> janres;//массив жанр - популярность (от 0 до 10)
vector<song> all_songs;//массив всех песен
vector<band> bands;
int TodayYear = 2018;

class song {
public:
    string name;
    string janre;
    int popularity = -1;
    int year;
    
    song (string n, string j, int y) {
        name = n;
        janre = j;
        year = y;
    }
    
    song (string n, string j, int y, int p) {
        name = n;
        janre = j;
        year = y;
        popularity = p;
    }
};

class band {
public:
    string name;
    vector<string> fav_janres;
    vector<song> songs;
    
    band (string n) {
        name = n;
    }
};

void home() { //начальное диалоговое окно
    int cho;
    cout << endl << " Главное меню" << endl;
    cout << "1. Список групп" << endl;
    cout << "2. Топ-песен" << endl;
    cout << "3. Добавить группу" << endl;
    cout << "4. Добавить жанр" << endl;
    cout << "5. Список жанров" << endl;
    cout << "6. Выход из программы" << endl;
    cin >> cho;
    switch (cho) {
        case 1: {
            show_bands();
            break;
        }
        case 2: {
            show_songs();
            break;
        }
        case 3: {
            add_band();
            break;
        }
        case 4: {
            add_janre();
            break;
        }
        case 5: {
            show_ganres();
            break;
        }
        case 6: {
            exit(0);
            break;
        }
        default: {
            home();
        }
    }
}

int search_band(string name){
    for (auto it = 0; it < bands.size(); it ++) {
        if (bands[it].name == name) {
            return it;
        }
    }
    return -1;
}

void add_song_to_band(int b) {
    string name;
    int i = 0;
    int cho;
    int cho2;
    cout << endl << "Введите название песни:" << endl;
    cin >> name;
    
    cout << endl << "Введите год выпуска песни:" << endl;
    cin >> cho2;
    
    cout << endl << "Выберите жанр песни:" << endl;
    for (auto it = janres.begin(); it != janres.end(); it ++) {
        i++;
        cout << i << ". " << it->first << endl;
    }
    cin >> cho;
    
    i = 0;
    for (auto it = janres.begin(); it != janres.end(); it++) {
        i++;
        if (i == cho) {
            bands[b].songs.push_back(song(name, it->first, cho2));
        }
    }
    
    for (auto it = bands[b].songs.begin(); it != bands[b].songs.end(); it++) {
        if (it->name == name) {
            int cnt = 0;
            int g_pop = 0;
            int b_pop = 0;
            int y_pop = 100 - abs(TodayYear - it->year);
            for (auto its = bands[b].songs.begin(); its != bands[b].songs.end(); its ++) {
                if (its->popularity > 0) {
                    cnt++;
                    g_pop = g_pop + its->popularity;
                }
            }
            if (cnt != 0) {
                g_pop = g_pop/cnt;
            }
            for (int i = 0; i < bands[b].fav_janres.size(); i++) {
                if (bands[b].fav_janres[i] == it->janre) {
                    b_pop = 100;
                }
            }
            
            for (auto its = janres.begin(); its != janres.end(); its++) {
                if (its->first == it->janre) {
                    if (g_pop != 0) {
                        it->popularity = (g_pop + (b_pop + y_pop + 10*its->second + rand()%100 + 1))/2;
                    } else {
                        it->popularity = b_pop + y_pop + 10*its->second + rand()%100 + 1;
                    }
                }
            }
            all_songs.push_back(song(it->name, it->janre, it->year, it->popularity));
        }
    }
    
    cout << endl << "1. Добавить еще песню" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        add_song_to_band(b);
    } else {
        home();
    }
}

void add_janre_to_band(int b) {
    int cho;
    int i = 0;
    cout << endl << " Выберите жанр, который хотите добавить:" << endl;
    for (auto it = janres.begin(); it != janres.end(); it ++) {
        i++;
        cout << i << ". " << it->first << endl;
    }
    cin >> cho;
    i = 0;
    for (auto it = janres.begin(); it != janres.end(); it++) {
        i++;
        if (i == cho) {
            bands[b].fav_janres.push_back(it->first);
        }
    }
    
    cout << endl << "1. Добавить еще любимый жанр" << endl;
    cout << "2. Добавить песню группы " << bands[b].name << endl;
    cout << "3. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        add_janre_to_band(b);
    } else if (cho == 2) {
        add_song_to_band(b);
    } else {
        home();
    }
}

void add_band() {
    string name;
    int cho;
    cout << endl << "Введите название группы:" << endl;
    cin >> name;
    bands.push_back(band(name));
    
    cout << endl << "1. Добавить любимый жанр" << endl;
    cout << "2. Добавить песню" << endl;
    cout << "3. Домой" << endl;
    cin >> cho;
    switch (cho) {
        case 1: {
            add_janre_to_band(search_band(name));
            break;
        }
        case 2: {
            add_song_to_band(search_band(name));
            break;
        default: {
            home();
        }
    }
    }
}

void add_janre() {
    string name;
    int popularity;
    int cho;
    cout << endl << "Введите название жанра:" << endl;
    cin >> name;
    cout << "Введите популярность жанра: (от 0 до 10)" << endl;
    cin >> popularity;
    while (popularity < 0 || popularity > 10) {
        cout << endl << "Неверное значение. Введите популярность жанра: (от 0 до 10)" << endl;
        cin >> popularity;
    }
    janres.insert(make_pair(name, popularity));
    cout << endl << "1. Добавить еще жанр" << endl << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        add_janre();
    } else {
        home();
    }
}

void show_ganres() {
    int cho;
    cout << endl << " Список жанров:" << endl;
    for (auto it = janres.begin(); it != janres.end(); it++) {
        cout << it->first << " с популярностью " << it->second << endl;
    }
    cout << "1. Домой" << endl;
    cin >> cho;
    if (cho){
        home();
    }
}

struct pred {
    bool operator()(const song& dot1, const song& dot2)
    {
        return dot1.popularity > dot2.popularity;
    }
};

struct nov {
    bool operator()(const song& dot1, const song& dot2)
    {
        return dot1.year > dot2.year;
    }
};

void song_info(int b) {
    int cho;
    cout << endl << " Вы выбрали песню: " << all_songs[b].name << endl;
    cout << "Год: " << all_songs[b].year << endl;
    cout << "Популярность: " << all_songs[b].popularity << endl;
    cout << "Жанр: " << all_songs[b].janre << endl;
    cout << "1. Назад" << endl;
    cout << "2. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        show_songs();
    } else {
        home();
    }
}

void show_songs() {
    int cho;
    cout << endl << "1. Отобразить по популярности" << endl << "2. Отобразить по новизне" << endl;
    cin >> cho;
    if (cho == 1) {
        cout << endl << " Список песен по популярности: (введите номер песни чтоб узнать больше)" << endl;
        sort(all_songs.begin(), all_songs.end(), pred());
        int i;
        for (i = 0; i != all_songs.size(); i++) {
            cout << i+1 << ". " << all_songs[i].name << " с популярностью " << all_songs[i].popularity << endl;
        }
        cout << i+1 << ". Домой" << endl;
        cin >> cho;
        if (cho > 0 && cho <= i) {
            song_info(cho -1);
        } else {
            home();
        }
    } else if (cho == 2) {
        cout << endl << " Список песен по новизне: (введите номер песни чтоб узнать больше)" << endl;
        sort(all_songs.begin(), all_songs.end(), nov());
        int i;
        for (i = 0; i != all_songs.size(); i++) {
            cout << i+1 << ". " << all_songs[i].name << " выпущеная в " << all_songs[i].year << endl;
        }
        cout << i+1 << ". Домой" << endl;
        cin >> cho;
        if (cho > 0 && cho <= i) {
            song_info(cho -1);
        } else {
            home();
        }
    } else {
        home();
    }
}

void info_band(int b) {
    int cho;
    cout << endl << " Вы выбрали группу: " << bands[b].name << endl;
    cout << " Любимые жанры: " << endl;
    for (int i = 0; i < bands[b].fav_janres.size(); i++) {
        cout << bands[b].fav_janres[i] << endl;
    }
    cout << " Песни группы: " << endl;
    for (int i = 0; i < bands[b].songs.size(); i++) {
        cout << bands[b].songs[i].name << " " << bands[b].songs[i].janre << " Рейтинг:" << bands[b].songs[i].popularity << " Год:" << bands[b].songs[i].year << endl;
    }
    cout << endl << "1. Добавить песню" << endl << "2. Добавить любимый жанр" << endl << "3. Назад" << endl << "4. Домой" << endl;
    cin >> cho;
    if (cho == 1) {
        add_song_to_band(b);
    } else if (cho == 2) {
        add_janre_to_band(b);
    } else if (cho == 3) {
        show_bands();
    } else {
        home();
    }
}

void show_bands() {
    int cho;
    cout << endl << " Список групп: (введите номер группы чтоб узнать больше)" << endl;
    int i = 0;
    for (i = 0; i != bands.size(); i++) {
        cout << i+1 << ". " << bands[i].name << endl;
    }
    cout << i+1 << ". Домой" << endl;
    cin >> cho;
    if (cho>0 && cho <= i) {
        info_band(cho-1);
    } else {
        home();
    }
}

int main(int argc, const char * argv[]) {
    janres.insert(make_pair("Rock", 6));
    janres.insert(make_pair("Metal", 3));
    janres.insert(make_pair("Pop", 9));
    janres.insert(make_pair("Rap", 10));
    janres.insert(make_pair("Blues", 6));
    janres.insert(make_pair("Jazz", 4));
    janres.insert(make_pair("Country", 5));
    janres.insert(make_pair("Key-pop", 7));
    janres.insert(make_pair("House", 6));
    janres.insert(make_pair("Techno", 8));
    home();
    return 0;
}
