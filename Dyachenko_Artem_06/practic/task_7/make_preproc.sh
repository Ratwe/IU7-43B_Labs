#!/bin/bash

echo "Starting preprocessing..."

for file in ./*; do

    if [[ "$file" =~ data[0-9]_O[0-9s]\.txt ]]; then
        opt=$(echo "$file" | cut -c10)
        num=$(echo "$file" | grep -o '[0-9]' | head -1)

        # Таблица обработанных данных
        file_data="method_""$num""_O""$opt"
        echo -n > "$file_data"
        echo "processing ""'$file_data'""..."

        iterations=20
        for i in $(seq 0 $iterations); do
            # Подготовка массива
            elems=$((i * 500))
            str=$( < "$file" grep -o "^$elems:[0-9]*\.[0-9]*")
            vals=$(echo "$str" | cut -d ':' -f 2)
            val_args=()

            sum="0"
            size=1
            cur_val=$(echo "$vals" | cut -d$'\n' -f 1)

            while [ -n "$cur_val" ]; do
                val_args+=("$cur_val")

                cur_val=$(echo "$vals" | cut -d$'\n' -f "$((size+1))")
                size=$((size+1))
            done
            size=$((size-1))

            # Сортируем
            IFS=$'\n' sorted_str=("$(sort <<<"${val_args[*]}")")
            unset IFS

            # Парсим в массив
            sorted=()

            while IFS=$'\n' read -ra sorted_str; do
                for j in "${sorted_str[@]}"; do
                    sorted+=("$j")
                done
            done <<< "${sorted_str[@]}"


            # Подсчёт среднего
            for t in "${sorted[@]}"; do
                sum=$(echo "$sum + $t" | bc -l)
            done
            mid=$(echo "$sum / $size" | bc -l)

            # Дополнить незначащим нулём, если mid < 1
            if [ "$(echo "$mid < 1" | bc -l)" -eq 1 ]; then
                mid="0""$mid"
            fi


            # Подсчёт медианы
            centre=$((size / 2))
            centre_val=${sorted[$centre]}

            # Eсли тестов нечётное кол-во - берём одно центрально значение
            median=$centre_val

            # Иначе - берём среднее двух центральных
            if [ $((size % 2)) -eq 0 ]; then
                centre_last_val=${sorted[$((centre - 1))]}
                sum_of_two=$(echo "${sorted[$centre]} + $centre_last_val" | bc -l)
                median=$(echo "$sum_of_two / 2" | bc -l)
            fi

            # Дополнить незначащим нулём, если median < 1
            if [ "$(echo "$median < 1" | bc -l)" -eq 1 ]; then
                median="0""$median"
            fi


            # Мин/макс значения
            min_val=${sorted[0]}
            max_val=${sorted[$((size - 1))]}


            # Верхний квартиль
            Q3=$(echo "3/4 * $((size + 1))" | bc -l)
            Q3=$(awk -v v="$Q3" 'BEGIN{printf "%d", v}') # перевод в int

            # Если Q3 - целое число (значит {size + 1} % 4 == 0)
            if [ "$size" -ge 3 ] && [ "$(( $((size + 1)) % 4 ))" -eq 0 ]; then
                up_quartile="${sorted[$Q3]}"
            else
                sum_of_two=$(echo "${sorted[$Q3]} + ${sorted[$((Q3 - 1))]}" | bc -l)
                up_quartile=$(echo "$sum_of_two/2" | bc -l)
            fi

            # Дополнить незначащим нулём, если up_quartile < 1
            if [ "$(echo "$up_quartile < 1" | bc -l)" -eq 1 ]; then
                up_quartile="0""$up_quartile"
            fi


            # Нижний квартиль
            Q1=$(echo "1/4 * $((size + 1))" | bc -l)
            Q1=$(awk -v v="$Q1" 'BEGIN{printf "%d", v}') # перевод в int

            # Если Q1 - целое число (значит {size + 1} % 4 == 0)
            if [ "$size" -ge 3 ] && [ "$(( $((size + 1)) % 4 ))" -eq 0 ]; then
                down_quartile="${sorted[$Q1]}"
            else
                sum_of_two=$(echo "${sorted[$Q1]} + ${sorted[$((Q1 - 1))]}" | bc -l)
                down_quartile=$(echo "$sum_of_two/2" | bc -l)
            fi

            # Дополнить незначащим нулём, если down_quartile < 1
            if [ "$(echo "$down_quartile < 1" | bc -l)" -eq 1 ]; then
                down_quartile="0""$down_quartile"
            fi

            # Запись данных в таблицу
            echo "$elems:""$mid:""$median:""$min_val:""$max_val:""$down_quartile:""$up_quartile" >> "$file_data"

            # # Отладка
            # echo "sorted size ${#sorted[@]}"
            # echo -n "[DB]: sorted'': "
            # for t in "${sorted[@]}"; do
            #     echo -n "$t "
            # done
            # echo
            #
            # echo "mid $mid median $median"
            # echo "min $min_val max $max_val"
            # echo "up_quartile $up_quartile"
            # echo "down_quartile $down_quartile"
            # echo
        done
    fi
done

echo "Preprocessing complete!"
echo
