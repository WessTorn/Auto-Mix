# Auto-Mix 5 vs 5 Counter Strike 1.6

Данный плагин автоматически запускает микс, когда на сервере находятся 10 игроков, также проверяет АФК и показывает урон, нанесенный вами в раунде сразу после смерти.

## Характеристики:
- Автоматический запуск игры
- Капитаны
- Ножевой раунд за выбор стороны
- Поддержка HLTV
- Меню на клавишу N
- Пауза (путем голосования)
- Мьюты / Анмьюты
- Кикнуть игрока из игры (путем голосования)
- Показывает дамаг в консоле
- Доступная настройка через квары, конфиг
- Сохраняет очки при переходе на другую сторону
- Живые могут читать мертвых
- Статистика [CSstatsX SQL](https://github.com/serfreeman1337/csstatsx-sql)

## Требования:

- [Amxmodx 1.9.0](https://www.amxmodx.org/downloads-new.php)
- [Reapi 5.19 (last)](https://dev-cs.ru/resources/73/updates)
- [ReGameDLL 5.19 (last)](https://dev-cs.ru/resources/67/updates)

## Команды в чат:

- Админ<br>
	.start		- Принудительно запустить игру<br>
	.stop		- Принудительно остановить игру<br>
	.manual		- Включить режим: Вручную<br>
	.auto		- Включить режим: Автоматический<br>

- Игрок<br>
	.menu			- Меню (N)<br>
	.votekick <nombre>	- Голосование за кик<br>
	.votepause		- Голосование за паузу<br>
	.mute <nombre>		- Замьютить<br>
	.unmute <nombre>	- Размьютить<br>

## Настройка плагина (pugconfig.cfg)

| Cvar                 | Default    | Descripción |
| :------------------- | :--------: | :--------------------------------------------------- |
| pug_tag              | ">" | Префикс микссистемы                                  |
| pug_owner	           | ""         | Ник админа сервера                   |
| pug_rounds_max       | 30         | Максимальное количество раундов матча                          |
| pug_rounds_ot        | 6          | Максимальное количество раундов овертайма                          |
| pug_show_money       | 1          | Показывать деньги тиммейтов. <br/>`0` Отключено<br/>`1` В чате<br/>`2` В HUD<br/>`3` По спрайтам |
| pug_votepause_time   | 60         | Время (сек), в течение которого длиться пауза                      |
| pug_afktime          | 60         | Время (в секундах), в течение которого игрока кикнет за АФК  |

## Дела, которые необходимо сделать
- Исправить все баги
- Зрители входят автоматически в порядке прибытия

## Благодарности | Авторы других плагинов 

[Leopoldo Brines - Competitive (Pugmod)](https://github.com/leobrines/pug_for_cs)<br>
[Sugisaki - Pugmod](https://amxmodx-es.com/Thread-Competitive-Face-it-Pick-Up-Game-PUG)<br>
[PredatorFlys - Pugmod](https://amxmodx-es.com/Thread-Auto-Mix-YAP-Capitan-resubido)<br>
[SmileYzn -Pugmod](https://github.com/SmileYzn/CS_PugMod)<br>
[GordonFreeman - CsstatsX](https://forums.alliedmods.net/showthread.php?t=279483)<br>
[CheesyPeteza - Afkicker](https://forums.alliedmods.net/showthread.php?t=3009)<br>
[OsweRRR - Votekick](https://amxmodx-es.com/Thread-Votekick-Player)<br>
[S1lentq - RegameDLL](https://github.com/s1lentq/ReGameDLL_CS)<br>

