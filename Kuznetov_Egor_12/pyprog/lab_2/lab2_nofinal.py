from sympy.abc import x
from sympy.parsing.sympy_parser import parse_expr

import tkinter as tk
import tkinter.messagebox as mb
import matplotlib as mpl
mpl.use('TkAgg')

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure

def grapth():
    if not check_entry():
        return
    f = parse_expr(entry[0].get())
    df = f.diff()
    a = float(entry[1].get())
    b = float(entry[2].get())
    step = (b - a) / 100

    gr = tk.Toplevel(window)
    gr.minsize(500, 500)
    gr.resizable(False, False)
    gr.title("График")

    frame = tk.Frame(gr, width=500, height=500)
    frame.pack_propagate(False)
    frame.pack()

    xs = []
    fs = []
    zs = []
    fzs = []
    while a < b:
        try:
            fs.append(float(f.evalf(subs={x:a})))
            xs.append(a)
        except:
            pass
        z = find_zeros(a, min(a+step, b), 0.001, 1000, f, df)
        if not z[0]:
            zs.append(z[1])
            fzs.append(f.evalf(subs={x: z[1]}))
        dz = find_zeros(a, min(a+step, b), 0.001, 1000, df)
        if not dz[0]:
            zs.append(dz[1])
            fzs.append(f.evalf(subs={x: dz[1]}))
        a += step
    

    fig = Figure(figsize=(3, 3), dpi=100)
    fig.plot = fig.add_subplot(111)
    fig.plot.plot(xs, fs)
    fig.plot.plot(zs, fzs, "ro")
    canvas = FigureCanvasTkAgg(fig, frame)
    canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)



def table():
    if not check_entry():
        return
    f = parse_expr(entry[0].get())
    df = f.diff()
    a = float(entry[1].get())
    b = float(entry[2].get())
    h = float(entry[3].get())
    Nmax = int(entry[4].get())
    eps = float(entry[5].get())
    
    content=[[ "#", "Интервал поиска", "x'", "f(x')", "Кол-во итер.", "Код ошибки" ]]
    count_root = 0
    while a < b:
        val = find_zeros(a, min(a+h, b), eps, Nmax, f, df)
        if val[0]:
            content.append([ "—", "[ {:.2f} - {:.2f} ]".format(a, min(a+h, b)), 
                "—", "—", "—", str(val[0]) ])
        else:
            content.append([ str(count_root + 1), 
                "[ {:.2f} - {:.2f} ]".format(a, min(a+h, b)), 
                "{:.4}".format(float(val[1])), 
                "{:.1e}".format(float(f.evalf(subs={x: val[1]}))), 
                str(val[2]), str(val[0]) ])
            count_root += 1
        a += h
    
    col_width = [ 30, 200, 100, 70, 100, 100 ]
    row_height = 25
    tab = tk.Toplevel(window)
    tab.minsize(sum(col_width), row_height*len(content))
    tab.resizable(False, False)
    tab.title("Таблица")

    for i, c in enumerate(content):
        frame = [ tk.Frame(tab, width=col_width[j], 
            height=row_height) for j in range(len(c)) ]
        s = 0
        for l, f in enumerate(frame):
            f.pack_propagate(False)
            f.place(x = s, y = i*row_height)
            s += col_width[l]
        lb = [ tk.Label(frame[j], text=content[i][j],
            font=std_font, bg=std_color, borderwidth=2, 
            relief="groove") for j in range(len(c)) ]
        for j in lb:
            j.pack(fill=tk.BOTH, expand=True)




def find_zeros(start, stop, eps, Nmax, f, df = None):
    if not df:
        df = f.diff()
    
    try:
        n = 1
        x_o = start
        dfv = float(df.evalf(subs={x: x_o}))
        if dfv == 0:
            dfv += eps
        x_n = x_o - float(f.evalf(subs={x: x_o}))/dfv
        while start <= x_n <= stop and abs(x_n - x_o) > eps and n < Nmax:
            x_o = x_n
            dfv = float(df.evalf(subs={x: x_o}))
            if dfv == 0:
                dfv += eps
            x_n = x_o - float(f.evalf(subs={x: x_o}))/dfv
            n += 1
        if not start <= x_n <= stop:
            return [ 1 ]
        if not n < Nmax:
            return [ 2 ]
        return [ 0, x_n, n ]
    except:
        return [ 3 ]

    




def check_entry():
    try:
        fx = parse_expr(entry[0].get())
        dx = fx.diff()
        complex(fx.evalf(subs={x: 0}))
    except:
        mb.showerror("", "Неверная функция")
        return False

    try:
        a = float(entry[1].get())
    except:
        mb.showerror("", "Неверное число 'a'")
        return False
    
    try:
        b = float(entry[2].get())
    except:
        mb.showerror("", "Неверное число 'b'")
        return False
    if b - a <= 0:
        mb.showerror("", "Неверное число 'b'. Число 'a' должно быть меньше 'b'")
        return False

    try:
        h = float(entry[3].get())
    except:
        mb.showerror("", "Неверное число 'h'")
        return False

    try:
        Nmax = int(entry[4].get())
    except:
        mb.showerror("", "Неверное число 'Nmax'")
        return False
    
    try:
        eps = float("-" + entry[5].get())
    except:
        mb.showerror("", "Неверное число 'eps'")
        return False
    if eps == 0:
        mb.showerror("", "Неверное число 'esp'")
        return False
    return True


        

std_font = ("Liberation Serif",12)
std_color = "#ffffff"

label_text = [ "f(x)=", "a=", "b=", "h=", "Nmax=", "eps=" ]
button_text = [ "Построить график", "Найти корни" ]
button_func = [ grapth, table ]
mark_text = [ "ИУ7-23Б Кузнецов Егор" ]

count_input = len(label_text)
count_button = 2
window_width = 300
label_width = 60
entry_width = window_width - label_width
button_width = window_width // count_button
input_height = 25
button_height = 50 
mark_height = 30
window_heigth = count_input*input_height + button_height + mark_height

window = tk.Tk()
window.minsize(window_width, window_heigth)
window.resizable(False, False)

label_frame = [ tk.Frame(window, width=label_width,
    height=input_height) for _ in range(count_input) ]
entry_frame = [ tk.Frame(window, width=entry_width, 
    height=input_height) for _ in range(count_input) ]
button_frame = [ tk.Frame(window, width=button_width, 
    height=button_height) for _ in range(count_button) ]
mark_frame = [ tk.Frame(window, width=window_width,
    height=mark_height) ]

for i, content in enumerate(zip(label_frame, entry_frame)):
    l, e = content
    l.pack_propagate(False)
    e.pack_propagate(False)
    l.place(x = 0, y = i*input_height)
    e.place(x = label_width, y = i*input_height)
for i, b in enumerate(button_frame):
    b.pack_propagate(False)
    b.place(x = button_width*i, y = count_input*input_height)
for i, m in enumerate(mark_frame):
    m.pack_propagate(False)
    m.place(x = 0, y = count_input*input_height+button_height)

label = [ tk.Label(label_frame[i], text=label_text[i],
    font=std_font, bg=std_color, borderwidth=2, 
    relief="groove") for i in range(count_input) ]
entry = [ tk.Entry(entry_frame[i], 
    font=std_font) for i in range(count_input) ]
button = [ tk.Button(button_frame[i], text=button_text[i], font=std_font,
    command=button_func[i], bg=std_color) for i in range(count_button) ]
mark = [ tk.Label(mark_frame[0], text=mark_text[0], 
    font=std_font, bg=std_color) ]

for i in label + entry + button + mark:
    i.pack(fill=tk.BOTH, expand=True)

window.mainloop()
