from scipy.stats import mannwhitneyu

x = [422.2, 418.7, 425.6, 420.3, 425.8, 423.1, 431.5, 428.2, 438.3, 434.0]
y = [431.3, 423.0, 436.5, 437.1, 428.3, 439.4, 427.7]
average_x = sum(x) / len(x)
average_y = sum(y) / len(y)

s_N_squared = (1 / (len(x) + len(y) - 2)) * (sum((xi - average_x) ** 2 for xi in x) + sum((yi - average_y) ** 2 for yi in y))

print("Исправленная выборочная дисперсия s_N^2:", s_N_squared)
print(average_x)
print(average_y)
print(sorted(x + y))

