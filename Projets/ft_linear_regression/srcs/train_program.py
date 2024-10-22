import matplotlib.pyplot as plt
import time
import sys

DEBUG_MODE = False
if len(sys.argv) > 1 and (sys.argv[1] == '--debug' or sys.argv[1] == '-d'):
	DEBUG_MODE = True

def print_header():
	print("""\033[1;32m███████████                      ███
░█░░░███░░░█                     ░░░
░   ░███  ░  ████████   ██████   ████  ████████    ██████  ████████
    ░███    ░░███░░███ ░░░░░███ ░░███ ░░███░░███  ███░░███░░███░░███
    ░███     ░███ ░░░   ███████  ░███  ░███ ░███ ░███████  ░███ ░░░
    ░███     ░███      ███░░███  ░███  ░███ ░███ ░███░░░   ░███
    █████    █████    ░░████████ █████ ████ █████░░██████  █████
   ░░░░░    ░░░░░      ░░░░░░░░ ░░░░░ ░░░░ ░░░░░  ░░░░░░  ░░░░░\033[0m""")

def calculate_default_thetas(x, y):
	theta0 = (y[-1] - y[0]) / (x[-1] - x[0]) # a
	theta1 = y[0] - theta0 * x[0] # b
	return [theta0, theta1]

def calculate_mean_square_error(a, b, data):
	mse = 0
	for x, y in data:
		mse += (y - a * x - b) ** 2
	return mse / len(data)

def calculate_gradient(data, theta0, theta1):
	grad_x = 0
	grad_y = 0
	for x, y in data:
		grad_x += -2 * x * (y - theta0 * x - theta1)
		grad_y += -2 * (y - theta0 * x - theta1)
	return [grad_x / len(data), grad_y / len(data)]

def calculate_min_max(data):
	min_x = min(data, key = lambda x: x[0])[0]
	max_x = max(data, key = lambda x: x[0])[0]
	min_y = min(data, key = lambda x: x[1])[1]
	max_y = max(data, key = lambda x: x[1])[1]
	return [min_x, max_x, min_y, max_y]

def normalize_data(data):
	new_data = []
	min_x, max_x, min_y, max_y = calculate_min_max(data)
	for x, y in data:
		x = (x - min_x) / (max_x - min_x)
		y = (y - min_y) / (max_y - min_y)
		new_data.append([x, y])
	return new_data

def denormalize_thetas(theta0, theta1, data):
	min_x, max_x, min_y, max_y = calculate_min_max(data)
	real_theta0 = theta0 * (max_y - min_y) / (max_x - min_x)
	real_theta1 = (max_y - min_y) * theta1 - real_theta0 * min_x + min_y
	return [real_theta0, real_theta1]

def draw_thetas(ax, theta0, theta1, data):
	X = ax.get_xbound()
	Y = [real_theta0 * x + real_theta1 for x in X]
	ax.plot(X, Y)

def draw_points(ax, x, y):
	return ax.plot(x, y, 'bo')

def read_data(filename):
	sorted_data = []
	normalized_data = []
	with open(filename, "r") as f:
		f.readline()
		for line in f:
			x, y = line.split(",")
			sorted_data.append([float(x), float(y)])
		normalized_data = normalize_data(sorted_data)
		f.close()
	return sorted_data, normalized_data

def get_data_to_X_Y(data):
	X = []
	Y = []
	for x, y in data:
		X.append(x)
		Y.append(y)
	return X, Y

def save_data(filename, thetas):
	with open(filename, "w") as f:
		f.write("theta0,theta1\n")
		f.write(str(thetas[0]) + "," + str(thetas[1]))
		f.close()

if __name__ == "__main__":
	print_header()

	delta_rate = 100000
	delta_mse = -1
	last_mse = 0

	print("Chargement et normalisation des données...")
	sorted_data, normalized_data = read_data("./data/data.csv")
	sorted_X, sorted_Y = get_data_to_X_Y(sorted_data)
	X, Y = get_data_to_X_Y(normalized_data)

	print("Calculation des paramètres par défaut (theta0, theta1)...")
	theta0, theta1 = calculate_default_thetas(X, Y)

	print("Regression lineaire via la methode des gradients...")
	total_step = 0
	while abs(delta_mse) > 0.000000001:
		last_mse = calculate_mean_square_error(theta0, theta1, normalized_data)
		gradient = calculate_gradient(normalized_data, theta0, theta1)
		theta0 = theta0 - (1 / delta_rate) * gradient[0]
		theta1 = theta1 - (1 / delta_rate) * gradient[1]
		delta_mse = last_mse - calculate_mean_square_error(theta0, theta1, normalized_data)
		if DEBUG_MODE and total_step % delta_rate == 0:
			print("=> precision:", delta_mse, "| theta0:", round(theta0, 10), "| theta1:", round(theta1, 10))
		total_step += 1

	if (DEBUG_MODE):
		print("=> nombre de pas:", total_step)

	print("Calcul des paramètres réels...")
	real_theta0, real_theta1 = denormalize_thetas(theta0, theta1, sorted_data)
	if (DEBUG_MODE):
		print("=> theta0 = " + str(real_theta0))
		print("=> theta1 = " + str(real_theta1))

	fig, ax = plt.subplots()
	plt.suptitle("ft_linear_regression", fontsize=18)
	plt.title("f(x)=" + str(round(real_theta0, 4)) + "x+" + str(round(real_theta1, 2)), fontsize=10)
	plt.xlabel("Kilometrage")
	plt.ylabel("Prix de vente")

	print("Sauvegarde des paramètres...")
	save_data("./data/thetas.csv", [real_theta0, real_theta1])

	print("Affichage de la fenetre...")
	draw_points(ax, sorted_X, sorted_Y)
	draw_thetas(ax, real_theta0, real_theta1, sorted_data)

	ax.set_ylim(bottom=0)
	ax.set_xlim(left=0)
	plt.show()
