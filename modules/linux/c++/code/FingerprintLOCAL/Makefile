# ===== Compiler =====
CXX      := g++

CXXFLAGS := -Wall -Wextra -Wpedantic -std=c++17 -g -MMD -MP

# ===== Directories =====
OBJ_DIR  := build
TARGET   := LocalFingerPrint

# ===== Automation =====

INC_DIRS := $(shell find . -type d -name "h")

SRCS := $(shell find . -path ./$(OBJ_DIR) -prune -o -name "*.cpp" -print)

# ===== Objects & Dependencies =====
OBJS := $(SRCS:./%.cpp=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# ===== Include flags =====
INCLUDES := $(addprefix -I, $(INC_DIRS)) -I.

# ===== Default =====
all: $(TARGET)

# ===== Link =====
$(TARGET): $(OBJS)
	@echo "🔨 Linkando o executável: $@"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@echo "✅ Success!"

# ===== Compile =====
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "⚙️  Compiling $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ===== Clean =====
clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "🧹 Clear."

# ===== Phony =====
.PHONY: all clean

-include $(DEPS)