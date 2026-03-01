CXX = g++
CXXFLAGS =  -std=c++23 
TARGET = practica3_DAA

SOURCES = src/lib/algoritmo_divide_y_venceras.cc src/ordenacion_vectores/escritor_instancia_vector.cc src/ordenacion_vectores/escritor_solucion_vector.cc src/ordenacion_vectores/instancia_vector.cc src/ordenacion_vectores/merge_sort.cc src/ordenacion_vectores/quick_sort.cc src/ordenacion_vectores/solucion_vector.cc src/main.cc src/funciones.cc

OBJECTS = $(SOURCES:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

cleano:
	rm -f $(OBJECTS)

.PHONY: all clean cleano