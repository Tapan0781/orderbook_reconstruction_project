CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = reconstruction_candidate
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET) --test

run: $(TARGET)
	./$(TARGET) mbo.csv > output.csv

.PHONY: clean test run