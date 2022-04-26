"""
Кузнецов Егор Владимирович ИУ7-23Б
Поиск выпуклых четырёхугольников и их отображение
"""
import tkinter as tk
from tkinter import messagebox as mb

points = []
result = []
current_value = 0


def create_widget(window, widget_type, width, height, x, y, **widget_args):
    """
    Создает объкт tkinter, настраивает и возвращает его
    """
    frame = tk.Frame(window, width=width, height=height)
    frame.pack_propagate(False)
    frame.place(x=x, y=y)

    widget = widget_type(frame, widget_args)
    widget.pack(fill=tk.BOTH, expand=True)
    return widget

def draw(x, y):
    """
    Рисует точку в координате
    """
    canvas.create_oval((x), (y), (x), (y), fill="#000000")

def redraw_values():
    """
    Перерисовывает все точки
    """
    canvas.delete("all")
    for i in points:
        draw(*i)

def clear():
    """
    Очищает графическое поле
    """
    canvas.delete("all")
    clean_result()
    points.clear()
    mb.showinfo("Поле", "Поле очищено")

def clean_result():
    """
    Удаляет результаты вычислений
    """
    result.clear()
    global current_value
    current_value = 0
    b_p["bg"] = "#7d7d7d"
    b_n["bg"] = "#7d7d7d"
    b_a["bg"] = "#7d7d7d"
    num["text"] = ""

def check_result():
    """
    Проверяет результаты на изменение данных
    """
    if result:
        clean_result()
        redraw_values()
        mb.showinfo("Результаты", "Изменение данных, результаты были сброшены")

def click(event):
    """
    Рисование новой точки на графическом поле 
    """
    if not ((event.x, event.y) in points):
        check_result()
        draw(event.x, event.y)
        points.append((event.x, event.y))

def add_point():
    """
    Добавление точки вручную
    """
    x = x_entry.get()
    y = y_entry.get()

    try:
        x = float(x)
        if x < 1 or x > 198:
            mb.showerror("Неверное число х", "Вне границ поля")
            return
    except:
        mb.showerror("Неверное число х", "Некорректный ввод")
        return

    try:
        y = float(y)
        if y < 1 or y > 198:
            mb.showerror("Неверное число y", "Вне границ поля")
            return
    except:
        mb.showerror("Неверное число y", "Некорректный ввод")
        return

    if not ((x, y) in points):
        check_result()
        draw(x, y)
        points.append((x, y))
        x_entry.delete(0, tk.END)
        y_entry.delete(0, tk.END)
    else:
        mb.showerror("Значение", "Данная точка уже записана")
        return

def get_sign(value):
    """
    Возвращает 0, если число 0, -1 если число отрицательное, 1 если число положительное
    """
    try:
        return value / abs(value)
    except:
        return 0

def calculate_result():
    """
    Ищет все невыпуклые четырёхугольники и выводит первый из них
    """
    enumerated_points = list(enumerate(points))
    for i, a in enumerated_points:
        for j, b in enumerated_points:
            if j == i:
                continue
            d_ab = (b[0] - a[0], b[1] - a[1])
            for k, c in enumerated_points:
                if k == j or k == i:
                    continue
                d_ac = (c[0] - a[0], c[1] - a[1])
                d_bc = (c[0] - b[0], c[1] - b[1])
                for l, d in enumerated_points:
                    if l == k or l == j or l == i:
                        continue
                    d_ad = (d[0] - a[0], d[1] - a[1])
                    d_bd = (d[0] - b[0], d[1] - b[1])
                    d_cd = (d[0] - c[0], d[1] - c[1])
                    
                    ad_pos = [ get_sign(d_ad[0] * d_ab[1] - d_ad[1] * d_ab[0]), 
                               get_sign(d_ad[0] * d_ac[1] - d_ad[1] * d_ac[0]) ]
                    ab_pos = [ get_sign(d_ab[0] * d_ac[1] - d_ab[1] * d_ac[0]),
                               get_sign(d_ab[0] * d_ad[1] - d_ab[1] * d_ad[0]) ]
                    bc_pos = [ - get_sign(d_bc[0] * d_ab[1] + d_bc[1] * d_ab[0]),
                                 get_sign(d_bc[0] * d_bd[1] - d_bc[1] * d_bd[0]) ]
                    cd_pos = [ get_sign(d_cd[0] * d_ac[1] - d_cd[1] * d_ac[0]),
                               get_sign(d_cd[0] * d_bc[1] - d_cd[1] * d_bc[0]) ]
    
                    if ad_pos[0] == ad_pos[1] and ab_pos[0] == ab_pos[1] and bc_pos[0] == bc_pos[1] and cd_pos[0] == cd_pos[1]:
                        res = (i, j, k, l)
                        s_res = tuple(sorted(res))
                        for r in result:
                             if s_res == tuple(sorted(r)):
                                 break
                        else:
                            result.append((i, j, k, l))
    if len(result):
        mb.showinfo("Результаты", "Всего найдено {:1} четырёхугольников".format(len(result)))
        show_result(result[0])
        global current_value
        current_value = 0
        b_p["bg"] = "#d9d9d9"
        b_n["bg"] = "#d9d9d9"
        b_a["bg"] = "#d9d9d9"
        num["text"] = "1"
    else:
        mb.showerror("Результаты", "Четырёхугольники не найдены")

def show_next_result():
    """
    Показывает следующих результат
    """
    if not result:
        return
    global current_value
    current_value = (current_value + 1) % len(result)
    num["text"] = str(current_value + 1)
    show_result(result[current_value])

def show_prev_result():
    """
    Показывает предыдущий результат
    """
    if not result:
        return
    global current_value
    current_value = (current_value - 1) % len(result)
    num["text"] = str(current_value + 1)
    show_result(result[current_value])

def show_all():
    """
    Показывает все результаты одновременно
    """
    if not result:
        return
    for i in result:
        show_result(i, False)

def show_result(result, clear = True):
    """
    Выводит четырёхугольник
    """
    if clear:
        redraw_values()
    canvas.create_line(*points[result[0]], *points[result[1]])
    canvas.create_line(*points[result[1]], *points[result[2]])
    canvas.create_line(*points[result[2]], *points[result[3]])
    canvas.create_line(*points[result[3]], *points[result[0]])

canvas_width = 200
canvas_height = 200
handed_width = 200
label_height = 25
button_height = 40

window = tk.Tk()
window.title("Lab 4")
window.minsize(canvas_width + handed_width, 300)
window.resizable(False, False)

create_widget(window, tk.Label, canvas_width, label_height, 0, 0, text = "Задайте точку")
canvas = create_widget(window, tk.Canvas, canvas_width, canvas_height, 0, label_height, bg = "#FFFFFF") 
create_widget(window, tk.Button, canvas_width, button_height, 0, canvas_height + label_height, text = "Очистить поле", command = clear)
canvas.bind("<1>", click)

create_widget(window, tk.Label, handed_width, label_height, canvas_width, 0, text = "Введите точку")
create_widget(window, tk.Label, handed_width / 4, label_height, canvas_width, label_height, text = "x:")
x_entry = create_widget(window, tk.Entry, handed_width / 4, label_height, canvas_width + handed_width / 4, label_height)
create_widget(window, tk.Label, handed_width / 4, label_height, canvas_width + handed_width / 2, label_height, text = "y:")
y_entry = create_widget(window, tk.Entry, handed_width / 4, label_height, canvas_width + 3 * handed_width / 4, label_height)
create_widget(window, tk.Button, handed_width, button_height, canvas_width, 2 * label_height, command = add_point, text = "Добавить")

create_widget(window, tk.Button, handed_width, button_height, canvas_width, 3 * label_height + button_height, command = calculate_result, text = "Посчитать")
b_p = create_widget(window, tk.Button, handed_width / 4, button_height, canvas_width, 3 * label_height + 2 * button_height, command = show_prev_result, text = "<<", bg = "#7d7d7d")
b_n = create_widget(window, tk.Button, handed_width / 4, button_height, canvas_width + handed_width / 2, 3 * label_height + 2 * button_height, command = show_next_result, text = ">>", bg = "#7d7d7d")
b_a = create_widget(window, tk.Button, handed_width / 4, button_height, canvas_width + 3 * handed_width / 4, 3 * label_height + 2 * button_height, command = show_all, text = "Все", bg = "#7d7d7d")
num = create_widget(window, tk.Label, handed_width / 4, button_height, canvas_width + handed_width / 4, 3 * label_height + 2 * button_height)

window.mainloop()
