# Author: Dylan Turner
# Description: Generic build system for Arduino Project

# Settings

## Build system settings

ARD_FLD :=			arduino-cli
ARD_CONF :=			./arduino-cli.yaml
ARDC :=				arduino-cli
ARD_BOARDS :=		CH55xDuino:mcs51
PKG_INDEX :=		$(ARD_FLD)/data/package_index.json
BOARD_PKG_INDEX :=	$(ARD_FLD)/data/packages/CH55xDuino/

## Project specific settings

PROJNAME :=			PsOhk
BOARD_FQBN :=		CH55xDuino:mcs51:ch552
BUILD_PATH :=		build
LIBS :=				
SRC :=				$(PROJNAME)/$(PROJNAME).ino \
					$(wildcard $(PROJNAME)/*.cpp) \
					$(wildcard $(PROJNAME)/*.hpp)
BOARD_PROPERTIES :=	--build-property build.extra_flags=-DUSER_USB_RAM=148 \
					--build-property upload.xdata_location=148 \
					--build-property upload.maximum_data_size=876
OBJNAME :=			$(PROJNAME).ino.hex

# Targets

## Helper targets

.PHONY: all
all: clean $(PROJNAME).bin

.PHONY: clean
clean:
	rm -rf $(ARD_FLD)
	rm -rf $(BUILD_PATH)
	rm -rf *.bin
	rm -rf *.hex
	rm -rf libraries/

### Set up arduino-cli to be able to find things
$(PKG_INDEX):
	$(ARDC) --config-file $(ARD_CONF) core update-index

### Add boards to arduino-cli
$(BOARD_PKG_INDEX): $(PKG_INDEX)
	$(ARDC) --config-file $(ARD_CONF) core install $(ARD_BOARDS)

### Download and install libraries
define download-lib
$(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip: $(PKG_INDEX)
	$(ARDC) --config-file $(ARD_CONF) lib download "$(subst \_, ,$(1))"
	cp $(ARD_FLD)/staging/libraries/$(subst \,,$(1))*.zip $(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip
endef
define install-lib
libraries/$(subst \,,$(1))/: $(ARD_FLD)/staging/libraries/$(subst \,,$(1)).zip
	$(ARDC) --config-file $(ARD_CONF) lib install "$(subst \_, ,$(1))"
endef
$(foreach lib,$(LIBS), \
	$(eval $(call download-lib,$(lib))); \
	$(eval $(call install-lib,$(lib))) \
)

libraries/USBHIDKeyboard/USBHIDKeyboard.h: $(BOARD_PKG_INDEX)
	mkdir -p libraries
	cp -r $(BOARD_PKG_INDEX)/hardware/mcs51/0.0.21/libraries/Generic_Examples/examples/05.USB/HidKeyboard/src/userUsbHidKeyboard libraries/USBHIDKeyboard

## Main targets

$(BUILD_PATH)/$(PROJNAME).ino.hex: $(SRC) $(BOARD_PKG_INDEX) $(foreach lib,$(LIBS),libraries/$(subst \,,$(lib))/) libraries/USBHIDKeyboard/USBHIDKeyboard.h
	mkdir -p $(BUILD_PATH)
	$(ARDC) compile \
		--config-file $(ARD_CONF) \
		--fqbn $(BOARD_FQBN) \
		--build-path $(BUILD_PATH) \
		--libraries "libraries/" \
		$(BOARD_PROPERTIES) \
		$(PROJNAME)

$(PROJNAME).bin: $(BUILD_PATH)/$(PROJNAME).ino.hex
	objcopy -I ihex -O binary $< $@

.PHONY: upload
upload: $(PROJNAME).bin
	python -m ch55xtool -f $<

