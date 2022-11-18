import numpy as np

def get_file_name(names, opts, sizes):
	co, total = 1, 15
	for name in names:
		for opt in opts:
			percent = co * 100 // total
			print("\t\033[36mMAKING PREPDATA: {}/100%\033[0m\r".format(percent), end="")
			co += 1
			for size in sizes:
				yield name, opt, size

def get_num(file):
	string = file.readline()
	file.seek(0)
	for string in file:
		yield float(string[:-1])

def main():

	names = ("idx", "exp", "pnt")
	opts = ("Os", "O0", "O1", "O2", "O3")
	sizes=["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "25", "50", "100"]

	for i in range(500, 10500, 500):
		sizes += [str(i)]
	sizes = tuple(sizes)

	print("\t\033[36mMAKING PREPDATA: 0/100%\033[0m\r", end="")

	for name, opt, size in get_file_name(names, opts, sizes):
		input_file = open("../data/" + "{}_{}_{}.txt".format(name, opt, size), 'r')
		output_file = open("../prepdata/" + "{}_{}.txt".format(name, opt), 'a')

		arr = [];
		
		for num in get_num(input_file):
			arr += [num]
		
		arr = np.array(arr)
		arr = np.sort(arr)
		
		average = np.mean(arr)
		max_num, min_num = np.max(arr), np.min(arr)
		lower = np.percentile(arr, 25)
		middle = np.percentile(arr, 50)
		upper = np.percentile(arr, 75)
		
		output_file.write("{}|{}|{}|{}|{}|{}|{}\n"\
			.format(size, average, middle, min_num, max_num, lower, upper))

		input_file.close()
		output_file.close()

	print("\t\033[32mCOMPLETE MAKING PREPDATA \033[0m")

if __name__ == "__main__":
	main()
