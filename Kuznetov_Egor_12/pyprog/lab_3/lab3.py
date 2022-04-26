import tkinter as tk
from tkinter import filedialog as fd
from tkinter import messagebox as mb
import pyperclip as pc
from PIL import Image

c_font = ("Times New Roman", 11)
encoded_msg = ""

def select_file():
    filetypes = (
        ( "Фотография для кодирования", "*.png *.bmp" ),
        ( "Все файлы", "*.*" )
    )

    name = fd.askopenfilename(
            title="Выберите файл для кодировки", 
            initialdir='~',
            filetypes=filetypes)
    select_file_path.delete(0, tk.END)
    select_file_path.insert(0, name)


def encode_file():
    try:
        image = Image.open(select_file_path.get())
        w, h = image.size
        msg = []
        symbol = ''
        count_pixel = 0
        for i in range(w):
            for j in range(h):
                pixel = list(image.getpixel((i, j)))
                for k in range(3):
                    symbol += str(pixel[k]%2)
                count_pixel += 1
                if count_pixel%3 == 0:
                    if int(symbol, 2) == 0:
                        try: 
                            encoded_msg = bytes(msg).decode("UTF-8")
                            out_text.delete(1.0, tk.END)
                            out_text.insert(tk.END, encoded_msg)
                        except:
                            mb.showerror(
                                "Неправильный файл", 
                                "Невозможно расшифровать"
                            )
                        return
                    msg.append(int(symbol[::-1], 2))
                    symbol = ''
        mb.showerror(
            "Неправильный файл",
            "Невозможно расшифровать"
        )
    except:
        mb.showerror(
            "Неправильный файл",
            "Невозможно открыть"
        )
 
def decode_file():
    try:
        image = Image.open(select_file_path.get())
        w, h = image.size
        max_msg_len = w*h//3
        msg = (text_to_code_entry.get() + '\0').encode("UTF-8")
        if len(msg) > max_msg_len:
            mb.showerror(
                "Неправильное сообщение",
                "Сообщение слишком длинное для шифрования"
            )
            return

        byte_arr = []
        for i in msg:
            for j in range(9):
                byte_arr.append(i%2)
                i //= 2 
        printed = 0
        for i in range(w):
            for j in range(h):
                pixel = list(image.getpixel((i, j)))
                for k in range(3):
                    pixel[k] -= pixel[k] % 2 
                    pixel[k] += byte_arr[printed]
                    printed += 1
                image.putpixel((i, j), tuple(pixel))
                if printed >= len(byte_arr):
                    image.save(select_file_path.get())
                    mb.showinfo("", "Сообщение успешно зашифровано") 
                    return
    except:
        mb.showerror(
            "Неправильный файл",
            "Невозможно открыть"
        )

window = tk.Tk()
window.title("Lab 3")
window.minsize(300, 300)
window.resizable(False, False)

select_file_frame = [ tk.Frame(window, width=150, height=50) for i in range(2) ]
for i in enumerate(select_file_frame):
    i[1].pack_propagate(False)
    i[1].place(x=i[0]*150, y=0)

select_file_button = tk.Button(select_file_frame[0], command = select_file, text="Выбор файла: ", font=c_font)
select_file_label = tk.Label(select_file_frame[1], text="Путь к файлу:", font=c_font)
select_file_path = tk.Entry(select_file_frame[1], font=c_font)

text_to_code_frame = [ tk.Frame(window, width=150, height=50) for i in range(2) ]
for i in enumerate(text_to_code_frame):
    i[1].pack_propagate(False)
    i[1].place(x=i[0]*150, y=50)

text_to_code_label = tk.Label(text_to_code_frame[0], text="Введите текст\n для кодирования:", font=c_font)
text_to_code_entry = tk.Entry(text_to_code_frame[1], font=c_font)

control_frame = [ tk.Frame(window, width=150, height=50) for i in range(2) ]
for i in enumerate(control_frame):
    i[1].pack_propagate(False)
    i[1].place(x=i[0]*150, y=100)
decode_button = tk.Button(control_frame[0], text="Закодировать в файл", command=decode_file, font=c_font)
encode_button = tk.Button(control_frame[1], text="Извлечь информацию\n из файла", command=encode_file, font=c_font)

out_frame = tk.Frame(window, width=300, height=150)
out_frame.pack_propagate(False)
out_frame.place(x=0, y=150)
out_text = tk.Text(out_frame, font=c_font)

for i in [ select_file_button, select_file_label, select_file_path, text_to_code_label, text_to_code_entry, encode_button, decode_button, out_text ]: 
    i.pack(fill=tk.BOTH, expand=True)
window.mainloop()
