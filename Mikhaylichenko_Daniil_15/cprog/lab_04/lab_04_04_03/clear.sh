# Скрипт, удаляющий побочные файлы после проверки покрытия

#!/bin/bash

rm -rf report
rm -f app-main.gcno
rm -f app-main.gcda
rm -f app.info
