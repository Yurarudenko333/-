Программа имеет текстовый интерфейс, с функционалом:
Добавление жанра песни
Добавление исполнителя (название/любимые жанры/песни)
Добавление песни (название/год выпуска/жанр)
Расчет рейтинга песни
Просмотр списка песен (топ по рейтингу и по новизне)
Просмотр списка групп
Просмотр доп. информации про песню
Просмотр доп. информации про группу

В программе уже заложены несколько популярных жанров, но можно добавить и свои

Основной алгоритм подсчета популярности песни работает по формуле:
(средняя популярность песен группы + 10*популярность жанра + соответствие жанра группе + дата выхода + фактор рандома)/2

Благодаря этому алгоритму новые песни популярных групп будут популярнее песен, выпущенных новыми группами

Описание структур:
class song - класс, который используется для хранения данных про песни (имя/год/жанр/популярность)
class band - класс, для хранения информации про исполнителей, хранит в себе имя группы/исполнителя, массив любимых жанров а также массив песен, принадлежащих этой группе

map<string, int> janres - ассоциативный массив, который хранит в себе все доступные жанры и значение их популярности (ключ - жанр, значение - популярность)

vector<song> all_songs - вектор всех песен, просто дублирует массивы песен разных групп

vector<band> bands - вектор всех групп