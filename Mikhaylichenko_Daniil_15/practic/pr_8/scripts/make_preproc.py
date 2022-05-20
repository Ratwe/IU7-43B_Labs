import numpy as np

def get_file_name(names, opts, sizes):
	co, total = 1, 10
	for name in names:
		for opt in opts:
			print("MAKING_PREPDATA: {}/{}\r".format(co, total), end="")
			co += 1
			for size in sizes:
				yield name, opt, size

def get_num(file):
	string = file.readline()
	file.seek(0)
	for string in file:
		yield float(string[:-1])

def main():

	names = ("main", "transp_main")
	opts = ("Os", "O0", "O1", "O2", "O3")
	sizes=["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]

	for i in range(15, 105, 5):
		sizes += [str(i)]
	sizes = tuple(sizes)

	print("MAKING_PREPDATA: 0/15\r", end="")

	for name, opt, size in get_file_name(names, opts, sizes):
		input_file = open("../data/" + "{}_{}_{}.txt".format(name, opt, size), 'r')
		output_file = open("../prepdata/" + "{}_{}.txt".format(name, opt), 'a')

		arr = [];
		
		for num in get_num(input_file):
			arr += [num]
		
		arr = np.array(arr)
		
		average = np.mean(arr)
		max_num, min_num = np.max(arr), np.min(arr)
		lower = np.percentile(arr, 25)
		middle = np.percentile(arr, 50)
		upper = np.percentile(arr, 75)
		
		output_file.write("{}|{}|{}|{}|{}|{}|{}\n"\
			.format(size, average, middle, max_num, min_num, lower, upper))

		input_file.close()
		output_file.close()

if __name__ == "__main__":
	main()
