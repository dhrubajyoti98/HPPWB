main_driver: src/main_driver.cpp src/lib/direct_integral_driver.cpp src/lib/lineq_driver.cpp src/lib/mc_integral_driver.cpp src/lib/ode_driver.cpp
	g++ -o main_driver.run src/main_driver.cpp src/lib/direct_integral_driver.cpp src/lib/lineq_driver.cpp src/lib/mc_integral_driver.cpp src/lib/ode_driver.cpp -lm -lgsl -lgslcblas -fopenmp -Ofast -march=native
