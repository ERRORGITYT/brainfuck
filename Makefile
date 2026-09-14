.PHONY: all configure build test install clean run

BUILD_DIR ?= build
CMAKE ?= cmake

all: build

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DBUILD_TESTING=ON

build: configure
	$(CMAKE) --build $(BUILD_DIR)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

install: build
	$(CMAKE) --install $(BUILD_DIR)

run: build
	$(BUILD_DIR)/brainfuck $(FILE)

clean:
	$(CMAKE) --build $(BUILD_DIR) --target clean 2>/dev/null || true
	rm -rf $(BUILD_DIR)
