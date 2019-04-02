from random import uniform
from math import pow, sqrt
from time import time


def func(arg):
	return pow(arg,1)



start_time = time()

sim_num = 10000
power = 2

x_high = 1;
x_low = 0;

y_high = func(x_high)
y_low = func(x_low)

sucess = 0


for i in range(sim_num):
	x = uniform(x_low, x_high)
	y = uniform(y_low, y_high)

	if(y < func(x)):
		sucess += 1

total_A = (x_high - x_low) * (y_high - y_low)
sucess_Rate = float(sucess) / sim_num

area = total_A * sucess_Rate

end_time = time()

print "Area is", area
print "Computation time is", start_time - end_time