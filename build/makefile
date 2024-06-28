CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I/opt/homebrew/Cellar/curlcpp/3.1/include
SRCDIR := ../src
BUILDDIR := ../build
TARGET := browser
LIBS := -L/opt/homebrew/Cellar/curlcpp/3.1/lib -lcurlcpp -lcurl

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -c -o $@ $<

-include $(DEPS)

clean:
	$(RM) -r $(BUILDDIR) $(TARGET)
