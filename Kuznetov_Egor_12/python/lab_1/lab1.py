import tkinter as tk
import tkinter.messagebox

# Настройки цветов
label_active_bg_color = '#ffffff'
label_disable_bg_color = '#6e6e6e'
label_fg_color = '#000000'
label_pressholder_color = '#cccccc'
# Максимальная вводимая длина
max_length = 30
# Заполнение полей ввода
pressholder = ['Введите первое число', 'Введите второе число']
# Значения полей / числа
value = ['', '']

def label_changing():
    """
    Меняет отображения полей ввода в зависимости от активного
    """
    active_label = value_id.get()
    value_label[active_label].config(
        text = value[active_label],
        bg = label_active_bg_color,
        fg = label_fg_color
    )

    disable_label = (active_label + 1) % 2
    if value[disable_label] != '':
        value_label[disable_label].config(
            text = value[disable_label],
            bg = label_disable_bg_color,
            fg = label_fg_color
        )
    else:
        value_label[disable_label].config(
            text = pressholder[disable_label],
            bg = label_disable_bg_color,
            fg = label_pressholder_color
        )

def add_to_value(symbol):
    """
    Добавляет в активное поле символ
    Если количество символов больше заданной нормы ничего не делает
    """
    active_label = value_id.get()
    if len(value[active_label]) >= max_length:
        return
    value[active_label] += symbol
    label_changing()
def add_dot():
    """
    Добавляет в активное поле точку если её ещё не было
    Если количество символов больше заданной нормы ничего не делает
    """
    active_label = value_id.get()
    if len(value[active_label]) >= max_length:
        return
    if '.' in value[active_label]:
        return
    value[active_label] += '.'
    label_changing()
def remove_symbol():
    """
    Удаляет символ из заданного поля
    """
    active_label = value_id.get()
    value[active_label] = value[active_label][:-1]
    label_changing()

def calc_arr(arr):
    """
    Считает числа в массиве для трочино-симметричной системе
    """
    for i in range(len(arr)):
        while len(arr[i]) > 1:
            if arr[i][0] == '+':
                if arr[i][1] == '-':
                    arr[i][1] = '0'
                elif arr[i][1] == '+':
                    arr[i][1] = '-'
                    arr[i+1].append('+')
                else:
                    arr[i][1] = '+'
            elif arr[i][0] == '-':
                if arr[i][1] == '+':
                    arr[i][1] = '0'
                elif arr[i][1] == '-':
                    arr[i][1] = '+'
                    arr[i+1].append('-')
                else:
                    arr[i][1] = '-'
            arr[i].pop(0)
def count_zeros(arr):
    """
    Удаляет ведущие элементы которые пустые или содержат 0
    """
    count = 0
    while count < len(arr) and \
    (len(arr[count]) == 1 and arr[count][0] == '0' or \
    len(arr[count]) == 0):
        count += 1
    return count
    
def calc_sum():
    """
    Вычисляет сумму в троично-симметричной системе
    """
    s_value = [ list(i.split('.')) for i in value ]
    for i in s_value:
        while len(i) < 2:
            i.append('')

    frac_part = [[] for i in range(max(len(s_value[0][1]), len(s_value[1][1])))]
    for i in s_value:
        for j in range(len(i[1])):
            frac_part[j].append(i[1][j])
    frac_part.reverse()

    real_part = [[] for i in range(max(len(s_value[0][0]), len(s_value[1][0])))]
    for i in s_value:
        q = list(reversed(i[0]))
        for j in range(len(q)):
            real_part[j].append(q[j])

    frac_part.append([])
    real_part.append([])

    calc_arr(frac_part)
    real_part[0].extend(frac_part[-1])
    frac_part.pop()
    count = count_zeros(frac_part)
    frac_part = frac_part[count:]
    frac_part.reverse()

    calc_arr(real_part)
    real_part.reverse()
    count = count_zeros(real_part)
    real_part = real_part[count:]
    
    result = ''
    if len(real_part) == 0:
        result = '0'
    else:
        for i in real_part:
            result += i[0]

    if len(frac_part) != 0:
        result += '.'
        for i in frac_part:
            result += i[0]

    out_label.config(text = result)
def calc_dev():
    """
    Вычисляет разность в троично-симметричной системе
    """
    old_value = value[1]
    value[1] = '' 
    for i in range(len(old_value)):
        if old_value[i] == '+':
            value[1] += '-'
        elif old_value[i] == '-':
            value[1] += '+'
        else:
            value[1] += old_value[i]
    calc_sum()
    value[1] = old_value

def clear(first, second, result):
    """
    Очищает заданные поля
    """
    if first:
        value[0] = ''
    if second:
        value[1] = ''
    if result:
        out_label.config(text = '')
    label_changing()

# Создание и настройка окна
window = tk.Tk()
window.minsize(300, 300)
window.resizable(False, False)

# Создание и расстановка полей содержимого
label_frame = [
    tk.Frame(
        window, 
        width = 300, 
        height = 45
    ) for i in range(2)
] # Рамка полей содержимого для фиксирования размера и расположения
for i in range(len(label_frame)):
    label_frame[i].pack_propagate(False)
    label_frame[i].place(x = 0, y = i*45)

value_id = tk.IntVar(value = 0)
value_label = [ 
    tk.Radiobutton(
       label_frame[0],
       variable = value_id,
       font = ("Times New Roman", 12),
       value = 0,
       command = label_changing, 
       indicatoron = 0
    ), 
    tk.Radiobutton(
       label_frame[1],
       variable = value_id,
       font = ("Times New Roman", 12),
       value = 1,
       command = label_changing, 
       indicatoron = 0
    ) 
] 
label_changing()

# Создание и расстановка полей для кнопок ввода
input_frame = [
    tk.Frame(
        window, 
        width = 60, 
        height = 60
    ) for i in range(5)
]
for i in range(len(input_frame)):
    input_frame[i].pack_propagate(False)
    input_frame[i].place(x = i*60, y = 90)

input_button = [
    tk.Button(
        input_frame[0],
        text = '+',
        font = ("Times New Roman", 18),
        command = lambda: add_to_value('+')
    ),
    tk.Button(
        input_frame[1],
        text = '0',
        font = ("Times New Roman", 18),
        command = lambda: add_to_value('0')
    ),
    tk.Button(
        input_frame[2],
        text = '-',
        font = ("Times New Roman", 18),
        command = lambda: add_to_value('-')
    ),
    tk.Button(
        input_frame[3],
        text = '.',
        font = ("Times New Roman", 18),
        command = add_dot
    ),
    tk.Button(
        input_frame[4],
        text = '←',
        font = ("Times New Roman", 18),
        command = remove_symbol
    )
]

# Подписка на события клавиатуры
window.bind('+', lambda e:  input_button[0].invoke())
window.bind('0', lambda e:  input_button[1].invoke())
window.bind('-', lambda e:  input_button[2].invoke())
window.bind('.', lambda e:  input_button[3].invoke())
window.bind('<BackSpace>', lambda e:  input_button[4].invoke())

# Создание и расстановка функциональных кнопок 
options_frame = [
    tk.Frame(
        window,
        width = 150,
        height = 60
    ) for i in range(2)
]

for i in options_frame:
    i.pack_propagate(False)
options_frame[0].place(x = 0, y = 150)
options_frame[1].place(x = 150, y = 150)

options_button = [
    tk.Button(
        options_frame[0],
        text = 'Сумма',
        font = ("Times New Roman", 12),
        command = calc_sum
    ),
    tk.Button(
        options_frame[1],
        text = 'Разность',
        font = ("Times New Roman", 12),
        command = calc_dev
    )  
]

# Создание и расстановка полей вывода
msg_frame = tk.Frame(
    window,
    width = 300,
    height = 30
)
out_frame = tk.Frame(
    window,
    width = 300,
    height = 60
)
msg_frame.pack_propagate(False)
out_frame.pack_propagate(False)
msg_frame.place(x = 0, y = 210)
out_frame.place(x = 0, y = 240)

msg_label = tk.Label(
    msg_frame, text = 'Результат:', 
    font = ("Times New Roman", 12), 
    bg = '#ffffff'
)
out_label = tk.Label(
    out_frame, 
    text = '', 
    font = ("Times New Roman", 12), 
    bg = '#ffffff'
)

# Отображение всех объектов с заполнением их размерных рамок
for i in value_label + input_button + options_button:
    i.pack(fill=tk.BOTH, expand=True)
msg_label.pack(fill=tk.BOTH, expand=True)
out_label.pack(fill=tk.BOTH, expand=True)

# Создание пунктов меню
main_menu = tk.Menu(window) 
window.config(menu=main_menu) 
 
opt_menu = tk.Menu(main_menu, tearoff=0)
opt_menu.add_command(
    label = "Вычислить сумму", 
    command = options_button[0].invoke
)
opt_menu.add_command(
    label = "Вычислить разность", 
    command = options_button[1].invoke
)

clear_menu = tk.Menu(main_menu, tearoff=0)
clear_menu.add_command(
    label = "Очистка первого поля ввода", 
    command = lambda: clear(True, False, False)
)
clear_menu.add_command(
    label = "Очистка второго поля ввода", 
    command = lambda: clear(False, True, False)
)
clear_menu.add_command(
    label = "Очистка полей ввода", 
    command = lambda: clear(True, True, False)
)
clear_menu.add_command(
    label = "Очистка поля вывода", 
    command = lambda: clear(False, False, True)
)
clear_menu.add_command(
    label = "Очистка полей ввода и вывода", 
    command = lambda: clear(True, True, True)
)
 
help_menu = tk.Menu(main_menu, tearoff=0)
help_menu.add_command(
    label = "Об авторе", 
    command = lambda: tk.messagebox.showinfo(
        title="Об авторе", 
        message="Программа сделана Кузнецовым Егором Владимировичем ИУ7-23Б"
    )
)
help_menu.add_command(
    label = "О программе", 
    command = lambda: tk.messagebox.showinfo(
        title="О программе", 
        message="Программа вычисляет сумму или разность заданных чисел"
    )
)

main_menu.add_cascade(label = "Функции", menu = opt_menu)
main_menu.add_cascade(label = "Очистка", menu = clear_menu)
main_menu.add_cascade(label = "Справка", menu = help_menu)

window.mainloop()