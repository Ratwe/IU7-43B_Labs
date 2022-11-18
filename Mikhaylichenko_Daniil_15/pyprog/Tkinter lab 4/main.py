from tkinter import *
from tkinter import messagebox as box
from settings import *
from math import pi


# Описание программы
def description():
    box.showinfo('О программе:', 'Из заданного множества точек выбрать три различные точки так, чтобы\
 разность между площадью круга, ограниченного окружностью, проходящей\
 через эти три точки, и площадью треугольника с вершинами в этих точках,\
 была минимальной.\n\n©Михайличенко Даниил ИУ7-23Б\n16.05.2022')


# Сообщение об ошибке
def error_msg(err):
    box.showinfo("Ошибка...", err)


# Создание объектов в окне
def make_object(obj_window, obj_type, obj_width, obj_height, obj_x, obj_y, **obj_args):
    frame = Frame(obj_window, width=obj_width, height=obj_height)
    frame.pack_propagate(False)
    frame.place(x=obj_x, y=obj_y)

    obj = obj_type(frame, obj_args)
    obj.pack(fill=BOTH, expand=True)
    return obj


# Считывание координаты места нажатия
def click_coordinates(event):
    return event.x, event.y


# Отрисовка точки
def draw_point(canvas, event, all_points):
    x, y = click_coordinates(event)
    point_coordinate = (x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS)
    canvas.create_oval(point_coordinate, width=1, outline="white", fill="white")
    all_points += [(x, y)]
    # print(all_points)


# Отрисовка окружности
def draw_circle(canvas, center, points):
    x, y = center[0], center[1]

    radius = ((x - points[0]) ** 2 + (y - points[1]) ** 2) ** 0.5

    point_coordinate = (x - radius, y - radius, x + radius, y + radius)
    canvas.create_oval(point_coordinate, width=1, outline="white")


# Отрисовка треугольника
def draw_triangle(canvas, first_dot, second_dot, third_dot):
    canvas.create_line(first_dot, second_dot, fill="white")
    canvas.create_line(second_dot, third_dot, fill="white")
    canvas.create_line(third_dot, first_dot, fill="white")


# Отрисовка всех точек заново
def draw_all_points(canvas, all_points):
    canvas.delete("all")
    for i in range(len(all_points)):
        x, y = all_points[i][0], all_points[i][1]
        canvas.create_oval(x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS, width=1, outline="white", fill='white')

    
# Добавление точки через поля ввода
def add_point(canvas, all_points, x_entry, y_entry):
    x, y = float(x_entry.get()), float(y_entry.get())

    if x < 2 or y < 2 or x > 247 or y > 247:
        error_msg("Координата выходит за границы поля")
        return

    point_coordinate = (x - RADIUS, y - RADIUS, x + RADIUS, y + RADIUS)
    canvas.create_oval(point_coordinate, width=1, fill='white', outline='white')
    all_points += [(x, y)]

    x_entry.delete(0, END)
    y_entry.delete(0, END)
    # print(all_points)


# Очистка поля рисования
def reset_canvas(canvas, all_points):
    all_points.clear()
    canvas.delete("all")
    # print(all_points)


# Проверка на существование треугольника
def is_triangle(first_dot, second_dot, third_dot):
    first_side = ((first_dot[0] - second_dot[0]) ** 2 + (first_dot[1] - second_dot[1]) ** 2) ** 0.5
    second_side = ((second_dot[0] - third_dot[0]) + (second_dot[1] - third_dot[1])) ** 0.5
    third_side = ((third_dot[0] - first_dot[0]) + (third_dot[1] - first_dot[1])) ** 0.5

    # print(first_side, second_side, third_side)
    if abs((first_side + second_side) - third_side) > EPS and \
            abs((second_side + third_side) - first_side) > EPS and \
            abs((third_side + first_side) - second_side) > EPS:
        return True
    return False


# Нахождение координаты центра окружности
def get_centre(first_dot, second_dot, third_dot):
    x1, x2, x3 = first_dot[0], second_dot[0], third_dot[0]
    y1, y2, y3 = first_dot[1], second_dot[1], third_dot[1]

    try:
        y = (2 * (x1 - x3) * (y2 ** 2 - y1 ** 2 - x1 ** 2 + x2 ** 2) + 2 * (x1 - x2) * \
             (x1 ** 2 - x3 ** 2 - y3 ** 2 + y1 ** 2)) / (4 * (y2 - y1) * (x1 - x3) - 4 * (x1 - x2) * (y3 - y1))
    except ZeroDivisionError:
        return (None, None)

    try:
        x = ((x1 ** 2 - x2 ** 2 - y2 ** 2 + y1 ** 2) + 2 * y * (y2 - y1)) / (2 * (x1 - x2))
    except ZeroDivisionError:
        return (None, None)

    return (x, y)


# Счёт разности площадей
def calc_values(values, centre, first_dot, second_dot, third_dot):
    x, y = centre[0], centre[1]
    x1, x2, x3 = first_dot[0], second_dot[0], third_dot[0]
    y1, y2, y3 = first_dot[1], second_dot[1], third_dot[1]

    radius = ((x - x1) ** 2 + (y - y1) ** 2) ** 0.5

    first_side = ((first_dot[0] - second_dot[0]) ** 2 + (first_dot[1] - second_dot[1]) ** 2) ** 0.5
    second_side = ((second_dot[0] - third_dot[0]) **2 + (second_dot[1] - third_dot[1]) **2) ** 0.5
    third_side = ((third_dot[0] - first_dot[0]) **2 + (third_dot[1] - first_dot[1]) **2) ** 0.5

    circle_square = pi * radius ** 2
    triangle_square = (first_side * second_side * third_side) / (4 * radius)
    dif = circle_square - triangle_square

    return dif


# Нахождение нужного круга
def find_circle(all_points):
    values = [1e6, "", ""]

    for i in range(len(all_points)):
        for j in range(len(all_points)):
            for k in range(len(all_points)):

                if all_points[i] == all_points[j] or \
                        all_points[j] == all_points[k] or \
                        all_points[k] == all_points[i]:
                    continue

                if is_triangle(all_points[i], all_points[j], all_points[k]):
                    centre = get_centre(all_points[i], all_points[j], all_points[k])

                    if centre[0] is None:
                        continue

                    temp = calc_values(values, centre, all_points[i], all_points[j], all_points[k])

                    if temp < values[0]:
                        values = [temp, centre, all_points[i], all_points[j], all_points[k]]

    if values[0] == "inf":
        error_msg("Не найдено н одного круга")

    return values


def find_objects(canvas, all_points):
    if len(all_points) < 3:
        error_msg("Недостаточно точек")

    draw_all_points(canvas, all_points)

    values = find_circle(all_points)

    if values[1] == "":
        error_msg("Не найдено ни одного круга")

    draw_circle(canvas, values[1], values[2])
    draw_triangle(canvas, values[2], values[3], values[4])


# Основная функция
def main():
    all_points = []

    window = Tk()
    window.title("Решение планиметрической задачи")
    window.geometry('500x300+100+100')
    window["bg"] = "#420516"
    window.bind("<Key>")

    # Создание пункта меню
    mainmenu = Menu(window)
    window.config(menu=mainmenu)
    mainmenu.add_cascade(label='О программе...', command=description)

    make_object(window, Label, USUAL_WIDTH, LABEL_HEIGHT, 0, 0,
                text="Задайте точки", font=(FONT, FONT_SIZE), bg=CHERRY, fg=PINK)
    make_object(window, Label, USUAL_WIDTH, LABEL_HEIGHT, CANVAS_WIDTH, 0,
                text="Введите координату", font=(FONT, FONT_SIZE), bg=CHERRY, fg=PINK)
    make_object(window, Label, USUAL_WIDTH / 4, LABEL_HEIGHT, USUAL_WIDTH, LABEL_HEIGHT,
                text="x:", font=(FONT, FONT_SIZE), bg=CHERRY, fg=PINK)
    make_object(window, Label, USUAL_WIDTH / 4, LABEL_HEIGHT, USUAL_WIDTH, LABEL_HEIGHT * 2,
                text="y:", font=(FONT, FONT_SIZE), bg=CHERRY, fg=PINK)

    x_entry = make_object(window, Entry, USUAL_WIDTH / 2, LABEL_HEIGHT,
                          USUAL_WIDTH + USUAL_WIDTH / 4, LABEL_HEIGHT, bg=STRONG_PINK)
    y_entry = make_object(window, Entry, USUAL_WIDTH / 2, LABEL_HEIGHT,
                          USUAL_WIDTH + USUAL_WIDTH / 4, LABEL_HEIGHT * 2, bg=STRONG_PINK)

    make_object(window, Button, USUAL_WIDTH, BUTTON_HEIGHT, CANVAS_WIDTH, 2 * LABEL_HEIGHT + LABEL_HEIGHT + 10,
                command=lambda: add_point(canvas, all_points, x_entry, y_entry), text="Добавить точку", bg=DARK_PINK, fg="white")
    make_object(window, Button, USUAL_WIDTH, BUTTON_HEIGHT, CANVAS_WIDTH, 3 * LABEL_HEIGHT + BUTTON_HEIGHT + 30,
                command=lambda: find_objects(canvas, all_points), text="Найти круг", bg=DARK_PINK, fg="white")
    make_object(window, Button, USUAL_WIDTH, BUTTON_HEIGHT, CANVAS_WIDTH, CANVAS_HEIGHT - 25,
                command=lambda: reset_canvas(canvas, all_points), text="Очистить поле", bg=DARK_PINK, fg="white")

    canvas = make_object(window, Canvas, CANVAS_WIDTH, CANVAS_HEIGHT, CANVAS_X, CANVAS_Y, \
                         bg=STRONG_PINK, highlightthicknes=0.5)
    canvas.bind("<1>", lambda event: draw_point(canvas, event, all_points))

    window.mainloop()


if __name__ == '__main__':
    main()
